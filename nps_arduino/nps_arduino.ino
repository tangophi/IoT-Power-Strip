/*
** Upload sketch with Arduino 1.0.5-r2.
** Board: Original Mighty 1284p 8MHz
*/

#include <EEPROM.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Adafruit_GFX_AS.h>    // Core graphics library
#include "Adafruit_ILI9341_AS.h" // Hardware-specific library
#include <Adafruit_NeoPixel.h>
#include <SD.h>
#include <UTouch.h>

#define PIN_BUZZER                  13     // Active buzzer
#define PIN_SD_CS                   21
#define PIN_RELAY_POWER              1

// Color definitions
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF

#define TFT_DC             23
#define TFT_CS             4
#define TFT_BACKLIGHT      15
Adafruit_ILI9341_AS tft = Adafruit_ILI9341_AS(TFT_CS, TFT_DC, 22);

UTouch  myTouch( 20, 12, 17, 16, 2);
extern uint8_t SmallFont[];

#define PIN_LATCH              A1
#define PIN_CLOCK              A0
#define PIN_DATA               A3
#define PIN_OUTPUT_ENABLE      A2
#define PIN_LEDS               18     // WS2812B LED data pin

struct relay
{
  int x;
  int y;
  boolean state;
};

relay relays[21]={  0,   0, false,
                   10,  10, false,
                   10,  48, false,
                   10,  86, false, 
                   10, 124, false,
                   10, 162, false,
                   10, 200, false,
                   10, 238, false,
                   10, 276, false,

                   90,  10, false,
                   90,  48, false,
                   90,  86, false,
                   90, 124, false,
                   90, 162, false,

                  170,  10, false,
                  170,  48, false,
                  170,  86, false,
                  170, 124, false,
                  170, 162, false,
                  170, 200, false,

                  170, 276, false};


unsigned long previousMillis = 0, currentMillis = 0, elapsedMillis = 0;
unsigned long idleMillis = 0;

unsigned long sendDataInterval      = 30000;
unsigned long sendDataTime          = 0;

boolean bBacklight = true;
boolean bStarted   = false;

#define LED_COUNT      8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN_LEDS, NEO_GRB + NEO_KHZ800);

#define BUFFPIXEL 20


// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.
void bmpDraw(char *filename, uint8_t x, uint16_t y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  if((x >= tft.width()) || (y >= tft.height())) return;

  //  Serial.println();
  //  Serial.print(F("Loading image '"));
  //  Serial.print(filename);
  //  Serial.println('\'');

  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.print(F("File not found"));
    return;
  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    //    Serial.print(F("File size: ")); 
    //    Serial.println(read32(bmpFile));
    (void)read32(bmpFile);
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    //    Serial.print(F("Image Offset: ")); 
    //    Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    //    Serial.print(F("Header size: ")); 
    //    Serial.println(read32(bmpFile));
    (void)read32(bmpFile);
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      //      Serial.print(F("Bit Depth: ")); 
      //      Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        //        Serial.print(F("Image size: "));
        //        Serial.print(bmpWidth);
        //        Serial.print('x');
        //        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) { // For each scanline...

          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
          pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each pixel...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format, push to display
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.pushColor(tft.color565(r,g,b));
          } // end pixel
        } // end scanline
        //        Serial.print(F("Loaded in "));
        //        Serial.print(millis() - startTime);
        //        Serial.println(" ms");
      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println(F("BMP format not recognized."));
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.
uint16_t read16(File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

void clearDisp()
{
  tft.fillScreen(ILI9341_BLACK);
} 

void drawButton(int r)
{
  if (relays[r].state)
  {
    tft.fillRect(relays[r].x, relays[r].y, 60, 30, ILI9341_GREEN);
  }
  else
  {
    tft.fillRect(relays[r].x, relays[r].y, 60, 30, ILI9341_RED);
  }
  
  tft.drawRect(relays[r].x, relays[r].y, 60, 30, ILI9341_WHITE);  
  tft.setTextColor(ILI9341_WHITE);  
  
  if (r<10)
  {
    tft.drawNumber(r, relays[r].x+25, relays[r].y+4, 4);
  }
  else
  {
    tft.drawNumber(r, relays[r].x+15, relays[r].y+4, 4);
  }
  
  if (r <= 8)
  {
    updateLeds();
  }
}

void updateLeds()
{
  int i=0;
  for (i=1; i<=8; i++)
  {
    if (relays[i].state)
    {
       strip.setPixelColor(i-1, 0, 255, 0);
    }
    else
    {
       strip.setPixelColor(i-1, 255, 0, 0);
    }    
  }
  strip.show();
}
void drawHomeScreen()
{
  int i;
  for (i=1; i<=20; i++)
  {
    drawButton(i);
  }
}

void turnOnLcdBacklight()
{
  idleMillis = 0;
  bBacklight = true;
  digitalWrite(TFT_BACKLIGHT, HIGH);
}

void turnOffLcdBacklight()
{
  bBacklight = false;
  digitalWrite(TFT_BACKLIGHT, LOW);
}

void updateRelays()
{
  byte b[3]={0, 0, 0};
  int i;

  for (i=1; i<=20; i++)
  {
    if (relays[i].state)
    {
      bitSet(b[(int)((i-1)/8)], (i-1)%8);
    }
    else
    {
      bitClear(b[(int)((i-1)/8)], (i-1)%8);
    }
  }

//  Serial.print("byte 0=");
//  Serial.println(b[0]);
//  Serial.print("byte 1=");
//  Serial.println(b[1]);
//  Serial.print("byte 2=");
//  Serial.println(b[2]);
  
  digitalWrite(PIN_LATCH, LOW);
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, b[2]);
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, b[1]);
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, b[0]);
  digitalWrite(PIN_LATCH, HIGH);


//  delay(500);
/*
  for (i=1; i<=20; i++)
  {
    digitalWrite(PIN_LATCH, LOW);
    shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, b[2]);
    shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, b[1]);
    shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, b[0]);
    digitalWrite(PIN_LATCH, HIGH);
    delay(10);
  }
*/
}

void toggleRelay(int r)
{
  if (relays[r].state)
  {
    relays[r].state = false;
    EEPROM.write(r, 0);
  }
  else
  {
    relays[r].state = true;
    EEPROM.write(r, 1);
  }
  updateRelays();
  sendRelaysState();
  drawButton(r);
}

void turnOnRelay(int r)
{
  if (!relays[r].state)
  {
    relays[r].state = true;
    EEPROM.write(r, 1);
    updateRelays();
    sendRelaysState();
    drawButton(r);
  }
}

void turnOffRelay(int r)
{
  if (relays[r].state)
  {
    relays[r].state = false;
    EEPROM.write(r, 0);
    updateRelays();
    sendRelaysState();
    drawButton(r);
  }
}

void resetRelay(int r)
{
  turnOffRelay(r);
  delay(3000);
  turnOnRelay(r);
}

// Read saved data from EEPROM to initialize relay state
void readSavedData()
{
  byte b[3]={0, 0, 0};
  int i;

  for (i=1; i<=20; i++)
  {
    if (EEPROM.read(i) == 0)
    {
      relays[i].state = false;
    }
    else
    {
      relays[i].state = true;
    }
    
    // This is to clear all relays.  So that all relays will not turn on initially.
    // See the next loop.  If relay is to be turned on, we do bitSet and if it is
    // to be turned off, we do bitClear.
    bitClear(b[(int)((i-1)/8)], (i-1)%8);
  }

  digitalWrite(PIN_LATCH, LOW);
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, b[2]);
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, b[1]);
  shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, b[0]);
  digitalWrite(PIN_LATCH, HIGH);
}

