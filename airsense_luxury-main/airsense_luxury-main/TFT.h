/************************************************************
 **    TFT_o3_ppb(int)  TFT_o3_ppm(float)  TFT_o3_ug(int)  **    
 **    min_o3_ppb(int)  min_o3_ppm(float)  min_o3_ug(int)  **
 **    max_o3_ppb(int)  max_o3_ppm(float)  max_o3_ug(int)  **
 **    TFT_temp(uint8_t)            TFT_wifi               **
 **    TFT_humi(uint8_t)            TFT_SDcard             **
 **    TFT_temp_F(uint16_t)         Rx: pin 33              **
 **    TFT_pm25(int)                Tx: pin 25              **
 **    TFT_pm10(int)                                       **
 **    TFT_time(string)                                    **
 ************************************************************/

/* Khai bao thu vien man hinh TFT */
#pragma once 
#include <iostream>
#include <string>
#include "string.h"
#include <sstream>
#include "config.h"
#include "SDcard.h"
#include "EasyNextionLibrary.h"
#include <EEPROM.h>
EasyNex myNex(Serial);
/* khai bao cac bien */
//int number = 0;
int tempFromDisplay = 0;
int humiFromDisplay = 0;
int pm1FromDisplay = 0;
int pm10FromDisplay = 0;
int pm25FromDisplay = 0;
int tempFloatFromDisplay = 0;
int humiFloatFromDisplay = 0;

char char_array[30];
char fileNameCalib[] = "calib.txt";


char nameFileCalib1[16];
char nameFileCalib[16];

void setup_TFT(){
    myNex.begin(9600);
    EEPROM.begin(512);
}


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
//    Serial.println(getTemp);
    if(0<=y && y<=22 && 0<getmonth && getmonth<=12 && 0<getday && getday<=31){
      myFile = SD.open(filename,FILE_APPEND);
      if(myFile){
        char mes[256] = {0};
        sprintf(mes,"%12s,%4d/%d/%d,%d:%d:%d,%d,%.1f,%.1f,%d,%d,%d,%d,%d,%d,%.3f,%.1f",nameDevice1,getyear,getmonth,getday,gethour,getminute,getsecond,epochTime,tem,hum,pm1,pm25,pm10,minpm25,maxpm25,O3ppb,O3ppm,O3ug);
        //Serial.println(mes);
        TFT_SDcard = 1;
        myFile.println(mes);        
        myFile.close();
      }
      else{ 
        //Serial.println("reconnect SD");
        if(!SD.begin(PIN_CS_SD_CARD,SPI)) TFT_SDcard = 0; 
        else TFT_SDcard = 1; 
      }
    } 
    else 
    {
      //Serial.println("--------------Loi lay ngay sai: "+String(filename)+"---------------");
      //rtc.begin();
    }
}

