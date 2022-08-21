#pragma once
#include <Arduino.h>
#include "DFRobot_OzoneSensor.h"
#include "config.h"
// init OzoneSensor
DFRobot_OzoneSensor Ozone;


int TFT_ozone = 0;

void Ozone_init()
{
    while (!Ozone.begin(Ozone_IICAddress))
    {
        Serial.println("I2c device number error !");
        delay(1000);
    }
    Serial.println("I2c connect success !");
    /*   Set iic mode, active mode or passive mode
           MEASURE_MODE_AUTOMATIC            // active  mode
           MEASURE_MODE_PASSIVE              // passive mode
    */
    Ozone.setModes(MEASURE_MODE_PASSIVE);
}

float get_OzoneData()
{
    float ozoneConcentration = (float)Ozone.readOzoneData(COLLECT_NUMBER)/1000.0;
    return ozoneConcentration;
}

void setCalib_Ozone(int a_ozone_input, int b_ozone_input)
{
    a_ozoneConcentration_Calib = a_ozone_input;
    b_ozoneConcentration_Calib = b_ozone_input;
}

int16_t calib_OzoneData()
{
    float ozoneConcentration = (float)Ozone.readOzoneData(COLLECT_NUMBER)/1000.0;
    TFT_ozone = a_ozoneConcentration_Calib * ozoneConcentration + b_ozoneConcentration_Calib;
    return TFT_ozone;
}
