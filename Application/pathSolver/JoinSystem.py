import math
import numpy as np

class JoinSystem:

    def __init__(self,allJoin = []):
        self.allJoin = allJoin

    def addJoin(self, newJoin):
        self.allJoin.append(newJoin)

    def getNbrJoin(self):
        return len(self.allJoin)

    def getEndPosition(self, q):
        endPosition = np.array([0.0,0.0,0.0]).reshape(3,1)
        RotMatrix = np.eye(3)
        for ctr in range(0, len(q)):
            RotMatrix = RotMatrix.dot(self.allJoin[ctr].getRotationMatrix(q[ctr]))
            endPosition += RotMatrix.dot(self.allJoin[ctr].getNextJoinRelativePosition(q[ctr]))
        return endPosition

    def getEndPose(self, q):
        endPosition = np.array([0.0, 0.0, 0.0]).reshape(3, 1)
        RotMatrix = np.eye(3)
        for ctr in range(0, len(q)):
            RotMatrix = RotMatrix.dot(self.allJoin[ctr].getRotationMatrix(q[ctr]))
            endPosition += RotMatrix.dot(self.allJoin[ctr].getNextJoinRelativePosition(q[ctr]))

        rotationVector = self.findRotationVector(RotMatrix)
        pose = np.concatenate((endPosition, rotationVector), axis=None)

        return pose.reshape(6, 1)

    def findRotationVector(self, RotMatrix):
        return np.array([self.findXRotation(RotMatrix), self.findYRotation(RotMatrix), self.findZRotation(RotMatrix)])

    def findXRotation(self,rotMatrix):
        z = np.array([0, 0, 1])
        zTransform = rotMatrix.dot(z)
        # remove Z dimention
        zTransform[0] = 0

        angle = math.acos(
            z.dot(zTransform) / (math.sqrt(z.dot(z.transpose())) * math.sqrt(zTransform.dot(zTransform.transpose()))))

        if zTransform[1] < 0:
            angle = 2 * math.pi - angle
        return angle

    def findYRotation(self,rotMatrix):
        z = np.array([0, 0, 1])
        zTransform = rotMatrix.dot(z)
        # remove Z dimention
        zTransform[1] = 0

        angle = math.acos(
            z.dot(zTransform) / (math.sqrt(z.dot(z.transpose())) * math.sqrt(zTransform.dot(zTransform.transpose()))))

        if zTransform[0] < 0:
            angle = 2 * math.pi - angle
        return angle

    def findZRotation(self,rotMatrix):
        x = np.array([1, 0, 0])
        xTransform = rotMatrix.dot(x)
        # remove Z dimention
        xTransform[2] = 0

        angle = math.acos(
            x.dot(xTransform) / (math.sqrt(x.dot(x.transpose())) * math.sqrt(xTransform.dot(xTransform.transpose()))))

        if xTransform[1] < 0:
            angle = 2 * math.pi - angle
        return angle
