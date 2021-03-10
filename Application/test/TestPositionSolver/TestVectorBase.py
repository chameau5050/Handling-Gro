import unittest
import math
from pathSolver.vectorBase import *


class testVectorBase(unittest.TestCase):

    def test_rotateX(self):
        base = VectorBase(0, 1, 0)
        base.rotateX(math.pi/2)

        self.assertVectorEqual([1.0, 0.0, 0], base.getXaxis())
        self.assertVectorEqual([0.0, 0.0, 1.0], base.getYaxis())
        self.assertVectorEqual([0.0, -1.0, 0], base.getZaxis())

    def test_rotateY(self):
        base = VectorBase(0, 0, 1)
        base.rotateY(math.pi / 2)

        self.assertVectorEqual([0.0, 0.0, -1.0], base.getXaxis())
        self.assertVectorEqual([0.0, 1.0, 0], base.getYaxis())
        self.assertVectorEqual([1.0, 0, 0], base.getZaxis())

    def test_rotateZ(self):
        base = VectorBase(1, 0, 0)
        base.rotateZ(math.pi / 2)

        self.assertVectorEqual([0.0, 1.0, 0.0], base.getXaxis())
        self.assertVectorEqual([-1.0, 0.0, 0], base.getYaxis())
        self.assertVectorEqual([0.0, 0.0, 1.0], base.getZaxis())

    def assertVectorEqual(self, expectedVector, currentVector):
        self.assertAlmostEqual(expectedVector[0], currentVector[0], delta=0.001)
        self.assertAlmostEqual(expectedVector[1], currentVector[1], delta=0.001)
        self.assertAlmostEqual(expectedVector[2], currentVector[2], delta=0.001)