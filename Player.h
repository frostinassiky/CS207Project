//
// Created by Yang on 12/11/2017.
//

#ifndef TANKCRAFT_PLAYER_H
#define TANKCRAFT_PLAYER_H

#include <SFML/Window/Event.hpp>
#include <map>
#include "CommandQ.h"

// Class play handles player input through keyboard

class Player {
public:
    enum Action {
        MoveLeft1,
        MoveRight1,
        MoveUp1,
        MoveDown1,
        Fire1,

        MoveLeft2,
        MoveRight2,
        MoveUp2,
        MoveDown2,
        Fire2,

        Info,
    };

public:
    Player();

    void handleEvent(const sf::Event &event, CommandQ &commands);

    void handleRealtimeInput(CommandQ &commands);

    void assignKey(Action action, sf::Keyboard::Key key);

    sf::Keyboard::Key getAssignedKey(Action action) const;


private:
    void initializeActions();

    static bool isRealtimeAction(Action action);


private:
    std::map<sf::Keyboard::Key, Action> mKeyBinding;  //bind key with action type
    std::map<Action, Command> mActionBinding;             //bind action type with movement of tank


};


#endif //TANKCRAFT_PLAYER_H
