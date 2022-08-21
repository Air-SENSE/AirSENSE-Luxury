#include "SHTSensor.h"
#include "config.h"
//#include "TFT.h"
//#include "SDcard.h"
SHTSensor sht(SHTSensor::SHT3X);

uint32_t lastReadSHT = 0;
//float temp_calib = 0;
//float humi_calib = 0;
float TFT_temp = 0;
float TFT_temp_F = 0;
float TFT_humi = 0;

void SHT85_init()
{
  Wire.begin();
  delay(1000);                   // let serial console settle


  if (sht.init()) {
    Serial.print("init(): Sucessed!\n");
  } else {
    Serial.print("init(): Failed!\n");
  }


  sht.setAccuracy(SHTSensor::SHT_ACCURACY_MEDIUM);     // only supported by SHT3x
}

float get_SHTdata_temp()
{
  if (sht.readSample())
  {
    TFT_temp = sht.getTemperature();
    TFT_humi = sht.getHumidity();
  }

  return TFT_temp;
}

float get_SHTdata_humi()
{
  if (sht.readSample())
  {
    TFT_temp = sht.getTemperature();
    TFT_humi = sht.getHumidity();
  }
  return TFT_humi;
}
// set calib
void setCalib_SHT85(float a_temp, float b_temp, float a_humi, float b_humi)
{
  a_tempCalib = a_temp;
  b_tempCalib = b_temp;
  a_humiCalib = a_humi;
  b_humiCalib = b_humi;
}
// calibrate

float calib_temp_SHT85data()
{
  // initialized to 0
  float sht_temp = 0;
  if (sht.readSample())
  {
    sht_temp = sht.getTemperature();
    TFT_temp = a_tempCalib * sht_temp + b_tempCalib;
    return TFT_temp;
  }
}

float calib_humi_SHT85data()
{
  // initialized to 0
  float sht_humi = 0;
  if (sht.readSample())
  {
    sht_humi = sht.getHumidity();
    TFT_humi = a_humiCalib * sht_humi + b_humiCalib;
    return TFT_humi;
  }
}
