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
        Component();
        virtual ~Component();
        virtual bool isSelectable();
        bool isSelected() {return mIsSelected;};
        virtual void select();
        virtual void deselect();
        bool isActive() {return mIsActive;};
        virtual void activate();
        virtual void deactivate();
        virtual void handleEvent(sf::Event& event) = 0;
    };

}


#endif //TANKCRAFT_COMPONENT_H
