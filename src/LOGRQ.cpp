//
// Created by romybu on 14/01/17.
//

#include "LOGRQ.h"

LOGRQ::LOGRQ(): opcode(7),PacketWithString(){}

LOGRQ::LOGRQ(string str): opcode(7),PacketWithString(str){}

short LOGRQ:: getOpcode(){
    return opcode;
}
void LOGRQ:: execute(BidiMessagingProtocolPacket& p){
    p.execute(this);
}

