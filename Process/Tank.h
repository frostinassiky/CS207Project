//
// Created by Mengmeng Xu on 11/8/17.
//

#ifndef TANKCRAFT_TANK_H
#define TANKCRAFT_TANK_H

#include "Entity.h"

class Tank : public Entity{
public:
    enum Type{
        Ally,
        Enemy,
    };

private:
    Type mType;
public:
    Tank(Type type): mType(type) {};
};


#endif //TANKCRAFT_TANK_H
