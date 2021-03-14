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
        self.assertEqual(driveManager.getJointIndex(),controller)

    def test_moveAxis(self):
        ctrlmsg = ControlMessage(1, [40, 23, 11, 52])
        controller = [1, 1, 2, 2]
        msg = MessageIO()
        msg.addDevice(testCommDevice(True))
        msg.addDevice(testCommDevice(True))
        driveManager = DriveManager(controller, msg)
        driveManager.moveAxis(ctrlmsg)
        sentboi = driveManager.paperBoy
        test_msg_1 = sentboi.readMessage(0)
        test_msg_2 = sentboi.readMessage(1)
        test_ctrl_1 = [40, 23]
        test_ctrl_2 = [11, 52]
        self.assertEqual(test_ctrl_1, test_msg_1.getPayload())
        self.assertEqual(test_ctrl_2, test_msg_2.getPayload())

