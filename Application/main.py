import threading
from Comm.EthernetComm import *
from Comm.MessageIO import *
from Comm.SerialComm import *

class app:
    def __init__(self):
        self.commPort = None
        self.messageIO = MessageIO()
    def newConnection(self, conn):
        self.commPort = EthernetComm(conn)
        self.messageIO.addDevice(self.commPort)
        self.messageIO.addDevice(SerialComm("COM4", 57000))
        while True:
            msg = self.messageIO.readMessage(0)
            if msg != None:
                print("type:", msg.getType())
                print("paload size: ", msg.getPayloadSize())
                print("payload :", msg.getPayload())
                self.messageIO.sendMessage(1, msg)



if __name__ == '__main__':

    x = threading.Thread(target=waitForConnection, args=("127.0.0.1", 50000, 1, app(),))
    x.start()


    print("run")
