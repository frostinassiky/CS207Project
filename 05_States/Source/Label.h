//
// Created by Mengmeng Xu on 11/15/17.
//

#ifndef TANKCRAFT_LABEL_H
#define TANKCRAFT_LABEL_H


#include "Component.h"

namespace GUI{
    class Label : public Component{
    private:
        sf::Text mText;

    public:
        Label(const std::string& text, sf::Font& font) : mText(text, font, 16) { ; };
        bool isSelectable() {return false;};
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void setText(const std::string& text) { mText.setString(text); };
    };

}


#endif //TANKCRAFT_LABEL_H
