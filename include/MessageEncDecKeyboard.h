//
// Created by alonam on 1/14/17.
//

#ifndef ASS3CLION_MESSAGEENCDECKEYBOARD_H
#define ASS3CLION_MESSAGEENCDECKEYBOARD_H

#endif //ASS3CLION_MESSAGEENCDECKEYBOARD_H
using namespace std;
#include <string>

class MessageEncDecKeyboard{
private:
    string command;
    string name;

public:
    void readFromKeyboard(string s);
    void setCommand(string _command);
    void setName(string _name);
};