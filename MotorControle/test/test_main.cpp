#include <Arduino.h>
#include <unity.h>
#include "testComm/testComm.h"


void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();    // IMPORTANT LINE!
}

void loop() 
{
    TestComm test_comm;

    test_comm.test();

    UNITY_END(); // stop unit testing
    
}