#include "abstractTest.h"
#include <unity.h>

#ifndef testSerialComm
#define testSerialComm

class test_Serial_Comm : public  abstractTest 
 {
    public:
        void test();
 };

    void test_one()
    {
        TEST_ASSERT_TRUE(true);
    }

    void test_two()
    {
        TEST_ASSERT_TRUE(true);
    }

    void test_Serial_Comm::test()
    {
        RUN_TEST(test_one);
        RUN_TEST(test_two);
    }

#endif