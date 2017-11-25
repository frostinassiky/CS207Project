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
    const float mWeight = 300; // Tank and bullet

public:
    Type mType;
    std::list<SceneNode*> tankBullets_;
public:
    Tank(Type type);
    virtual void updateCurrent(sf::Time dt);
    float getMaxV() { return 300.f; };
    void Fire(Type type);
    void createProjectile(SceneNode& node, Tank::Type type);
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual sf::FloatRect getBoundingRect() const;
    void shotTest(SceneNode* bullet);
    void gotoBullets(const std::list<SceneNode*>& bullets);
    void gotoOb(const std::list<SceneNode*>&  obstacles);
    void bulletShotOb(const std::list<SceneNode*>&  obstacles);
    bool lost() { return HP<=0; }
};
//class Projectile;
#endif //TANKCRAFT_TANK_H
