//
// Created by romybu on 14/01/17.
//

//#include "Packets/RRQ.h"
#include "Packets/Packet.h"


RRQ::RRQ(): opcode(1),PacketWithString(){}

RRQ::RRQ(string str): PacketWithString(str),opcode(1){}

short RRQ:: getOpcode(){
    return opcode;
}

RRQ::~RRQ() {

}
