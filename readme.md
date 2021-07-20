功能实现：

1. 串口调试利用宏实现局部串口功能调试，方便快速的定位出错地点
2. 引入操作系统，实现带缓冲区的信息发送与接收，保证不会存在数据的遗漏
3. 实现SDO字典配置功能，根据EPOS2 firmware pdf ，构建了字典结构体
4. 单电机中实现了5 ms间隔的PDO控制的位置模式，未发现明显的抖动
5. 柔性膝关节项目中实现了双电机电机的10 ms控制周期的稳定同步运行


缺点：
1. CAN发送需要延迟[不确定是否只能通过延迟才能保证]才能保证同步稳定运行，因此控制周期较长
2. 从控制指令到电机实际执行，存在几十毫秒的延迟，因此在实时控制的项目中，这是一大弊端


Function
1. Serial port debugging using macros to achieve partial serial port function debugging, which is convenient and help locate the error fast
2. The operating system is introduced to realize the sending and receiving of information with buffer to ensure that there will be no data omission 
3. CANOPEN dictionary structure is built to achieve the SDO dictionary configuration function, according to EPOS2 firmware PDF
4. The position mode controlled by PDO with an interval of 5 ms was realized in a single motor, and no obvious jitter was found. 
5. In the flexible knee joint project, the stable and synchronous operation of the dual-motor control cycle of 10 ms is realized

disadvantages
1. CAN transmission requires introducing delay [it is not sure whether it can only be guaranteed by delay] to ensure the stable and synchronous operation, so the control cycle is long. 
2. There is a delay of tens of milliseconds between the control instruction and the actual execution of the motor, which is a major drawback in real-time control application

