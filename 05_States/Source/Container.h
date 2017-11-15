//
// Created by Mengmeng Xu on 11/15/17.
//

#ifndef TANKCRAFT_CONTAINER_H
#define TANKCRAFT_CONTAINER_H

#include "Component.h"
namespace GUI{
    class Container : public Component{
    private:
        std::vector<Component*> mChildren;
        int mSelected;

    public:
        Container() : mChildren(), mSelected(-1) {;};
        void pack(Component* component) {mChildren.push_back(component);} // may have bug
        bool isSelectable() {return false;};
        void handleEvent(sf::Event& event);
        void select(int t);
        bool hasSelection() {return mSelected != -1;};
        void selectPrevious();
        void selectNext();
    };

}


#endif //TANKCRAFT_CONTAINER_H
