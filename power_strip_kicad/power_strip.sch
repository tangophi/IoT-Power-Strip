EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:mylib
LIBS:power_strip-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "IoT Power Strip"
Date "10 may 2016"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATMEGA1284P-P IC1
U 1 1 557C87A3
P 3000 4300
F 0 "IC1" H 2150 6180 40  0000 L BNN
F 1 "ATMEGA1284P-P" H 3400 2350 40  0000 L BNN
F 2 "DIL40" H 3000 4300 30  0000 C CIN
F 3 "" H 3000 4300 60  0000 C CNN
	1    3000 4300
	1    0    0    -1  
$EndComp
$Comp
L CRYSTAL X1
U 1 1 557C87EC
P 1700 3200
F 0 "X1" H 1700 3350 60  0000 C CNN
F 1 "16 MHz" H 1700 3050 60  0000 C CNN
F 2 "~" H 1700 3200 60  0000 C CNN
F 3 "~" H 1700 3200 60  0000 C CNN
	1    1700 3200
	0    -1   -1   0   
$EndComp
$Comp
L C C1
U 1 1 557C87FF
P 1200 2900
F 0 "C1" H 1200 3000 40  0000 L CNN
F 1 "22pF" H 1206 2815 40  0000 L CNN
F 2 "~" H 1238 2750 30  0000 C CNN
F 3 "~" H 1200 2900 60  0000 C CNN
	1    1200 2900
	0    -1   -1   0   
$EndComp
$Comp
L C C2
U 1 1 557C880E
P 1200 3500
F 0 "C2" H 1200 3600 40  0000 L CNN
F 1 "22pF" H 1206 3415 40  0000 L CNN
F 2 "~" H 1238 3350 30  0000 C CNN
F 3 "~" H 1200 3500 60  0000 C CNN
	1    1200 3500
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR1
U 1 1 557C8828
P 600 3250
F 0 "#PWR1" H 600 3250 30  0001 C CNN
F 1 "GND" H 600 3180 30  0001 C CNN
F 2 "" H 600 3250 60  0000 C CNN
F 3 "" H 600 3250 60  0000 C CNN
	1    600  3250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 557C884B
P 2900 6450
F 0 "#PWR8" H 2900 6450 30  0001 C CNN
F 1 "GND" H 2900 6380 30  0001 C CNN
F 2 "" H 2900 6450 60  0000 C CNN
F 3 "" H 2900 6450 60  0000 C CNN
	1    2900 6450
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR7
U 1 1 557C8876
P 2900 2000
F 0 "#PWR7" H 2900 2090 20  0001 C CNN
F 1 "+5V" H 2900 2090 30  0000 C CNN
F 2 "" H 2900 2000 60  0000 C CNN
F 3 "" H 2900 2000 60  0000 C CNN
	1    2900 2000
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 557C88AB
P 3300 2100
F 0 "C5" H 3300 2200 40  0000 L CNN
F 1 "0.1uF" H 3306 2015 40  0000 L CNN
F 2 "~" H 3338 1950 30  0000 C CNN
F 3 "~" H 3300 2100 60  0000 C CNN
	1    3300 2100
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR9
U 1 1 557C88BA
P 3700 2200
F 0 "#PWR9" H 3700 2200 30  0001 C CNN
F 1 "GND" H 3700 2130 30  0001 C CNN
F 2 "" H 3700 2200 60  0000 C CNN
F 3 "" H 3700 2200 60  0000 C CNN
	1    3700 2200
	1    0    0    -1  
$EndComp
$Comp
L ESP-01 U3
U 1 1 557C89F7
P 9200 950
F 0 "U3" H 9200 650 60  0000 C CNN
F 1 "ESP-01" H 9150 1350 60  0000 C CNN
F 2 "~" H 9200 950 60  0000 C CNN
F 3 "~" H 9200 950 60  0000 C CNN
	1    9200 950 
	1    0    0    -1  
$EndComp
$Comp
L NCP1117ST285T3G U2
U 1 1 557CDB86
P 2100 1050
F 0 "U2" H 2250 854 40  0000 C CNN
F 1 "LM1117" H 2100 1250 40  0000 C CNN
F 2 "~" H 2100 1050 60  0000 C CNN
F 3 "~" H 2100 1050 60  0000 C CNN
	1    2100 1050
	1    0    0    -1  
