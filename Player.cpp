//
// Created by Yang on 12/11/2017.
//

#include "Player.h"
#include "Tank.h"
#include <cmath>
#define PI 3.14159265

struct TankMover
{
    // rot is the rotation angle in degree
    TankMover(float rot, float v, Tank::Type type) : mRot(rot), mV(v),mTypeChecker(type) {};

    void assign(Tank& _tank, sf::Time) const
    {
        if (_tank.mType != mTypeChecker )
            return;
        float vx = _tank.getVelocity().x;
        float vy = _tank.getVelocity().y;
        float c = _tank.getMaxV();
        float V = sqrtf(vx*vx+vy*vy)*_tank.getDirection();
        if ( V>0 )
            // Relative Theory
            V = (V - mV) / (1-V*mV/c/c);
        else
            V = (V - mV) / (1-V*mV/c/c*4);
        _tank.setDirection(V>0? 1.f:-1.f);
        float theta = _tank.getRotation()+mRot;
        _tank.setRotation(theta);
        // two negative symbols because of the figure....
        _tank.setVelocity( V*sin(-theta*PI/180.f),V*cos(-theta*PI/180.f));

    }

    float mRot, mV;
    Tank::Type mTypeChecker;
};


Player::Player()
{
    // Set initial key bindings
    mKeyBinding[sf::Keyboard::Left] = MoveLeft1;
    mKeyBinding[sf::Keyboard::Right] = MoveRight1;
    mKeyBinding[sf::Keyboard::Up] = MoveUp1;
    mKeyBinding[sf::Keyboard::Down] = MoveDown1;
    mKeyBinding[sf::Keyboard::Return] = Fire1;
    mKeyBinding[sf::Keyboard::A] = MoveLeft2;
    mKeyBinding[sf::Keyboard::D] = MoveRight2;
    mKeyBinding[sf::Keyboard::W] = MoveUp2;
    mKeyBinding[sf::Keyboard::S] = MoveDown2;
    mKeyBinding[sf::Keyboard::Space] = Fire2;


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
    const float playerSpeed = 10.f;
    const float playerAngle = 1.f;

    // Safely converts pointers and references to classes up, adown, and sideways along the inheritance hierarchy.
    // in book P104
    mActionBinding[MoveLeft1].action	 = [=] (SceneNode& node, sf::Time dt)
    {
        TankMover(-playerAngle, 0.f, Tank::Type::PlayerUp).assign(static_cast<Tank&>(node),dt);
    };
    mActionBinding[MoveRight1].action = [=] (SceneNode& node, sf::Time dt)
    {
        TankMover(+playerAngle, 0.f, Tank::Type::PlayerUp).assign(static_cast<Tank&>(node),dt);
    };
    mActionBinding[MoveUp1].action    = [=] (SceneNode& node, sf::Time dt)
    {
        TankMover(0.f, -playerSpeed, Tank::Type::PlayerUp).assign(static_cast<Tank&>(node),dt);
    };
    mActionBinding[MoveDown1].action  = [=] (SceneNode& node, sf::Time dt)
    {
        TankMover(0.f, +playerSpeed, Tank::Type::PlayerUp).assign(static_cast<Tank&>(node),dt);
    };
    mActionBinding[Fire1].action  = [=] (SceneNode& node, sf::Time dt)
    {
        static_cast<Tank&>(node).Fire(Tank::Type::PlayerUp);
    };
    // Safely converts pointers and references to classes up, adown, and sideways along the inheritance hierarchy.
    // in book P104
    mActionBinding[MoveLeft2].action	 = [=] (SceneNode& node, sf::Time dt)
    {
        TankMover(-playerAngle, 0.f, Tank::Type::PlayerWS).assign(static_cast<Tank&>(node),dt);
    };
    mActionBinding[MoveRight2].action = [=] (SceneNode& node, sf::Time dt)
    {
        TankMover(+playerAngle, 0.f, Tank::Type::PlayerWS).assign(static_cast<Tank&>(node),dt);
    };
    mActionBinding[MoveUp2].action    = [=] (SceneNode& node, sf::Time dt)
    {
        TankMover(0.f, -playerSpeed, Tank::Type::PlayerWS).assign(static_cast<Tank&>(node),dt);
    };
    mActionBinding[MoveDown2].action  = [=] (SceneNode& node, sf::Time dt)
    {
        TankMover(0.f, +playerSpeed, Tank::Type::PlayerWS).assign(static_cast<Tank&>(node),dt);
    };
    mActionBinding[Fire2].action  = [=] (SceneNode& node, sf::Time dt)
    {
        static_cast<Tank&>(node).Fire(Tank::Type::PlayerWS);
    };

}

bool Player::isRealtimeAction(Action action)
{
    switch (action)
    {
        case MoveLeft1:
        case MoveRight1:
        case MoveDown1:
        case MoveUp1:
        case Fire1:
        case MoveLeft2:
        case MoveRight2:
        case MoveDown2:
        case MoveUp2:
        case Fire2:
            return true;
        default:
            return false;
    }
}