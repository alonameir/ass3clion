//
// Created by alonam on 1/14/17.
//

#include <DISC.h>
#include "../include/Packet.h"

using namespace std;


short DISC::getOpcode() {
    return 10;
}

DISC::DISC() : opcode(10) {}

void DISC:: execute(BidiMessagingProtocolPacket& p){
    p.execute(this);
}