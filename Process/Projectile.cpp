//
// Created by Mengmeng Xu on 11/18/17.
//

#include <iostream>
#include "Projectile.h"

Projectile::Projectile(Projectile::Type type) : mType(type)
{
    mTexture.loadFromFile("../Media/Bullet.png");
    mSprite.setTexture(mTexture);
    mSprite.setOrigin(mSprite.getLocalBounds().width/2,mSprite.getLocalBounds().height/2);
    mSprite.setPosition(0,0);

}

void Projectile::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mSprite, states);
    std::cout<<"biu~";
}
