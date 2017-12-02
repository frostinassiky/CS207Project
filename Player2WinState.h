//
// Created by Mengmeng Xu on 11/27/17.
//

#ifndef TANKCRAFT_PLAYER2WINSTATE_H
#define TANKCRAFT_PLAYER2WINSTATE_H


#include "State.h"

class Player2WinState : public State {
public:
    Player2WinState(StateStack &stack, Context context);

    virtual void draw();

    virtual bool update(sf::Time dt);

    virtual bool handleEvent(const sf::Event &event);


private:
    sf::Sprite mBackgroundSprite;
    sf::Text mPausedText;
    sf::Text mInstructionText;
    sf::Font mFont;

};

#endif //TANKCRAFT_PLAYER2WINSTATE_H
