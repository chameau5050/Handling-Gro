#include "SerialComm.h"

SerialComm::SerialComm(HardwareSerial serialPort, unsigned long baud)
{
    serialPort.begin(baud);
    this->serialPort = &serialPort;
}

bool SerialComm::isMessageAvailable()
{
    return getSerialPort().available() > 0;
}

StaticJsonDocument<MaxSerialCommMessageSize> SerialComm::ReadJSon()
{
        StaticJsonDocument<MaxSerialCommMessageSize> message;
        DeserializationError err = deserializeJson(message, *serialPort);
        return message;
}


void SerialComm::sendJSon(StaticJsonDocument<MaxSerialCommMessageSize> message)
{
  serializeJson(message, Serial);
}


HardwareSerial SerialComm::getSerialPort()
{
    
    return *serialPort;
    
}