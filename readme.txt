这是一个基于FreeRTOS、Qt框架、TCP协议和STM32的温室大棚系统，以STM32F407ZGT6为下位机和Qt设计的应用程序为上位机。

STM32主控通过IO口外接DHT11温湿度传感器、土壤湿度传感器、超声波测距传感器、人体红外检测传感器、光照强度传感器、电机驱动排气扇、Wifi无线传输模块。下位机通过传感器感知环境，接收数据，通过Wifi模块传输到上位机。上位机通过和STM32建立TCP连接实现数据通信。上位机可显示数据，也可通过按钮或是发送指令的方式对下位机进行操控。

FreeRTOS文件夹是STM32F407ZGT6的源文件；GreenHouse文件夹是上位机的源文件。
下位机的编程环境是Keil 5 MDK；上位机是Visual Studio 2022 + Qt tools拓展。




This is a greenhouse greenhouse system based on FreeRTOS, Qt framework, TCP protocol, and STM32, with STM32F407ZGT6 as the lower computer and Qt designed application program as the upper computer.

The STM32 main control is connected to the DHT11 temperature and humidity sensor, soil humidity sensor, ultrasonic distance measurement sensor, human infrared detection sensor, light intensity sensor, motor driven exhaust fan, and WiFi wireless transmission module through the IO port. The lower computer senses the environment through sensors, receives data, and transmits it to the upper computer through WiFi modules. The upper computer establishes a TCP connection with STM32 to achieve data communication. The upper computer can display data, and can also control the lower computer through buttons or sending instructions.

The FreeRTOS folder is the source file for STM32F407ZGT6; The GreenHouse folder is the source file for the upper computer.
The programming environment for the lower computer is Keil 5 MDK; The upper computer is an extension of Visual Studio 2022+Qt tools.