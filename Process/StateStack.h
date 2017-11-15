//
// Created by Yang on 15/11/2017.
//

#ifndef TANKCRAFT_STATESTACK_H
#define TANKCRAFT_STATESTACK_H


#include <SFML/Graphics.hpp>
//#include <SFML/Time.h>
//#include <SFML/Event.hpp>
#include <vector>
#include "State.h"
#include <map>

class State;
namespace sf
{
    class Event;
    class RenderWindow;
}

class StateStack : private sf::NonCopyable
{
public:
    enum Action
    {
        Push,
        Pop,
        Clear,
    };


public:
    explicit			StateStack(State::Context context);

    //template <typename T>
    void				registerState(States::ID stateID);

    void				update(sf::Time dt);
    void				draw();
    void				handleEvent(const sf::Event& event);

    void				pushState(States::ID stateID);
    void				popState();
    void				clearStates();

    //bool				isEmpty() const;


private:
    State*			createState(States::ID stateID);
    void				applyPendingChanges();


private:
    struct PendingChange
    {
        explicit			PendingChange(Action action, States::ID stateID = States::None);

        Action				action;
        States::ID			stateID;
    };


private:
    std::vector<State*>								mStack;
    std::vector<PendingChange>							mPendingList;

    State::Context										mContext;
    std::map<States::ID, State*>	mFactories;
    //State state;
};


template <typename T>
void StateStack::registerState(States::ID stateID)
{
    mFactories[stateID] = new T(*this, mContext);
}



#endif //TANKCRAFT_STATESTACK_H
