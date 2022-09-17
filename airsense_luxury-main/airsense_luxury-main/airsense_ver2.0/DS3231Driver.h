#include "RTClib.h"
#include <ESP32Ping.h>

const char* remote_host = "www.google.com";
RTC_DS3231 rtc;
char  TFT_time[16];


/**
 * @brief	Khoi tao module thoi gian thuc
 *
 * @return  None
 */
void DS3231_Init()
{
  rtc.begin();
  if (WiFi.status() == WL_CONNECTED){
    if (Ping.ping(remote_host)){
      timeClient.update();
      uint32_t epochTime = timeClient.getEpochTime();
      rtc.adjust(DateTime(epochTime));
      Serial.println("updatetimeDS3231");
    }
  }
    DateTime now = rtc.now();
#ifdef	DEBUG_SERIAL
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
#endif
}


/**
 * @brief	luu tru thoi gian thuc vao bien TFT_time
 *
 * @return  None
 */
void DS3231_GetData()
{
    DateTime now = rtc.now();
    if(now.hour()<10 && now.minute()<10){
      sprintf(TFT_time,"0%d:0%d  %d/%d/%d",int(now.hour()),int(now.minute()),int(now.day()),int(now.month()),int(now.year()%2000));
    }
    if(now.hour()>=10 && now.minute()<10){
      sprintf(TFT_time,"%d:0%d  %d/%d/%d",int(now.hour()),int(now.minute()),int(now.day()),int(now.month()),int(now.year()%2000));
    } 
    if(now.hour()<10 && now.minute()>=10){
      sprintf(TFT_time,"0%d:%d  %d/%d/%d",int(now.hour()),int(now.minute()),int(now.day()),int(now.month()),int(now.year()%2000));
    } 
    if(now.hour()>=10 && now.minute()>=10){
      sprintf(TFT_time,"%d:%d  %d/%d/%d",int(now.hour()),int(now.minute()),int(now.day()),int(now.month()),int(now.year()%2000));
    } 
    
#ifdef  DEBUG_SERIAL
      Serial.println(TFT_time);
#endif
}
