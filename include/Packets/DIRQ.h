//
// Created by romybu on 14/01/17.
//

#ifndef ASS3CLION_DIRQ_H
#define ASS3CLION_DIRQ_H


#include "Packet.h"
#include "BidiMessagingProtocolPacket.h"

class DIRQ: public Packet{
private:
    short opcode;
public:
    DIRQ();
    ~DIRQ();
    short getOpcode();
    void execute(BidiMessagingProtocolPacket& p);
};

#endif //ASS3CLION_DIRQ_H
