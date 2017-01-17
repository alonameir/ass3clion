//
// Created by alonam on 1/16/17.
//

#ifndef ASS3CLION_KEYBOARDTASK_H
#define ASS3CLION_KEYBOARDTASK_H
#include <iostream>
#include <boost/thread.hpp>
#include "connectionHandler.h"
#include <string>

using namespace std;

#endif //ASS3CLION_KEYBOARDTASK_H

class KeyboardTask{
private:
    ConnectionHandler connectionHandler;
    boost::mutex * _mutex;
    string command;
    string name;
public:

    KeyboardTask(ConnectionHandler c, boost::mutex* mutex);

    void run();

    void setCommandAndName(string line);

    void buildRRQ(string name);

    void buildWRQ(string name);

    void buildACK(string blockNumber);

    void buildLOGRQ(string name);

    void buildDELRQ(string name);

};
