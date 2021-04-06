from Cinematic.vectorBase import *


class LinearJoin:
    def __init__(self,translationAxis, nextJoinRelativePosition, axisLimit = [0,10], hardwareIntervalStep = 2000):
        if translationAxis == VectorSpaceAxis.X:
            self.translationMatrix = translateX
        elif translationAxis == VectorSpaceAxis.Y:
            self.translationMatrix = translateY
        else:
            self.translationMatrix = translateZ

        self.rotationMatrix = np.eye(3)
        self.nexJoinRelativePosition = nextJoinRelativePosition.reshape((3, 1))

        if axisLimit[0] > axisLimit[1]:
            temp = axisLimit[0]
            axisLimit[0] = axisLimit[1]
            axisLimit[1] = temp

        self.axisMin = axisLimit[0]
        self.axisMax = axisLimit[1]

        self.hardwareIntervalStep = hardwareIntervalStep

    def getRotationMatrix(self,state):
        return self.rotationMatrix

    def getNextJoinRelativePosition(self, joinState):
        if joinState > self.axisMax:
            return self.translationMatrix(self.nexJoinRelativePosition, self.axisMax)
        elif joinState < self.axisMin:
            return self.translationMatrix(self.nexJoinRelativePosition, self.axisMin)
        else:
            return self.translationMatrix(self.nexJoinRelativePosition, joinState)

    def convertToHardWarePosition(self, q):
        return math.floor((q-self.axisMin)/((self.axisMax-self.axisMin)/self.hardwareIntervalStep))

    def convertHardWarePositionToModelPosition(self, step):
        return self.axisMin + step*((self.axisMax-self.axisMin)/self.hardwareIntervalStep)

    def getMinLimit(self):
        return self.axisMin

    def getMaxLimit(self):
        return self.axisMax
