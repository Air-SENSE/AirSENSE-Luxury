# DFRobot_OzoneSensor
- [中文版](./README_CN.md)

This is a compact arduino compatible ozone sensor module that can easily and accurately measure the concentration of ozone gas in the environment. <br>
It can be widely used in portable instruments, air quality monitoring equipment, disinfection cabinets, smart homes and other equipment places. <br>

![效果图](resources/images/SEN0321.jpg)


## Product Link(https://www.dfrobot.com/product-2005.html)

    SKU：SEN0321

## Table of Contents

* [Summary](#Summary)
* [Installation](#Installation)
* [Methods](#Methods)
* [Compatibility](#Compatibility)
* [History](#History)
* [Credits](#Credits)

## Summary
- The ozone sensor launched by DFRobot adopts the principle of electrochemistry and has been calibrated before leaving the factory, which can accurately measure the ozone concentration in the environment.<br>
- And it has the characteristics of anti-interference, high stability and high sensitivity. <br>
- The resolution can reach 10ppb<br>
- support 3.3~5.5V wide voltage input<br>
- use I2C output<br>
- compatible with mainstream devices such as Arduino, ESP32, Raspberry Pi, etc<br>
- the service life in the air is up to two years<br>

## Installation
There are two methods for using this library:<br>
1. Open Arduino IDE, search for "DFRobot_OzoneSensor" on the status bar in Tools ->Manager Libraries and install the library.<br>
2. Download the library file before use, paste it into \Arduino\libraries directory, then open the examples folder and run the demo in the folder.<br>

## Methods

```C++
  /**
   * @fn begin
   * @brief initialization function 
   * @param i2c address
   * @n     OZONE_ADDRESS_0  0x70
   * @n     OZONE_ADDRESS_1  0x71
   * @n     OZONE_ADDRESS_2  0x72
   * @n     OZONE_ADDRESS_3  0x73
   * @return bool type
   * @retval true initialization success
   * @retval false initialization failed
   */
  bool begin(uint8_t addr = OZONE_ADDRESS_0);

  /**
   * @fn setModes
   * @brief Set mode Active or passive measurement.
   * @param mode mode is Active or passive.
   * @n       MEASURE_MODE_AUTOMATIC    active  mode
   * @n       MEASURE_MODE_PASSIVE      passive mode
   * @return None
   */
  void setModes(uint8_t mode);

  /**
   * @fn readOzoneData
   * @brief read ozone data.
   * @param collectNum is the number of data collected,(The default value is 20)
   * @n       COLLECT_NUMBER       The collection range is 1-100
   * @return ozone concentration: one part per billion (PPB).
   */
  int16_t readOzoneData(uint8_t collectNum = 20);
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | :----:
Arduino Uno        |      √       |              |             |
Arduino MEGA2560   |      √       |              |             |
Arduino Leonardo   |      √       |              |             |
FireBeetle-ESP32   |      √       |              |             |
Micro:bit          |              |              |      √      |


## History

- 2019/10/10 - V1.0.0 Version

## Credits

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))
