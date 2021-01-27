
#ifndef CONTROLMESSAGE
#define CONTROLMESSAGE

class ControlMessage
{
    public:
        ControlMessage(int type,int payloadSize, int* payload);
        ~ControlMessage();
        int  getType()          {return type;};
        int  getPayLoadSize()   {return payloadSize;};
        int* getPayload()       {return payload;};

    private:
        int type;
        int payloadSize;
        int* payload;
};

ControlMessage::~ControlMessage()
{
    if(payload != 0)
        delete[] payload;
}

ControlMessage::ControlMessage(int type, int payloadSize=0, int* payload=0)
{
    this->type = type;
    this->payloadSize = payloadSize;

    if(payloadSize != 0 && payload !=0)
    {
        this->payload = new int[payloadSize];
        for(int x=0; x< payloadSize;x++)
        {
            this->payload[x] = payload[x];
        }
    }
    else
    {
        this->payload = 0;
        this->payloadSize = 0;
    }
        
}

#endif