//
// Created by Yang on 12/11/2017.
//

#ifndef TANKCRAFT_PLAYER_H
#define TANKCRAFT_PLAYER_H

#include <SFML/Window/Event.hpp>
#include <map>
#include "CommandQ.h"

// class CommandQ;

class Player {
public:
    enum Action
    {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        ActionCount
    };

public:
    Player();

    void handleEvent(const sf::Event& event, CommandQ& commands);
    void handleRealtimeInput(CommandQ& commands);

    void					assignKey(Action action, sf::Keyboard::Key key);
    sf::Keyboard::Key		getAssignedKey(Action action) const;


private:
    void					initializeActions();
    static bool				isRealtimeAction(Action action);


private:
    std::map<sf::Keyboard::Key, Action>		mKeyBinding;
    std::map<Action, CommandQ::Command> mActionBinding;


};


#endif //TANKCRAFT_PLAYER_H
