//
// Created by Mengmeng Xu on 11/8/17.
//

#ifndef TANKCRAFT_ENTITY_H
#define TANKCRAFT_ENTITY_H
#include <SFML/Graphics.hpp>
#include "SceneNode.h"

// the most base class
class Entity : public SceneNode{
private:
    sf::Vector2f mVelocity;
    float mDirection;

public:
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;

    void setDirection(float dir);
    float getDirection() const;

private:
    // update Entity
    virtual void updateCurrent(sf::Time dt);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {};

};


#endif //TANKCRAFT_ENTITY_H
