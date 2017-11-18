//
// Created by Yang on 15/11/2017.
//

#ifndef TANKCRAFT_PAUSESTATE_H
#define TANKCRAFT_PAUSESTATE_H


#include "State.h"

class PauseState : public State{
public:
    PauseState(StateStack& stack, Context context);

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const sf::Event& event);


private:
    sf::Sprite			mBackgroundSprite;
    sf::Text			mPausedText;
    sf::Text			mInstructionText;
    sf::Font            mFont;

};


#endif //TANKCRAFT_PAUSESTATE_H
