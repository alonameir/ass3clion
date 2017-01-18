//
// Created by romybu on 14/01/17.
//

//#include "Packets/LOGRQ.h"
#include "Packets/Packet.h"


LOGRQ::LOGRQ(): opcode(7),PacketWithString(){}

LOGRQ::LOGRQ(string str): PacketWithString(str),opcode(7){}

short LOGRQ:: getOpcode(){
    return opcode;
}

LOGRQ::~LOGRQ() {

}


