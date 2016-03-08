# Get Start
This repository is for ZeroPi libraries and example code.

This library is v1.0.0, it is build on 2016/03/05. If you have any comments you can contact on Pull requests or send mail to myan@makeblock.cc.

How to use:

Install the driver and package as introduction <01 Introduction to ZeroPi and Driver Installation EN.pdf> in path https://github.com/ZeroPiProject/ZeroPi_lib/tree/master/Instruction/English
Download the source from the git https://github.com/ZeroPiProject/ZeroPi_lib
copy the ZeroPi folder to your arduino default library. Your Arduino library folder should now look like this
(on Windows): [arduino installation directory]\libraries\ZeroPi\src
(On MACOS): [arduino Package Contents]\contents\Jave\libraries\ZeroPi\src
Open the Arduino Application. (If it's already open, you will need to restart it to see changes.)
Click "File-> Examples". Here are some test programs in ZeroPi-> example.

-----------------

# ZeroPi
ZeroPi is an Arduino Zero Compatible development kit for robotic motion structure systems. It uses Atmel SAMD21J18, 32-bit ARM Cortex M0+ as the MCU, which is fully compatible with the official Arduino Zero, Raspberry Pi and with more hardware resources dedicate for robot drive. ZeroPi can be applied to all kinds of application scenes such as 3D printer, tracked mobile robot and etc

ZeroPi is based on official arduino zero but changed the mcu to SAMD21J18 to support more io pins.

![](http://i.imgur.com/v8Zns1a.png)

ZeroPi size

![](http://i.imgur.com/QMah5YA.png)
# Resource

Raspberry compatable plugin port

4 x SLOTs: stepper, dc-motor

2 x mosfet driver

2 x temperature sensor input

11 x extension genernal io or servo driver

# The CMSIS-DAP debugger
![](http://i.imgur.com/Xu6gvPG.png)
# Powerful Motor Driver Modules
ZeroPi can control 11 micro servos and 8 DC motors at the same time (or 4 stepper motors). The 4-channel SLOT module is compatible with common stepper motor and DC motor drivers (such as DRV8825 or A4988 Stepper motor driver and TB6612 DC motor driver). It also support the opens-source sensors.

Control 8 DC motors and 11 micro servos
![](http://i.imgur.com/t6cK1ZC.gif)

Control 4 stepper motors and 11 micro servos

![](http://i.imgur.com/6o5QVsD.gif)



# Technical Specs

![](http://i.imgur.com/XcjDVrn.jpg)

![](http://i.imgur.com/kxzg2lp.jpg)
# Arduino Compatible

ZeroPi is an Arduino zero compatible board. It is based on ATSAMD21G18, 32-Bit ARM Cortex M0+ microcontroller (Arduino zero CPU). This represent a big step towards greater computing power when compared to the existing solution based on 8-bit MCU. ZeroPi can be programmed using the Arduino IDE, giving you access to a wide range of easy to use libraries. The example codes will be provided for ZeroPi specific functions such as encoder readout and temperature monitoring.

Arduino IDE Programming

![](http://i.imgur.com/3vPIVoa.png)
# Raspberry Pi Compatible

By simply connecting Raspberry Pi to ZeroPi (just plug in the RPI connector), you will discover countless features, such as full tablet control, wireless control, Bluetooth and much more. You can install a web interface to control the motors and servos directly. It even can achieve interface with Java Script.

ZeroPi with Raspberry Pi

![](http://i.imgur.com/ymk4XEn.jpg)

![](http://i.imgur.com/6gnuXR4.gif)



--------






