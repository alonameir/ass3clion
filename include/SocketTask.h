//
// Created by alonam on 1/17/17.
//

#ifndef ASS3CLION_SOCKETTASK_H
#define ASS3CLION_SOCKETTASK_H

#endif //ASS3CLION_SOCKETTASK_H
#include <connectionHandler.h>

class SocketTask{
private:
    ConnectionHandler handler;
    char bytes[];
    bool int blockNumber;

    short bytesToShort(char* bytesArr);
    void shortToBytes(short num, char* bytesArr);
    void handelWithAck();
    void handelWithError();
    void handelWithBCAST();
    void handelWithDATA();
public:
    SocketTask(ConnectionHandler c);
    ~SocketTask();
    void run();
};