$EndComp
$Comp
L CP1 C3
U 1 1 557CDC27
P 1500 1200
F 0 "C3" H 1550 1300 50  0000 L CNN
F 1 "10uF" H 1550 1100 50  0000 L CNN
F 2 "~" H 1500 1200 60  0000 C CNN
F 3 "~" H 1500 1200 60  0000 C CNN
	1    1500 1200
	1    0    0    -1  
$EndComp
$Comp
L CP1 C4
U 1 1 557CDC36
P 2700 1200
F 0 "C4" H 2750 1300 50  0000 L CNN
F 1 "10uF" H 2750 1100 50  0000 L CNN
F 2 "~" H 2700 1200 60  0000 C CNN
F 3 "~" H 2700 1200 60  0000 C CNN
	1    2700 1200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 557CDD0F
P 2100 1600
F 0 "#PWR5" H 2100 1600 30  0001 C CNN
F 1 "GND" H 2100 1530 30  0001 C CNN
F 2 "" H 2100 1600 60  0000 C CNN
F 3 "" H 2100 1600 60  0000 C CNN
	1    2100 1600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR4
U 1 1 557CDD6C
P 1500 900
F 0 "#PWR4" H 1500 990 20  0001 C CNN
F 1 "+5V" H 1500 990 30  0000 C CNN
F 2 "" H 1500 900 60  0000 C CNN
F 3 "" H 1500 900 60  0000 C CNN
	1    1500 900 
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR6
U 1 1 557CDDBB
P 2700 900
F 0 "#PWR6" H 2700 860 30  0001 C CNN
F 1 "+3.3V" H 2700 1010 30  0000 C CNN
F 2 "" H 2700 900 60  0000 C CNN
F 3 "" H 2700 900 60  0000 C CNN
	1    2700 900 
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR19
U 1 1 557CDFCD
P 8200 600
F 0 "#PWR19" H 8200 560 30  0001 C CNN
F 1 "+3.3V" H 8200 710 30  0000 C CNN
F 2 "" H 8200 600 60  0000 C CNN
F 3 "" H 8200 600 60  0000 C CNN
	1    8200 600 
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR10
U 1 1 557CE3B3
P 5550 5200
F 0 "#PWR10" H 5550 5290 20  0001 C CNN
F 1 "+5V" H 5550 5290 30  0000 C CNN
F 2 "" H 5550 5200 60  0000 C CNN
F 3 "" H 5550 5200 60  0000 C CNN
	1    5550 5200
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR11
U 1 1 557CE448
P 5700 5500
F 0 "#PWR11" H 5700 5500 30  0001 C CNN
F 1 "GND" H 5700 5430 30  0001 C CNN
F 2 "" H 5700 5500 60  0000 C CNN
F 3 "" H 5700 5500 60  0000 C CNN
	1    5700 5500
	1    0    0    -1  
$EndComp
$Comp
L FTDI P7
U 1 1 557CE5DD
P 7850 5150
F 0 "P7" V 7800 5150 60  0000 C CNN
F 1 "FTDI" V 7900 5150 60  0000 C CNN
F 2 "" H 7850 5150 60  0000 C CNN
F 3 "" H 7850 5150 60  0000 C CNN
	1    7850 5150
	1    0    0    -1  
$EndComp
$Comp
L ARDUINO_SPI P5
U 1 1 557CE66E
P 7800 4000
F 0 "P5" V 7750 4000 50  0000 C CNN
F 1 "ARDUINO_SPI" V 7850 4000 50  0000 C CNN
F 2 "" H 7800 4000 60  0000 C CNN
F 3 "" H 7800 4000 60  0000 C CNN
	1    7800 4000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR15
U 1 1 557CE693
P 7150 3800
F 0 "#PWR15" H 7150 3800 30  0001 C CNN
F 1 "GND" H 7150 3730 30  0001 C CNN
F 2 "" H 7150 3800 60  0000 C CNN
F 3 "" H 7150 3800 60  0000 C CNN
	1    7150 3800
	0    1    1    0   
