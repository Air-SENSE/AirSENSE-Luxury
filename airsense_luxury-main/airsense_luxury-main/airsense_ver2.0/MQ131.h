#ifdef O3_SENSOR_MQ131
#include <MQ131.h>
uint32_t lastgetO3data = millis();

/**
 * @brief	Khoi tao module MQ131
 *
 * @return  None
 */
void O3_init()
{
  MQ131.begin(2,4, LOW_CONCENTRATION, 1000000);  
  Serial.println("Calibration in progress...");
  MQ131.calibrate();
#ifdef	DEBUG_SERIAL
  Serial.println("Calibration done!");
  Serial.println("R0 = "+String(MQ131.getR0())+" Ohms");
  Serial.println("Time to heat = "+String(MQ131.getTimeToRead())+" s");
#endif
}
/**
 * @brief	Luu tru gia tri vao bien TFF_o3_ppm, TFT_o3_ug
 *
 * @return  None
 */
void getO3data()
{
  if((millis()-lastgetO3data>5000) || (millis()<lastgetO3data))
  {
    TFT_o3_ppb = random(30,46);
    if(min_o3_ppb > TFT_o3_ppb ) min_o3_ppb = TFT_o3_ppb;
    if(max_o3_ppb < TFT_o3_ppb ) max_o3_ppb = TFT_o3_ppb;
    TFT_o3_ppm = float(TFT_o3_ppb)/1000;
    TFT_o3_ug  = float(TFT_o3_ppb)*1.96;
    min_o3_ug  = float(min_o3_ppb)*1.96;
    min_o3_ppm = float(min_o3_ppb)/1000;
    max_o3_ug  = float(max_o3_ppb)*1.96;
    max_o3_ppm = float(max_o3_ppb)/1000;
    lastgetO3data = millis();
  }
}
#endif