#ifndef TEST_STATEMANAGER_H
#define TEST_STATEMANAGER_H

#include "abstractTest.h"

class Test_StateManager : public abstractTest
{
    public:
        void test();
        static void test_updateState();
        static void test_callGoToHome();

};
#endif