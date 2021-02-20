#include "TestApp.h"

#include "test/TestDataFrame.h"
#include "test/TestAccumulator.h"
#include "test/testmessagemanager.h"
TestApp::TestApp()
{

}


bool TestApp::test()
{
    TestDataFrame::testAll();

    TestAccumulator::testAll();

    if(!testMessageManager::testAll())
        return false;

    return true;
}
