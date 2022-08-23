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


void DS3231_init();
void getDS3231data();
void initMqttClient(char* _topic, char* _espID, PubSubClient& _mqttClient);
void senddatatoMQTT(float hum,float tem,int pm1,int pm25,int pm10,float O3);
void SDcard_init();
void senddatatoSD(float hum,float tem,int pm1,int pm25,int pm10,int O3ppb,float O3ppm,float O3ug ,int minpm25, int maxpm25);
void runProgramWithSD();
void getSHTdata();
void SHT85_init();
void getTFLP01data();
void readDataFromDisplay();
void sendCalibToSD();
void split_string();
void read_file_inSD() ;
void sendDataCalibToTFT();
void senddatatoTFT();
bool longPressButton();



//========================== Khai bao cac file code ========================

#include "./config.h"
#include "./SHT85.h"
#include "./TFLP01.h"
#include "./DS3231.h"
#include "./mqttServer.h"
#include "./SDcard.h"
#include "./MQ131.h"
#include "./TFT.h"



//==========================     SETUP       ========================

void setup() {
  myNex.NextionListen();
  Serial.begin(SERIAL_DEBUG_BAUDRATE);
  pinMode(PIN_BUTTON_1,	INPUT);
  Wire.begin(PIN_SDA_GPIO, PIN_SCL_GPIO, I2C_CLOCK_SPEED);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin();
  WiFi.macAddress(MacAddress1);
  SDcard_init();
  timeClient.begin();
  SHT85_init();
  DS3231_init();
  initMqttClient(topic, espID, mqttClient);
  setup_TFT();
  // luu file text theo nam
  sprintf(nameFileCalib,"/calib-%d.txt",yearCalib);
}

//==========================     LOOP       ========================

void loop() {
    
	// check button de smartConfig
    if (longPressButton())
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
    getSHTdata();
    getTFLP01data();
    getDS3231data();
    getO3data();
	// hien thi len man hinh
    senddatatoTFT();
    
	//gui du lieu len mqtt va luu tru trong the nho
    if((millis()-lastsenddatatoSD_MQTT> 10000) || (millis()<lastsenddatatoSD_MQTT))
    {
		// luu vao trong the nho
      senddatatoSD(TFT_humi,TFT_temp,TFT_pm1,TFT_pm25,TFT_pm10,TFT_o3_ppb,TFT_o3_ppm,TFT_o3_ug,min_pm25,max_pm25);
      runProgramWithSD();
      senddatatoMQTT(TFT_humi,TFT_temp,TFT_pm1,TFT_pm25,TFT_pm10,TFT_o3_ppb);
      lastsenddatatoSD_MQTT = millis();
    }
    mqttClient.loop();

}


bool longPressButton()
{
  if (millis() - lastPressButton > 4000 && digitalRead(35) == 0)
  {
    return true;
  }
  else if (digitalRead(35) == 1)
  {
    lastPressButton = millis();
  }
  return false;
}