#include <unity.h>
#include "abstractTest.h"
#include "SerialComm.cpp"

#ifndef testSerialComm
#define testSerialComm

class test_Serial_Comm : public  abstractTest 
 {
    public:
        void test();
 };

    void isSendingGoodHardwareSerial()
    {
        SerialComm a(Serial,115200);
        TEST_ASSERT_EQUAL(Serial,a.getSerialPort());
    }


    void test_Serial_Comm::test()
    {
        RUN_TEST(isSendingGoodHardwareSerial);
    }

#endif