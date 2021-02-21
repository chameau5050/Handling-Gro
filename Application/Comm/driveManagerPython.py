from Comm.MessageIO import *
from Comm.ControlMessage import *


class DriveManagerPython:
    def __init__(self, controller):
        # payload buffer
        self.axis = []
        # Message to send to controllers
        self.axisMsg = MessageIO()
        # Get the number of controllers
        self.conSort = controller.sorted()
        self.ctrlNumber = conSort[len(conSort)]
        # Indexes of joints controlled by controllers
        self.jointIndex = []
        # create array of arrays
        for y in range(0, self.ctrlNumber-1):
            self.jointIndex[y] = []
        # create number of messages and controller index equal to number of controllers
        for n in range(1, self.ctrlNumber):
            for i in range(0, len(controller)):
                if controller[i] == n:
                    temp = i
                    self.jointIndex[n].append(temp)

    def moveAxis(self, msg):
        readMessage = msg.readMessage(0)
        # if the message is of type int
        if readMessage.getType == 1:
            #get the actual message
            payload = readMessage.getPayload()
            #store payload
            for x in range(0, readMessage.getPayloadSize()):
                self.axis[x] = payload[x]
            # create messages for the different controllers
            msgPayloadSend = []
            for m in range(0, len(self.jointIndex)):
                msgPayloadSend.clear()
                jointBuffer = self.jointIndex[m]
                for k in range(0, len(jointIndex)):
                    tempIndex = jointBuffer[k]
                    msgPayloadSend[k] = self.axis[tempIndex]
                axisMessage = ControlMessage(len(jointBuffer), msgPayloadSend)
                self.axisMsg.sendMessage(0, axisMessage)
        # if the message is not of type int, do nothing
        else:
            return None



