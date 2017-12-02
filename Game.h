//
// Created by Mengmeng Xu on 11/8/17.
//

#ifndef TANKCRAFT_GAME_H
#define TANKCRAFT_GAME_H

#include <SFML/Graphics.hpp>
#include <curses.h>
#include <iostream>
#include <cmath>
#include <SFML/Audio/Music.hpp>
#include "Tank.h"
#include "World.h"
#include "Player.h"
#include "StateStack.h"

// Entrance, Our application
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
    sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    sf::Music mMusic;
private:
    void processEvents();

    void update(sf::Time deltaTime);

    void render();

    // add all states
    void registerStates();

};


#endif //TANKCRAFT_GAME_H
