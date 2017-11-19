//
// Created by Mengmeng Xu on 11/10/17.
//

#ifndef TANKCRAFT_SPRITENODE_H
#define TANKCRAFT_SPRITENODE_H

// only used for background
#include "SceneNode.h"

class SpriteNode : public SceneNode{
public:
    SpriteNode(const sf::Texture& texture):  mSprite(texture){mCategory=CBackGround; };
    SpriteNode(const sf::Texture& texture, const sf::IntRect& rect) : mSprite(texture,rect) {mCategory=CBackGround;};

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::Sprite mSprite;
};


#endif //TANKCRAFT_SPRITENODE_H
