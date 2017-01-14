//
// Created by romybu on 14/01/17.
//

#include "DIRQ.h"

short DIRQ::getOpcode() {
    return 10;
}

DIRQ::DIRQ() : opcode(10) {}

void DIRQ:: execute(BidiMessagingProtocolPacket& p){
    p.execute(this);
}