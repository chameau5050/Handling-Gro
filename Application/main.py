import threading
from Comm.EthernetComm import *
from Comm.MessageIO import *
from Comm.SerialComm import *
from Comm.driveManager import *


from Cinematic.PositionSolver import *
from Cinematic.JoinSystem import *
from Cinematic.LinearJoin import *
from Cinematic.RevoluteJoin import *
from Cinematic.robotAPI import *



class app:
    def __init__(self):
        self.commPort = None
        self.messageIO = MessageIO()
        self.messageIO.addDevice(SerialComm("/dev/ttyACM0", 57000))
        self.driveManager = DriveManager([0,0,0], self.messageIO)
        self.JS = JoinSystem([LinearJoin(VectorSpaceAxis.X, np.array([0, 0, 0]), [0, 0.40])])
        self.JS.addJoin(RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0.275, 0]), [0, 2 * math.pi]))
        self.JS.addJoin(RevoluteJoin(VectorSpaceAxis.X, np.array([0, 0.19, 0]), [0, 2 * math.pi]))

        self.robot = robotAPI(self.JS,[1, 1, 1 ], self.driveManager)

    def newConnection(self, conn):
        self.commPort = EthernetComm(conn)
        self.messageIO.addDevice(self.commPort)
        print("conected")
        while True:
            msg = self.messageIO.readMessage(1)
            if msg != None:
                print("type:", msg.getType())
                print("paload size: ", msg.getPayloadSize())
                print("payload :", msg.getPayload())
                self.robot.moveInJoinTo(msg.getPayload())

if __name__ == '__main__':

    x = threading.Thread(target=waitForConnection, args=("192.168.1.126", 50008, 1, app(),))
    x.start()
