# DFRobot_OzoneSensor
- [English Version](./README.md)

这是一款体积小巧的arduino兼容的臭氧传感器模组,可方便、准确地测量环境中臭氧气体的浓度。可广泛应用于便携式仪器仪表、空气质量监测设备、消毒柜、智能家居等设备场所。<br>

![效果图](resources/images/SEN0321.jpg)

## 产品链接(https://www.dfrobot.com.cn/goods-2672.html)

    SKU：SEN0321

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性y)
* [历史](#历史)
* [创作者](#创作者)

## 概述

- DFRobot推出的臭氧传感器采用电化学原理,出厂前已经过校准,可以准确测量环境中的臭氧浓度。<br>
- 并具有抗干扰、高稳定性、高灵敏度等特点。 <br>
- 分辨率可达10ppb<br>
- 支持3.3~5.5V宽电压输入<br>
- 使用 I2C 输出<br>
- 兼容Arduino、ESP32、Raspberry Pi等主流设备<br>
- 空气中使用寿命长达两年<br> 

## 库安装
这里提供两种使用本库的方法：<br>
1.打开Arduino IDE,在状态栏中的Tools--->Manager Libraries 搜索"DFRobot_OzoneSensor"并安装本库.<br>
2.首先下载库文件,将其粘贴到\Arduino\libraries目录中,然后打开examples文件夹并在该文件夹中运行演示.<br>

## 方法

```C++
 /**
   * @fn begin
   * @brief 初始化函数 
   * @param i2c 地址
   * @n     OZONE_ADDRESS_0  0x70
   * @n     OZONE_ADDRESS_1  0x71
   * @n     OZONE_ADDRESS_2  0x72
   * @n     OZONE_ADDRESS_3  0x73
   * @return bool 类型
   * @retval true 初始化成功
   * @retval false 初始化失败
   */
  bool begin(uint8_t addr = OZONE_ADDRESS_0);

  /**
   * @fn setModes
   * @brief 设置主动模式或被动模式
   * @param mode 
   * @n       MEASURE_MODE_AUTOMATIC   主动测量
   * @n       MEASURE_MODE_PASSIVE     问答测量
   * @return None
   */
  void setModes(uint8_t mode);

  /**
   * @fn readOzoneData
   * @brief 读取臭氧浓度
   * @param collectNum is 平滑数据参数,默认采集个数20
   * @n       COLLECT_NUMBER       采集个数
   * @return 臭氧浓度 ,单位(PPB).
   */
  int16_t readOzoneData(uint8_t collectNum = 20);
```

## 兼容性

| 主板        | 通过 | 未通过 | 未测试 | 备注 |
| ----------- | :--: | :----: | :----: | ---- |
| Arduino uno |  √   |        |        |      |
| Mega2560    |  √   |        |        |      |
| Leonardo    |  √   |        |        |      |
| ESP32       |  √   |        |        |      |
| micro:bit   |      |        |   √    |      |


## 历史

- 2019/10/10 - V1.0.0 版本

## 创作者

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))
