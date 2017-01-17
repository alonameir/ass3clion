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

using namespace std;


KeyboardTask::KeyboardTask
        (ConnectionHandler c, boost::mutex* mutex): connectionHandler(c), _mutex(mutex), command(""), name("") {}

void KeyboardTask:: run(){
    while (1) {
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
            buildDIRQ();
        }
        else if (command.compare("LOGRQ")==0){
            buildLOGRQ(name);
        }
        else if (command.compare("DELRQ")==0){
            buildDELRQ(name);
        }
        else if (command.compare("DISC")==0){
            buildDISC();
            break; //here i should exit the loop and disconnect once i get an ACK in return
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
    RRQ* toSend=new RRQ(name);
    connectionHandler.sendPacket(*toSend);
}

void KeyboardTask::buildWRQ(string name){
    WRQ* toSend=new WRQ(name);
    connectionHandler.sendPacket(*toSend);
}

void KeyboardTask::buildDIRQ() {
    DIRQ* toSend=new DIRQ();
    connectionHandler.sendPacket(*toSend);
}

void KeyboardTask::buildLOGRQ(string name) {
    LOGRQ* toSend=new LOGRQ(name);
    connectionHandler.sendPacket(*toSend);
}

void KeyboardTask::buildDELRQ(string name) {
    DELRQ* toSend= new DELRQ(name);
    connectionHandler.sendPacket(*toSend);
}

void KeyboardTask::buildDISC() {
    DISC* toSend=new DISC();
    connectionHandler.sendPacket(*toSend);
}
