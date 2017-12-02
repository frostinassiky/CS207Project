//
// Created by Yang on 15/11/2017.
//

#ifndef TANKCRAFT_MENUSTATE_H
#define TANKCRAFT_MENUSTATE_H

// The first state: menu
#include "State.h"
#include "Container.h"

class MenuState : public State {
private:
    sf::Texture mTexture;
    sf::Sprite mBackgroundSprite;
    std::vector<sf::Text> mOptions;
    std::size_t mOptionIndex;
    GUI::Container mGUIContainer;

public:
    MenuState(StateStack &stack, Context context);

    virtual void draw();

    virtual bool update(sf::Time dt);

    virtual bool handleEvent(const sf::Event &event);

};


#endif //TANKCRAFT_MENUSTATE_H
