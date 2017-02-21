/* main.c -- MQTT client example
*
* Copyright (c) 2014-2015, Tuan PM <tuanpm at live dot com>
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
* * Neither the name of Redis nor the names of its contributors may be used
* to endorse or promote products derived from this software without
* specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/
#include <stdio.h>
#include "ets_sys.h"
#include "driver/uart.h"
#include "osapi.h"
#include "mqtt.h"
#include "wifi.h"
#include "config.h"
#include "debug.h"
#include "gpio.h"
#include "user_interface.h"
#include "mem.h"
#include "user_json.h"

LOCAL int intOnCommand              = 0;
LOCAL int intOffCommand             = 0;
LOCAL int intResetCommand           = 0;
LOCAL int intStateCommand           = 0;
LOCAL char strStateResponse[22]     = "";

LOCAL int intStartingState         = 0;

MQTT_Client mqttClient;

#define user_procTaskPrio        1
#define user_procTaskQueueLen    1
os_event_t    user_procTaskQueue[user_procTaskQueueLen];
static void loop(os_event_t *events);

/******************************************************************************
 * FunctionName : data_get
 * Description  : Process the data received through MQTT and send it to Arduino
 * Parameters   : js_ctx -- A pointer to a JSON set up
 * Returns      : result
*******************************************************************************/
LOCAL int ICACHE_FLASH_ATTR
data_get(struct jsontree_context *js_ctx)
{
    const char *path = jsontree_path_name(js_ctx, js_ctx->depth - 1);

    if (os_strncmp(path, "OnCommand", 9) == 0)
    {
        jsontree_write_int(js_ctx, intOnCommand);
    }
    else if (os_strncmp(path, "OffCommand", 10) == 0)
    {
        jsontree_write_int(js_ctx, intOffCommand);
    }
    else if (os_strncmp(path, "ResetCommand", 12) == 0)
    {
        jsontree_write_int(js_ctx, intResetCommand);
    }
    else if (os_strncmp(path, "StateCommand", 12) == 0)
    {
        jsontree_write_int(js_ctx, intStateCommand);
    }

    return 0;
}


/******************************************************************************
 * FunctionName : data_set
 * Description  : Receive data from Arduino and store it in global variables
 * Parameters   : js_ctx -- A pointer to a JSON set up
 *                parser -- A pointer to a JSON parser state
 * Returns      : result
*******************************************************************************/
LOCAL int ICACHE_FLASH_ATTR
data_set(struct jsontree_context *js_ctx, struct jsonparse_state *parser)
{
    int type;
	char str_buf[64];

	while ((type = jsonparse_next(parser)) != 0) {
	    if (type == JSON_TYPE_PAIR_NAME) {

	        if (jsonparse_strcmp_value(parser, "StateResponse") == 0) {
	            jsonparse_next(parser);
	            jsonparse_next(parser);
	            jsonparse_copy_value(parser, strStateResponse, 21);
	//          INFO("StateResponse:%s:\n", strStateResponse);
            	MQTT_Publish(&mqttClient, "/board3/StateResponse", strStateResponse, os_strlen(strStateResponse), 2, 0);

	        }
            else if (jsonparse_strcmp_value(parser, "ArduinoStarting") == 0) {
                jsonparse_next(parser);
                jsonparse_next(parser);
                intStartingState = jsonparse_get_value_as_int(parser);
                os_bzero(str_buf, sizeof(str_buf));
                os_sprintf(str_buf,"1");
                MQTT_Publish(&mqttClient, "/board3/ArduinoStarting", str_buf, os_strlen(str_buf), 2, 0);
            }
	    }
	}
}

LOCAL struct jsontree_callback data_callback =
    JSONTREE_CALLBACK(data_get, data_set);

JSONTREE_OBJECT(get_on_command_data_tree,
                JSONTREE_PAIR("OnCommand", &data_callback));
JSONTREE_OBJECT(get_off_command_data_tree,
                JSONTREE_PAIR("OffCommand", &data_callback));
JSONTREE_OBJECT(get_reset_command_data_tree,
                JSONTREE_PAIR("ResetCommand", &data_callback));
JSONTREE_OBJECT(get_state_command_data_tree,
                JSONTREE_PAIR("StateCommand", &data_callback));

JSONTREE_OBJECT(on_command_data_get_tree,
                JSONTREE_PAIR("board3", &get_on_command_data_tree));
JSONTREE_OBJECT(off_command_data_get_tree,
                JSONTREE_PAIR("board3", &get_off_command_data_tree));
JSONTREE_OBJECT(reset_command_data_get_tree,
                JSONTREE_PAIR("board3", &get_reset_command_data_tree));
JSONTREE_OBJECT(state_command_data_get_tree,
                JSONTREE_PAIR("board3", &get_state_command_data_tree));


JSONTREE_OBJECT(set_data_tree,
                JSONTREE_PAIR("StateResponse", &data_callback),
				JSONTREE_PAIR("ArduinoStarting", &data_callback));

JSONTREE_OBJECT(data_set_tree,
                JSONTREE_PAIR("board3", &set_data_tree));

void wifiConnectCb(uint8_t status)
{
	if(status == STATION_GOT_IP){
		MQTT_Connect(&mqttClient);
	} else {
		MQTT_Disconnect(&mqttClient);
	}
}

