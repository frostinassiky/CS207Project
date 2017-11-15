//
// Created by Mengmeng Xu on 11/15/17.
//

#include "Label.h"

void GUI::Label::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mText, states);
}
