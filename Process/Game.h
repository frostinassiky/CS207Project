//
// Created by Mengmeng Xu on 11/8/17.
//

#ifndef TANKCRAFT_GAME_H
#define TANKCRAFT_GAME_H

#include <SFML/Graphics.hpp>
#include <curses.h>
#include <iostream>
#include <cmath>
#include "Tank.h"
#include "World.h"
#include "Player.h"
#include "StateStack.h"


class Game{
public:
    Game();
    void run();
private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
    sf::RenderWindow mWindow;
    World mWorld;
    Tank oneTank;
    bool mIsMovingUp=FALSE;
    bool mIsMovingDown=FALSE;
    bool mIsMovingLeft=FALSE;
    bool mIsMovingRight=FALSE;
    bool mIsMovingClock=FALSE;
    bool mIsMovingAntiClock=FALSE;
    bool mIsMovingBrake=FALSE;
    double moveSpeed = 150, rotateSpeed = 10;
    double momentum = 0;
    sf::Time TimePerFrame = sf::seconds(1.f / 12.f);
    sf::Texture mBackground;
    sf::Sprite  mLand;
    Player mPlayer;
    StateStack				mStateStack;
    sf::Texture			mTextures;
    sf::Font				mFonts;


};


#endif //TANKCRAFT_GAME_H
