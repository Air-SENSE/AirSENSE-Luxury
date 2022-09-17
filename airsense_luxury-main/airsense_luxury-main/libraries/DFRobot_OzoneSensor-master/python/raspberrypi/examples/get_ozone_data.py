# -*- coding:utf-8 -*-
'''!
  @file get_ozone_data.py
  @brief Reading ozone concentration, A concentration of one part per billion (PPB).
  @n step: we must first determine the iic device address, will dial the code switch A0, A1 (OZONE_ADDRESS_0 for [0 0]), (OZONE_ADDRESS_1 for [1 0]), (OZONE_ADDRESS_2 for [0 1]), (OZONE_ADDRESS_3 for [1 1]).
  @n       Then configure the mode of active and passive acquisition, Finally, ozone data can be read.
  @n note: it takes time to stable oxygen concentration, about 3 minutes.
  @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license The MIT License (MIT)
  @author [ZhixinLiu](zhixin.liu@dfrobot.com)
  @version V1.0
  @date 2020-5-27
  @url https://github.com/DFRobot/DFRobot_Ozone
'''
import sys
import time
sys.path.append("../")
from DFRobot_Ozone import *

COLLECT_NUMBER   = 20              # collect number, the collection range is 1-100
IIC_MODE         = 0x01            # default use IIC1

'''
   The first  parameter is to select i2c0 or i2c1
   The second parameter is the i2c device address
   The default address for i2c is OZONE_ADDRESS_3
      OZONE_ADDRESS_0        0x70
      OZONE_ADDRESS_1        0x71
      OZONE_ADDRESS_2        0x72
      OZONE_ADDRESS_3        0x73
'''
ozone = DFRobot_Ozone_IIC(IIC_MODE ,OZONE_ADDRESS_3)
'''
  The module is configured in automatic mode or passive
    MEASURE_MODE_AUTOMATIC  active  mode
    MEASURE_MODE_PASSIVE    passive mode
''' 
ozone.set_mode(MEASURE_MODE_AUTOMATIC)
while(1):
  ''' Smooth data collection the collection range is 1-100 '''
  ozone_concentration = ozone.get_ozone_data(COLLECT_NUMBER)
  print("Ozone concentration is %d PPB."%ozone_concentration)
  time.sleep(1)