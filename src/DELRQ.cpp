//
// Created by romybu on 14/01/17.
//

#include "DELRQ.h"

DELRQ::DELRQ(): opcode(8),PacketWithString(){}

DELRQ::DELRQ(string str): PacketWithString(str),opcode(8){}

short DELRQ:: getOpcode(){
    return opcode;
}
void DELRQ:: execute(BidiMessagingProtocolPacket& p){
    p.execute(this);
}