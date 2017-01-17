//
// Created by romybu on 14/01/17.
//

#include "Packets/WRQ.h"


WRQ::WRQ(): opcode(2),PacketWithString(){}

WRQ::WRQ(string str): PacketWithString(str),opcode(2){}

short WRQ:: getOpcode(){
    return opcode;
}
void WRQ:: execute(BidiMessagingProtocolPacket& p){
    p.execute(this);
}