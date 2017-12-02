//
// Created by Mengmeng Xu on 11/20/17.
//

#include "SceneNode.h"

#ifndef TANKCRAFT_OBSTACLE_H
#define TANKCRAFT_OBSTACLE_H

// Scene obstacle cannot move, it is from SceneNode
// There was a mistake on the slide!!
class Obstacle : public SceneNode {

private:
    sf::Vector2f mBound;
    sf::Sprite mSprite;
    sf::Texture mTexture;
    sf::Rect<float> mRect; // collision boundary
public:

    Obstacle(const std::string &path, sf::Vector2f mBound);

    Obstacle(const std::string &path, sf::Vector2f mBound, int x, int y);

    virtual void updateCurrent(sf::Time dt) {};

    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const { target.draw(mSprite, states); }

    virtual sf::FloatRect getBoundingRect() const;
};

#endif //TANKCRAFT_OBSTACLE_H