void mqttConnectedCb(uint32_t *args)
{
	MQTT_Client* client = (MQTT_Client*)args;

	MQTT_Subscribe(client,"/board3/OnCommand",    2);
	MQTT_Subscribe(client,"/board3/OffCommand",   2);
	MQTT_Subscribe(client,"/board3/ResetCommand", 2);
	MQTT_Subscribe(client,"/board3/StateCommand", 2);

	MQTT_Publish(&mqttClient, "/board3/ESP8266Starting", "1", 1, 2, 0);
}

void mqttDisconnectedCb(uint32_t *args)
{
	MQTT_Client* client = (MQTT_Client*)args;
//	INFO("MQTT: Disconnected\r\n");
}

void mqttPublishedCb(uint32_t *args)
{
	MQTT_Client* client = (MQTT_Client*)args;
//	INFO("MQTT: Published\r\n");
}

void mqttDataCb(uint32_t *args, const char* topic, uint32_t topic_len, const char *data, uint32_t data_len)
{
	char *pbuf = (char *)os_zalloc(jsonSize);
	char *topicBuf = (char*)os_zalloc(topic_len+1);
	char *dataBuf  = (char*)os_zalloc(data_len+1);

	MQTT_Client* client = (MQTT_Client*)args;

	os_memcpy(topicBuf, topic, topic_len);
	topicBuf[topic_len] = 0;
	os_memcpy(dataBuf, data, data_len);
	dataBuf[data_len] = 0;

//	INFO("Received on topic: %s, data: %s \r\n", topicBuf, dataBuf);
//	os_delay_us(500);

	if (os_strcmp(topicBuf, "/board3/OnCommand") == 0)
	{
		intOnCommand = atoi(dataBuf);
        json_ws_send((struct jsontree_value *)&on_command_data_get_tree, "board3", pbuf);
	}
	else if (os_strcmp(topicBuf, "/board3/OffCommand") == 0)
    {
		intOffCommand = atoi(dataBuf);
        json_ws_send((struct jsontree_value *)&off_command_data_get_tree, "board3", pbuf);
	}
	else if (os_strcmp(topicBuf, "/board3/ResetCommand") == 0)
    {
		intResetCommand = atoi(dataBuf);
        json_ws_send((struct jsontree_value *)&reset_command_data_get_tree, "board3", pbuf);
	}
	else if (os_strcmp(topicBuf, "/board3/StateCommand") == 0)
    {
		intStateCommand = atoi(dataBuf);
        json_ws_send((struct jsontree_value *)&state_command_data_get_tree, "board3", pbuf);
	}

	// Send to Arduino as Json string
	INFO("%s",pbuf);
//	os_delay_us(500);

	os_free(dataBuf);
	os_free(topicBuf);
	os_free(pbuf);
}

//Main code function
static void ICACHE_FLASH_ATTR loop(os_event_t *events)
{
	char str[256];
	int position = 0;
	int opening_brace = 0;

	int c = uart0_rx_one_char();

	if (c != -1)
	{
		if (c == 123) // {
		{
			os_bzero(str, sizeof(str));
			struct jsontree_context js;
			str[position] = (char)c;
			position++;
			opening_brace++;

			while(c = uart0_rx_one_char())
			{
				if ((c >= 32) && (c <= 126))
				{
					str[position++] = (char)c;
				}

				if (c == 125)  // }
				{
					opening_brace--;
				}

				if ((opening_brace == 0 ) || (position > 254))
				{
					break;
				}
			}

			if (opening_brace == 0 )
			{
    			str[position++] = 0;
//	    	    INFO("String received=%s:position=%d\n",str,position);

                jsontree_setup(&js, (struct jsontree_value *)&data_set_tree, json_putchar);
                json_parse(&js, str);
			}
   		}
	}
}

void user_init(void)
{
//	uart_init(BIT_RATE_115200, BIT_RATE_115200);
	uart_init(BIT_RATE_57600, BIT_RATE_57600);

	gpio_init();

	// check GPIO setting (for config mode selection)
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0);
    PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO0_U);

	os_delay_us(1000000);

	CFG_Load();

	MQTT_InitConnection(&mqttClient, sysCfg.mqtt_host, sysCfg.mqtt_port, sysCfg.security);
	MQTT_InitClient(&mqttClient, sysCfg.device_id, sysCfg.mqtt_user, sysCfg.mqtt_pass, sysCfg.mqtt_keepalive, 1);
	MQTT_InitLWT(&mqttClient, "/lwt", "offline", 2, 0);

	MQTT_OnConnected(&mqttClient, mqttConnectedCb);
	MQTT_OnDisconnected(&mqttClient, mqttDisconnectedCb);
	MQTT_OnPublished(&mqttClient, mqttPublishedCb);
	MQTT_OnData(&mqttClient, mqttDataCb);

	WIFI_Connect(sysCfg.sta_ssid, sysCfg.sta_pwd, wifiConnectCb);

	//Start os task
	system_os_task(loop, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
	system_os_post(user_procTaskPrio, 0, 0 );

//	INFO("\r\nSystem started ...\r\n");
}
