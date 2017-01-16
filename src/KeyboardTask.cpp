//
// Created by alonam on 1/16/17.
//

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

        }
        else if (command.compare("ACK")==0){

        }
        else if (command.compare("DIRQ")==0){

        }
        else if (command.compare("LOGRQ")==0){

        }
        else if (command.compare("DELRQ")==0){

        }
        else if (command.compare("DISC")==0){

        }
        else{//which means the command is illegal

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

}

