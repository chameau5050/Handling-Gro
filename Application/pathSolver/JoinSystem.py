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

    def computeLastJoinPositionExplicit(self, q):
        lastJoinPosition = np.array([0.0, 0.0, 0.0]).reshape(3, 1)
        rotMatrix = np.eye(3)
        allJointPosition = []
        allJointOrientation = []

        for ctr in range(0, len(q)):
            rotMatrix = rotMatrix.dot(self.allJoin[ctr].getRotationMatrix(q[ctr]))
            lastJoinPosition += rotMatrix.dot(self.allJoin[ctr].getNextJoinRelativePosition(q[ctr]))
            allJointPosition.append(lastJoinPosition)
            allJointOrientation.append(rotMatrix)

        return allJointOrientation, allJointPosition

    def fastGradientComputation(self, q, h=0.0001):
        orientation, position = self.computeLastJoinPositionExplicit(q)

        for ctr in range(0, len(q)):
            if ctr == 0:
                before = q.copy()
                after = q.copy()
                before[ctr] -= h
                after[ctr] += h
                newRotation = self.allJoin[ctr].getRotationMatrix(before)
                newPosition = self.allJoin[ctr].getNextJoinRelativePosition(before)
                newPosition = newRotation.dot(newPosition)


                delq = (self.getLastJoinPosition(after) - self.getLastJoinPosition(before)) / (2 * h)



    def findVectorRotation(self, rotMatrix):
        return np.array([findXRotation(rotMatrix), findYRotation(rotMatrix), findZRotation(rotMatrix)])

    def findPositionGradient(self, q, h=0.0001):
        gradient = None
        for x in range(0, len(q)):
            before = q.copy()
            after = q.copy()
            before[x] -= h
            after[x] += h
            delq = (self.getLastJoinPosition(after)-self.getLastJoinPosition(before))/(2*h)
            delq.reshape(3, 1)
            if gradient is None:
                gradient = delq
            else:
                gradient = np.concatenate((gradient, delq), axis=1)
        return gradient

    def quadratiqueCostFunction(self, wanted, actual):
        error = 0
        for ctr in range(0, len(wanted)):
            deleta = (wanted[ctr]-actual[ctr])
            error += deleta*deleta
        return error

    def computeGradientOfPositionBasedCostFuction(self, wantedPosition, q, h):
        gradient = None
        for x in range(0, len(q)):
            before = q.copy()
            after = q.copy()
            before[x] -= h
            after[x] += h
            delq = (self.quadratiqueCostFunction(wantedPosition, self.getLastJoinPosition(after)) - self.quadratiqueCostFunction(wantedPosition, self.getLastJoinPosition(before))) / (2 * h)
            if gradient is None:
                gradient = delq
            else:
                gradient = np.concatenate((gradient, delq), axis=None)
        return gradient.reshape(len(q),1)

    def findPoseGradient(self, q, h=0.0001):
        gradient = None
        for x in range(0, len(q)):
            before = q.copy()
            after = q.copy()
            before[x] -= h
            after[x] += h
            delq = (self.getLastJoinPose(after)-self.getLastJoinPose(before))/(2*h)
            delq.reshape(6, 1)
            if gradient is None:
                gradient = delq
            else:
                gradient = np.concatenate((gradient, delq), axis=1)
        return gradient