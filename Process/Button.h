//
// Created by Mengmeng Xu on 11/15/17.
//

#ifndef TANKCRAFT_BUTTON_H
#define TANKCRAFT_BUTTON_H

#include <utility>

#include "Component.h"

namespace GUI {
    class Button : public Component {
    private:
        sf::Texture mTexture;
        sf::Sprite mSprite;
        sf::Text mText;
        sf::Font mFont;
        bool mIsToggle;
        std::function<void()> mCallback;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    public:
        Button();

        void setText(const std::string& text){ mText.setString(text); };
        void setText(const std::string& text, const sf::Color color);
        void setCallback(std::function<void()> callback) {mCallback = std::move(callback); } ;
        bool isSelectable() { return true; };
        void select();
        void deselect();
        void activate();
        void deactivate();
    };
}



#endif //TANKCRAFT_BUTTON_H
