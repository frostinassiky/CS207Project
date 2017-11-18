//
// Created by Mengmeng Xu on 11/15/17.
//

#ifndef TANKCRAFT_CONTAINER_H
#define TANKCRAFT_CONTAINER_H

#include "Component.h"
#include "Button.h"

namespace GUI{
    class Container : public Component{
    private:
        std::vector<Button*> mChildren;
        int mSelected;

    public:
        Container() : mChildren(), mSelected(-1) {;};
        void pack(Button* component); // may have bug
        bool isSelectable() override {return false;};

        void handleEvent(const sf::Event& event) override;
        void select(int t);
        bool hasSelection() {return mSelected != -1;};
        void selectPrevious();
        void selectNext();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    };

}


#endif //TANKCRAFT_CONTAINER_H
