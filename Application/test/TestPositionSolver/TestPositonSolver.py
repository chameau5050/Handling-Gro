from test.TestPositionSolver.VectorTester import *
from pathSolver.JoinSystem import *
from pathSolver.PositionSolver import *
from pathSolver.RevoluteJoin import *
from pathSolver.LinearJoin import *


class TestPositionSolver(VectorTester):

    def test_3DLinSolve(self):
        JS = JoinSystem([LinearJoin(VectorSpaceAxis.X, np.array([1, 0, 0]))])
        JS.addJoin(LinearJoin(VectorSpaceAxis.Y, np.array([0, 0, 1])))
        JS.addJoin(LinearJoin(VectorSpaceAxis.Z, np.array([0, 1, 0])))
        solver = positionSolver()

        q = solver.solvePosition(JS, np.array([2, 2, 3]), [0.99, 0.99, 0.99])
        self.assertMatrixEqual(np.array([1, 1, 2]).reshape(3, 1), q)

    def test_3DLinSolveBackProg(self):
        JS = JoinSystem([LinearJoin(VectorSpaceAxis.X, np.array([1, 0, 0]))])
        JS.addJoin(LinearJoin(VectorSpaceAxis.Y, np.array([0, 0, 1])))
        JS.addJoin(LinearJoin(VectorSpaceAxis.Z, np.array([0, 1, 0])))
        solver = positionSolver()

        q = solver.solvePosition(JS, np.array([3, 2, 3]), [2.5, 0.99, 0.99])
        self.assertMatrixEqual(np.array([2, 1, 2]).reshape(3, 1), q)