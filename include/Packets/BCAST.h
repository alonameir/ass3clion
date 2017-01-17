//
// Created by alonam on 1/14/17.
//

#ifndef ASS3CLION_BCAST_H
#define ASS3CLION_BCAST_H
#include <vector>
#include "Packet.h"

class BCAST {
private:
    short opcode;
    char deletedOrAdded;
    string fileName;
    char lastByte;
public:
    BCAST();
    ~BCAST();
    BCAST(char deletedOrAdded, string str);
    short getOpcode();
    char getDeletedOrAdded();
    void setDeletedOrAdded(char deletedOrAdded);
    string getFileName();
    void setFileName(string fileName);
    void execute(BidiMessagingProtocolPacket p);

};


#endif //ASS3CLION_BCAST_H
