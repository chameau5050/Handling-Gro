from enum import Enum
from Comm.Frame import *
from Util.BytesUtil import *

class AccumulatorState(Enum):
        READSTARTBYTES = 0
        READTYPE =1
        READPAYLOADSIZE = 2
        READPAYLOAD = 3


class Accumulator:
    MaxBytes = 1000

    def __init__(self, messageManager):
        self.frame = Frame()
        self.state = AccumulatorState.READSTARTBYTES
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

        if self.state == AccumulatorState.READSTARTBYTES:
            print("startByte")
            self.writeByte(byte)

            if self.bufferIndex == Frame.TypeIndex:
                if BytesToInt(self.buffer[Frame.StartByteIndex:Frame.StartBytesValue]) == Frame.StartBytesValue:
                    self.state = AccumulatorState.READTYPE
                else:
                    self.reset()

        elif self.state == AccumulatorState.READTYPE:
            print("read type")
            self.writeByte(byte)

            if self.bufferIndex == Frame.PayloadSizeIndex:
                self.state = AccumulatorState.READPAYLOADSIZE

        elif self.state == AccumulatorState.READPAYLOADSIZE:
            print("read payload size")
            self.writeByte(byte)

            if self.bufferIndex == Frame.PayloadIndex:
                self.state = AccumulatorState.READPAYLOAD
                self.endOfPayloadIndex = self.readSizeOfPayload()
                print("payload read size:", self.endOfPayloadIndex)

        elif self.state == AccumulatorState.READPAYLOAD:
            print("read payload")
            self.writeByte(byte)

            if self.bufferIndex == self.endOfPayloadIndex:
                self.fowardReceveMessage()
                print("forward frame : ")
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
        self.state = AccumulatorState.READSTARTBYTES
        self.bufferIndex = 0

    def getState(self):
        return self.state



