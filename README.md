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

**This is an academic project by robotics engineering students at Université de Sherbrooke.**
**Handling GRO is a four degrees of freedom robot.**

<div id="platform" align="center">
    <img src="./Docs/bro_bot_final.jpg" alt="Robot Assembly" width="703"/>
</div>

## Table of Contents
- [Authors](#Authors)
- [Setup](#Setup)
- [Documentation](#Documentation)
- [Recommended manufacturing device](#Recommended_device)
- [External Resources](#Resources)
    - [Single-Board Computer](#Computer)
    - [Controller_OpenCr](#Controller)
    - [Dynamixel motors](#dynamixel) 
    - [Steppermotor](#StepperMotor)
    - [DriveBoard (with steppermotor)](#DriveBoard)
    - [Servomotor](#ServoMotor)
    - [Power Supply: Motor/(OpenCr or Arduino)](#Power)
    - [Linear Rods](#Rods)
    - [Linear bearing](#linear_bearing)
    - [Timing belt](#Timing_belt)
- [License](#License)

    
[//]: # (------------------------------------------------)
## <a id="Authors"></a>Authors
- Olivier Demers - _Initial work_ - [chameau5050](https://github.com/chameau5050)
- Jérémy Giguère - _Initial work_ - [gigj1302](https://github.com/gigj1302)
- Philippe Gadeyne - _Initial work_ - [gadp1401](https://github.com/gigj1302)
- Francis Amyot - _Initial work_ - [FrancisAmyot](https://github.com/FrancisAmyot)
- Vincent-Xavier Voyer - _Initial work_ - [Theparky105](https://github.com/Theparky105)

## <a id="Setup"></a>Setup

1. Buy the component in the [External Resources](#Resources) section.
2. Use the [CAD models](https://github.com/chameau5050/Handling-Gro/tree/main/Mechanical/STL%20(For%203D%20printing)) to 3D print all the different parts of the robot.
3. Assemble the robot according to the [assembly guide](https://github.com/chameau5050/Handling-Gro/blob/main/Docs/Doc_mecanical/Assembly%20manual.pdf).
4. Do the electrical connections using the [electrical schematics](https://github.com/chameau5050/Handling-Gro/blob/main/Electrical_hardware/electrical_wiring_V1.pdf) in the documentation section.
4. Set up the [Raspberry Pi](#Computer) by connecting it with the [OpenCr](#Controller_OpenCr), your computer and the to a power source.
5. Download or clone the repository in the Raspberry Pi.
6. Verify your Python version (3.5 and above) and the port series.
7. Build and transfer all the code to the OpenCr (or Arduino). See [Compilation procedure](https://github.com/chameau5050/Handling-Gro/wiki/setup-IDE-for-ControlMotor(OpenCr)) documentation.
8. Build and transfer all the code to Raspberry Pi. See [Compilation procedure](https://github.com/chameau5050/Handling-Gro/wiki/setup-IDE-for-Application) documentation.
8. Open the interface and look your new Handgling GRO robot in action.
8. Congigure UI with Qt
9. For more information, see the [documentation](https://github.com/chameau5050/Handling-Gro/wiki) section
## <a id="Documentation"></a>Documentation

All the different information is available [here](https://github.com/chameau5050/Handling-Gro/wiki) in the project wiki.

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
- **If you want to use other motors than dynamixel motors, you can.

#### <a id="dynamixel"></a>Dynamixel_motors
- Brand: [Dynamixel](https://www.robotis.us/dynamixel-xm430-w350-r/)
- Model: XM430-W350
- Quantity: 4

#### <a id="StepperMotor"></a>Steppermotor
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


#### <a id="Timing_belt"></a> Timing belt
- Brand: [Uranny](https://www.amazon.ca/gp/product/B071HKC52V/ref=ppx_yo_dt_b_asin_image_o04_s00?ie=UTF8&psc=1&fbclid=IwAR3l580aQXrcDcnFzXKQVBHzXT6OlFWot1Oq8B5DTtPKzNiy5tsO_97gNR8)
- ASIN: Timing Belt 6mm Wide & 10X 5MM Pulley for 3D Printer
- Quantity: 1


## <a id="License"></a>License
This project is licenced under a  [![GPL-3.0](https://img.shields.io/badge/License-GPLv3-blue.svg?style=flat-square)](https://github.com/chameau5050/Handling-Gro/blob/main/LICENSE) license.
