//
// Created by Yang on 12/11/2017.
//

#include "Player.h"
#include "Tank.h"

struct TankMover
{
    TankMover(float vx, float vy)
            : velocity(vx, vy)
    {}

    void assign(Tank& _tank, sf::Time) const
    {
        _tank.setVelocity(velocity);
    }

    sf::Vector2f velocity;
};


Player::Player()
{
    // Set initial key bindings
    mKeyBinding[sf::Keyboard::Left] = MoveLeft;
    mKeyBinding[sf::Keyboard::Right] = MoveRight;
    mKeyBinding[sf::Keyboard::Up] = MoveUp;
    mKeyBinding[sf::Keyboard::Down] = MoveDown;

    // Set initial action bindings
    initializeActions();

    // Assign all categories to player's aircraft
    /*
    for(auto it=mActionBinding.cbegin();it!=mActionBinding.cend();it++)
    {
        // TODO debug
        Command tmpCommand=it->second;
        tmpCommand.mCategory = CTank;
        it->second = tmpCommand; // Tank
    }
     */
    for(auto& content : mActionBinding)
    {
        content.second.mCategory = CTank; // Tank
    }
}

void Player::handleEvent(const sf::Event& event, CommandQ& commands)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // Check if pressed key appears in key binding, trigger command if so
        auto found = mKeyBinding.find(event.key.code);
        if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
            commands.push(mActionBinding[found->second]);
    }
}

void Player::handleRealtimeInput(CommandQ& commands)
{
    // Traverse all assigned keys and check if they are pressed

    for(auto it=mKeyBinding.cbegin();it!=mKeyBinding.cend();it++)
    {
        // If key is pressed, lookup action and trigger corresponding command
        if (sf::Keyboard::isKeyPressed(it->first) && isRealtimeAction(it->second))
            commands.push(mActionBinding[it->second]);
    }
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
    // Remove all keys that already map to action
    for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
    {
        if (itr->second == action)
            mKeyBinding.erase(itr++);
        else
            ++itr;
    }

    // Insert new binding
    mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
    for(auto it=mKeyBinding.cbegin();it!=mKeyBinding.cend();it++)
    {
        if (it->second == action)
            return it->first;
    }

    return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
    const float playerSpeed = 200.f;

    // Safely converts pointers and references to classes up, adown, and sideways along the inheritance hierarchy.
    // in book P104
    mActionBinding[MoveLeft].action	 = [=] (SceneNode& node, sf::Time dt)
    {
        TankMover(-playerSpeed, 0.f).assign(static_cast<Tank&>(node),dt);
    };
    mActionBinding[MoveRight].action = [=] (SceneNode& node, sf::Time dt)
    {
        TankMover(+playerSpeed, 0.f).assign(static_cast<Tank&>(node),dt);
    };
    mActionBinding[MoveUp].action    = [=] (SceneNode& node, sf::Time dt)
    {
        TankMover(0.f, -playerSpeed).assign(static_cast<Tank&>(node),dt);
    };
    mActionBinding[MoveDown].action  = [=] (SceneNode& node, sf::Time dt)
    {
        TankMover(0.f, +playerSpeed).assign(static_cast<Tank&>(node),dt);
    };
}

bool Player::isRealtimeAction(Action action)
{
    switch (action)
    {
        case MoveLeft:
        case MoveRight:
        case MoveDown:
        case MoveUp:
            return true;
        default:
            return false;
    }
}