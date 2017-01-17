//
// Created by romybu on 14/01/17.
//

#include "Packets/DIRQ.h"

short DIRQ::getOpcode() {
    return 10;
}

DIRQ::DIRQ() : opcode(10) {}


DIRQ::~DIRQ() {
}