$EndComp
$Comp
L C C6
U 1 1 557CE713
P 6800 4600
F 0 "C6" H 6800 4700 40  0000 L CNN
F 1 "0.1uF" H 6806 4515 40  0000 L CNN
F 2 "~" H 6838 4450 30  0000 C CNN
F 3 "~" H 6800 4600 60  0000 C CNN
	1    6800 4600
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 557CE722
P 7250 4400
F 0 "R1" V 7330 4400 40  0000 C CNN
F 1 "10K" V 7257 4401 40  0000 C CNN
F 2 "~" V 7180 4400 30  0000 C CNN
F 3 "~" H 7250 4400 30  0000 C CNN
	1    7250 4400
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR18
U 1 1 557CE821
P 7700 4550
F 0 "#PWR18" H 7700 4640 20  0001 C CNN
F 1 "+5V" H 7700 4640 30  0000 C CNN
F 2 "" H 7700 4550 60  0000 C CNN
F 3 "" H 7700 4550 60  0000 C CNN
	1    7700 4550
	-1   0    0    1   
$EndComp
$Comp
L BUZZER U1
U 1 1 557D2BBB
P 1300 6350
F 0 "U1" H 1300 6700 60  0000 C CNN
F 1 "BUZZER" H 1300 6350 60  0000 C CNN
F 2 "" H 750 6400 60  0000 C CNN
F 3 "" H 750 6400 60  0000 C CNN
	1    1300 6350
	1    0    0    -1  
$EndComp
$Comp
L PN2222A Q1
U 1 1 557D2BCA
P 1200 7000
F 0 "Q1" H 1200 6852 40  0000 R CNN
F 1 "PN2222A" H 1200 7150 40  0000 R CNN
F 2 "TO92" H 1100 7102 29  0000 C CNN
F 3 "~" H 1200 7000 60  0000 C CNN
	1    1200 7000
	1    0    0    -1  
$EndComp
$Comp
L DIODE D1
U 1 1 557D2BED
P 1800 6400
F 0 "D1" H 1800 6500 40  0000 C CNN
F 1 "DIODE" H 1800 6300 40  0000 C CNN
F 2 "~" H 1800 6400 60  0000 C CNN
F 3 "~" H 1800 6400 60  0000 C CNN
	1    1800 6400
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR3
U 1 1 557D2C10
P 1300 7400
F 0 "#PWR3" H 1300 7400 30  0001 C CNN
F 1 "GND" H 1300 7330 30  0001 C CNN
F 2 "" H 1300 7400 60  0000 C CNN
F 3 "" H 1300 7400 60  0000 C CNN
	1    1300 7400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR2
U 1 1 557D2F4F
P 1300 5800
F 0 "#PWR2" H 1300 5890 20  0001 C CNN
F 1 "+5V" H 1300 5890 30  0000 C CNN
F 2 "" H 1300 5800 60  0000 C CNN
F 3 "" H 1300 5800 60  0000 C CNN
	1    1300 5800
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 557D300E
P 800 7250
F 0 "R2" V 880 7250 40  0000 C CNN
F 1 "1K" V 807 7251 40  0000 C CNN
F 2 "~" V 730 7250 30  0000 C CNN
F 3 "~" H 800 7250 30  0000 C CNN
	1    800  7250
	1    0    0    -1  
$EndComp
$Comp
L 2.4_INCH_TOUCH_LCD P4
U 1 1 557D428C
P 5650 750
F 0 "P4" V 5620 750 60  0000 C CNN
F 1 "2.4_INCH_TOUCH_LCD" V 5730 750 60  0000 C CNN
F 2 "" H 5650 750 60  0000 C CNN
F 3 "" H 5650 750 60  0000 C CNN
	1    5650 750 
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR12
U 1 1 55A0CA24
P 6200 1250
F 0 "#PWR12" H 6200 1250 30  0001 C CNN
F 1 "GND" H 6200 1180 30  0001 C CNN
F 2 "" H 6200 1250 60  0000 C CNN
F 3 "" H 6200 1250 60  0000 C CNN
	1    6200 1250
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U5
U 1 1 573206D2
P 9200 3050
F 0 "U5" H 9350 3650 70  0000 C CNN
F 1 "74HC595" H 9200 2450 70  0000 C CNN
F 2 "~" H 9200 3050 60  0000 C CNN
F 3 "~" H 9200 3050 60  0000 C CNN
	1    9200 3050
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U6
U 1 1 573206EB
P 9200 4450
F 0 "U6" H 9350 5050 70  0000 C CNN
F 1 "74HC595" H 9200 3850 70  0000 C CNN
F 2 "~" H 9200 4450 60  0000 C CNN
F 3 "~" H 9200 4450 60  0000 C CNN
	1    9200 4450
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U7
U 1 1 573206FA
P 9200 5850
F 0 "U7" H 9350 6450 70  0000 C CNN
F 1 "74HC595" H 9200 5250 70  0000 C CNN
F 2 "~" H 9200 5850 60  0000 C CNN
F 3 "~" H 9200 5850 60  0000 C CNN
	1    9200 5850
	1    0    0    -1  
