//
// Created by Mengmeng Xu on 11/20/17.
//

#include "Cloud.h"
#include "Utility.h"

Cloud::Cloud(const std::string& path, sf::Vector2f bound, sf::Uint8 alpha) : mBound(bound),mSprite(){
    mTexture.loadFromFile(path);
    mSprite.setTexture(mTexture);
    centerOrigin(mSprite);
    // texture: load Tank pictures
    sf::Vector2f randP;
    randP.x = (rand() % 100)/100.f;
    randP.y = (rand() % 100)/100.f;
    setPosition(mBound.x*randP.x, mBound.y*randP.y);
    // setPosition(1000,500);
    randP.x = (rand() % 100-50)/50.f;
    randP.y = (rand() % 100-50)/50.f;
    setScale(mBound.x/mTexture.getSize().x*randP.x,
                mBound.x/mTexture.getSize().x*randP.x);
    setVelocity(0,10);
    setDirection(1);
    mSprite.setColor(sf::Color(255,255,255,alpha));
    mCategory = CCloud;

}

void Cloud::updateCurrent(sf::Time dt) {
    float alpha = .005f;
    float vol = 5.f;
    sf::Vector2f randV( vol*(rand() % 100-50)/50.f, vol*(rand() % 100-50)/50.f);
    this->setVelocity(this->getVelocity()*(1.f-alpha)+randV);
    Entity::updateCurrent(dt);
}

void Cloud::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}


