#include <Arduino.h>
#include <unity.h>
#include "test_Serial_Comm.h"

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();    // IMPORTANT LINE!
}

void loop() 
{
    auto a = test_Serial_Comm();

    a.test();    
    UNITY_END(); // stop unit testing
    
}