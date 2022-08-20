#pragma once
//#include "EasyNextionLibrary.h"
//#include "./TFT.h"
#include "config.h"
File myFile;
File myFile2;
File myFile3;
File myFile4;
const int chipSelect = 5;
//
//int number = 0;
//int lastnumber = 0;


void SDcard_init(){
  SPI.begin(PIN_NUM_CLK, PIN_NUM_MISO, PIN_NUM_MOSI, PIN_CS_SD_CARD);
  pinMode(SS, OUTPUT);
  if(!SD.begin(PIN_CS_SD_CARD,SPI)){ 
    TFT_SDcard = 0; 
    Serial.println("SD init false");
  }else{
    TFT_SDcard = 1; 
    Serial.println("SD init done");
   }
}
//void senddatatoSD(float hum,float tem,int pm1,int pm25,int pm10,int O3ppb,float O3ppm,float O3ug ,int minpm25, int maxpm25)
//{
//    DateTime now = rtc.now();
//    int getyear =now.year();
//    uint8_t getmonth =now.month();
//    uint8_t getday =now.day();
//    uint8_t gethour =now.hour();
//    uint8_t getminute =now.minute();
//    uint8_t getsecond =now.second();
//    uint32_t epochTime=now.unixtime();
//    uint8_t y = getyear%2000;
//    
//    char filename[16];
//    if(getday<10 && getmonth<10) sprintf(filename,"/%d-0%d-0%d.txt",y,getmonth,getday);
//    if(getday<10 && getmonth>=10) sprintf(filename,"/%d-%d-0%d.txt",y,getmonth,getday);
//    if(getday>=10 && getmonth<10) sprintf(filename,"/%d-0%d-%d.txt",y,getmonth,getday);
//    if(getday>=10 && getmonth>=10) sprintf(filename,"/%d-%d-%d.txt",y,getmonth,getday);
//    
//    if(0<=y && y<=22 && 0<getmonth && getmonth<=12 && 0<getday && getday<=31){
//      myFile = SD.open(filename,FILE_APPEND);
//      if(myFile){
//        char mes[256] = {0};
//        sprintf(mes,"%12s,%4d/%d/%d,%d:%d:%d,%d,%.1f,%.1f,%d,%d,%d,%d,%d,%d,%.3f,%.1f",nameDevice1,getyear,getmonth,getday,gethour,getminute,getsecond,epochTime,tem,hum,pm1,pm25,pm10,minpm25,maxpm25,O3ppb,O3ppm,O3ug);
//        //Serial.println(mes);
//        TFT_SDcard = 1;
//        myFile.println(mes);        
//        myFile.close();
//      }
//      else{ 
//        //Serial.println("reconnect SD");
//        if(!SD.begin(PIN_CS_SD_CARD,SPI)) TFT_SDcard = 0; 
//        else TFT_SDcard = 1; 
//      }
//    } 
//    else 
//    {
//      //Serial.println("--------------Loi lay ngay sai: "+String(filename)+"---------------");
//      //rtc.begin();
//    }
//}
// void save_temp()
// {
//     number = myNex.readNumber("calib.n0.val");   // We read the value of n0 and store it to number variable
//     if(number != 777777){                     // 777777 is the return value if the code fails to read the new value
//       lastnumber = number;  
//       if(lastnumber !=0)                                     
//       {
//          getTemp = lastnumber;
//       }
//     }
                                           
//     else if(number == 777777){
//       number = lastnumber;
//     }
//      int temp_in_flash = EEPROM.read(20); // read in adddresss 0 eeprom esp32
     
//   if(lastnumber==0)
//   {
//   myNex.writeNum("calib.n0.val",temp_in_flash);
//   }
// }
//void sendCalibToSD()
//{
//    char nameFileCalib[16] = "temp.txt";
//    // sprintf(nameFileCalib,"/%d-%d-%d.txt",y,getmonth,getday);
//    number = myNex.readNumber("calib.n0.val");   // We read the value of n0 and store it to number variable
//    if(number != 777777){                     // 777777 is the return value if the code fails to read the new value
//      lastnumber = number;  
//      if(lastnumber !=0)                                     
//      {
//         getTemp = lastnumber;
//      }
//    }
//                                           
//    else if(number == 777777){
//      number = lastnumber;
//    }
//    //  int temp_in_flash = EEPROM.read(20); // read in adddresss 0 eeprom esp32
//     
//  if(lastnumber==0)
//  {
//  // myNex.writeNum("calib.n0.val",temp_in_flash);
//      myFile = SD.open(nameFileCalib,FILE_APPEND);
//      if(myFile){
//        char mes[256] = {0};
//        sprintf(mes,"%d",getTemp);
//        //Serial.println(mes);
//        TFT_SDcard = 1;
//        myFile.println(mes);        
//        myFile.close();
//      }
//      else{ 
//        //Serial.println("reconnect SD");
//        if(!SD.begin(PIN_CS_SD_CARD,SPI)) TFT_SDcard = 0; 
//        else TFT_SDcard = 1; 
//      }
//
//  }
//}