void readDataFromDisplay()
{
    int lastnumber = 0;
    int lastnumber1 = 0;
    int lastnumber2 = 0;
    int lastnumber3 = 0;
    int lastnumber4 = 0;
    int lastnumber5 = 0;
    int lastnumber6 = 0;  
    int number10 = myNex.readNumber("calibEdit.n8.val");  
    int number = myNex.readNumber("calibEdit.n0.val"); 
    int number1 = myNex.readNumber("calibEdit.n1.val");  
    int number2 = myNex.readNumber("calibEdit.n2.val");
    int number3 = myNex.readNumber("calibEdit.n3.val");  
    int number4 = myNex.readNumber("calibEdit.n4.val");
    int number5 = myNex.readNumber("calibEdit.n5.val");  
    int number6 = myNex.readNumber("calibEdit.n6.val");

                    
    if(number != ERROR_READ_DISPLAY){                     
      lastnumber = number;  
      if(lastnumber !=0)                                     
      {
         tempFromDisplay = lastnumber;
      }
    }
                                           
    else if(number == ERROR_READ_DISPLAY){
      number = lastnumber;
    }

    //// read data humidity
    if(number1 != ERROR_READ_DISPLAY){                     
      lastnumber1 = number1;  
      if(lastnumber1 !=0)                                     
      {
         humiFromDisplay = lastnumber1;
      }
    }
                                           
    else if(number1 == ERROR_READ_DISPLAY){
      number1 = lastnumber1;
    }


///// read data pm1
    if(number2 != ERROR_READ_DISPLAY){                     
      lastnumber2 = number2;  
      if(lastnumber2 !=0)                                     
      {
         pm1FromDisplay = lastnumber2;
      }
    }
                                           
    else if(number2 == ERROR_READ_DISPLAY){
      number2 = lastnumber2;
    }

///////// Read data pm10
    if(number3 != ERROR_READ_DISPLAY){                     
      lastnumber3 = number3;  
      if(lastnumber3 !=0)                                     
      {
         pm10FromDisplay = lastnumber3;
      }
    }
                                           
    else if(number3 == ERROR_READ_DISPLAY){
      number3 = lastnumber3;
    }

        //// Read data pm2.5
    if(number4 != ERROR_READ_DISPLAY){                     
      lastnumber4 = number4;  
      if(lastnumber4 !=0)                                     
      {
         pm25FromDisplay = lastnumber4;
      }
    }
                                           
    else if(number4 == ERROR_READ_DISPLAY){
      number4 = lastnumber4;
    }
            //// Read data temp Float
    if(number5 != ERROR_READ_DISPLAY){                     
      lastnumber5 = number5;  
      if(lastnumber5 !=0)                                     
      {
         tempFloatFromDisplay = lastnumber5;
      }
    }
                                           
    else if(number5 == ERROR_READ_DISPLAY){
      number5 = lastnumber5;
    }
            //// Read data humi Float
    if(number6 != ERROR_READ_DISPLAY){                     
      lastnumber6 = number6;  
      if(lastnumber6 !=0)                                     
      {
         humiFloatFromDisplay = lastnumber6;
      }
    }
                                           
    else if(number6 == ERROR_READ_DISPLAY){
      number6 = lastnumber6;
    }
    Serial.println(tempFromDisplay); 
    Serial.println(humiFromDisplay);
    Serial.println(pm1FromDisplay);
    Serial.println(pm10FromDisplay);
    Serial.println(pm25FromDisplay);  
    Serial.println(tempFloatFromDisplay);
    Serial.println(humiFloatFromDisplay);
    Serial.println("---------");
}
void sendCalibToSD()
{
      if( tempFromDisplay < -100 || tempFromDisplay >1000 || humiFromDisplay < -100 || humiFromDisplay >1000 || pm1FromDisplay < -100 || pm1FromDisplay >1000 || pm10FromDisplay < -100  || pm10FromDisplay >1000 || pm25FromDisplay < -100 || pm25FromDisplay >1000)
      {
        Serial.println("-----*** Dont write to SD card ***----");
      }
      else
      {
          myFile = SD.open(nameFileCalib,FILE_WRITE);
          if(myFile){
          char mess[256] = {0};
          sprintf(mess,"%d|%d|%d|%d|%d|%d|%d|",tempFromDisplay,humiFromDisplay,pm1FromDisplay,pm10FromDisplay,pm25FromDisplay,tempFloatFromDisplay,humiFloatFromDisplay);
          Serial.print("mess:");
          Serial.println(mess);
          TFT_SDcard = 1;
          myFile.println(mess);        
          myFile.close();
          }
          else{ 
          //Serial.println("reconnect SD");
          if(!SD.begin(PIN_CS_SD_CARD,SPI)) TFT_SDcard = 0; 
          else TFT_SDcard = 1; 
      }
      }
      
}

