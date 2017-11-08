//
// Created by Mengmeng Xu on 11/8/17.
//

#include "Game.h"

Game::Game():
        mWindow(sf::VideoMode(590*2, 983*2), "Tank Craft Application"),
        mPlayer()
{
    mWindow.setVerticalSyncEnabled(TRUE);
    mWindow.setFramerateLimit(20); // in case of use up resource
    if (!mTexture.loadFromFile("../Media/tanks.png"))
        std::cout << "error" << std::endl;
    if (!mBackground.loadFromFile("../Media/Map.png"))
        std::cout << "error" << std::endl;
    mPlayer.setTexture(mTexture);
    mLand.setTexture(mBackground);
    mLand.setScale(2,2);
    size_x = mTexture.getSize().x;
    size_y = mTexture.getSize().y;
    // rescale
    // mPlayer.setScale(0.5f,0.5f);
    mPlayer.setPosition(128.f, 450.f);
    mPlayer.setTextureRect(sf::IntRect(0,0,512/3, 605/3));
    mPlayer.setScale(0.4,-0.4);

}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        processEvents();

        render();
    } }


void Game::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
        movement.y -= moveSpeed;
    if (mIsMovingDown)
        movement.y += moveSpeed;
    if (mIsMovingLeft){
        mPlayer.move(dir*size_x/seqN/4,0);
        dir = -1;

    }

    if (mIsMovingRight){
        mPlayer.move(dir*size_x/seqN/4,0);
        dir = 1;
    }
    if (mIsMovingClock){
        momentum = -rotateSpeed;
        mPlayer.rotate(momentum * deltaTime.asSeconds());
    }
    /*
    if (mIsMovingAntiClock){
        momentum = rotateSpeed;
        mPlayer.rotate(momentum * deltaTime.asSeconds());
    }

    if (mIsMovingBrake)
        momentum /= 1.01;
    seq++;

    if (seq>=seqN){
        seq -= seqN;
        mPlayer.move(dir*size_x/seqN/1.5 * cos(mPlayer.getRotation()/180.0*3.14),dir*size_x/seqN/1.5 * sin(mPlayer.getRotation()/180.0*3.14));
        if (mPlayer.getPosition().x+size_x/seqN>res_x){
            mPlayer.move(-1300,0);
            //dir = -1;
        }
        if (mPlayer.getPosition().x<size_x/seqN ) {
            dir = 1;
        }

    }



    mPlayer.setScale(dir,1);
    mPlayer.setTextureRect(sf::IntRect(seq*size_x/seqN,0,size_x/seqN, size_y));
*/

    mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
    // mWindow.clear();
    mWindow.clear(sf::Color(128, 128, 128));
    mWindow.draw(mLand);
    mWindow.draw(mPlayer);
    mWindow.display();
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {

            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break; }
    }

}
void Game::handlePlayerInput(sf::Keyboard::Key key,
                             bool isPressed)
{
    switch (key) {
        case  sf::Keyboard::Up:
            mIsMovingUp = isPressed; break;
        case  sf::Keyboard::Down:
            mIsMovingDown = isPressed; break;
        case  sf::Keyboard::Left:
            mIsMovingLeft = isPressed; break;
        case  sf::Keyboard::Right:
            mIsMovingRight = isPressed; break;

    }
    /*
    if (key == sf::Keyboard::Up)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
    else if (key == sf::Keyboard::Q)
        mIsMovingClock = isPressed;
    else if (key == sf::Keyboard::E)
        mIsMovingAntiClock = isPressed;
    else if (key == sf::Keyboard::X)
        mIsMovingBrake = isPressed;
        */
}
