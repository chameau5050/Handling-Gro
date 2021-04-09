from Comm.SerialComm import *
from Cinematic.PositionSolver import *
from Comm.ControlMessage import *

class robotAPI:
    def __init__(self, JS, basePosition, driveManager):
        self.JS = JS
        self.driveManager = driveManager
        self.solver = positionSolver
        self.q = basePosition

    def findPosition(self, pos):
        pos = self.solver.solvePosition(self.JS, pos, self.q)
        return pos

    def moveInCartesianTo(self, newPosition):
        newJoinPosition = self.findPosition(newPosition)
        if newJoinPosition != None:
            self.moveInJoinTo(newJoinPosition)

    def moveXWorld(self, dis):
        newPosition = self.JS.getLastJoinPosition(self.q) + np.array([dis, 0, 0]).reshape(3,1)
        self.moveInCartesianTo(newPosition)

    def moveYWorld(self, dis):
        newPosition = self.JS.getLastJoinPosition(self.q) + np.array([0, dis, 0]).reshape(3, 1)
        self.moveInCartesianTo(newPosition)

    def moveZWorld(self, dis):
        newPosition = self.JS.getLastJoinPosition(self.q) + np.array([0, 0, dis]).reshape(3, 1)
        self.moveInCartesianTo(newPosition)

    def moveInJoinTo(self, newJoinPosition):
        self.driveManager.setJoinPosition(newJoinPosition)
        self.q = newJoinPosition

    def getPosition(self, q):
        return self.JS.getLastJoinPosition(q)

    def setRobotState(self, q):
        self.q = q

    def openGripper(self, rate):
        self.driveManager.openGripper(rate)

    def closeGripper(self, rate):
        self.driveManager.closeGripper(rate)

    def setHomeStep(self, qHome):
        self.driveManager.setHome(qHome)

    def goToHome(self):
        self.driveManager.gotoHome()

    def setPositionModel(self, q):
        hardWarePosition = self.JS.getHardwareJoinPosition(q)
        self.moveInJoinTo(hardWarePosition)

    def setHomeModel(self, qHome):
        hardWarePosition = self.JS.getHardwareJoinPosition(qHome)
        self.setHomeStep(hardWarePosition)

    def executeCommand(self, controlMsg):
        if controlMsg.getType() == ControlMessage.SET_JOIN_POSITION:
            self.moveInJoinTo(controlMsg.getPayload())

        elif controlMsg.getType() == ControlMessage.SET_CARTESIAN_POSITION:
            self.moveInCartesianTo(controlMsg.getPayload())

        elif controlMsg.getType() == ControlMessage.SET_HOME:
            self.setHomeStep(controlMsg.getPayload())

        elif controlMsg.getType() == ControlMessage.OPEN_GRIPPER:
            self.openGripper(controlMsg.getPayload()[0])

        elif controlMsg.getType() == ControlMessage.CLOSE_GRIPPER:
            self.closeGripper(controlMsg.getPayload()[0])

        elif controlMsg.getType() == ControlMessage.GOTO_HOME:
            self.goToHome()
        elif controlMsg.getType() == ControlMessage.SET_HOME_MODEL:
            self.setHomeModel(controlMsg.getPayload())
        elif controlMsg.getType() == ControlMessage.SET_JOIN_POSITION_MODEL:
            self.setPositionModel(controlMsg.getPayload())


