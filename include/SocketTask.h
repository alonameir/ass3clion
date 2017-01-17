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
    short blockNumber;
    char* toSend;
    bool upLoadfinished;
    long sizeToSend;
    long counterSend;
    short packetSizeData;
    short currentNumOfBlockACK;
    FILE * dataFile;

    short bytesToShort(char* bytesArr);
    void shortToBytes(short num, char* bytesArr);
    int handelWithAck();
    void handelWithError();
    void handelWithBCAST();
    void handelWithDATA();
    void keepUploading(short currentBlock);
    void keepHanderWithData();
public:
    SocketTask(ConnectionHandler& c);
    ~SocketTask();
    void run();
};