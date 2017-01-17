//
// Created by alonam on 1/14/17.
//

#include "Packet.h"
#include "BidiMessagingProtocolPacket.h"

#ifndef ASS3CLION_DISC_H
#define ASS3CLION_DISC_H

#endif //ASS3CLION_DISC_H

class DISC: public Packet{
private:
    short opcode;
public:
    DISC();
    short getOpcode();
    void execute(BidiMessagingProtocolPacket& p);
};