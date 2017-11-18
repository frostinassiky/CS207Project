//
// Created by Mengmeng Xu on 11/15/17.
//

#include "Container.h"

void GUI::Container::handleEvent(sf::Event &event){
    if (hasSelection() && mChildren[mSelected]->isActive())
        mChildren[mSelected]->handleEvent(event);
    else if (event.type == sf::Event::KeyReleased){
        switch (event.key.code) {
            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                selectPrevious();
                break;
            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                selectNext();
                break;
            case sf::Keyboard::D:
            case sf::Keyboard::Right:
            case sf::Keyboard::Return:
            case sf::Keyboard::Space:
                if (hasSelection()) mChildren[mSelected]->activate();
                break;
            default:
                break;
        }
    }
}

void GUI::Container::select(int t) {
    if (mChildren[t]->isSelectable()) {
        if (hasSelection())
            mChildren[mSelected]->deselect();
        mChildren[t]->select();
        mSelected = t;
    }
}

void GUI::Container::selectPrevious() {
    if (!hasSelection())    return;
    int t = mSelected, s = (int)mChildren.size();
    do {
        t = (t + s - 1) % s;
    } while (mChildren[t]->isSelectable());
    select(t);
}

void GUI::Container::selectNext() {
    if (!hasSelection())    return;
    int t = mSelected, s = (int)mChildren.size();
    do {
        t = (t + 1) % s;
    } while (mChildren[t]->isSelectable());
    select(t);
}
