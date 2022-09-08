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
 * @brief	Doc du lieu tu cam bien bui
 *
 * @return  None
 */
void TFLP01_GetData()
{
  uint8_t TFLP01data[17] = {0};
  while (Serial.available() > 0) 
  {  
    for(uint8_t i=0; i<17; i++) TFLP01data[i] = Serial.read();
    TFLP01_read = true;
  }
  // lay du lieu tam thoi (chua co datasheet)
  if(TFLP01_read == true){
    TFLP01_read = false;
   // Serial.println("Pm2.5:"+String(TFLP01data[11])+" Pm10:"+String(TFLP01data[13]));
    TFT_pm25 = TFLP01data[13]+pm25CalibInt;
    TFT_pm10 = TFLP01data[15]+pm10CalibInt;
    TFT_pm1  = TFLP01data[11]+pm1CalibInt;
    if(TFT_pm25!=255){
    if(max_pm25 < TFT_pm25) max_pm25=TFT_pm25;
    if(min_pm25 > TFT_pm25) min_pm25=TFT_pm25;
  } 
  }  
}
