import unittest
from Comm.driveManagerPython import *
from Comm.ControlMessage import ControlMessage
from Comm.MessageIO import MessageIO
from test.TestComm.testCommDevice import *


class TestDriveManagerPython(unittest.TestCase):
    def test_init(self):
        controller = [1,2,3,4]
        msg = MessageIO()
        msg.addDevice(testCommDevice())
        driveManager = DriveManager(controller,msg)
        self.assertEqual(driveManager.getJointIndex(), controller)

    def test_moveAxis(self):
        ctrlmsg = ControlMessage(1, [40, 23, 11, 52])
        controller = [0, 0, 2, 1]
        msgManager = MessageIO()
        msgManager.addDevice(testCommDevice(True))
        msgManager.addDevice(testCommDevice(True))
        msgManager.addDevice(testCommDevice(True))
        driveManager = DriveManager(controller, msgManager)
        driveManager.moveAxis(ctrlmsg)

        test_msg_1 = msgManager.readMessage(0)
        test_msg_2 = msgManager.readMessage(1)
        test_msg_3 = msgManager.readMessage(2)

        test_ctrl_1 = [40, 23]
        test_ctrl_2 = [52]
        test_ctrl_3 = [11]

        self.assertEqual(test_ctrl_1, test_msg_1.getPayload())
        self.assertEqual(test_ctrl_2, test_msg_2.getPayload())
        self.assertEqual(test_ctrl_3, test_msg_3.getPayload())

