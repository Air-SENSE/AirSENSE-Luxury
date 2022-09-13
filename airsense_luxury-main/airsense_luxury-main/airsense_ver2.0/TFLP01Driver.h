#include "config.h"
uint32_t TFLP01_pm10sum 	= 0;
uint32_t TFLP01_pm25sum 	= 0;
uint32_t TFLP01_pm1sum 		= 0;
int 	 dataTFLP01count 	= 0;
bool 	 TFLP01_read 		= false;
int 	 TFT_pm1			= 0;
int 	 TFT_pm25			= 0;
int 	 TFT_pm10			= 0;
int 	 max_pm25			= 0;
int 	 min_pm25			= 1000;

/**
 * @brief  Return CRC trong data response của TF-LP-01
 *
 * @return  None
 */
uint16_t crc16_modbus(uint8_t *modbusdata , uint16_t Length) 
{
  uint16_t i, j;
  uint16_t crc16 = 0xFFFF;
  for (i = 0; i < Length; i++)
  {
    crc16 ^= modbusdata[i];
    for (j = 0; j < 8; j++)
    {
      if ((crc16 & 0x01) == 1) crc16 = (crc16 >> 1) ^ 0xA001; 
      else
      crc16 >>= 1;
     }
  }
  return crc16;
}
/**
 * @brief Setup TF-LP-01
 *
 * @return  None
 */
void TFLP01_Init()
{
    Serial2.begin(115200);
}
/**
 * @brief Doc du lieu tu cam bien bui
 *
 * @return  None
 */
void TFLP01_GetData()
{
  uint8_t TFLP01data[17] = {0};
  if (Serial2.available() > 0) 
  {  
    Serial.println("Check");
    for(uint8_t i=0; i<17; i++)
    {
      Serial.print(i);
      Serial.print(": ");
      byte tmp = Serial2.read();
      TFLP01data[i] = tmp;
      Serial.println(tmp);
    }
    
      TFLP01_read = true;
  }
//  while(Serial2.available() > 0) Serial2.read();
//      Serial.println(TFLP01data[15] + TFLP01data[16]<<8 );
//      Serial.println(crc16_modbus(TFLP01data, 15));
//    if (TFLP01data[15] + TFLP01data[16]<<8 == crc16_modbus(TFLP01data, 15))
//    {
//    }
  
  // lay du lieu tam thoi (chua co datasheet)
  if(TFLP01_read == true)
  {
    TFLP01_read = false;
    TFT_pm1  = TFLP01data[9]+TFLP01data[10]*256+pm1CalibInt;
    TFT_pm25 = TFLP01data[11]+TFLP01data[12]*256+pm25CalibInt;
    TFT_pm10 = TFLP01data[13]+TFLP01data[14]*256+pm10CalibInt;
    if(TFT_pm25!=255)
    {
      if(max_pm25 < TFT_pm25) max_pm25=TFT_pm25;
      if(min_pm25 > TFT_pm25) min_pm25=TFT_pm25;
    } 
#ifdef  DEBUG_SERIAL

    for(uint8_t i=0; i<17; i++)
    {
      Serial.print(i);
      Serial.print(": ");
      Serial.println(TFLP01data[i]);
    }
    Serial.println("Pm2.5:"+String(TFT_pm25)+" Pm10:"+String(TFT_pm10));

#endif
  }  
}
