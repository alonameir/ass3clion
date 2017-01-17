//
// Created by alonam on 1/14/17.
//

#include <Packets/ACK.h>
#include "Packets/Packet.h"

ACK::ACK(): opcode(4), blockNumber(-1) {}
ACK::~ACK(){}

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

