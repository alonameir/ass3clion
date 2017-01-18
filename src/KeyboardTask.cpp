//
// Created by alonam on 1/16/17.
//

#include <Packets/RRQ.h>
#include <Packets/WRQ.h>
#include <Packets/ACK.h>
#include <Packets/DIRQ.h>
#include <Packets/LOGRQ.h>
#include <Packets/DELRQ.h>
#include <Packets/DISC.h>
#include "KeyboardTask.h"
#include "Packets/Packet.h"

using namespace std;


KeyboardTask::KeyboardTask
        (ConnectionHandler c, boost::mutex* mutex): connectionHandler(c), _mutex(mutex), command(""), name("") {}

void KeyboardTask:: run(){
    while (1) { /** maybe this should be an infinite loop?? **/
        /**read a line from input:**/
        string line;
        getline(cin, line);
        /**************************/
        setCommandAndName(line);
        if (command.compare("RRQ")==0){
            buildRRQ(name);
        }
        else if (command.compare("WRQ")==0){
            buildWRQ(name);
        }
        else if (command.compare("ACK")==0){
            buildACK(name);
        }
        else if (command.compare("DIRQ")==0){
            connectionHandler.sendPacketDIRQ();
        }
        else if (command.compare("LOGRQ")==0){
            buildLOGRQ(name);
        }
        else if (command.compare("DELRQ")==0){
            buildDELRQ(name);
        }
        else if (command.compare("DISC")==0){
            connectionHandler.sendPacketDISC();
        }
        else{//which means the command is illegal
            cout << "Illegal command as input. Please type again." <<endl;
        }
    }
}

void KeyboardTask::setCommandAndName(string line){
    string _command="";
    string _name="";
    int counter=0;
    for (int i = 0; i < line.size(); i = i + 1) {
        char c = line.at((unsigned long) i);
        if (c != ' ') {
            if (counter == 0)
                _command.push_back(c);
            else {
                _name.push_back(c);
            }
        } else {
            counter++;
        }
    }
}

void KeyboardTask::buildRRQ(string name){
    /** in this function, we get a name which is the fileName we want to read.
     * what we should do here is send a RRQ packet to "sendPacket" in connection Handler.
     * **/
    RRQ toSend(name);
    connectionHandler.setLastSent(1);
    connectionHandler.setFileUpload(name);
    connectionHandler.sendPacket(toSend);
}

void KeyboardTask::buildWRQ(string name){
    WRQ toSend(name);
    connectionHandler.setLastSent(2);
    connectionHandler.setFileDownload(name);
    connectionHandler.sendPacket(toSend);
    //delete??
}


void KeyboardTask::buildLOGRQ(string name) {
    LOGRQ toSend(name);
    connectionHandler.setLastSent(7);
    connectionHandler.sendPacket(toSend);
}

void KeyboardTask::buildDELRQ(string name) {
    DELRQ toSend(name);
    connectionHandler.setLastSent(8);
    connectionHandler.sendPacket(toSend);
}


KeyboardTask::~KeyboardTask() {
    //delete connectionHandler;
    //delete _mutex;
}
