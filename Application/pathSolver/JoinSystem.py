import numpy as np
from pathSolver.vectorBase import *


class JoinSystem:

    def __init__(self,allJoin = []):
        self.allJoin = allJoin

    def addJoin(self, newJoin):
        self.allJoin.append(newJoin)

    def getNbrJoin(self):
        return len(self.allJoin)

    def getLastJoinPosition(self, q):
        rotMatrix, lastJoinPosition = self.computeLastJoinPosition(q)
        return lastJoinPosition

    def getLastJoinPositionAndOrientation(self, q):
        rotMatrix, lastJoinPosition = self.computeLastJoinPosition(q)

        pose = np.concatenate((lastJoinPosition, rotMatrix), axis=None)
        return pose.reshape(12, 1)

    def computeLastJoinPosition(self, q):
        lastJoinPosition = np.array([0.0, 0.0, 0.0]).reshape(3, 1)
        rotMatrix = np.eye(3)
        for ctr in range(0, len(q)):
            rotMatrix = rotMatrix.dot(self.allJoin[ctr].getRotationMatrix(q[ctr]))
            lastJoinPosition += rotMatrix.dot(self.allJoin[ctr].getNextJoinRelativePosition(q[ctr]))
        return rotMatrix, lastJoinPosition

    def findVectorRotation(self, rotMatrix):
        return np.array([findXRotation(rotMatrix), findYRotation(rotMatrix), findZRotation(rotMatrix)])

