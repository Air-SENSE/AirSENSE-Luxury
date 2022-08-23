#pragma once

#include <SD.h>
#include "config.h"
File myFile;
File myFile2;
File myFile3;
File myFile4;
const int chipSelect = 5;

/**
 * @brief	ham de khoi tao the nho
 *
 * @return  None
 */
void SDcard_init()
{
  SPI.begin(PIN_NUM_CLK, PIN_NUM_MISO, PIN_NUM_MOSI, PIN_CS_SD_CARD);
  pinMode(SS, OUTPUT);
  if(!SD.begin(PIN_CS_SD_CARD)){ 
    TFT_SDcard = 0; 
    Serial.println("SD init false");
  }else{
    TFT_SDcard = 1; 
    Serial.println("SD init done");
   }
}


/**
 * @brief	ham de luu gia tri vao the nho
 * @param	hum - gia tri do am
 * @param	tem - gia tri nhiet do
 * @param	pm1 - pm1.0
 * @param	pm25 - pm2.5
 * @param	pm10 - pm10
 * @param	O3ppb - 03
 * @param	O3ppm - 03
 * @param	O3ug - 03
 * @param	minpm25 - muc min cua pm25
 * @param	maxpm25 - muc max cua pm25
 * @return  None
 */
void senddatatoSD(float hum,float tem,int pm1,int pm25,int pm10,int O3ppb,float O3ppm,float O3ug ,int minpm25, int maxpm25)
{
    DateTime now = rtc.now();
    int getyear =now.year();
    uint8_t getmonth =now.month();
    uint8_t getday =now.day();
    uint8_t gethour =now.hour();
    uint8_t getminute =now.minute();
    uint8_t getsecond =now.second();
    uint32_t epochTime=now.unixtime();
    uint8_t y = getyear%2000;
    
    char filename[16];
    if(getday<10 && getmonth<10) sprintf(filename,"/%d-0%d-0%d.txt",y,getmonth,getday);
    if(getday<10 && getmonth>=10) sprintf(filename,"/%d-%d-0%d.txt",y,getmonth,getday);
    if(getday>=10 && getmonth<10) sprintf(filename,"/%d-0%d-%d.txt",y,getmonth,getday);
    if(getday>=10 && getmonth>=10) sprintf(filename,"/%d-%d-%d.txt",y,getmonth,getday);
	
    if(0<=y && y<=22 && 0<getmonth && getmonth<=12 && 0<getday && getday<=31){
      myFile = SD.open(filename,FILE_WRITE);
      if(myFile){
        char mes[256] = {0};
        sprintf(mes,"%12s,%4d/%d/%d,%d:%d:%d,%d,%.1f,%.1f,%d,%d,%d,%d,%d,%d,%.3f,%.1f",nameDevice1,getyear,getmonth,getday,gethour,getminute,getsecond,epochTime,tem,hum,pm1,pm25,pm10,minpm25,maxpm25,O3ppb,O3ppm,O3ug);
#ifdef	DEBUG_SERIAL
		Serial.println(mes);
#endif
        TFT_SDcard = 1;
        myFile.println(mes);        
        myFile.close();
      }
      else{ 
#ifdef	DEBUG_SERIAL
        //Serial.println("reconnect SD");
#endif
        if(!SD.begin(PIN_CS_SD_CARD, SPI)) TFT_SDcard = 0; 
        else TFT_SDcard = 1; 
      }
    } 
    else 
    {
#ifdef	DEBUG_SERIAL
      Serial.println("--------------Loi lay ngay sai: "+String(filename)+"---------------");
      //rtc.begin();
#endif
    }
}

/**
 * @brief	Chuong trinh hoat dong cua the nho
 *
 * @return  None
 */
void runProgramWithSD()
{
    // doc gia tri tu man hinh
    readDataFromDisplay();
	// neu man hinh moi khoi tao
    if( tempFromDisplay == 0 && humiFromDisplay == 0 && pm1FromDisplay == 0 && pm10FromDisplay == 0 && pm25FromDisplay == 0)
    {
		// doc gia tri tu the nho
      read_file_inSD();
		// gui gia tri len man hinh calib
      sendDataCalibToTFT();
    }
    else
    {
		// doc gia tri tu calib vao the sd
		sendCalibToSD();
		// doc nguoc lai the sd
		read_file_inSD();
		// hien thi lai len man hinh
		sendDataCalibToTFT();
    }
}