#include <unity.h> 
#include "Test_StateManager.h"
#include "StateManager.h"
#include "TestJoinDevice.h"

#include "Comm/SerialComm.h"
#include "Comm/ControlMessage.h"
#include "Comm/MessageIO.h"
#include "testComm/TestCommDevice2.h"

void Test_StateManager::test()
{
    RUN_TEST(test_updateState);
    RUN_TEST(test_callGoToHome);

}

//faire ce test la en dernier, ca ce test sert a valider que l,ensemble du test fonctionne

void Test_StateManager::test_updateState()
{
    StateManager* stateManager;
    DriveManager* driveManager;
    TestJoinDevice* testJoinDevice1 = new TestJoinDevice(0,228100,0,0,0);
    driveManager = new DriveManager;
    driveManager->addJoin(testJoinDevice1);
    stateManager = new StateManager(driveManager);

// //FACON #1 
//     int data[] = {1};
//     int size = 1;
//     int type = 1;
//     ControlMessage msgTest1(type,size,data);
//     ControlMessage* msg = msgTest1;
//     stateManager->updateState(msg);

    
// //FACON #2
//     int data[] = {1};
//     int size = 1;
//     int typ* = 1;
//     ControlMessage* msgTest2(type,size,data);
//     stateManager->updateState(msgTest2);

//Facon #3
    MessageIO msgIO1;
    TestCommDevice2 device1;
    msgIO1.addDevice(&device1);
    int data1[] = {101};
    ControlMessage msg(7,1,data1);

    msgIO1.sendMessage(0,msg);
    
    ControlMessage* Cmsg1 = msgIO1.readMessage(0);
    stateManager->updateState(Cmsg1);

    //TEST_ASSERT_EQUAL(0,testJoinDevice1->getPosition());
    TEST_ASSERT_EQUAL(101,testJoinDevice1->getPosition());
}


void Test_StateManager::test_callGoToHome()
{
    TEST_ASSERT_EQUAL(0,1);

}