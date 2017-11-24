//
// Created by Mengmeng Xu on 11/8/17.
//

#ifndef TANKCRAFT_TANK_H
#define TANKCRAFT_TANK_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
//#include "Projectile.h"
#include <vector>
#include <list>
//extern class Projectile;
class Tank : public Entity {
public:
    enum Type {
        PlayerWS,
        PlayerUp,
        PlayerNet,
        Count
    };

public:
    Type mType;
    sf::Texture mTexture;
    sf::Sprite mSprite;

public:
    Tank(Type type);
    virtual void updateCurrent(sf::Time dt);
    float getMaxV() { return 300.f; };
    void Fire(Type type);
    void createProjectile(SceneNode& node, Tank::Type type);
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual sf::FloatRect getBoundingRect() const;
    std::list<SceneNode*> tankBullets_;
};
//class Projectile;
#endif //TANKCRAFT_TANK_H
