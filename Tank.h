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
#include <stack>
#include <SFML/Audio/Music.hpp>

//extern class Projectile;
class Tank : public Entity {
public:
    enum Type {
        PlayerWS,
        PlayerUp,
        PlayerNet,
        Count
    };

private:
    sf::Texture mTexture;
    sf::Sprite mSprite;
private:
    void obstacleTest(SceneNode* ob);
    int HP;
    const float mWeight = 30; // Tank and bullet
    const float mCDBullet = 1; // bullet cd second
    const float mCDHP = 2; // HP cd second
    float mCDBulletCount;
    float mCDHPCount;
    sf::Music mSoundFire;
    sf::Music mSoundWall;
    sf::Music mSoundHit1;
    sf::Music mSoundHit2;
    sf::Music mSoundExp;
    sf::Music mSoundDriving;
public:
    Type mType;
    std::list<SceneNode*> tankBullets_;
public:
    Tank(Type type);
    virtual void updateCurrent(sf::Time dt);
    float getMaxV() { return 900.f; };
    void Fire(Type type);
    void createProjectile(SceneNode& node, Tank::Type type);
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual sf::FloatRect getBoundingRect() const;
    void shotTest(SceneNode* bullet);
    void gotoBullets(const std::list<SceneNode*>& bullets);
    void gotoOb(const std::list<SceneNode*>&  obstacles, sf::FloatRect mWorldBounds);
    void bulletShotOb(const std::list<SceneNode*>&  obstacles);
    bool lost() { return HP<=0; }
    void reset() {HP = 4;}
};
//class Projectile;
#endif //TANKCRAFT_TANK_H