void updateRelaysFromSavedData()
{
  byte b[3]={0, 0, 0};
  int i;

  for (i=1; i<=20; i++)
  {
    // This is to clear all relays.  So that all relays will not turn on initially.
    // See the next loop.  If relay is to be turned on, we do bitSet and if it is
    // to be turned off, we do bitClear.
    bitClear(b[(int)((i-1)/8)], (i-1)%8);
  }


  for (i=1; i<=20; i++)
  {
    if (relays[i].state)
    {
      bitSet(b[(int)((i-1)/8)], (i-1)%8);
    }
    else
    {
      bitClear(b[(int)((i-1)/8)], (i-1)%8);
    }

    digitalWrite(PIN_LATCH, LOW);
    shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, b[2]);
    shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, b[1]);
    shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, b[0]);
    digitalWrite(PIN_LATCH, HIGH);

    delay(500);
  }
}    

void sendIntToESP8266(char *type, int value)
{
  StaticJsonBuffer<20> jsonBuffer;
  StaticJsonBuffer<50> jsonBuffer2;
  JsonObject& root = jsonBuffer.createObject();
  JsonObject& root2 = jsonBuffer2.createObject();

  // Send to ESP8266
  root[type] = value;

  root2["board3"] = root;
  root2.printTo(Serial1);
  Serial1.println();
}


void sendRelaysState()
{
  char str[22] = "";
  int i;
  StaticJsonBuffer<200> jsonBuffer;
  StaticJsonBuffer<200> jsonBuffer2;
  JsonObject& root = jsonBuffer.createObject();
  JsonObject& root2 = jsonBuffer2.createObject();
  
  for (i=0; i<=20; i++)
  {
    if (relays[i].state)
    {
      str[i-1] = '1';
    }
    else
    {
      str[i-1] = '0';
    }
  }

  root["StateResponse"] = str;
  root2["board3"] = root;
  root2.printTo(Serial1);
  Serial1.println();
  root2.printTo(Serial);
  Serial.println();
}

int getRelayNumber(int x, int y)
{
  int r=0;
  for (int i=1; i<=20; i++)
  {
    if( ((x - relays[i].x) < 60) && ((y - relays[i].y) < 30))
    {
      r = i;
      break;
    }
  }  
  return r;
}
                   
// Draw a red frame while a button is touched
void waitForIt(int x, int y, int w, int h)  
{
  tft.drawRect(x, y, w, h, ILI9341_BLUE);
  tft.drawRect(x+1, y+1, w-1, h-1, ILI9341_BLUE);
  tft.drawRect(x+2, y+2, w-2, h-2, ILI9341_BLUE);
  buzz(2500, 100);
  while (myTouch.dataAvailable())
  {
    myTouch.read();
    if (millis() - currentMillis > 500)
    {
      buzz(5000, 200);
      break;
    }
  }
}

