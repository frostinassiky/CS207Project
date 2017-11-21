//
// Created by Mengmeng Xu on 11/20/17.
//

#include "SceneNode.h"

#ifndef TANKCRAFT_OBSTACLE_H
#define TANKCRAFT_OBSTACLE_H


class Obstacle : public SceneNode{

private:
    sf::Vector2f mBound;
    sf::Sprite mSprite;
    sf::Texture mTexture;
    sf::Rect<float> mRect;
public:

    Obstacle(const std::string& path,sf::Vector2f mBound );
    virtual void updateCurrent(sf::Time dt) {};

    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {target.draw(mSprite, states);}


};


#endif //TANKCRAFT_OBSTACLE_H

//
// Created by Mengmeng Xu on 11/20/17.
//

#include "Entity.h"

