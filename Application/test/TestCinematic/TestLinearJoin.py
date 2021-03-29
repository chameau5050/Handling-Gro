import unittest
from Cinematic.LinearJoin import *
from test.TestCinematic.VectorTester import *

class TestLinearJoin(VectorTester):
    def test_rotationMatrixInit(self):
        join = LinearJoin(VectorSpaceAxis.X, np.array([0, 0, 1]))
        self.assertMatrixEqual(np.eye(3),join.rotationMatrix)

    def test_initRevoluteX(self):
        join = LinearJoin(VectorSpaceAxis.X, np.array([0, 0, 1]))
        self.assertEqual(join.translationMatrix, translateX)

    def test_initRevoluteY(self):
        join = LinearJoin(VectorSpaceAxis.Y, np.array([0, 0, 1]))

        self.assertEqual(join.translationMatrix, translateY)

    def test_initRevoluteZ(self):
        join = LinearJoin(VectorSpaceAxis.Z, np.array([0, 0, 1]))

        self.assertEqual(join.translationMatrix, translateZ)

    def test_getRotationMatrix(self):
        join = LinearJoin(VectorSpaceAxis.X, np.array([0, 0, 1]))
        self.assertMatrixEqual(np.eye(3), join.getRotationMatrix(1))

    def test_moveXJoin(self):
        join = LinearJoin(VectorSpaceAxis.X, np.array([0, 0, 1]))
        self.assertMatrixEqual(np.array([1, 0, 1]).reshape(3, 1), join.getNextJoinRelativePosition(1))

    def test_moveYJoin(self):
        join = LinearJoin(VectorSpaceAxis.Y, np.array([0, 0, 1]))
        self.assertMatrixEqual(np.array([0, 1, 1]).reshape(3, 1), join.getNextJoinRelativePosition(1))

    def test_moveZJoin(self):
        join = LinearJoin(VectorSpaceAxis.Z, np.array([0, 0, 1]))
        self.assertMatrixEqual(np.array([0, 0, 2]).reshape(3, 1), join.getNextJoinRelativePosition(1))

    def test_initLimitJoinLimit(self):
        self.initJoin(8, -1, 8, -1)
        self.initJoin(5, 1, 5, 1)
        self.initJoin(1,5, 5, 1)

    def initJoin(self, argMax, argMin, expectedMax, expectedMin):
        join = LinearJoin(VectorSpaceAxis.X, np.array([0, 0, 1]), [argMin, argMax])
        self.assertEqual(expectedMin, join.getMinLimit())
        self.assertEqual(expectedMax, join.getMaxLimit())

    def test_isLimitJoinLimitWorking(self):
        join = LinearJoin(VectorSpaceAxis.X, np.array([0, 0, 1]), [5, 1])
        self.assertMatrixEqual(join.getNextJoinRelativePosition(5), join.getNextJoinRelativePosition(6))
        self.assertMatrixEqual(join.getNextJoinRelativePosition(4.1), join.getNextJoinRelativePosition(4.1))
        self.assertMatrixEqual(join.getNextJoinRelativePosition(0), join.getNextJoinRelativePosition(-6))

    def isNewJoinPositionWithIncorrectShapeOk(self):
        self.isNewJoinPositionOk(np.array([1, 0, 0]).reshape((3, 1)), np.array([1, 0, 0]).reshape((1, 3)))
        self.isNewJoinPositionOk(np.array([0, 1, 0]).reshape((3, 1)), np.array([0, 1, 0]).reshape((1, 3)))
        self.isNewJoinPositionOk(np.array([1, 0, 0]).reshape((3, 1)), np.array([1, 0, 0]).reshape((1, 3)))

    def isNewJoinPositionWithCorrectShapeOk(self):
        self.isNewJoinPositionOk(np.array([0, 0, 1]).reshape((3, 1)), np.array([0, 0, 1]))
        self.isNewJoinPositionOk(np.array([0, 1, 0]).reshape((3, 1)), np.array([0, 1, 0]))
        self.isNewJoinPositionOk(np.array([1, 0, 0]).reshape((3, 1)), np.array([1, 0, 0]))

    def isNewJoinPositionOk(self,expected, positionArray):
        joinX = LinearJoin(VectorSpaceAxis.X, positionArray)
        joinY = LinearJoin(VectorSpaceAxis.Y, positionArray)
        joinZ = LinearJoin(VectorSpaceAxis.Z, positionArray)

        self.assertVectorEqual(expected, joinX.getNextJoinRelativePosition(0))
        self.assertVectorEqual(expected, joinY.getNextJoinRelativePosition(0))
        self.assertVectorEqual(expected, joinZ.getNextJoinRelativePosition(0))

    def test_JoinTranslation(self):
        positionArray = np.array([0, 0, 1]).reshape(3, 1)
        joinX = LinearJoin(VectorSpaceAxis.X, positionArray)
        joinY = LinearJoin(VectorSpaceAxis.Y, positionArray)
        joinZ = LinearJoin(VectorSpaceAxis.Z, positionArray)

        self.assertVectorEqual(np.array([2, 0, 1]).reshape(3, 1), joinX.getNextJoinRelativePosition(2))
        self.assertVectorEqual(np.array([0, 2, 1]).reshape(3, 1), joinY.getNextJoinRelativePosition(2))
        self.assertVectorEqual(np.array([0, 0, 3]).reshape(3, 1), joinZ.getNextJoinRelativePosition(2))

