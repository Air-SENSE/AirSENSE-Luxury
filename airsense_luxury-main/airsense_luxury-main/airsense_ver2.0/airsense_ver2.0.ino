//========================== Khai bao thu vien ========================

#include <Arduino.h>
#include <string>
#include "Wire.h"
#include <SPI.h>
#include "WiFi.h"
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>



//========================== Cac ham su dung ========================


void DS3231_Init();
void DS3231_GetData();

void MQTT_InitClient(char* _topic, char* _espID, PubSubClient& _mqttClient);
void MQTT_PostData(float hum,float tem,int pm1,int pm25,int pm10,float O3);

void SDcard_Init();
void SDcard_GetData(float hum,float tem,int pm1,int pm25,int pm10,int O3ppb,float O3ppm,float O3ug ,int minpm25, int maxpm25);
void SDcardScreen_SplitStringData();
void SDcard_ReadFile();
void SDcard_SaveDataFile();
void runProgramWithSD();

void SHT_GetData();
void SHT_Init();

void TFLP01_GetData();

void Screen_Init();
void Screen_SaveCalibData2SDcard();
void Screen_GetDisplayData();
void Screen_DisplayData();
void Screen_DisplayCalibData();

void O3_Init();
void O3_GetData();

bool isLongPressButton();



//========================== Khai bao cac file code ========================

#include "./config.h"
#include "./SHT85Driver.h"
#include "./TFLP01Driver.h"
#include "./DS3231Driver.h"
#include "./MQTTConnection.h"
#include "./SDcardDriver.h"
#include "./MQ131Driver.h"
#include "./NextionDriver.h"



//==========================     SETUP       ========================

void setup() {
  Serial.begin(SERIAL_DEBUG_BAUDRATE);
  pinMode(PIN_BUTTON_1,	INPUT);
  Wire.begin(PIN_SDA_GPIO, PIN_SCL_GPIO, I2C_CLOCK_SPEED);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin();
  WiFi.macAddress(MacAddress1);
  MQTT_InitClient(topic, espID, mqttClient);
  timeClient.begin();
  // khoi tao cac cam bien
  myNex.NextionListen();
//  O3_init();
  DS3231_Init();
  SHT_Init();
  SDcard_Init();
  Screen_Init();
  // luu file text theo nam
  sprintf(nameFileCalib,"/calib-%d.txt",yearCalib);
}

//==========================     LOOP       ========================

void loop() {
    
	// check button de smartConfig
    if (isLongPressButton())
    {
      uint8_t a=0;
      while (!WiFi.smartConfigDone() && a<120) {
        delay(500);
        TFT_wifi = 2;
        myNex.writeNum("dl.wifi.val",TFT_wifi);
        a++;
      }
    }
	// check neu wifi da ket noi thi cho bien wifi man hinh bat len
    if (WiFi.status() == WL_CONNECTED){
       TFT_wifi = 1;
    }
    else
	{
		// hien thi chua ket noi wifi
      TFT_wifi = 0;
      if((millis()-lastreconnectwifi>60000) || (millis()<lastreconnectwifi)){
        lastreconnectwifi = millis();
      }
    }
	// get data
    SHT_GetData();
    TFLP01_GetData();
    DS3231_GetData();
//    O3_GetData();
	// hien thi len man hinh
    Screen_DisplayData();
    
	//gui du lieu len mqtt va luu tru trong the nho
    if((millis()-lastsenddatatoSD_MQTT> 10000) || (millis()<lastsenddatatoSD_MQTT))
    {
		// luu vao trong the nho
      SDcard_SaveDataFile(TFT_humi,TFT_temp,TFT_pm1,TFT_pm25,TFT_pm10,TFT_o3_ppb,TFT_o3_ppm,TFT_o3_ug,min_pm25,max_pm25);
      runProgramWithSD();
      MQTT_PostData(TFT_humi,TFT_temp,TFT_pm1,TFT_pm25,TFT_pm10,TFT_o3_ppb);
      lastsenddatatoSD_MQTT = millis();
    }
    mqttClient.loop();

}


bool isLongPressButton()
{
  if (millis() - lastPressButton > 4000 && digitalRead(PIN_BUTTON_1) == 0)
  {
    return true;
  }
  else if (digitalRead(PIN_BUTTON_1) == 1)
  {
    lastPressButton = millis();
  }
  return false;
}
