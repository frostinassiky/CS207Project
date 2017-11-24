//
// Created by Mengmeng Xu on 11/12/17.
//

#include "CommandQ.h"

Command CommandQ::pop() {
    Command command = mQueue.front();
    mQueue.pop();
    return command;
}
