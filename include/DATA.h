//
// Created by alonam on 1/14/17.
//

#ifndef ASS3CLION_DATA_H
#define ASS3CLION_DATA_H

#endif //ASS3CLION_DATA_H

#include <vector>
#include "Packet.h"

class DATA: public Packet{
private:
    short opcode;
    short packetSize;
    short blockNumber;
    vector<char> data;
    int index;

public:
    DATA(short packetSize);
    DATA();
    DATA(short packetSize, vector<char> data, short blockNumber );
    short getOpcode();
    short getPacketSize();
    void setPacketSize(short ps);
    short getBlockNumber();
    void setBlockNumber(short blockNumber);
    vector<char> getData(); //TODO: CHECK IF WE NEED TO RETURN POINTER
    void initDataArray(short size);
    void addToData(char b);
    void execute(BidiMessagingProtocolPacket p);

};