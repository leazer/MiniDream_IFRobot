# MiniDream IFRobot
## IFRobot Remote

当时因为项目需要有个用无线串口通讯的多通道遥控器，所以遥控器这部分是我在参加RTT“造车”活动之前就制作了的，当然也就是我选择作为IFRobot遥控的原因。
### 简介
首先是遥控器的外壳了，我是从淘宝上找的一款，它有6个模拟量通道和5个按键，可以说是很丰富了。
![遥控器](https://img.alicdn.com/imgextra/i4/24574358/TB2JyxqXbFkpuFjy1XcXXclapXa_!!24574358.png)

基于这款遥控器外壳，对遥控器的硬件及软件功能架构进行了设计：
![遥控器硬件导图.png](https://ws1.sinaimg.cn/large/a0a22756ly1g6oj2yrr3gj21fg0uu17d.jpg)
电路图纸和代码均开源咯，不过代码写的比较乱，而且不是很完善，谨慎参考。。。
![遥控器PCB.png](https://ws1.sinaimg.cn/large/a0a22756ly1g6oj5zmljhj21gz0pndlv.jpg)


### 通讯定义
数据帧总长20字节，由帧头、6个模拟通道、按键、鼠标信息、键盘信息构成，帧定义如下：
| 字节序 | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | 10   | 11   | 12   | 13   | 14   | 15   | 16   | 17       | 18       | 19       | 20       |
| ------ | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | -------- | -------- | -------- | -------- |
| 帧定义 | 帧头 | CH0H | CH0L | CH1H | CH1L | CH2H | CH2L | CH3H | CH3L | CH4H | CH4L | CH5H | CH5L | CH6H | CH6L | KEY  | mouse.xH | mouse.xL | mouse.yH | mouse.yL |
所选遥控器的按键分布图
![遥控对应图.png](https://ws1.sinaimg.cn/large/a0a22756ly1g6ojp08054j20g20b4weu.jpg)
#### CH通道范围值
| 最小值 | 中间值 | 最大值 |
| ------ | ------ | ------ |
| 0      | 1024   | 2048   |
#### KEY对应值
| 按键名 | 值   |
| ------ | ---- |
| key0   | 0x80 |
| key1   | 0x40 |
| key2   | 0x20 |
| key3   | 0x10 |
| key4   | 0x08 |