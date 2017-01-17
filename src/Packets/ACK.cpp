//
// Created by alonam on 1/14/17.
//

#include <ACK.h>
#include <BidiMessagingProtocolPacket.h>
#include "../include/Packet.h"

ACK::ACK(): opcode(4), blockNumber(-1) {}

ACK::ACK(short blockNumber): opcode(4), blockNumber(blockNumber) {}

short ACK::getOpcode() {
    return 4;
}

short ACK::getBlockNumber() {
    return blockNumber;
}

void ACK::setBlockNumber(short blockNumber) {
    this->blockNumber=blockNumber;
}

void ACK::execute(BidiMessagingProtocolPacket p){
    p.execute(this);
}
