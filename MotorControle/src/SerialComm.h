#include <Arduino.h>
#include <ArduinoJson.h>


#ifndef SERIALCOM_H
#define SERIALCOM_H

#define MaxSerialCommMessageSize 64

class SerialComm 
{
    public:
        SerialComm(HardwareSerial serialPort,unsigned long baud);
        StaticJsonDocument<MaxSerialCommMessageSize> ReadJSon();
        void sendJSon(StaticJsonDocument<MaxSerialCommMessageSize> message);
        bool isMessageAvailable();
        HardwareSerial getSerialPort();
    private:
        HardwareSerial* serialPort;
};

#endif