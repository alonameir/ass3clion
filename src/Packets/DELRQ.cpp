//
// Created by romybu on 14/01/17.
//

//#include "Packets/DELRQ.h"
#include "Packets/Packet.h"

DELRQ::DELRQ(): opcode(8),PacketWithString(){}

DELRQ::DELRQ(string str): PacketWithString(str),opcode(8){}

short DELRQ:: getOpcode(){
    return opcode;
}

DELRQ::~DELRQ() {
}
