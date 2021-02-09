#include "SerialComm.h"

SerialComm::SerialComm(HardwareSerial *serialPort)
{
    this->serialPort = serialPort;
}

bool SerialComm::isMessageAvailable()
{
    return getSerialPort().available() > 0;
}

StaticJsonDocument<MaxJsonSize> SerialComm::ReadJSon()
{
   
    StaticJsonDocument<MaxJsonSize> message;
    DeserializationError err = deserializeJson(message, *serialPort);
    if(err) 
    {
        message["error"] = "deserialisation";        
    }
    
    return message;
}


void SerialComm::sendJSon(StaticJsonDocument<MaxJsonSize> message)
{
    serializeJson(message, *serialPort);
    serialPort->print('\n');
}


HardwareSerial SerialComm::getSerialPort()
{
    return *serialPort;   
}
