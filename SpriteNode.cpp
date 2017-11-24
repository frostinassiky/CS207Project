//
// Created by Mengmeng Xu on 11/10/17.
//

#include "SpriteNode.h"

void SpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}
