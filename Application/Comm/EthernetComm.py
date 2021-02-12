import json
from Comm.Accumulator import *


class EthernetComm:

    JSONTYPE =1

    def __init__(self, socket):
        self.sock = socket
        self.sock.setblocking(False)
        self.acc = Accumulator(self)
        self.frameReceveList =[]

    def receveFrame(self,frame):
        self.frameReceveList.append(frame)


    def getSocket(self):
        return self.sock

    def readFrame(self):
        self.extractRecevedData()

        if len(self.frameReceveList) > 0:
            frameToReturn = self.frameReceveList[0]
            del self.frameReceveList[-1]
            return frameToReturn
        else:
            return None

    def extractRecevedData(self):
        # check for new frame
        data = 1
        while data:
            try:
                data = self.sock.recv(1024)

                if not data:
                    break
                else:
                    self.acc.accumulate(data)
            except:
                return None

    def sendJSON(self, JSON):
        frame = self.JSONtoFrame(JSON)
        self.sendFrame(frame)

    def JSONtoFrame(self, JSON):
        msgPayload = bytearray(json.dumps(JSON).encode(encoding="UTF-8"))
        frame = Frame()
        frame.setType(EthernetComm.JSONTYPE)
        frame.setPayloadSize(len(msgPayload))
        frame.writeBytesToPayload(msgPayload)
        return frame

    def isMessageAvailable(self):
        self.extractRecevedData()

        for frame in self.frameReceveList:
            if frame.getType() == EthernetComm.JSONTYPE:
                return True
        return False

    def readJSON(self):
        self.extractRecevedData()

        for frame in self.frameReceveList:
            if frame.getType() == EthernetComm.JSONTYPE:
                self.frameReceveList.remove(frame)
                return json.loads(str(frame.getPayload(), encoding="UTF-8"))
        return None

    def sendFrame(self, frame):
        data = self.sock.sendall(frame.toBytes())

