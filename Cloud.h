//
// Created by Mengmeng Xu on 11/20/17.
//

#include "Entity.h"

#ifndef TANKCRAFT_CLOUD_H
#define TANKCRAFT_CLOUD_H

// No collision detection
// float on sky layer
class Cloud : public Entity {
private:
    sf::Vector2f mBound;
    sf::Sprite mSprite;
    sf::Texture mTexture;
public:

    Cloud(const std::string &path, sf::Vector2f bound, sf::Uint8);

    virtual void updateCurrent(sf::Time dt);

    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

};


#endif //TANKCRAFT_CLOUD_H