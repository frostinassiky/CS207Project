//
// Created by Mengmeng Xu on 11/18/17.
//

#include <iostream>
#include "Projectile.h"
#include "Tank.h"

Projectile::Projectile(Tank::Type type) : mType(type)
{
    mCategory = CBullet;
    mTexture.loadFromFile("../Media/bullet.png");
    mSprite.setTexture(mTexture);
    mSprite.setOrigin(mSprite.getLocalBounds().width/2,mSprite.getLocalBounds().height/2);
    mSprite.setPosition(0,0);
    mSprite.setScale(2,2);

}

void Projectile::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mSprite, states);
    // std::cout<<"biu~";
}


sf::FloatRect Projectile::getBoundingRect() const
{
    return getWorldTransform()
            .transformRect(mSprite.getGlobalBounds());
}
