import math
from Cinematic.vectorBase import *


class RevoluteJoin:

    def __init__(self,rotationAxis, nextJoinRelativePosition, axisLimit = [0,2*math.pi], hardwareIntervalStep=2000):
        if rotationAxis == VectorSpaceAxis.X:
            self.rotationMatrix = getRotationMatrixX
        elif rotationAxis == VectorSpaceAxis.Y:
            self.rotationMatrix = getRotationMatrixY
        else:
            self.rotationMatrix = getRotationMatrixZ

        self.nexJoinRelativePosition = nextJoinRelativePosition.reshape((3, 1))

        if axisLimit[0] > axisLimit[1]:
            temp = axisLimit[0]
            axisLimit[0] = axisLimit[1]
            axisLimit[1] = temp


        self.axisMin = axisLimit[0]

        self.axisMax = axisLimit[1]

        self.hardwareIntervalStep = hardwareIntervalStep


    def getNextJoinRelativePosition(self, joinState):
        return self.nexJoinRelativePosition

    def getRotationMatrix(self, theta):
        if theta > self.axisMax:
            return self.rotationMatrix(self.axisMax)
        elif theta < self.axisMin:
            return self.rotationMatrix(self.axisMin)
        else:
            return self.rotationMatrix(theta)

    def convertToHardWarePosition(self, q):
        return math.floor((q-self.axisMin)/((self.axisMax-self.axisMin)/self.hardwareIntervalStep))

    def convertHardWarePositionToModelPosition(self, step):
        return self.axisMin + step*((self.axisMax-self.axisMin)/self.hardwareIntervalStep)

    def getMinLimit(self):
        return self.axisMin

    def getMaxLimit(self):
        return self.axisMax
