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


class Game {
public:
    Game();

    void run();

private:

    sf::RenderWindow mWindow;
    Player mPlayer;

    StateStack mStateStack;
    sf::Font mFont;
    sf::Texture mTexture;
    sf::Time TimePerFrame = sf::seconds(1.f / 12.f);
private:
    void processEvents();

    void update(sf::Time deltaTime);

    void render();

    // void updateStatistics(sf::Time dt);
    void registerStates();

};


#endif //TANKCRAFT_GAME_H
