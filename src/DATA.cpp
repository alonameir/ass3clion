//
// Created by alonam on 1/14/17.
//


#include <DATA.h>
#include "../include/Packet.h"

//DATA::DATA(short packetSize): opcode(3), packetSize(packetSize), blockNumber(0), index(0), data() {}

DATA::DATA():  opcode(3), packetSize(0), blockNumber(0), index(0), data()  {}


short DATA::getOpcode() {
    return 3;
}

short DATA::getPacketSize() {
    return packetSize;
}

void DATA::setPacketSize(short ps) {
    this->packetSize=ps;
}

short DATA::getBlockNumber() {
    return blockNumber;
}

void DATA::setBlockNumber(short blockNumber) {
    this->blockNumber=blockNumber;
}

vector<char> DATA::getData() {
    return data;
}

void DATA::addToData(char b) {
    data.push_back(b);
}
