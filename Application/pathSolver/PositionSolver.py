import numpy as np
import time

class positionSolver:
    def __init__(self):
        return

    def solvePositionWithJoinSystem(self, joiSystem, wantedPosition, guessConfiguration):
        q = guessConfiguration
        wantedPosition = wantedPosition.reshape(3,1)
        base = np.array(q).reshape(3,1)
        for n in range(0, 15):

            J = joiSystem.findPositionGradient(q, 0.0001)
            base = base - np.linalg.inv(J).dot(joiSystem.getLastJoinPosition(q) - wantedPosition)
            q = base
        return np.array(q)




    def solvePositionWithJoinSystemBackProg(self, joiSystem, wantedPosition, guessConfiguration, rate=0.5):
        q = np.array(guessConfiguration).reshape(len(guessConfiguration), 1)
        wantedPosition = wantedPosition.reshape(3, 1)
        for x in range(1, 10):
            for n in range(0, 50):
                a = time.time()
                J = joiSystem.computeGradientOfPositionBasedCostFuction(wantedPosition, q, h=0.000001)
                b = time.time()
                print("time gradient:")
                print(b-a)
                old = q
                q = q-rate*J

                actualError = joiSystem.quadratiqueCostFunction(wantedPosition, joiSystem.getLastJoinPosition(old))
                newError = joiSystem.quadratiqueCostFunction(wantedPosition, joiSystem.getLastJoinPosition(q))

                if actualError < newError:
                    rate /=2
                    q = old




            error = np.max(np.abs(joiSystem.getLastJoinPosition(q) - wantedPosition))


        return np.array(q)