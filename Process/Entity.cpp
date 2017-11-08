//
// Created by Mengmeng Xu on 11/8/17.
//

#include "Entity.h"

void Entity::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
    return mVelocity;
}

void Entity::setDirection(float dir)
{
    // default in degree
    while (dir > 180)   dir -= 360;
    while (dir < -180)   dir += 360;
    mDirection = dir;
}
float Entity::getDirection() const
{
    return mDirection;
}
