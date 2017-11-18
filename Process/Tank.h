//
// Created by Mengmeng Xu on 11/8/17.
//

#ifndef TANKCRAFT_TANK_H
#define TANKCRAFT_TANK_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Projectile.h"

class Tank : public Entity {
public:
    enum Type {
        Ally,
        Enemy,
    };

public:
    Type mType;
    sf::Texture mTexture;
    sf::Sprite mSprite;

public:
    Tank(Type type);
    void Fire();
    void createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset) const;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

};


#endif //TANKCRAFT_TANK_H
