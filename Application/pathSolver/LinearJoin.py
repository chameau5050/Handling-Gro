from pathSolver.vectorBase import *


class LinearJoin:
    def __init__(self,translationAxis, nextJoinRelativePosition, axisLimit = [0,10]):
        if translationAxis == VectorSpaceAxis.X:
            self.translationMatrix = translateXvector
        elif translationAxis == VectorSpaceAxis.Y:
            self.translationMatrix = translateYvector
        else:
            self.translationMatrix = translateZvector

        self.rotationMatrix = np.eye(3)
        self.nexJoinRelativePosition = nextJoinRelativePosition.reshape((3, 1))

        if axisLimit[0] > axisLimit[1]:
            temp = axisLimit[0]
            axisLimit[0] = axisLimit[1]
            axisLimit[1] = temp

        self.axisMin = axisLimit[0]
        self.axisMax = axisLimit[1]



    def getRotationMatrix(self,state):
        return self.rotationMatrix

    def getNextJoinRelativePosition(self, joinState):
        if joinState > self.axisMax:
            return self.translationMatrix(self.nexJoinRelativePosition, self.axisMax)
        elif joinState < self.axisMin:
            return self.translationMatrix(self.nexJoinRelativePosition, self.axisMin)
        else:
            return self.translationMatrix(self.nexJoinRelativePosition, joinState)

    def getMinlimit(self):
        return self.axisMin

    def getMaxlimit(self):
        return self.axisMax
