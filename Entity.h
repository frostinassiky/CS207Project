//
// Created by Mengmeng Xu on 11/8/17.
//

#ifndef TANKCRAFT_ENTITY_H
#define TANKCRAFT_ENTITY_H

#include <SFML/Graphics.hpp>
#include "SceneNode.h"

// the most base class
class Entity : public SceneNode {
private:
    // record both current and last position
    sf::Vector2f mVelocity;
    sf::Vector2f mLastPosotion;
    float mDirection;
    float mLastRotation;
public:
    void setVelocity(sf::Vector2f velocity);

    void setVelocity(float vx, float vy);

    sf::Vector2f getVelocity() const;

    void setDirection(float dir);

    float getDirection() const;

public:
    // update Entity
    virtual void updateCurrent(sf::Time dt);

    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {};

    void lastCondition(); // used when collision detected

};


#endif //TANKCRAFT_ENTITY_H
