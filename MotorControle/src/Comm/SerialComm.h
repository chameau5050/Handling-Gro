#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "CommDevice.h"




class SerialComm : public CommDevice
{
    public:
        SerialComm(HardwareSerial* serialPort);
        StaticJsonDocument<MaxJsonSize> ReadJSon();
        void sendJSon(StaticJsonDocument<MaxJsonSize> message);
        bool isMessageAvailable();
        HardwareSerial getSerialPort();
    private:
        HardwareSerial* serialPort;
};

#endif