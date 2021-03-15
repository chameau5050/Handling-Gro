import unittest
from test.TestPositionSolver.vectorTester import *
from pathSolver.JoinSystem import *
from pathSolver.RevoluteJoin import *
from pathSolver.LinearJoin import *

class TestJoinSystem(vectorTester):

    def test_addJoin(self):
        JS = JoinSystem()
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0])))
        self.assertEqual(1,JS.getNbrJoin())

    def test_1DResultantPosition(self):
        JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0]))])
        self.assertVectorEqual(np.array([0,-1,0]), JS.getEndPosition([math.pi]), delta=0.001)

    def test_2DJoinResultantPosition(self):
        JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0]))])
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0, 1])))
        self.assertVectorEqual(np.array([0,-1,1]), JS.getEndPosition([math.pi, math.pi]), delta=0.001)

    def test_3DJoinResultantPosition(self):
        JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0]))])
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0, 1])))
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.Z, np.array([1, 0, 0])))
        self.assertVectorEqual(np.array([1,-1,1]), JS.getEndPosition([math.pi, math.pi, math.pi]), delta=0.001)

    def test_1DResultantPose(self):
        JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0]))])
        self.assertVectorEqual(np.array([0, -1, 0, math.pi, 0, 0]), JS.getEndPose([math.pi]), delta=0.001)

    def test_2DResultantPose(self):
        JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0]))])
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0, 1])))
        self.assertPoseVectorEqual(np.array([0, -1, 1, 0, 0, math.pi]).reshape(6,1), JS.getEndPose([math.pi, math.pi]), delta=0.001)

    def test_3DResultantPose(self):
        JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0]))])
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0, 1])))
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.Z, np.array([1, 0, 0])))
        self.assertPoseVectorEqual(np.array([1, -1, 1, 0, 0, 0]).reshape(6,1), JS.getEndPose([math.pi, math.pi, math.pi]), delta=0.001)

    def test_3DWithLinearJoin(self):
        JS = JoinSystem([RevoluteJoin(VectorSpaceAxis.X, np.array([0, 1, 0]))])
        JS.addJoin(RevoluteJoin(VectorSpaceAxis.Y, np.array([0, 0, 1])))
        JS.addJoin(LinearJoin(VectorSpaceAxis.Z, np.array([1, 0, 0])))
        a = JS.getEndPose([math.pi, math.pi,10])
        self.assertPoseVectorEqual(np.array([-1, -1, 11, 0, 0, math.pi]).reshape(6, 1), JS.getEndPose([math.pi, math.pi, 10]), delta=0.001)
