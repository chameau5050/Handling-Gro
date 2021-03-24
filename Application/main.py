import threading
from Comm.EthernetComm import *
from Comm.MessageIO import *
from Comm.SerialComm import *

from pathSolver.PositionSolver import *
from pathSolver.JoinSystem import *
from pathSolver.LinearJoin import *
from pathSolver.RevoluteJoin import *
import  time

class Robot:
    def __init__(self):
        self.JS = JoinSystem([LinearJoin(VectorSpaceAxis.X,np.array([0, 0, 0]),[0, 0.40])])
        self.JS.addJoin(RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0.275, 0]), [0, 2*math.pi]))
        self.JS.addJoin(RevoluteJoin(VectorSpaceAxis.X, np.array([0, 0.19, 0]), [0, 2*math.pi]))
        self.solver = positionSolver()
        self.q = [1.,1.,1.]

    def findPosition(self, pos):
        a = time.time()
        #tim = timeit.timeit(self.solver.solvePositionWithJoinSystemBackProg,self.JS,pos,self.q)
        pos = self.solver.solvePositionWithJoinSystemBackProg(self.JS, pos, [float(self.JS.allJoin[0].getMinLimit()),float(self.JS.allJoin[1].getMinLimit()),float(self.JS.allJoin[2].getMinLimit())])
        pos2 =self.solver.solvePositionWithJoinSystemBackProg(self.JS, pos, [float(self.JS.allJoin[0].getMaxLimit()),float(self.JS.allJoin[1].getMaxLimit()), float(self.JS.allJoin[2].getMaxLimit())])
        #pos = self.solver.solvePositionWithJoinSystem(self.JS,pos,self.q)
        b = time.time()
        print("time")
        print(b-a)
        return pos , pos2
        #return self.solver.solvePositionWithJoinSystem(self.JS, pos, self.q)

    def getPosition(self,q):
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
