//
// Created by alonam on 1/14/17.
//


#include <DATA.h>
#include "../include/Packet.h"

DATA::DATA(short packetSize): opcode(3), packetSize(packetSize), blockNumber(0),  {}

DATA::DATA():  {

}

DATA::DATA(short packetSize, vector<char> data, short blockNumber) {

}

short DATA::getOpcode() {
    return 0;
}

short DATA::getPacketSize() {
    return 0;
}

void DATA::setPacketSize(short ps) {

}

short DATA::getBlockNumber() {
    return 0;
}

void DATA::setBlockNumber(short blockNumber) {

}

vector<char> DATA::getData() {
    return vector<char>();
}

void DATA::initDataArray(short size) {

}

void DATA::addToData(char b) {

}
