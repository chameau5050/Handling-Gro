from Comm.MessageIO import *
from Comm.ControlMessage import *


class DriveManager:
    def __init__(self, controller, msgIO):
        # Indexes of joints controlled by controllers
        self.jointIndex = controller
        self.msgManager = msgIO

    def getJointIndex(self):
        return self.jointIndex

    def moveAxis(self, ctrlmsg):
        readPayload = ctrlmsg.getPayload()
        msgType = ctrlmsg.getType()
        # Create a dictionnary to store the axis with controller number as keys
        controllerDict = {}
        for x in range(0, len(self.jointIndex)):
            if controllerDict.get(self.jointIndex[x]) is None:
                controllerDict[self.jointIndex[x]] = [readPayload[x]]
            else:
                controllerDict[self.jointIndex[x]].append(readPayload[x])
        for controllerId in controllerDict:
            newMessage = ControlMessage(msgType, controllerDict[controllerId])
            self.msgManager.sendMessage(controllerId, newMessage)



