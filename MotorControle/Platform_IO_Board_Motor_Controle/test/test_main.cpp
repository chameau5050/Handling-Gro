#include <Arduino.h>
#include <unity.h>
#include "testComm/testComm.h"
#include "Test_Join.h"


void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();    // IMPORTANT LINE!
}

void loop() 
{
    //initialisation
    TestComm test_comm;
    Test_Join test_join;

    //lunch_ de_test
    test_comm.test();
    test_join.test();


    UNITY_END(); // stop unit testing
    
}