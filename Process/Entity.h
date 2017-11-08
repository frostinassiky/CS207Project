//
// Created by Mengmeng Xu on 11/8/17.
//

#ifndef TANKCRAFT_ENTITY_H
#define TANKCRAFT_ENTITY_H
#include <SFML/Graphics.hpp>

// the most base class
class Entity {
private:
    sf::Vector2f mVelocity;
    float mDirection;
public:
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;

    void setDirection(float dir);
    float getDirection() const;

};


#endif //TANKCRAFT_ENTITY_H
