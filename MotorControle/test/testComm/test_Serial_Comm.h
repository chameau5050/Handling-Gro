#include <unity.h>
#include "../test/abstractTest.h"
#include "Comm/SerialComm.h"

#ifndef TESTSERIALCOMM_H
#define TESTSERIALCOMM_H

class test_Serial_Comm : public  abstractTest 
{
    public:
        void test();
        static void isSendingGoodHardwareSerial();
};

void test_Serial_Comm::isSendingGoodHardwareSerial()
{
    SerialComm a(&Serial);
    TEST_ASSERT_EQUAL(Serial,a.getSerialPort());
}


void test_Serial_Comm::test()
{
    RUN_TEST(isSendingGoodHardwareSerial);
}

#endif