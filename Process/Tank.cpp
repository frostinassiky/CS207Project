//
// Created by Mengmeng Xu on 11/8/17.
//

#include <iostream>
#include "Tank.h"
void Tank::drawCurrent( sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

Tank::Tank(Type type) : mType(type) {
    // load Tank pictures
    mTexture.loadFromFile("../Media/tanks.png");
    // Tank init
    mSprite.setTexture(mTexture);
    mSprite.setPosition(128.f, 450.f);
    // rescale
    mSprite.setScale(0.4,-0.4);
    mCategory = CTank;
    // set cloth by type
    switch (type) {
        case Ally:
            mSprite.setTextureRect(sf::IntRect(0,0,512/3, 605/3));
            break;
        case Enemy:
            mSprite.setTextureRect(sf::IntRect(0,605/3,512/3, 605/3));
            break;
    }
    // reset origin
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Tank::Fire() {
    createProjectile(*this, Projectile::Type::P1Bullet, 0,0);
    // std::cout << "Fire!" << std::endl;
}

void Tank::createProjectile(SceneNode &node, Projectile::Type type, float xOffset, float yOffset) const {
    auto projectile =new Projectile(type);
    sf::Vector2f offset(xOffset * mSprite.getGlobalBounds().width/2, yOffset * mSprite.getGlobalBounds().height/2);
    sf::Vector2f velocity(0, -projectile->getMaxSpeed());
    projectile->setPosition(offset);//getWorldPosition() );//offset );
    projectile->setVelocity(velocity );
    node.attach(projectile);
}
