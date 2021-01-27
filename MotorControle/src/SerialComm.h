#include <Arduino.h>
#include "../lib/ArduinoJson.h"

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