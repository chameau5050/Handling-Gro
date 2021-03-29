import threading
from Comm.EthernetComm import *
from Comm.MessageIO import *
from Comm.SerialComm import *

from Cinematic.PositionSolver import *
from Cinematic.JoinSystem import *
from Cinematic.LinearJoin import *
from Cinematic.RevoluteJoin import *

class Robot:
    def __init__(self):
        self.JS = JoinSystem([LinearJoin(VectorSpaceAxis.X,np.array([0, 0, 0]),[0, 0.40])])
        self.JS.addJoin(RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0.275, 0]), [0, 2*math.pi]))
        self.JS.addJoin(RevoluteJoin(VectorSpaceAxis.X, np.array([0, 0.19, 0]), [0, 2*math.pi]))
        self.solver = positionSolver()
        self.q = [1.,1.,1.]

    def findPosition(self, pos):
        pos = self.solver.solvePosition(self.JS, pos, self.q)
        return pos

    def moveInCartesianTo(self, newPosition):
        newJoinPosition = self.findPosition(newPosition)
        if newJoinPosition != None:
            self.moveInJoinTo(newJoinPosition)

    def moveXWorld(self, dis):
        newPosition = self.JS.getLastJoinPosition(self.q) + np.array([dis,0,0]).reshape(3,1)
        self.moveInCartesianTo(newPosition)

    def moveYWorld(self, dis):
        newPosition = self.JS.getLastJoinPosition(self.q) + np.array([0, dis, 0]).reshape(3, 1)
        self.moveInCartesianTo(newPosition)

    def moveZWorld(self, dis):
        newPosition = self.JS.getLastJoinPosition(self.q) + np.array([0, 0, dis]).reshape(3, 1)
        self.moveInCartesianTo(newPosition)

    def moveInJoinTo(self):
        return

    def getPosition(self, q):
        return self.JS.getLastJoinPosition(q)

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

    robot = Robot()
    want = np.array([0.3, 0.275, -0.19]).reshape(3,1)
    q,q2 = robot.findPosition(want)
    approx = robot.getPosition(q)
    print("config:")
    print(q)
    print("Quadratic error on position:")
    print(want-approx)
    print("run")
