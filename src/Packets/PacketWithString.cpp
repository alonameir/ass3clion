//
// Created by romybu on 14/01/17.
//
#include <string>
#include "Packets/Packet.h"

PacketWithString::PacketWithString(): s(""), lastByte('0'){}
PacketWithString::~PacketWithString(){};
PacketWithString::PacketWithString(string str): s(str), lastByte('0'){};

string PacketWithString:: getString(){
    return s;
}

char PacketWithString:: getLastByte(){
    return lastByte;
}

void PacketWithString:: setString(string& str){
    s.append(str);
}

