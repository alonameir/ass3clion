//
// Created by romybu on 14/01/17.
//

#ifndef ASS3CLION_DELRQ_H
#define ASS3CLION_DELRQ_H
#include "Packet.h"
#include "BidiMessagingProtocolPacket.h"

class DELRQ : public PacketWithString {
private:
    short opcode;
public:
    DELRQ();
    ~DELRQ();
    DELRQ(string str);
    short getOpcode();
};




#endif //ASS3CLION_DELRQ_H
