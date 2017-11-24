//
// Created by Mengmeng Xu on 11/20/17.
//

#include "Obstacle.h"
#include "Utility.h"

Obstacle::Obstacle(const std::string &path, sf::Vector2f bound) : mBound(bound), mRect(){
    mTexture.loadFromFile(path);
    mSprite.setTexture(mTexture);
    centerOrigin(mSprite);
    // texture: load Tank pictures
    sf::Vector2f randP;
    randP.x = (rand() % 100)/100.f;
    randP.y = (rand() % 100)/100.f;
    setPosition(mBound.x*randP.x, mBound.y*randP.y);
    // setPosition(1000,500);
    setScale(mBound.x/mTexture.getSize().x*0.02,
             mBound.x/mTexture.getSize().x*0.02);
    mCategory = CObstacle;


}

Obstacle::Obstacle(const std::string &path, sf::Vector2f bound, int x, int y) : mBound(bound), mRect(){
    mTexture.loadFromFile(path);
    mSprite.setTexture(mTexture);
    centerOrigin(mSprite);
    // texture: load Tank pictures
    setPosition(mBound.x/2+x*mSprite.getLocalBounds().width,
                mBound.y/2+y*mSprite.getLocalBounds().height);
    mCategory = CObstacle;

}