void split_string()
{
    Serial.print("char_arr in split:"); 
    Serial.println(char_array);
   char temp[30] = "";
   char humi[30] = "";
   char pm1[30] = "";
   char pm10[30] = "";
   char pm25[30] = "";
   char tempFl[30] = "";
   char humiFl[30] = "";
    
    // split string
    char* pt = NULL;
    pt = strtok(char_array, "|");
    if(pt)
    strcpy(temp, pt);
    tempCalibInt = atoi(temp);
    
    pt = strtok(NULL, "|");
    if(pt)
    strcpy(humi, pt);
    humiCalibInt = atoi(humi);
    
    pt = strtok(NULL, "|");
    if(pt)
    strcpy(pm1, pt);
    pm1CalibInt = atoi(pm1);

    pt = strtok(NULL, "|");
    if(pt)
    strcpy(pm10, pt);
    pm10CalibInt = atoi(pm10);

    pt = strtok(NULL, "|");
    if(pt)
    strcpy(pm25, pt);
    pm25CalibInt = atoi(pm25);


        pt = strtok(NULL, "|");
    if(pt)
    strcpy(tempFl, pt);
    tempCalibFloat = atoi(tempFl);
    
        pt = strtok(NULL, "|");
    if(pt)
    strcpy(humiFl, pt);
    humiCalibFloat = atoi(humiFl);
    Serial.println("After Split: ");
    Serial.println(tempCalibInt);
    Serial.println(humiCalibInt);
    Serial.println(pm1CalibInt);
    Serial.println(pm10CalibInt);
    Serial.println(pm25CalibInt);
    Serial.println(tempCalibFloat);
    Serial.println(humiCalibFloat);
    Serial.println("*********");
}
void read_file_inSD() {
//      DateTime now = rtc.now();
//    int getyear =now.year();
//    uint8_t y = getyear%2000;
//    sprintf("calib.txt","/%d.txt",y);
  Serial.println("--- Reading file ---");
  myFile3 = SD.open(nameFileCalib, FILE_READ);
  String finalString = "";
  while (myFile3.available())
  {
    finalString += (char)myFile3.read();
  }
    strcpy(char_array, finalString.c_str());
    Serial.print("char_array:");
    Serial.println(char_array);
    split_string();
    myFile3.close();
}
void sendDataCalibToTFT(){
  myNex.writeNum("dl.n9.val",dataCalibInt); //
  myNex.writeNum("dl.n4.val",tempCalibInt);
  myNex.writeNum("dl.n5.val",humiCalibInt);
  myNex.writeNum("dl.n6.val",pm1CalibInt);
  myNex.writeNum("dl.n7.val",pm10CalibInt);
  myNex.writeNum("dl.n8.val",pm25CalibInt);
  myNex.writeNum("dl.n7.val",tempCalibFloat);
  myNex.writeNum("dl.n8.val",humiCalibFloat);
}
void runProgramWithSD()
{
    
    readDataFromDisplay();
    if( tempFromDisplay == 0 && humiFromDisplay == 0 && pm1FromDisplay == 0 && pm10FromDisplay == 0 && pm25FromDisplay == 0)
    {
      read_file_inSD();
      sendDataCalibToTFT();
    }
    else
    {
    sendCalibToSD();
    read_file_inSD();
    sendDataCalibToTFT();
    }
}
void senddatatoTFT(){
  myNex.writeNum("dl.wifi.val",TFT_wifi);
  myNex.writeNum("dl.sd.val",TFT_SDcard);
  
  myNex.writeStr("dl.time.txt",TFT_time);

  sprintf(TFT_string,"%.1f",TFT_temp);
  myNex.writeStr("dl.temc.txt",TFT_string);
  
  sprintf(TFT_string,"%.1f",TFT_humi);
  myNex.writeStr("dl.hum.txt",TFT_string);
  
  sprintf(TFT_string,"%.1f",TFT_temp_F);
  myNex.writeStr("dl.temf.txt",TFT_string);
  
  myNex.writeNum("dl.nppb.val",TFT_o3_ppb);
  sprintf(TFT_string,"%d",TFT_o3_ppb);
  myNex.writeStr("dl.sppb.txt",TFT_string);
  
  sprintf(TFT_string,"%.1f",TFT_o3_ug);
  myNex.writeStr("dl.sug.txt",TFT_string);

  if(TFT_o3_ppb<10)sprintf(TFT_string,"0.00%d",TFT_o3_ppb);
  if(10<=TFT_o3_ppb && TFT_o3_ppb<100)sprintf(TFT_string,"0.0%d",TFT_o3_ppb);
  if(100<=TFT_o3_ppb && TFT_o3_ppb<1000)sprintf(TFT_string,"0.%d",TFT_o3_ppb);
  if(1000 <= TFT_o3_ppb)sprintf(TFT_string,"%d.%d",int(TFT_o3_ppb/1000),int(TFT_o3_ppb%1000));
  myNex.writeStr("dl.sppm.txt",TFT_string);

  sprintf(TFT_string,"%d",min_o3_ppb);
  myNex.writeStr("dl.sminppb.txt",TFT_string);
  
  sprintf(TFT_string,"%.1f",min_o3_ug);
  myNex.writeStr("dl.sminug.txt",TFT_string);

  if(min_o3_ppb<10)sprintf(TFT_string,"0.00%d",min_o3_ppb);
  if(10<=min_o3_ppb && min_o3_ppb<100)sprintf(TFT_string,"0.0%d",min_o3_ppb);
  if(100<=min_o3_ppb && min_o3_ppb<1000)sprintf(TFT_string,"0.%d",min_o3_ppb);
  if(1000 <= min_o3_ppb)sprintf(TFT_string,"%d.%d",int(min_o3_ppb/1000),int(min_o3_ppb%1000));
  myNex.writeStr("dl.sminppm.txt",TFT_string);
  
  sprintf(TFT_string,"%d",max_o3_ppb);
  myNex.writeStr("dl.smaxppb.txt",TFT_string);
  
  sprintf(TFT_string,"%.1f",max_o3_ug);
  myNex.writeStr("dl.smaxug.txt",TFT_string);
  
  if(max_o3_ppb<10)sprintf(TFT_string,"0.00%d",max_o3_ppb);
  if(10<=max_o3_ppb && max_o3_ppb<100)sprintf(TFT_string,"0.0%d",max_o3_ppb);
  if(100<=max_o3_ppb && max_o3_ppb<1000)sprintf(TFT_string,"0.%d",max_o3_ppb);
  if(1000 <= max_o3_ppb)sprintf(TFT_string,"%d.%d",int(max_o3_ppb/1000),int(max_o3_ppb%1000));
  myNex.writeStr("dl.smaxppm.txt",TFT_string);

  myNex.writeNum("dl.npm25.val",TFT_pm25);
  myNex.writeNum("dl.npm1.val",TFT_pm1);
  myNex.writeNum("dl.npm10.val",TFT_pm10);
  sprintf(TFT_string,"%d",TFT_pm1);
  myNex.writeStr("dl.spm1.txt",TFT_string);
  sprintf(TFT_string,"%d",TFT_pm25);
  myNex.writeStr("dl.spm25.txt",TFT_string);
  sprintf(TFT_string,"%d",TFT_pm10);
  myNex.writeStr("dl.spm10.txt",TFT_string);
  sprintf(TFT_string,"%d",max_pm25);
  myNex.writeStr("dl.maxpm25.txt",TFT_string);
  sprintf(TFT_string,"%d",min_pm25);
  myNex.writeStr("dl.minpm25.txt",TFT_string);

}
