#include "TestApp.h"

#include "test/TestDataFrame.h"
#include "test/TestAccumulator.h"
#include "test/testmessagemanager.h"
#include "test/Testcontrolmessage.h"
#include "test/TestEthernetComm.h"


TestApp::TestApp()
{

}


bool TestApp::test()
{
    TestDataFrame::testAll();

    TestAccumulator::testAll();

    testControlMessage::testAll();

    testEthernetComm::testAll();

    if(!testMessageManager::testAll())
        return false;

    return true;
}
