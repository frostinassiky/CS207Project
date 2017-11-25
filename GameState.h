//
// Created by Yang on 15/11/2017.
//

#ifndef TANKCRAFT_GAMESTATE_H
#define TANKCRAFT_GAMESTATE_H


#include <SFML/Audio/Music.hpp>
#include "State.h"
#include "World.h"
class GameState : public State{
public:
    GameState(StateStack& stack,
              Context context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);
private:
    World mWorld;
    Player& mPlayer;
};


#endif //TANKCRAFT_GAMESTATE_H
