from Comm.MessageIO import *
from Comm.ControlMessage import *


class DriveManagerPython:
    def __init__(self, controller, message):
        # Message to send to controllers
        self.axisMsg = message
        # Indexes of joints controlled by controllers
        self.jointIndex = controller
        # Message type
        self.msgType = message.getType()

    def moveAxis(self, ctrlmsg):
        readPayload = ctrlmsg.getPayload()
        # Create a dictionnary to store the axis with controller number as keys
        controllerDict = {}
        for x in range(0, len(self.jointIndex)-1):
            temp[x] = self.jointIndex[x]
            if temp[x] in controllerDict is None:
                controllerDict[temp[x]] = [readPayload[x]]
            else:
                controllerDict[temp[x]].append(readPayload[temp[x]])
        for y in range(0, len(temp)-1):
            newMessage = ControlMessage(self.msgType, controllerDict[temp[y]])
            self.axisMsg.sendMessage(y, newMessage)



