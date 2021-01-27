#include <Arduino.h>
#include <unity.h>
#include "test_Serial_Comm.h"
#include "test_ControlMessage.h"

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();    // IMPORTANT LINE!
}

void loop() 
{
    auto test_SerialComm = test_Serial_Comm();
    auto test_ControlMessage = testControlMessage();

    test_SerialComm.test();
    test_ControlMessage.test();    
    UNITY_END(); // stop unit testing
    
}