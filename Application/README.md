<div id="Handling GRO!">
    <h1>Handling GRO</h1>
    <h3>Projet S4 Université de Sherbrooke</h3>
    <h3>UdeS-GRO | 65<sup>th</sup> Promotion | 2021</h3>
</div>

[//]: # (------------------------------------------------)

<div id="badges">
    

[![License: GPL-3.0](https://img.shields.io/badge/License-GPLv3-blue.svg?style=flat-square)](https://github.com/chameau5050/Handling-Gro/main/LICENSE) 

</div>

[//]: # (------------------------------------------------)

**This is an academic project by robotics engineering undergraduates at Université de Sherbrooke.**
**Handling GRO is a five degrees of freedom fanuc robot. This is an academic project by robotics engineering undergraduates at l'Université de Sherbrooke.**

<div id="platform" align="center">
    <img src="./Documentation/img/HandlingGRO.png" alt="Robot Assembly" width="703"/>
</div>

## Table of Contents
- [Setup](#Setup)
- [Documentation](#Documentation)
- [Platform Operation](#Operation)
- [Authors](#Authors)
- [External Resources](#Resources)
    - [Single-Board Computer](#Computer)
    - [Microcontroller](#Controller)
    - [Servomotors](#Servo)
    - [Power Supply: Motor/Arduino](#Power)
    - [Servo Rods](#Rods)


    
[//]: # (------------------------------------------------)

## <a id="Setup"></a>Setup
1. Buy the component in the [External Resources](#Resources) section.
2. Use the [CAD models](https://github.com/chameau5050/Handling-Gro/tree/main/Mechanical/STL%20(For%203D%20printing)) to 3D print all the different parts of the robot.
3. Do the electrical connections using the [electrical schematics](https://github.com/chameau5050/Handling-Gro/) in the documentation section.
4. Set up the [Raspberry Pi](#Computer) by connecting it with the [OpenCr](#Controller_OpenCr), your computer and the to a power source.
5. Download or clone the repository in the Raspberry Pi.
6. Verify your Python version (3.5 and above) and the port series.
7. Build and transfer all the code to the OpenCr (or Arduino) and Raspberry Pi.
8. Open the interface and look your new Handgling GRO robot in action.
9. For more information, see the [documentation]((#Documentation)) section
## <a id="Documentation"></a>Documentation

All the different information is available [here](https://github.com/chameau5050/Handling-Gro/wiki) in the project wiki.
## <a id="Operation"></a>Robot Operation
-TODO

## <a id="Authors"></a>Authors
- Olivier Demers - _Initial work_ - [chameau5050](https://github.com/chameau5050)
- Jérémy Giguère - _Initial work_ - [gigj1302](https://github.com/gigj1302)
- Philippe Gadeyne - _Initial work_ - 
- Francis Amyot - _Initial work_ 
- Vincent-Xavier Voyer - _Initial work_ - 


## <a id="Resources"></a>External Resources
This section specifies the external resources used in the project.

#### <a id="Computer"></a>Single-Board Computer
- Brand: [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-3-model-b-plus/)
- Model: Raspberry Pi 3 Model 3B+
- Quantity: 1

#### <a id="Controller_OpenCr"></a>Microcontroller
- Brand: [OpenCr](https://store.arduino.cc/mega-2560-r3)
- Model: OpenCr
- Quantity: 1

#### <a id="Controller"></a>Microcontroller (optional)
- Brand: [Arduino](https://store.arduino.cc/mega-2560-r3)
- Model: Mega 2560 REV3
- Quantity: 1
- **If you want to use other motors than dynamixel motors.

<!--#### <a id="Servo"></a>Servomotors
- Brand: [Hitec RCD](https://hitecrcd.com/products/servos/sport-servos/analog-sport-servos/hs-422/product)
- Model: HS-422
- Quantity: 6
-->
#### <a id="dynamixel"></a>Dynamixel_motors
- Brand: [Dynamixel](https://www.robotis.us/dynamixel-xm430-w350-r/)
- Model: XM430-W350
- Quantity: 4

#### <a id="SteperMotor"></a>SteperMotors
- Brand: [Elegoo](https://www.elegoo.com/products/elegoo-uln2003-5v-stepper-motor-uln2003-driver-board)
- Model: 28BYJ-48 
- Quantity: 1

#### <a id="ServoMotor"></a>ServoMotors
- Brand: [a changer_Elegoo](https://www.elegoo.com/products/elegoo-uln2003-5v-stepper-motor-uln2003-driver-board)
- Model: 28BYJ-48 : change pour le bon modèle
- Quantity: 1

#### <a id="DriveBoard"></a>DriveBoard
- Brand: [Elegoo](https://www.elegoo.com/products/elegoo-uln2003-5v-stepper-motor-uln2003-driver-board)
- Model: ULN2003 
- Quantity: 1
<!--
#### <a id="info"></a>exemple pour le commenter
- Brand: [Adafruit](https://www.amazon.ca/Adafruit-2201-Sub-micro-Servo-SG51R/dp/B0137LG0KW)
- Model: SG51R
- Quantity: 6
-->
#### <a id="Power"></a>Power Supply: Motor/(OpenCr or Arduino)
- Brand: [PowerPayless Inc](https://www.amazon.com/7-5A-Power-Adapter-Device-Payless/dp/B01CYZWAWY)
- Model: B01CYZWAWY (65107)
- Quantity: 1

#### <a id="Rods"></a> Linear Rods
- Brand: [yqltd](https://www.amazon.ca/CNBTR-Horizontal-Bearing-Bushing-Optical/dp/B01KLE9QEU)
- ASIN: CNBTR4040 road
- Quantity: 2

#### <a id="linear_bearing"></a> Linear bearing
- Brand: [yqltd](https://www.amazon.ca/CNBTR-Horizontal-Bearing-Bushing-Optical/dp/B01KLE9QEU)
- ASIN: CNBTR4040 bearing
- Quantity: 4


## <a id="License"></a>License
This project is licenced under a  [![GPL-3.0](https://img.shields.io/badge/License-GPLv3-blue.svg?style=flat-square)](https://github.com/chameau5050/Handling-Gro/blob/main/LICENSE) license.
