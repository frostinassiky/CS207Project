//
// Created by Yang on 15/11/2017.
//

#include "MenuState.h"
#include "Button.h"

MenuState::MenuState(StateStack& stack, Context context)
        : State(stack, context)
        , mOptions()
        , mOptionIndex(0)
        , mGUIContainer()
{


    GUI::Button* playButton = new GUI::Button();
    playButton->setPosition(100, 600);
    playButton->setText("Play");
    playButton->setCallback([this] ()
                            {
                                requestStackPop();
                                requestStackPush(StatesID::Game);
                            });
    mGUIContainer.pack(playButton);

    GUI::Button* joinButton = new GUI::Button();
    joinButton->setPosition(100, 780);
    joinButton->setText("Join",sf::Color::Yellow);
    joinButton->setCallback([this] ()
                            {
                                requestStackPush(StatesID::TODO);
                            });
    mGUIContainer.pack(joinButton);

    GUI::Button* moreButton = new GUI::Button();
    moreButton->setPosition(100, 960);
    moreButton->setText("More");
    moreButton->setCallback([this] ()   { system("open https://goo.gl/9zRVXf"); });
    mGUIContainer.pack(moreButton);


    GUI::Button* helpButton = new GUI::Button();
    helpButton->setPosition(100, 1140);
    helpButton->setText("Help");
    helpButton->setCallback([this] () { system("open https://goo.gl/9ufTLA"); });
    mGUIContainer.pack(helpButton);

    GUI::Button*  exitButton = new GUI::Button;
    exitButton->setPosition(100, 1320);
    exitButton->setText("Exit");
    exitButton->setCallback([this] ()
                            {
                                requestStackPop();
                                requestStackPush(StatesID::Confirm);
                            });
    mGUIContainer.pack(exitButton);
    mTexture.loadFromFile("../Media/cover.png");

}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());
    mBackgroundSprite.setTexture(mTexture);
    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);

}

bool MenuState::update(sf::Time)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    mGUIContainer.handleEvent(event);
    return false;
}