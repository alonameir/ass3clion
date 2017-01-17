//
// Created by romybu on 14/01/17.
//

#ifndef ASS3CLION_LOGRQ_H
#define ASS3CLION_LOGRQ_H


#include "Packet.h"

class LOGRQ: public PacketWithString {
private:
    short opcode;
public:
    LOGRQ();
    ~LOGRQ();
    LOGRQ(string str);
    short getOpcode();
};


#endif //ASS3CLION_LOGRQ_H
