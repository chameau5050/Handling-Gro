class ControlMessage:
    def __init__(self,type,payload=[]):
        self.type = type
        self.payload = payload

    def getType(self):
        return self.type

    def getPayloadSize(self):
        return len(self.payload)

    def getPayload(self):
        return self.payload
