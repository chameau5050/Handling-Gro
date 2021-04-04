class ControlMessage:
    SET_HOME = 3
    SET_JOIN_POSITION = 7
    SET_CARTESIAN_POSITION = 8
    GOTO_HOME = 9
    OPEN_GRIPPER = 10
    CLOSE_GRIPPER = 12

    def __init__(self, type, payload=[]):
        self.type = type
        self.payload = payload

    def getType(self):
        return self.type

    def getPayloadSize(self):
        return len(self.payload)

    def getPayload(self):
        return self.payload
