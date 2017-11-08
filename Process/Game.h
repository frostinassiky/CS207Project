//
// Created by Mengmeng Xu on 11/8/17.
//

#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include <SFML/Graphics.hpp>
#include <curses.h>
#include <iostream>
#include <math.h>


class Game {
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
    sf::Texture mTexture;
    sf::Sprite  mPlayer;
    double size_x = 0;
    double size_y = 0;
    int seqN = 8;
    int seq = 0;
    int shift = 0;
    int dir = 1;
    double res_x = 1600;
    double res_y = 900;

};


#endif //PROJECT_GAME_H
