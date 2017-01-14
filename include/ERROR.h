//
// Created by romybu on 14/01/17.
//
#include "Packet.h"

#ifndef ASS3CLION_ERROR_H
#define ASS3CLION_ERROR_H
#endif //ASS3CLION_ERROR_H


class ERROR: public Packet{
private:
    short opcode;
    short errorCode;
    string msg;
    char lastByte;
public:
    ERROR();
    short getOpcode();
    void execute(BidiMessagingProtocolPacket& p);
    short getErrorCode();
    void setErrorCode(short errorCode);
    string getErrMsg();
    void setErrMsg(String errMsg);
};


