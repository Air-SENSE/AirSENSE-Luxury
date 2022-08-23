#pragma once


//#define DEBUG_SERIAL

//========================== DEFINE CHO MAN HINH ========================
#define SERIAL_DEBUG_BAUDRATE 115200
#define ERROR_READ_DISPLAY 777777

//========================== DEFINE CHO MAN HINH ========================

#define PIN_TX_TFLP01   17
#define PIN_RX_TFLP01   16

//========================== DEFINE CHO MAN HINH ========================

#define PIN_TX_TFT      33
#define PIN_RX_TFT      25

//========================== DEFINE CHO MAN HINH ========================

#define PIN_NUM_MISO    21
#define PIN_NUM_MOSI    19
#define PIN_NUM_CLK     18
#define PIN_CS_SD_CARD  5
//========================== DEFINE CHO MAN HINH ========================

#define PIN_SDA_GPIO    26
#define PIN_SCL_GPIO    27
#define I2C_CLOCK_SPEED 100000
//========================== DEFINE CHO MAN HINH ========================

#define PIN_NEO_PIXEL   23
//========================== DEFINE CHO MAN HINH ========================

#define PIN_BUTTON_1    35
#define PIN_BUTTON_2    34
#define outputA         33
#define outputB         25
#define switch          32
//========================== DEFINE CHO MAN HINH ========================

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "de.pool.ntp.org", 3600*7, 60000);

//========================== DEFINE CHO MAN HINH ========================

uint32_t lastreconnectwifi=0;
uint32_t lastPressButton = 0;
uint32_t lastsenddatatoSD_MQTT = millis();

//========================== khai bao cac bien hien thi tren man hinh ========================

uint8_t  TFT_wifi = 0;
uint8_t  TFT_SDcard=0;

char  TFT_string[10];

float temp		 = 20.5;
float humi		 = 60;
int   yearCalib  = 2021;
int   TFT_o3_ppb = 0;
float TFT_o3_ppm = 0;
float TFT_o3_ug  = 0;
int   min_o3_ppb = 100;
float min_o3_ppm = 100;
float min_o3_ug  = 100;
int   max_o3_ppb = 0;
float max_o3_ppm = 0;
float max_o3_ug  = 0;

//========================== khai bao de dung cho the nho ========================

bool  	stateSDcard	 = 0;
uint8_t MacAddress1[6];
char 	nameDevice1[12];

//========================== cac bien de calib gia tri ========================

extern int dataCalibInt = 0;
extern int tempCalibInt = 0;
extern int humiCalibInt = 0;
extern int pm1CalibInt = 0;
extern int pm10CalibInt = 0;
extern int pm25CalibInt = 0;
extern int tempCalibFloat = 0;
extern int humiCalibFloat = 0;
int getTemp = 0;

//========================== cac bien de doc gia tri tu man hinh ========================

int tempFromDisplay 	= 0;
int humiFromDisplay 	= 0;
int pm1FromDisplay		= 0;
int pm10FromDisplay 	= 0;
int pm25FromDisplay 	= 0;
int tempFloatFromDisplay = 0;
int humiFloatFromDisplay = 0;