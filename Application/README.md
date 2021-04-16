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
**Handling GRO is a five degrees of freedom robot. This is an academic project by robotics engineering undergraduates at l'Université de Sherbrooke.**

<div id="platform" align="center">
    <img src="https://github.com/chameau5050/Handling-Gro/blob/create_new_read_me/Documentation/image/HandlingGRO.png" alt="Robot Assembly" width="703"/>
</div>

## Table of Contents
- [Authors](#Authors)
- [Setup](#Setup)
- [Documentation](#Documentation)
- [Platform Operation](#Operation)
- [Recommended manufacturing device](#Recommended_device)
- [External Resources](#Resources)
    - [Single-Board Computer](#Computer)
    - [Microcontroller](#Controller)
    - [Dynamixel motors](#dynamixel) 
    - [Steppermotor](#StepperMotor)
    - [DriveBoard (with steppermotor)](#DriveBoard)
    - [Servomotor](#ServoMotor)
    - [Power Supply: Motor/(OpenCr or Arduino)](#Power)
    - [Linear Rods](#Rods)
    - [linear_bearing](#linear_bearing)
- [License](#License)

AJOUTER AUSSI LES DIFFERENTS LIENS QUE J AI EN BAS CAR IL NE FIGURE PAS ICI
    
[//]: # (------------------------------------------------)
## <a id="Authors"></a>Authors
- Olivier Demers - _Initial work_ - [chameau5050](https://github.com/chameau5050)
- Jérémy Giguère - _Initial work_ - [gigj1302](https://github.com/gigj1302)
- Philippe Gadeyne - _Initial work_ - 
- Francis Amyot - _Initial work_ 
- Vincent-Xavier Voyer - _Initial work_ - 
METTRE LE LIEN VERS LA PHOTO DES MEMBRES DE L'ÉQUIPE DU PROJET


## <a id="Setup"></a>Setup
mettre a jour les numeros!!!!
Mettres a jour les lien pour les taches built and transfert code to OpenCr
Mettres a jour les lien pour les taches built and transfert code to Raspberry Pi

1. Buy the component in the [External Resources](#Resources) section.
2. Use the [CAD models](https://github.com/chameau5050/Handling-Gro/tree/main/Mechanical/STL%20(For%203D%20printing)) to 3D print all the different parts of the robot.
3. Assemble the robot according to the [assembly guide](https://github.com/chameau5050/Handling-Gro/).
4. Do the electrical connections using the [electrical schematics](https://github.com/chameau5050/Handling-Gro/) in the documentation section.
4. Set up the [Raspberry Pi](#Computer) by connecting it with the [OpenCr](#Controller_OpenCr), your computer and the to a power source.
5. Download or clone the repository in the Raspberry Pi.
6. Verify your Python version (3.5 and above) and the port series.
7. Build and transfer all the code to the OpenCr (or Arduino). See [Compilation procedure](https://github.com/chameau5050/Handling-Gro/) documentation.
8. Build and transfer all the code to Raspberry Pi. See [Compilation procedure](https://github.com/chameau5050/Handling-Gro/) documentation.
8. Open the interface and look your new Handgling GRO robot in action.
8. Congigure UI with Qt????
9. For more information, see the [documentation]((#Documentation)) section
## <a id="Documentation"></a>Documentation

All the different information is available [here](https://github.com/chameau5050/Handling-Gro/wiki) in the project wiki.

## <a id="Operation"></a>Robot Operation
-TODO

## <a id="Recommended_device"></a>Recommended manufacturing device
The following rapid design devices are required for this project are:
- For plastic part 
  - 3D Printer
  
- For wood part (choose one of the 2 following choices) 
  - Laser cutter
  - Basic tools for wood (drill, saw, sand paper, ...)

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

#### <a id="Controller_Arduino"></a>Microcontroller (optional)
- Brand: [Arduino](https://store.arduino.cc/mega-2560-r3)
- Model: Mega 2560 REV3
- Quantity: 1
- **If you want to use other motors than dynamixel motors.

#### <a id="dynamixel"></a>Dynamixel_motors
- Brand: [Dynamixel](https://www.robotis.us/dynamixel-xm430-w350-r/)
- Model: XM430-W350
- Quantity: 4

#### <a id="SteperMotor"></a>Stepermotor
- Brand: [Elegoo](https://www.elegoo.com/products/elegoo-uln2003-5v-stepper-motor-uln2003-driver-board)
- Model: 28BYJ-48 
- Quantity: 1

#### <a id="DriveBoard"></a>DriveBoard (with steppermotor)
- Brand: [Elegoo](https://www.elegoo.com/products/elegoo-uln2003-5v-stepper-motor-uln2003-driver-board)
- Model: ULN2003 
- Quantity: 1

#### <a id="ServoMotor"></a>Servomotor
- Brand: [Miuzei](https://www.amazon.ca/-/fr/Miuzei-num%C3%A9rique-%C3%A9tanche-voiture-contr%C3%B4le/dp/B07MDM1C3M)
- Model: Miuzei Servo Motor 20 Kg
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
