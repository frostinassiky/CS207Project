//
// Created by Mengmeng Xu on 11/18/17.
//

#ifndef TANKCRAFT_PROJECTILE_H
#define TANKCRAFT_PROJECTILE_H

#include <iostream>
#include "Entity.h"

class Projectile : public Entity {
public:
    enum Type
    {
        P1Bullet,
        P2Bullet,
        P3Bullet,
        TypeCount
    };
private:
    Type mType;
    sf::Sprite mSprite;
    sf::Vector2f mTargetDir;
    sf::Texture mTexture;

private:
    virtual void updateCurrent(sf::Time dt) {
        Entity::updateCurrent(dt);
        // std::cout << "move~ " << this->getVelocity().y ;
    }

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Projectile(Type type);
    float getMaxSpeed() const { return 200.f; };
/*
    void guideTowards(sf::Vector2f position);
    virtual unsigned int getCategory() const;
    virtual sf::FloatRect getBoundingRect() const;

    int getDamage() const;
    */
};


#endif //TANKCRAFT_PROJECTILE_H
