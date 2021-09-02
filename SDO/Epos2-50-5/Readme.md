# 简介

本项目采用stm32单片机控制电机。

针对stm32F103系列的，电机驱动器为EPOS2 50-5

![SDO1](D:\10-Chip_learning\0-硬件\3-motor\0-MOTOR controller\Epos2-50-5\SDO1.png)

![SDO2](D:\10-Chip_learning\0-硬件\3-motor\0-MOTOR controller\Epos2-50-5\SDO2.png)

![SDO3](D:\10-Chip_learning\0-硬件\3-motor\0-MOTOR controller\Epos2-50-5\SDO3.png)



纯手写实现SDO控制代码，目前可以实现：

    * SDO速度模式控制
    
    * SDO位置模式控制： 



# TODO

引入CANOpen库，实现PDO控制方式
