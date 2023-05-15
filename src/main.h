#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#include <DNSServer.h>
#include "WiFi.h"
#include <ESPAsyncWebServer.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include <Preferences.h>
#include <HTTPClient.h>
#include <Update.h>
#include "TFT_eSPI.h"
#include "SPIFFS.h"
#include <esp_task_wdt.h>

#include "alite.h"
#include "panel_page.h"
#include "manual_page.h"
#include "wifi_page.h"
#include "params_page.h"
#include "update_esp.h"
#include "update_stm.h"
#include "help_page.h"
//#include "rus_font.h"

#define WDT_TIMEOUT 4

#define PIN_POWER_ON	15
//screen size 170x320

#define stm_firmware "/termoplast.bin"
#define esp_firmware "/termo_wifi.bin"


#define START_MSG0 0x84
#define START_MSG1 0x53
#define WIFI_CONTROL_ID 0x64

typedef struct {
	uint8_t start_msg0;
	uint8_t start_msg1;
	uint8_t control_id;
	uint8_t msg_id;
	float temp1;
	float temp2;
	float temp3;
	uint16_t sensors;
	uint16_t errors;
	uint32_t cycles_count;
	uint32_t cycles_set;
	uint8_t status;
	uint8_t cs_errors;
	uint8_t reserv1;
	uint8_t CS;
} StatusMsgTypeDef;

enum WIFI_MSG_ID {
	WIFI_NONE = 0,
	WIFI_GET_STATUS = 1,
	WIFI_SET_MANUAL_COM,
	WIFI_RESERV1,
	WIFI_RESERV2,
	WIFI_RESERV3,
	WIFI_RESERV4,
	WIFI_MSG_MAX,
};

// control command send
typedef struct
{
	uint8_t start_msg0;
	uint8_t start_msg1;
	uint8_t control_id;
	uint8_t msg_id;
	uint8_t comm;
	uint8_t r0;
	uint8_t r1;
	uint8_t CS;
} CommMsgTypeDef;

#endif /* INC_MAIN_H_ */