$EndComp
$Comp
L CONN_8 P1
U 1 1 5732274C
P 10650 2950
F 0 "P1" V 10600 2950 60  0000 C CNN
F 1 "CONN_8" V 10700 2950 60  0000 C CNN
F 2 "~" H 10650 2950 60  0000 C CNN
F 3 "~" H 10650 2950 60  0000 C CNN
	1    10650 2950
	1    0    0    -1  
$EndComp
$Comp
L CONN_8 P2
U 1 1 5732275B
P 10650 4350
F 0 "P2" V 10600 4350 60  0000 C CNN
F 1 "CONN_8" V 10700 4350 60  0000 C CNN
F 2 "~" H 10650 4350 60  0000 C CNN
F 3 "~" H 10650 4350 60  0000 C CNN
	1    10650 4350
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P3
U 1 1 5732276A
P 10650 5550
F 0 "P3" V 10600 5550 50  0000 C CNN
F 1 "CONN_4" V 10700 5550 50  0000 C CNN
F 2 "~" H 10650 5550 60  0000 C CNN
F 3 "~" H 10650 5550 60  0000 C CNN
	1    10650 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 2900 2000 2900
Wire Wire Line
	2000 2900 2000 3000
Wire Wire Line
	1400 3500 2000 3500
Wire Wire Line
	2000 3500 2000 3400
Connection ~ 1700 2900
Connection ~ 1700 3500
Wire Wire Line
	600  3250 600  3200
Wire Wire Line
	600  3200 900  3200
Wire Wire Line
	900  2900 900  3500
Wire Wire Line
	900  3500 1000 3500
Wire Wire Line
	900  2900 1000 2900
Connection ~ 900  3200
Wire Wire Line
	2800 6300 3000 6300
Wire Wire Line
	2900 6300 2900 6450
Connection ~ 2900 6300
Wire Wire Line
	2800 2300 2800 2100
Wire Wire Line
	2800 2100 3100 2100
Wire Wire Line
	2900 2100 2900 2000
Wire Wire Line
	3000 2100 3000 2300
Connection ~ 2900 2100
Connection ~ 3000 2100
Wire Wire Line
	3500 2100 3700 2100
Wire Wire Line
	3700 2100 3700 2200
Wire Wire Line
	4000 4200 7400 4200
Wire Wire Line
	4000 4100 7400 4100
Wire Wire Line
	4000 4000 7400 4000
Connection ~ 1500 1000
Wire Wire Line
	2500 1000 2700 1000
Wire Wire Line
	2100 1300 2100 1600
Connection ~ 2100 1400
Wire Wire Line
	1500 1000 1500 900 
Wire Wire Line
	2700 1000 2700 900 
Wire Wire Line
	8200 600  8200 1050
Wire Wire Line
	8200 1050 8600 1050
Wire Wire Line
	8600 850  8200 850 
Connection ~ 8200 850 
Wire Wire Line
	5550 5200 7500 5200
Wire Wire Line
	5700 5300 5700 5500
Wire Wire Line
	5700 5400 7500 5400
Wire Wire Line
	5700 5300 7500 5300
Connection ~ 5700 5400
Wire Wire Line
	7400 3800 7150 3800
Wire Wire Line
	6800 4800 6800 4900
Wire Wire Line
	6800 4400 7000 4400
Wire Wire Line
	7500 4400 7700 4400
Wire Wire Line
	7700 4400 7700 4550
Wire Wire Line
	2000 2600 2000 1800
Wire Wire Line
	1300 7200 1300 7400
Wire Wire Line
	1300 6500 1300 6800
Wire Wire Line
	1300 6700 1800 6700
Wire Wire Line
	1800 6700 1800 6600
Connection ~ 1300 6700
Wire Wire Line
	1300 6200 1800 6200
Wire Wire Line
	1300 6200 1300 5800
Wire Wire Line
	800  7000 1000 7000
Wire Wire Line
	800  7500 800  7600
Wire Wire Line
	800  7600 3400 7600
Wire Wire Line
	3400 7600 3400 6500
Wire Wire Line
	3400 6500 4300 6500
Wire Wire Line
	4300 6500 4300 5800
Wire Wire Line
	4300 5800 4000 5800
