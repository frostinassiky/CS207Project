//
// Created by Mengmeng Xu on 11/27/17.
//

#ifndef TANKCRAFT_PLAYER1WINSTATE_H
#define TANKCRAFT_PLAYER1WINSTATE_H


#include "State.h"
//player 1 wins
class Player1WinState : public  State{
    public:
        Player1WinState(StateStack& stack, Context context);

        virtual void		draw();
        virtual bool		update(sf::Time dt);
        virtual bool		handleEvent(const sf::Event& event);


    private:
        sf::Sprite			mBackgroundSprite;
        sf::Text			mPausedText;
        sf::Text			mInstructionText;
        sf::Font            mFont;

    };



#endif //TANKCRAFT_PLAYER1WINSTATE_H
