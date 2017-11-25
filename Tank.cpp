//
// Created by Mengmeng Xu on 11/8/17.
//

#include <iostream>
#include "Tank.h"
#include "Projectile.h"
#include "Obstacle.h"
#include <cmath>
#define PI 3.1415926
void Tank::drawCurrent( sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

Tank::Tank(Type type) : mType(type), HP(4),
                        mCDBulletCount(0),mCDHPCount(0){
    // load Tank pictures
    mTexture.loadFromFile("../Media/tanks_c.png");
    int wid = mTexture.getSize().x;
    int hig = mTexture.getSize().y;
    // Tank init
    mSprite.setTexture(mTexture);
    mSprite.setPosition(0, 0);
    // rescale
    mSprite.setScale(0.4,0.4);
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
    // load music
    mSoundFire.openFromFile("../Media/Sounds/TankFiring.wav");
    mSoundHit2.openFromFile("../Media/Sounds/TankHit.wav");
    mSoundHit1.openFromFile("../Media/Sounds/ShotCar.wav");
    mSoundWall.openFromFile("../Media/Sounds/ShotWall.wav");
    mSoundExp.openFromFile("../Media/Sounds/TankExplosion.wav");
    mSoundDriving.openFromFile("../Media/Sounds/TankDriving.wav");
}

void Tank::Fire(Tank::Type type) {
    if (mType!=type || mCDBulletCount > 0)
        return;
    createProjectile(*this, mType);
    mCDBulletCount = mCDBullet;
    // std::cout << "Fire!" << std::endl;
}

void Tank::createProjectile(SceneNode &node, Tank::Type type)  {
    // info
    sf::Vector2f pos = this->getWorldPosition();
    sf::Vector2f vol = this->getVelocity();
    // play sound
    mSoundFire.play();
    // create bullet
    SceneNode* projectile =new Projectile(type);
    tankBullets_.push_back(projectile);
    float v = 400;
    float dir = this->getRotation();
    // std::cout << dir << std::endl;
    projectile->setPosition(pos);//getWorldPosition() );//offset );
    vol.x += v*sin(-dir*PI/180.f);
    vol.y += v*cos(-dir*PI/180.f);
    dynamic_cast<Projectile*>(projectile)->setVelocity(vol);
    dynamic_cast<Projectile*>(projectile)->setRotation(180+dir);
    node.getParent()->attach(projectile);
//    node.attach(projectile);
    // decrease current valocity
    setVelocity(getVelocity().x-vol.x/mWeight,getVelocity().y-vol.y/mWeight);

}

void Tank::updateCurrent(sf::Time dt) {
    // pause sound
    mSoundDriving.pause();
    // count down CDs
    if (mCDBulletCount > 0) mCDBulletCount -= dt.asSeconds();

    if (mCDHPCount > 0) mCDHPCount -= dt.asSeconds();
    Entity::updateCurrent(dt);
    // friction
    float alpha = .05f;
    sf::Vector2f v(getVelocity());
    float dir = getRotation();
    float vx = v.x*sin(-dir*PI/180)+v.y*cos(-dir*PI/180);
    vx *= 1.f-alpha;
    this->setVelocity(vx*sin(-dir*PI/180),vx*cos(-dir*PI/180));
    // sound
    mSoundDriving.setVolume(abs(vx)*20);
    mSoundDriving.play();
}


sf::FloatRect Tank::getBoundingRect() const
{
    return getWorldTransform()
            .transformRect(mSprite.getGlobalBounds());
}

void Tank::shotTest(SceneNode *bullet) {
    if (mCDHPCount > 0) return; // CD
    if ((dynamic_cast<Projectile *> (bullet)->getBoundingRect().intersects(
            getBoundingRect()))) {
        // play sound
        switch (HP){
            case 4:
                mSoundHit1.play(); break;
            default:
                mSoundHit2.play(); break;
        }

        // change v
        sf::Vector2f v(dynamic_cast<Projectile *>(bullet)->getVelocity());
        v.x = v.x*(1/mWeight)+getVelocity().x;
        v.y = v.y*(1/mWeight)+getVelocity().y;
        setVelocity(v); // add bullet moment
        HP--; // decrease HP
        std::cout << "HP" << HP << std::endl;
        mCDHPCount = mCDHP; // CD start
        if (HP==0) mSoundExp.play();
    }
}

void Tank::obstacleTest(SceneNode *ob) {
    if ((dynamic_cast<Obstacle *> (ob)->getBoundingRect().intersects(
            getBoundingRect()))) {
        sf::Vector2f v(getVelocity());
        setVelocity(v.x/8, v.y/8);
        lastCondition();
    }

}

void Tank::bulletShotOb(const std::list<SceneNode*>&  obstacles) {
    std::stack<SceneNode *> bulletStack;
    for (auto bullet : tankBullets_)
        if (dynamic_cast<Projectile *>(bullet)->obstacleTest(obstacles)){
            mSoundWall.play();
            bulletStack.push(bullet);
        }

    while (!bulletStack.empty()) {
        getParent()->detach(bulletStack.top());
        tankBullets_.remove(bulletStack.top());
        delete bulletStack.top();
        bulletStack.pop();
    }

}

void Tank::gotoOb(const std::list<SceneNode *> &obstacles) {
    for (auto ob:obstacles)
        obstacleTest(ob);
}

void Tank::gotoBullets(const std::list<SceneNode *> &bullets) {
    for (auto bullet : bullets)
        shotTest(bullet);

}
