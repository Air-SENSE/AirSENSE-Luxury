#include "WiFi.h"
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <string>
#include <SPI.h>
#include <SD.h>
#include "Wire.h"
#include "./config.h"
#include "./SHT85.h"
#include "./TFLP01.h"
#include "ozone.h"
#include "calib.h"
//#include "FireBase.h"
//#include <FirebaseESP32.h>
/////////////////
//    uint32_t number = 0;
//    uint32_t lastnumber = 0;

    ///////
//File myFile;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "de.pool.ntp.org", 3600*7, 60000);
#include "./DS3231.h"

uint32_t lastreconnectwifi=0;
uint32_t lastPressButton = 0;
uint32_t lastsenddatatoSD_MQTT = millis();

uint8_t  TFT_wifi = 0;
uint8_t  TFT_SDcard=0;

char  TFT_string[10];

float temp=20.5;
float humi=60;
int yearCalib = 2021;
int   TFT_o3_ppb = 0;
float TFT_o3_ppm = 0;
float TFT_o3_ug  = 0;
int   min_o3_ppb = 100;
float min_o3_ppm = 100;
float min_o3_ug  = 100;
int   max_o3_ppb = 0;
float max_o3_ppm = 0;
float max_o3_ug  = 0;

bool  stateSDcard=0;
uint8_t MacAddress1[6];
char nameDevice1[12];
#include "./mqttServer.h"
#include "./SDcard.h"
#include "./MQ131.h"
#include "./TFT.h"
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
void setup() {
  //Serial.begin(115200);
  myNex.NextionListen();
  Serial2.begin(115200);
  pinMode(35,INPUT);
  Wire.begin(PIN_SDA_GPIO, PIN_SCL_GPIO, I2C_CLOCK_SPEED);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin();
  WiFi.macAddress(MacAddress1);
  sprintf(nameDevice1,"%02X%02X%02X%02X%02X%02X",MacAddress1[0],MacAddress1[1],MacAddress1[2],MacAddress1[3],MacAddress1[4],MacAddress1[5]);
  Serial.println(nameDevice1);
  SDcard_init();
  timeClient.begin();
  SHT85_init();
  Ozone_init();
  DS3231_init();
  initMqttClient(topic, espID, mqttClient);
  setup_TFT();
  sprintf(nameFileCalib,"/calib-%d.txt",yearCalib);
}

void loop() {
    

    if (longPressButton())
    {
      uint8_t a=0;
      WiFi.beginSmartConfig();
      while (!WiFi.smartConfigDone() && a<120) {
        delay(500);
        TFT_wifi = 2;
        myNex.writeNum("dl.wifi.val",TFT_wifi);
//        Serial.println(a);
        a++;
      }
    }
    if (WiFi.status() == WL_CONNECTED){
       TFT_wifi = 1;
    }
    else{
      TFT_wifi = 0;
      if((millis()-lastreconnectwifi>60000) || (millis()<lastreconnectwifi)){
        WiFi.begin();
        lastreconnectwifi = millis();
      }
    }
//    myNex.NextionListen();
    getSHTdata();
    getTFLP01data();
    getDS3231data();
    TFT_o3_ppm =(float) get_OzoneData() /1000.0;
    senddatatoTFT();
    
    if((millis()-lastsenddatatoSD_MQTT> 10000) || (millis()<lastsenddatatoSD_MQTT))
    {
      senddatatoSD(TFT_humi,TFT_temp,TFT_pm1,TFT_pm25,TFT_pm10,TFT_o3_ppb,TFT_o3_ppm,TFT_o3_ug,min_pm25,max_pm25);
      runProgramWithSD();
      senddatatoMQTT(TFT_humi,TFT_temp,TFT_pm1,TFT_pm25,TFT_pm10,TFT_o3_ppb);
      lastsenddatatoSD_MQTT = millis();
    }
    mqttClient.loop();

//    
//    save_temp();
//    save_humi();
//    save_pm1();
//    save_pm10();
//    save_pm25();
//    save_ozone();
}
