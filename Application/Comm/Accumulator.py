from enum import Enum
from Comm.Frame import *
from Util.BytesUtil import *

class AccumulatorState(Enum):
        READTYPE =0
        READPAYLOADSIZE = 1
        READPAYLOAD = 2


class Accumulator:
    MaxBytes = 1000

    def __init__(self, messageManager):
        self.frame = Frame()
        self.state = AccumulatorState.READTYPE
        self.buffer = bytearray(Accumulator.MaxBytes)
        self.endOfPayloadIndex = 0
        self.bufferIndex = 0
        self.messageManager = messageManager

    def accumulate(self, bytes):
        for byte in bytes:
            self.addData(byte)

    def writeByte(self, byte):
        self.buffer[self.bufferIndex] = byte
        self.bufferIndex += 1

    def addData(self, byte):

        if self.state == AccumulatorState.READTYPE:
            self.writeByte(byte)

            if self.bufferIndex == Frame.PayloadSizeIndex:
                self.state = AccumulatorState.READPAYLOADSIZE

        elif self.state == AccumulatorState.READPAYLOADSIZE:
            self.writeByte(byte)

            if self.bufferIndex == Frame.PayloadIndex:
                self.state = AccumulatorState.READPAYLOAD
                self.endOfPayloadIndex = self.readSizeOfPayload()

        elif self.state == AccumulatorState.READPAYLOAD:
            self.writeByte(byte)

            if self.bufferIndex == self.endOfPayloadIndex:
                self.fowardReceveMessage()
                self.reset()

    def fowardReceveMessage(self):
        self.messageManager.receveFrame(self.getAccumulatedFrame())

    def getAccumulatedFrame(self):
        return Frame(self.buffer[0:self.bufferIndex])

    def readSizeOfPayload(self):
        return BytesToInt(self.getReadPayloadSize()) + Frame.PayloadIndex

    def getReadPayloadSize(self):
        return self.buffer[Frame.PayloadSizeIndex:Frame.PayloadIndex + Frame.PayloadIndexSize]

    def reset(self):
        self.state = AccumulatorState.READTYPE
        self.bufferIndex = 0

    def getState(self):
        return self.state



