# DFRobot_OzoneSensor
- [English Version](./README.md)

这是一款体积小巧的arduino兼容的臭氧传感器模组,可方便、准确地测量环境中臭氧气体的浓度。可广泛应用于便携式仪器仪表、空气质量监测设备、消毒柜、智能家居等设备场所。<br>

![正反面svg效果图](../../resources/images/SEN0321.jpg)

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
使用此库前,请首先下载库文件,将其粘贴到树莓派的自定义目录中,然后打开examples文件夹并在该文件夹中运行演示。<br>

## 方法

```python
  '''!
    @brief 设置模式
    @param MEASURE_MODE_AUTOMATIC  主动模式
    @param MEASURE_MODE_PASSIVE    问答模式
  '''
  def set_mode(self ,mode):

  '''!
    @brief 获取臭氧浓度
    @param 平滑数据的个数
    @return 臭氧浓度 (单位 PPB)
  '''
  def get_ozone_data(self ,collectnum):

```

## 兼容性

* RaspberryPi Version

| Board        | 正常运行  | 运行失败   | 未测试    | 备注
| ------------ | :-------: | :--------: | :------: | :-----: |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python版本

| Python  | 正常运行  | 运行失败   | 未测试    | 备注
| ------- | :-------: | :--------: | :------: | :-----: |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## 历史

- 2020/5/27 - V1.0.0 版本

## 创作者

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))