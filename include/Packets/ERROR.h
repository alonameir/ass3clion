//
// Created by alonam on 1/14/17.
//

#ifndef ASS3CLION_ERROR_H
#define ASS3CLION_ERROR_H

#endif //ASS3CLION_ERROR_H

#include "Packet.h";

class ERROR: public Packet{
private:
    short opcode;
    short errorCode;
    string str;
    char byte;
public:
    ERROR();
    ~ERROR();
    short getOpcode();
    short getErrorcode();
    void setErrorcode(short errcode);
    string getStr();
    void setStr(string msg);
};