//
// Created by Yang on 15/11/2017.
//

#ifndef TANKCRAFT_STATESTACK_H
#define TANKCRAFT_STATESTACK_H


#include <SFML/Graphics.hpp>
//#include <SFML/Time.h>
//#include <SFML/Event.hpp>
#include <vector>
#include <map>
#include "State.h"

//the stack that holds states
class State;

class StateStack : private sf::NonCopyable {
public:
    enum Action {
        Push,
        Pop,
        Clear,
    };

public:
    explicit StateStack(State::Context context);

    template<typename T>
    void registerState(StatesID::ID stateID) { mFactories[stateID] = new T(*this, mContext); };

    void update(sf::Time dt);

    void draw();

    void handleEvent(const sf::Event &event);

    void pushState(StatesID::ID stateID);

    void popState();

    void clearStates();

    bool isEmpty() const;


private:
    State *createState(StatesID::ID stateID);

    void applyPendingChanges();


private:
    struct PendingChange {
        explicit PendingChange(Action action, StatesID::ID stateID = StatesID::None);

        Action action;
        StatesID::ID stateID;
    };


private:
    std::vector<State *> mStack;
    std::vector<PendingChange> mPendingList; //a vector stores operations on the state stack

    State::Context mContext;
    std::map<StatesID::ID, State *> mFactories; //bind statesID with state
    //State state;
};


#endif //TANKCRAFT_STATESTACK_H
