//
// Created by Mengmeng Xu on 11/18/17.
//

#include "Projectile.h"

Projectile::Projectile(Projectile::Type type) :
        Entity()
        , mType(type)
{
    auto texture = new sf::Texture;
    texture->loadFromFile("../Media/Bullet.png");
    mSprite.setTexture(*texture);
    mSprite.setOrigin(mSprite.getLocalBounds().width/2,mSprite.getLocalBounds().height/2);

}
