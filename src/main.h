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

typedef struct
{
	unsigned char ind : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char b3 : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} BitParasmsTypeDef;

typedef struct {
	float volume_per_rev;
	uint32_t motor1_speed;
	uint32_t motor1_acc;
	uint32_t motor2_speed;
	uint32_t motor2_acc;
	uint32_t time_hold;
	float volume;
	float temp1;
	float temp2;
	float temp3;
	float Kp;
	float Ki;
	float Kd;
	BitParasmsTypeDef bitParams;
	uint8_t reservU0;
	uint8_t flash_init;
	uint8_t CS;
} TermoplastConfigTypeDef;

typedef struct {
	uint8_t start_msg0;
	uint8_t start_msg1;
	uint8_t control_id;
	uint8_t msg_id;
	TermoplastConfigTypeDef termConfig;
	uint8_t reservU0;
	uint8_t reservU1;
	uint8_t reservU2;
	uint8_t CS;
} StmConfigTypeDef;

typedef struct {
	unsigned char limit_sw1		:1;
	unsigned char limit_sw2		:1;
	unsigned char button1		:1;
	unsigned char button2		:1;
	unsigned char button3		:1;
	unsigned char button4		:1;
	unsigned char button5		:1;
	unsigned char button6		:1;
	unsigned char r0		:1;
	unsigned char r1		:1;
	unsigned char r2		:1;
	unsigned char r3		:1;
	unsigned char r4		:1;
	unsigned char r5		:1;
	unsigned char r6		:1;
	unsigned char r7		:1;
} SensorsTypeDef;

typedef struct {
	unsigned char err0  :1;
	unsigned char err1  :1;
	unsigned char err2  :1;
	unsigned char err3  :1;
	unsigned char err4  :1;
	unsigned char err5  :1;
	unsigned char err6  :1;
	unsigned char err7  :1;
	unsigned char err8  :1;
	unsigned char err9  :1;
	unsigned char err10 :1;
	unsigned char err11 :1;
	unsigned char err12 :1;
	unsigned char err13 :1;
	unsigned char err14 :1;
	unsigned char err15 :1;
} ErrorMsgTypeDef;

typedef struct {
	uint8_t start_msg0;
	uint8_t start_msg1;
	uint8_t control_id;
	uint8_t msg_id;
	float temp1;
	float temp2;
	float temp3;
	SensorsTypeDef sens;
	ErrorMsgTypeDef error;
	uint32_t cycles_count;
	uint32_t cycles_set;
	uint8_t status;
	uint8_t cs_errors;
	uint8_t reserv1;
	uint8_t CS;
} StatusMsgTypeDef;

typedef struct {
	uint8_t start_msg0;
	uint8_t start_msg1;
	uint8_t control_id;
	uint8_t msg_id;
	uint8_t comm;
	uint8_t c1;
	uint8_t c2;
	uint8_t c3;
	float volume;
	uint32_t time_hold;
	uint32_t cycles;
	uint8_t r0;
	uint8_t r1;
	uint8_t r2;
	uint8_t CS;
} JobMsgTypeDef;

enum WIFI_MSG_ID {
	WIFI_NONE = 0,
	WIFI_GET_STATUS = 1,
	WIFI_SET_MANUAL_COM,
	WIFI_GET_STM_CONFIG,
	WIFI_SET_STM_CONFIG,
	WIFI_SET_JOB,
	WIFI_SET_HEATING,
	WIFI_RESERV1,
	WIFI_RESERV2,
	WIFI_RESERV3,
	WIFI_RESERV4,
	WIFI_MSG_MAX,
};

enum JOB_STATUS {
	JOB_WAITING = 0,
	JOB_START,
	JOB_PAUSE,
	JOB_RESUME,
	JOB_COMPLETED,
	JOB_STOP,
	JOB_ERROR,
	JOB_MAX,
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