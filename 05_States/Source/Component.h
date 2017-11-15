//
// Created by Mengmeng Xu on 11/15/17.
//

#ifndef TANKCRAFT_COMPONENT_H
#define TANKCRAFT_COMPONENT_H

// use a namespace in case of repeat
#include <SFML/Graphics.hpp>

namespace GUI{
    class Component :  public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
    private:
        bool mIsSelected;
        bool mIsActive;
    public:
        Component() ;
        virtual bool isSelectable() = 0;
        bool isSelected() {return mIsSelected;};
        virtual void select() {mIsSelected = true;};
        virtual void deselect() { mIsSelected = false;} ;
        bool isActive() {return mIsActive;};
        virtual void activate() {mIsActive = true;};
        virtual void deactivate() {mIsActive = false;};
        virtual void handleEvent(sf::Event& event) = 0;
    };

}


#endif //TANKCRAFT_COMPONENT_H
