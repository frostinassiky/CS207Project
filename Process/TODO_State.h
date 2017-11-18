//
// Created by Yang on 18/11/2017.
//

#ifndef TANKCRAFT_TODO_STATE_H
#define TANKCRAFT_TODO_STATE_H


#include "State.h"

class TODO_State : public State{
public:
    TODO_State(StateStack& stack, Context context);

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const sf::Event& event);


private:
    sf::Sprite			mBackgroundSprite;
    sf::Text			mPausedText;
    sf::Text			mInstructionText;
    sf::Font            mFont;

};

#endif //TANKCRAFT_TODO_STATE_H
