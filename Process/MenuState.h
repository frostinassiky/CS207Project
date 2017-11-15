//
// Created by Yang on 15/11/2017.
//

#ifndef TANKCRAFT_MENUSTATE_H
#define TANKCRAFT_MENUSTATE_H


#include "State.h"

class MenuState : public State{
public:
    MenuState(StateStack& stack, Context context);

    virtual void			draw();
    virtual bool			update(sf::Time dt);
    virtual bool			handleEvent(const sf::Event& event);

    // void					updateOptionText();


private:
    enum OptionNames
    {
        Play,
        Exit,
    };


private:
    sf::Sprite				mBackgroundSprite;

    std::vector<sf::Text>	mOptions;
    std::size_t				mOptionIndex;
};


#endif //TANKCRAFT_MENUSTATE_H
