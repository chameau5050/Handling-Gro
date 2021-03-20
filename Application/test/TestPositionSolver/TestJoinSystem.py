import unittest
import numpy as np
from test.TestPositionSolver.VectorTester import *
from pathSolver.JoinSystem import *
from pathSolver.RevoluteJoin import *
from pathSolver.LinearJoin import *

class TestJoinSystem(VectorTester):

    def test_addJoin(self):
        JS = JoinSystem()
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0])))
        self.assertEqual(1, JS.getNbrJoin())

    def test_1DResultantPosition(self):
        JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0]))])
        self.assertVectorEqual(np.array([0,-1,0]), JS.getLastJoinPosition([math.pi]), delta=0.001)

    def test_2DJoinResultantPosition(self):
        JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0]))])
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0, 1])))
        self.assertVectorEqual(np.array([0,-1,1]), JS.getLastJoinPosition([math.pi, math.pi]), delta=0.001)

    def test_3DJoinResultantPosition(self):
        JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0]))])
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0, 1])))
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.Z, np.array([1, 0, 0])))
        self.assertVectorEqual(np.array([1,-1,1]), JS.getLastJoinPosition([math.pi, math.pi, math.pi]), delta=0.001)

    def test_1DResultantPositionAndOrientation(self):
        JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0]))])
        expectedMatrix = np.array([0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1])
        computeMatrix  = JS.getLastJoinPositionAndOrientation([0])
        self.assertVectorEqual(expectedMatrix, computeMatrix, delta=0.001)

    def test_1DResultantPositionAndOrientation(self):
        JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0]))])
        expectedMatrix = np.array([0, -1, 0, -1, 0, 0, 0, -1, 0, 0, 0, 1])
        computeMatrix  = JS.getLastJoinPositionAndOrientation([math.pi])
        self.assertVectorEqual(expectedMatrix, computeMatrix, delta=0.001)

    def test_2DResultantPositionAndOrientation(self):
        JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0]))])
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0, 1])))
        expectedMatrix = np.array([0, -1, 1, -1, 0, 0, 0, -1, 0, 0, 0, 1]).reshape(12,1)
        computeMatrix  = JS.getLastJoinPositionAndOrientation([math.pi, math.pi])
        self.assertPoseVectorEqual(expectedMatrix, computeMatrix, delta=0.001)

    def test_3DResultantPositionAndOrientation(self):
        JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0]))])
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0, 1])))
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.Z, np.array([1, 0, 0])))
        expectedMatrix = np.array([1, -1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1]).reshape(12,1)
        computeMatrix  = JS.getLastJoinPositionAndOrientation([math.pi, math.pi, math.pi])
        self.assertPoseVectorEqual(expectedMatrix,computeMatrix , delta=0.001)

    def test_3DWithLinearJoin(self):
        JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0]))])
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0, 1])))
        JS.addJoin(LinearJoin(VectorSpaceAxis.Z, np.array([1, 0, 0])))
        expectedMatrix = np.array([-1, -1, 11, -1, 0, 0, 0, -1, 0, 0, 0, 1]).reshape(12, 1)
        computeMatrix = JS.getLastJoinPositionAndOrientation([math.pi, math.pi, 10])
        self.assertPoseVectorEqual(expectedMatrix, computeMatrix, delta=0.001)
