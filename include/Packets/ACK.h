
#ifndef ASS3CLION_ACK_H
#define ASS3CLION_ACK_H

#endif //ASS3CLION_ACK_H
#include "Packet.h"

class ACK: public Packet {

private:
    short opcode;
    short blockNumber;

public:
    ACK();
    ACK(short blockNumber);
    short getOpcode();
    short getBlockNumber();
    void setBlockNumber(short blockNumber);
//    void execute(BidiMessagingProtocolPacket p);
};