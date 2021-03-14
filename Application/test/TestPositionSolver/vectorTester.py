import unittest
import numpy as np

class vectorTester(unittest.TestCase):

    def assertVectorEqual(self, expectedVector, currentVector):
        self.assertAlmostEqual(expectedVector[0], currentVector[0], delta=0.001)
        self.assertAlmostEqual(expectedVector[1], currentVector[1], delta=0.001)
        self.assertAlmostEqual(expectedVector[2], currentVector[2], delta=0.001)

    def asserMatrixEqual(self,expectedMatrix, currentMatrix):
        self.assertTrue(np.array_equal(expectedMatrix, currentMatrix))

