import threading
from Comm.EthernetComm import *
from Comm.MessageIO import *

class app:
    def __init__(self):
        self.commPort = None
        self.messageIO = MessageIO()

    def newConnection(self, conn):
        self.commPort = EthernetComm(conn)
        self.messageIO.addDevice(self.commPort)
        while True:
            msg = self.messageIO.readMessage(0)
            if msg != None:
                print("type:", msg.getType())
                print("paload size: ",msg.getPayloadSize())
                print("payload :", msg.getPayload())


if __name__ == '__main__':

    x = threading.Thread(target=waitForConnection, args=("127.0.0.1", 50000, 1, app(),))
    x.start()


    print("run")
