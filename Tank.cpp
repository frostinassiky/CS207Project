//
// Created by Mengmeng Xu on 11/8/17.
//

#include <iostream>
#include "Tank.h"
#include "Projectile.h"
#include <cmath>
#define PI 3.1415926
void Tank::drawCurrent( sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

Tank::Tank(Type type) : mType(type) {
    // load Tank pictures
    mTexture.loadFromFile("../Media/tanks_c.png");
    int wid = mTexture.getSize().x;
    int hig = mTexture.getSize().y;
    // Tank init
    mSprite.setTexture(mTexture);
    mSprite.setPosition(0, 0);
    // rescale
    mSprite.setScale(0.4,-0.4);
    mCategory = CTank;
    // set cloth by type
    switch (type) {
        case PlayerUp:
            mSprite.setTextureRect(sf::IntRect(0,0,wid/3, hig/3));
            break;
        case PlayerWS:
            mSprite.setTextureRect(sf::IntRect(wid/3,hig/3,wid/3, hig/3));
            break;
        case PlayerNet:
            mSprite.setTextureRect(sf::IntRect(0,2*hig/3,wid/3, hig/3));
            break;
    }
    // reset origin
    sf::IntRect bounds = mSprite.getTextureRect();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    /*
    std::cout << "Position debug:" << std::endl;
    std::cout << mSprite.getTextureRect().left << " " << mSprite.getTextureRect().top << " " << mSprite.getTextureRect().height << " "<< mSprite.getTextureRect().width << std::endl;
    std::cout << mSprite.getLocalBounds().left << " " << mSprite.getLocalBounds().top << " " << mSprite.getLocalBounds().height << " "<< mSprite.getLocalBounds().width << std::endl;
    std::cout << mSprite.getGlobalBounds().left << " " << mSprite.getGlobalBounds().top << " " << mSprite.getGlobalBounds().height << " "<< mSprite.getGlobalBounds().width << std::endl;
    std::cout << mSprite.getOrigin().x <<" "<< mSprite.getOrigin().y;
*/
}

void Tank::Fire(Tank::Type type) {
    if (mType!=type)
        return;
    createProjectile(*this, mType);
    // std::cout << "Fire!" << std::endl;
}

void Tank::createProjectile(SceneNode &node, Tank::Type type)  {
    SceneNode* projectile =new Projectile(type);
    tankBullets_.push_back(projectile);
    sf::Vector2f pos = this->getWorldPosition();
    sf::Vector2f vol = this->getVelocity();
    float v = 400;
    float dir = this->getRotation();
    std::cout << dir << std::endl;
    projectile->setPosition(pos);//getWorldPosition() );//offset );
    vol.x += v*sin(PI-dir*PI/180.f);
    vol.y += v*cos(PI-dir*PI/180.f);
    dynamic_cast<Projectile*>(projectile)->setVelocity(vol);
    dynamic_cast<Projectile*>(projectile)->setRotation(dir);
    node.getParent()->attach(projectile);
//    node.attach(projectile);

}

void Tank::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    // friction
    float alpha = .05f;
    this->setVelocity(this->getVelocity()*(1.f-alpha));
}


sf::FloatRect Tank::getBoundingRect() const
{
    return getWorldTransform()
            .transformRect(mSprite.getGlobalBounds());
}