Wire Wire Line
	2000 1800 3300 1800
Wire Wire Line
	3300 1800 3300 500 
Wire Wire Line
	6800 3900 7400 3900
Connection ~ 6800 3900
Wire Wire Line
	6800 4900 7500 4900
Wire Wire Line
	6300 1100 8200 1100
Wire Wire Line
	8200 1100 8200 850 
Wire Wire Line
	6200 1100 6200 1250
Wire Wire Line
	5000 1100 5000 3700
Wire Wire Line
	5000 3700 4000 3700
Wire Wire Line
	5100 1100 5100 4400
Wire Wire Line
	5100 4400 4000 4400
Wire Wire Line
	5200 1100 5200 4500
Wire Wire Line
	5200 4500 4000 4500
Wire Wire Line
	4000 5700 4700 5700
Wire Wire Line
	4700 5700 4700 5000
Wire Wire Line
	4700 5000 5300 5000
Wire Wire Line
	5300 5000 5300 1100
Wire Wire Line
	5400 1100 5400 4800
Wire Wire Line
	5400 4800 4000 4800
Wire Wire Line
	5500 1100 5500 4100
Connection ~ 5500 4100
Wire Wire Line
	4000 6000 5600 6000
Wire Wire Line
	5600 6000 5600 1100
Wire Wire Line
	5800 1100 5800 4000
Connection ~ 5800 4000
Wire Wire Line
	4000 5100 5900 5100
Wire Wire Line
	5900 5100 5900 1100
Wire Wire Line
	4000 5000 4500 5000
Wire Wire Line
	4500 5000 4500 4900
Wire Wire Line
	4500 4900 6000 4900
Wire Wire Line
	6000 4900 6000 1100
Wire Wire Line
	4000 3900 6100 3900
Wire Wire Line
	6100 3900 6100 1100
Wire Wire Line
	6800 500  6800 4400
Connection ~ 6800 500 
Wire Wire Line
	3300 500  6800 500 
Wire Wire Line
	4000 5300 5400 5300
Wire Wire Line
	5400 5300 5400 5000
Wire Wire Line
	5400 5000 7500 5000
Wire Wire Line
	4000 5400 4800 5400
Wire Wire Line
	4800 5400 4800 5600
Wire Wire Line
	4800 5600 7300 5600
Wire Wire Line
	7300 5600 7300 5100
Wire Wire Line
	7300 5100 7500 5100
Connection ~ 5700 4200
Wire Wire Line
	5700 1100 5700 4200
Wire Wire Line
	4000 2600 7500 2600
Wire Wire Line
	7500 2600 7500 2800
Wire Wire Line
	7500 2800 8500 2800
Wire Wire Line
	4000 2700 7400 2700
Wire Wire Line
	7400 2700 7400 3100
Wire Wire Line
	7400 3100 8500 3100
Wire Wire Line
	4000 2800 7300 2800
Wire Wire Line
	7300 2800 7300 3200
Wire Wire Line
	7300 3200 8500 3200
Wire Wire Line
	4000 2900 7200 2900
Wire Wire Line
	7200 2900 7200 2500
Wire Wire Line
	7200 2500 7600 2500
Wire Wire Line
	7600 2500 7600 2600
Wire Wire Line
	7600 2600 8500 2600
Wire Wire Line
	9900 3500 9900 3800
Wire Wire Line
	9900 3800 8400 3800
Wire Wire Line
	8400 3800 8400 4000
Wire Wire Line
	8400 4000 8500 4000
Wire Wire Line
	9900 4900 9900 5200
Wire Wire Line
	9900 5200 8400 5200
Wire Wire Line
	8400 5200 8400 5400
Wire Wire Line
	8400 5400 8500 5400
Wire Wire Line
	8300 2800 8300 5600
Wire Wire Line
	8300 5600 8500 5600
Connection ~ 8300 2800
Wire Wire Line
	8200 3100 8200 5900
Wire Wire Line
	8200 5900 8500 5900
Connection ~ 8200 3100
Wire Wire Line
	8100 3200 8100 6000
Wire Wire Line
	8100 6000 8500 6000
Connection ~ 8100 3200
Wire Wire Line
	8100 4600 8500 4600
Connection ~ 8100 4600
Wire Wire Line
	8200 4500 8500 4500
Connection ~ 8200 4500
Wire Wire Line
	8200 4200 8500 4200
Connection ~ 8200 4200
Wire Wire Line
	4000 5500 4200 5500
