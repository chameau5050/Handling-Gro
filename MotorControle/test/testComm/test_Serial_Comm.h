#include <unity.h>
#include "../test/abstractTest.h"
#include "../src/Comm/SerialComm.cpp"

#ifndef testSerialComm
#define testSerialComm

class test_Serial_Comm : public  abstractTest 
 {
    public:
        void test();
 };

    void isSendingGoodHardwareSerial()
    {
        SerialComm a(Serial);
        TEST_ASSERT_EQUAL(Serial,a.getSerialPort());
    }


    void test_Serial_Comm::test()
    {
        RUN_TEST(isSendingGoodHardwareSerial);
    }

#endif