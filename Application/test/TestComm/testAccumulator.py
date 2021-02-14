import unittest
from Comm.Accumulator import *
from Util.BytesUtil import *
from test.TestComm.testMessageManager import *

class testAccumulator(unittest.TestCase):
    def test_inisalisation(self):
        msgManager = testMessageManager()
        acc = Accumulator(msgManager)
        self.assertEqual(AccumulatorState.READTYPE, acc.getState())

    def test_accumulateType(self):
        msgManager = testMessageManager()
        acc = Accumulator(msgManager)
        acc.accumulate(IntToBytes(5))

        self.assertEqual(AccumulatorState.READPAYLOADSIZE, acc.getState())

    def test_accumulatePayloadSize(self):
        msgManager = testMessageManager()
        acc = Accumulator(msgManager)
        acc.accumulate(IntToBytes(5))
        acc.accumulate(IntToBytes(4))
        self.assertEqual(AccumulatorState.READPAYLOAD, acc.getState())

    def test_accumulatePayload(self):
        msgManager = testMessageManager()
        acc = Accumulator(msgManager)
        msgType = 5
        msg = "this is a comm test"
        msgBytes = bytearray(msg, encoding="UTF-8")
        acc.accumulate(IntToBytes(msgType))
        acc.accumulate(IntToBytes(len(msgBytes)))
        acc.accumulate(msgBytes)

        self.assertEqual(AccumulatorState.READTYPE, acc.getState())

    def test_isSendingFrameToMessageControl(self):
        msgManager = testMessageManager()
        acc = Accumulator(msgManager)
        msgType = 5
        msg = "this is a comm test"
        msgBytes = bytearray(msg, encoding="UTF-8")
        msgPayloadSize = len(msgBytes)

        acc.accumulate(IntToBytes(msgType))
        acc.accumulate(IntToBytes(msgPayloadSize))
        acc.accumulate(msgBytes)

        self.assertEqual(msgType, msgManager.RXFrame.getType())
        self.assertEqual(msgPayloadSize, msgManager.RXFrame.getPayloadSize())
        self.assertEqual(msgBytes, msgManager.RXFrame.getPayload())