void buzz(long frequency, long length) {
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
  for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(PIN_BUZZER,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(PIN_BUZZER, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait againf or the calculated delay value
  }
}

void setup()
{
  Serial.begin(57600);
  Serial1.begin(57600);

  pinMode(TFT_BACKLIGHT,       OUTPUT);
  pinMode(PIN_LATCH,           OUTPUT);
  pinMode(PIN_CLOCK,           OUTPUT);
  pinMode(PIN_DATA,            OUTPUT);
  pinMode(PIN_OUTPUT_ENABLE,   OUTPUT);
  pinMode(PIN_BUZZER,          OUTPUT);
  pinMode(PIN_RELAY_POWER,     OUTPUT);

  // Enable output of HC595
  digitalWrite(PIN_OUTPUT_ENABLE, HIGH);

  readSavedData();
  delay(1000);

  // Enable output of HC595
  digitalWrite(PIN_OUTPUT_ENABLE, LOW);

  // Enable power to relays
  digitalWrite(PIN_RELAY_POWER, HIGH);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  updateRelaysFromSavedData();  

  tft.init();
  digitalWrite(TFT_BACKLIGHT, HIGH);
  clearDisp();    

  myTouch.InitTouch(PORTRAIT);

  if (!SD.begin(PIN_SD_CS)) {
    Serial.println("failed!");
  }
  Serial.println("OK!");

  bmpDraw("arduino.bmp", 64, 80);
  bmpDraw("esp8266.bmp", 65, 166);

  tft.setTextColor(WHITE);  
  tft.setTextSize(1);
  tft.setCursor(70,245);
  tft.println("Initializing...");
  Serial.println("Initializing...");

  buzz(5000, 200);

  bmpDraw("backgrnd.bmp", 0, 0);

  drawHomeScreen();
}

void loop()
{
  int x=0,y=0,r=0,pos=0,opening_brace=0;
  unsigned long keyPressTime = 0;
  char c, str[64]="";

  currentMillis = millis();
  elapsedMillis = currentMillis - previousMillis;
  previousMillis = currentMillis;

  idleMillis      += elapsedMillis;
  sendDataTime    += elapsedMillis;
  
  if (myTouch.dataAvailable())
  {
    myTouch.read();
    x=myTouch.getX();
    y=myTouch.getY();
    
    Serial.print("x=");
    Serial.println(x);
    Serial.print("y=");
    Serial.println(y);

    if (!bBacklight)
    {
      turnOnLcdBacklight();
    }
    else
    {
      r = getRelayNumber(x, y);
      if ( r > 0)
      {
        waitForIt(relays[r].x, relays[r].y, 60, 30);
        keyPressTime = millis() - currentMillis;

        // If fan is pressed for more than half a second only, toggle the
        // relay.
        if (keyPressTime > 500)
        {
          toggleRelay(r);
        }
        drawButton(r);
      }
    }
  }

  if(Serial1.available())
  {
    while (Serial1.available())
    {
      c = (int) Serial1.read();

      if (c == 123)
      {
        delay(5);
        break;
      }
    }

    if (c == 123) // {
    {
      str[pos++] = (char)c;
      opening_brace++;

      while(Serial1.available())
      {        
        c = (int) Serial1.read();
        if ((c >= 32) && (c <= 126))
        {
          str[pos++] = (char)c;

          // In case we get more starting braces than closing braces, then we
          // may overflow the str buffer.  As it is, since we dont expect long
          // input, cap the limit to 100.
          if (pos > 100)
          {
            break;
          }
        }

        if (c == 125)  // }
        {
          opening_brace--;
        }

        if (opening_brace == 0 )
        {
          str[pos++] = 0;

          Serial.print("Received from ESP8266: ");
          Serial.println(str);
 
          StaticJsonBuffer<200> jsonBuffer;
          JsonObject& root = jsonBuffer.parseObject(str);

          if (root.success())
          {
            turnOnLcdBacklight();
            if(strstr(str,"OnCommand"))
            {
              r = root["OnCommand"];
              if (r>0)
              {
                turnOnRelay(r);
              }
            }
            else if(strstr(str,"OffCommand"))
            {
              r = root["OffCommand"];
              if (r>0)
              {
                turnOffRelay(r);
              }
            }
            else if(strstr(str,"ResetCommand"))
            {
              r = root["ResetCommand"];
              if (r>0)
              {
                resetRelay(r);
              }
            }
            else if(strstr(str,"StateCommand"))
            {
              sendRelaysState();
            }
          }
          break;
        }
      }
    }
  }    

  if (idleMillis > 60000) // 5 mins
  {
    turnOffLcdBacklight();
  }

  if (sendDataTime > sendDataInterval)
  {
    sendDataTime = 0;

    if(!bStarted)
    {
      bStarted = true;
      sendIntToESP8266("ArduinoStarting", 1);
    }
    
    sendRelaysState();
  }  
  
  delay(1);
}
