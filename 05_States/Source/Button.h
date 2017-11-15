//
// Created by Mengmeng Xu on 11/15/17.
//

#ifndef TANKCRAFT_BUTTON_H
#define TANKCRAFT_BUTTON_H

#include "Component.h"

namespace GUI {
    class Button : public Component {
    private:
        sf::Texture mTexture;
        sf::Sprite mSprite;
        sf::Text mText;
        bool mIsToggle;
        std::function<void()> mCallback;

    public:
        Button();
        bool isSelectable() { return true; };
        void select();
        void deselect();
        void activate();
        void deactivate();
    };
}



#endif //TANKCRAFT_BUTTON_H
