//
// Created by Yang on 18/11/2017.
//

#ifndef TANKCRAFT_CONFIRMSTATE_H
#define TANKCRAFT_CONFIRMSTATE_H

#include "State.h"
#include "Container.h"

class ConfirmState : public State{
    public:
        ConfirmState(StateStack& stack, Context context);

        virtual void			draw();
        virtual bool			update(sf::Time dt);
        virtual bool			handleEvent(const sf::Event& event);

        // void					updateOptionText();


    private:
        enum OptionNames
        {
            Yes,
            No,
        };


    private:
        sf::Texture mTexture;
        sf::Sprite mBackgroundSprite;
        std::vector<sf::Text> mOptions;
        std::size_t mOptionIndex;
        GUI::Container mGUIContainer;
        sf::Text			mPausedText;
        sf::Font            mFont;

};



#endif //TANKCRAFT_CONFIRMSTATE_H
