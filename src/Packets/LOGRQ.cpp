//
// Created by romybu on 14/01/17.
//

#include "Packets/LOGRQ.h"

LOGRQ::LOGRQ(): opcode(7),PacketWithString(){}

LOGRQ::LOGRQ(string str): PacketWithString(str),opcode(7){}

short LOGRQ:: getOpcode(){
    return opcode;
}

LOGRQ::~LOGRQ() {

}

void LOGRQ:: execute(BidiMessagingProtocolPacket p){
    //p.execute(this);
}