Wire Wire Line
	4200 5500 4200 1400
Wire Wire Line
	4200 1400 8400 1400
Wire Wire Line
	8400 1400 8400 750 
Wire Wire Line
	8400 750  8600 750 
Wire Wire Line
	4000 5600 4300 5600
Wire Wire Line
	4300 5600 4300 1500
Wire Wire Line
	4300 1500 9900 1500
Wire Wire Line
	9900 1500 9900 1050
Wire Wire Line
	9900 1050 9800 1050
Wire Wire Line
	9900 2600 10300 2600
Wire Wire Line
	9900 2700 10300 2700
Wire Wire Line
	9900 2800 10300 2800
Wire Wire Line
	9900 2900 10300 2900
Wire Wire Line
	9900 3000 10300 3000
Wire Wire Line
	9900 3100 10300 3100
Wire Wire Line
	9900 3200 10300 3200
Wire Wire Line
	9900 3300 10300 3300
Wire Wire Line
	9900 4000 10300 4000
Wire Wire Line
	9900 4100 10300 4100
Wire Wire Line
	9900 4200 10300 4200
Wire Wire Line
	9900 4300 10300 4300
Wire Wire Line
	9900 4400 10300 4400
Wire Wire Line
	9900 4500 10300 4500
Wire Wire Line
	9900 4600 10300 4600
Wire Wire Line
	9900 4700 10300 4700
Wire Wire Line
	9900 5400 10300 5400
Wire Wire Line
	9900 5500 10300 5500
Wire Wire Line
	9900 5600 10300 5600
Wire Wire Line
	9900 5700 10300 5700
$Comp
L 220V_AC_TO_5V_2A_DC_POWER_SUPPLY U4
U 1 1 573236D1
P 5650 6900
F 0 "U4" H 5600 7550 60  0000 C CNN
F 1 "220V_AC_TO_5V_2A_DC_POWER_SUPPLY" H 5500 6900 60  0000 C CNN
F 2 "~" H 5700 6800 60  0000 C CNN
F 3 "~" H 5700 6800 60  0000 C CNN
	1    5650 6900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR13
U 1 1 573236EA
P 6700 6650
F 0 "#PWR13" H 6700 6740 20  0001 C CNN
F 1 "+5V" H 6700 6740 30  0000 C CNN
F 2 "" H 6700 6650 60  0000 C CNN
F 3 "" H 6700 6650 60  0000 C CNN
	1    6700 6650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR14
U 1 1 573236F9
P 6700 7150
F 0 "#PWR14" H 6700 7150 30  0001 C CNN
F 1 "GND" H 6700 7080 30  0001 C CNN
F 2 "" H 6700 7150 60  0000 C CNN
F 3 "" H 6700 7150 60  0000 C CNN
	1    6700 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 6700 6700 6700
Wire Wire Line
	6700 6700 6700 6650
Wire Wire Line
	6450 7100 6700 7100
Wire Wire Line
	6700 7100 6700 7150
Wire Wire Line
	1500 1000 1700 1000
Wire Wire Line
	1500 1400 2700 1400
$Comp
L CONN_3 K1
U 1 1 57323C04
P 7850 5900
F 0 "K1" V 7800 5900 50  0000 C CNN
F 1 "CONN_3" V 7900 5900 40  0000 C CNN
F 2 "~" H 7850 5900 60  0000 C CNN
F 3 "~" H 7850 5900 60  0000 C CNN
	1    7850 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 5900 7500 5900
$Comp
L +5V #PWR16
U 1 1 57323CDD
P 7400 5650
F 0 "#PWR16" H 7400 5740 20  0001 C CNN
F 1 "+5V" H 7400 5740 30  0000 C CNN
F 2 "" H 7400 5650 60  0000 C CNN
F 3 "" H 7400 5650 60  0000 C CNN
	1    7400 5650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR17
U 1 1 57323CFB
P 7400 6100
F 0 "#PWR17" H 7400 6100 30  0001 C CNN
F 1 "GND" H 7400 6030 30  0001 C CNN
F 2 "" H 7400 6100 60  0000 C CNN
F 3 "" H 7400 6100 60  0000 C CNN
	1    7400 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 5650 7400 5800
Wire Wire Line
	7400 5800 7500 5800
Wire Wire Line
	7500 6000 7400 6000
Wire Wire Line
	7400 6000 7400 6100
$EndSCHEMATC
