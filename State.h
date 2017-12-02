//
// Created by Yang on 15/11/2017.
//

#ifndef TANKCRAFT_STATE_H
#define TANKCRAFT_STATE_H

#include <SFML/Graphics.hpp>
#include "StateID.h"

// all states inherit this class
namespace sf {
    class RenderWindow;
}

class StateStack;

class Player;

class State {
public:
    struct Context {
        Context(sf::RenderWindow &window, sf::Texture &textures, sf::Font &fonts, Player &player);

        sf::RenderWindow *window;
        sf::Texture *textures;
        sf::Font *fonts;
        Player *player;
    };

public:
    State(StateStack &stack, Context context);

    virtual ~State();

    virtual void draw() = 0;

    virtual bool update(sf::Time dt) = 0;

    virtual bool handleEvent(const sf::Event &event) = 0;

protected:
    void requestStackPush(StatesID::ID stateID);

    void requestStackPop();

    void requestStateClear();

    Context getContext() const;

private:
    StateStack *mStack;
    Context mContext;
};


#endif //TANKCRAFT_STATE_H
