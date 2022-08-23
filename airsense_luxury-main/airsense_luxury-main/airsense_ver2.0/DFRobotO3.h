#ifdef O3_SENSOR_DF_ROBOT

#define COLLECT_NUMBER   20              // collect number, the collection range is 1-100
#define Ozone_IICAddress ADDRESS_3
/*   iic slave Address, The default is ADDRESS_3
       ADDRESS_0               0x70      // iic device address
       ADDRESS_1               0x71
       ADDRESS_2               0x72
       ADDRESS_3               0x73
*/
DFRobot_OzoneSensor Ozone;uint32_t lastgetO3data = millis();

/**
 * @brief	Khoi tao module Ozone
 *
 * @return  None
 */
void O3_init()
{
  if(!Ozone.begin(Ozone_IICAddress)) 
  {
#ifdef	DEBUG_SERIAL
    Serial.println("I2c device number error !");
#endif
  }  
#ifdef	DEBUG_SERIAL
    Serial.println("I2c connect success !");
#endif
  Ozone.SetModes(MEASURE_MODE_PASSIVE);

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
    TFT_o3_ppb = Ozone.ReadOzoneData(COLLECT_NUMBER);
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