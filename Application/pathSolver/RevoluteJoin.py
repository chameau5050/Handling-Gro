import math
from pathSolver.vectorBase import *


class RevoluteJoin:

    def __init__(self,rotationAxis, nextJoinRelativePosition, axisLimit = [0,2*math.pi]):
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

        if axisLimit[0] < 0:
            self.axisMin = 0
        else:
            self.axisMin = axisLimit[0]

        if axisLimit[1] > 2*math.pi:
            self.axisMax = 2*math.pi
        else:
            self.axisMax = axisLimit[1]

    def getNextJoinRelativePosition(self, joinState):
        return self.nexJoinRelativePosition

    def getRotationMatrix(self, theta):
        if theta > self.axisMax:
            return self.rotationMatrix(self.axisMax)
        elif theta < self.axisMin:
            return self.rotationMatrix(self.axisMin)
        else:
            return self.rotationMatrix(theta)

    def getMinLimit(self):
        return self.axisMin

    def getMaxLimit(self):
        return self.axisMax
