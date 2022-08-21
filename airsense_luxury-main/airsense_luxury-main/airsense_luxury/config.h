#pragma once
#pragma once
#include "Arduino.h"
#include "Wire.h"
#include "SPI.h"

#define SERIAL_DEBUG_BAUDRATE 115200

#define ERROR_READ_DISPLAY 777777



// Ozone sensor

#define COLLECT_NUMBER 20     // collect number, the collection range is 1-100
#define Ozone_IICAddress 0x73 // I2C address of Ozone Sensor
extern int a_ozoneConcentration_Calib = 0;
extern int b_ozoneConcentration_Calib = 0;

extern int dataCalibInt = 0;
extern int tempCalibInt = 0;
extern int humiCalibInt = 0;
extern int pm1CalibInt = 0;
extern int pm10CalibInt = 0;
extern int pm25CalibInt = 0;
extern int tempCalibFloat = 0;
extern int humiCalibFloat = 0;
//#define PIN_TX_PMS7003  17
//#define PIN_RX_PMS7003  16
//#define PORT_UART_PMS7003 Seria2
int getTemp = 0;
#define PIN_TX_TFLP01   17
#define PIN_RX_TFLP01   16
// #define PORT_UART_TFLP01 Serial2

#define PIN_TX_TFT      33
#define PIN_RX_TFT      25
//#define PORT_UART_SDS011 Serial1

#define PIN_NUM_MISO    21
#define PIN_NUM_MOSI    19
#define PIN_NUM_CLK     18
//#define PIN_NUM_CS    17

#define PIN_CS_SD_CARD  5

//#define PIN_TFT_RST   15
//#define PIN_TFT_DC    12
//#define PIN_TFT_CS    13
//#define PIN_TFT_LED   14

#define PIN_SDA_GPIO    26
#define PIN_SCL_GPIO    27
#define I2C_CLOCK_SPEED 100000

#define PIN_NEO_PIXEL   23

#define PIN_BUTTON_1    35
#define PIN_BUTTON_2    34
#define outputA         33
#define outputB         25
#define switch          32
