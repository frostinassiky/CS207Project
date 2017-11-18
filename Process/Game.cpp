//
// Created by Mengmeng Xu on 11/8/17.
//

#include "Game.h"
#include "State.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "ConfirmState.h"
#include "TODO_State.h"

Game::Game():
        mWindow(sf::VideoMode(2560, 1600), "Tank Craft Application"),
        mPlayer(),
        mStateStack(State::Context(mWindow, mTexture, mFont, mPlayer))

{
    mWindow.setVerticalSyncEnabled(TRUE);
    mWindow.setFramerateLimit(20); // in case of use up resource

    mWindow.setKeyRepeatEnabled(false);

    registerStates();
    mStateStack.pushState(StatesID::Menu);

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
    mStateStack.update(deltaTime);
}

void Game::render()
{
    // mWindow.clear();
    mWindow.clear(sf::Color(128, 128, 128));
    // mWindow.draw(mLand);
    mStateStack.draw();
    // TODO bug
    // mWindow.draw(oneTank);
    mWindow.setView(mWindow.getDefaultView());
    mWindow.display();
}

void Game::processEvents()
{
    // CommandQ& commands = mWorld.getCommandQ();

    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);

        if (event.type == sf::Event::Closed)
            mWindow.close();
    }

}

void Game::registerStates()
{
    mStateStack.registerState<MenuState>(StatesID::Menu);
    mStateStack.registerState<GameState>(StatesID::Game);
    mStateStack.registerState<PauseState>(StatesID::Pause);
    mStateStack.registerState<ConfirmState>(StatesID::Confirm);
    mStateStack.registerState<TODO_State>(StatesID::TODO);
}
