import json
from Comm.Accumulator import *
import socket


def waitForConnection(address, port, maxConection, objetToNotifie=None):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((address, port))
    server.listen(maxConection)

    conn, addr = server.accept()
    objetToNotifie.newConnection(conn)

class EthernetComm:

    JSONTYPE =1

    def __init__(self, socket):
        self.sock = socket
        self.sock.setblocking(False)
        self.acc = Accumulator(self)
        self.frameReceveList = []
        self.isSocketAlive = True

    def receveFrame(self, frame):
        self.frameReceveList.append(frame)


    def getSocket(self):
        return self.sock

    def readFrame(self):
        self.extractRecevedData()

        if len(self.frameReceveList) > 0:
            frameToReturn = self.frameReceveList[0]
            del self.frameReceveList[0]
            print(frameToReturn)
            return frameToReturn
        else:
            return None

    def extractRecevedData(self):
        # check for new frame
        data = 1
        while data:
            try:
                data = self.sock.recv(1024)
                print(data)
                if not data:
                    break
                else:
                    self.acc.accumulate(data)
            except:
                return None

    def sendJSon(self, JSON):
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
            print("frame type: ", frame.getType())
            if frame.getType() == EthernetComm.JSONTYPE:
                print("frame available: ", frame.getPayload())
                return True
        return False

    def readJSon(self):
        self.extractRecevedData()
        print("try to read")
        for frame in self.frameReceveList:
            print("frame readable: ", frame.getPayload())
            if frame.getType() == EthernetComm.JSONTYPE:
                self.frameReceveList.remove(frame)
                print("frameRemoved :")
                print("remove frame :", frame.getPayload().decode())

                print(json.loads(str(frame.getPayload(), encoding="UTF-8")))
                print("payload read")
                return json.loads(str(frame.getPayload(), encoding="UTF-8"))
        return None

    def isAlive(self):
        return self.isSocketAlive

    def closeConnection(self):
        self.sock.close()

    def sendFrame(self, frame):
        data = self.sock.send(frame.toBytes())

