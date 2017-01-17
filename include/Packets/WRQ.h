//
// Created by romybu on 14/01/17.
//

#ifndef ASS3CLION_WRQ_H
#define ASS3CLION_WRQ_H

#include "Packet.h"

class WRQ: public PacketWithString {
private:
    short opcode;
public:
    WRQ();
    ~WRQ();
    WRQ(string str);
    short getOpcode();
};




#endif //ASS3CLION_WRQ_H
