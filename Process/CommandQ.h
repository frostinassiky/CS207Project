//
// Created by Mengmeng Xu on 11/12/17.
//

#ifndef TANKCRAFT_COMMANDQ_H
#define TANKCRAFT_COMMANDQ_H

#include <SFML/System.hpp>
#include <queue>
#include "SceneNode.h"

class SceneNode; // TODO know why

struct Command{
    int category =1;
    std::function<void(SceneNode&, sf::Time)> action;
};



class CommandQ {

public:
    CommandQ(): mQueue() {};
    void push(const Command& command) {mQueue.push(command);};
    Command pop();
    bool isEmpty() const {return mQueue.empty(); };

private:
    std::queue<Command> mQueue;
};


#endif //TANKCRAFT_COMMANDQ_H
