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
    playButton->setPosition(100, 700);
    playButton->setText("Play");
    playButton->setCallback([this] ()
                            {
                                requestStackPop();
                                requestStackPush(StatesID::Game);
                            });
    mGUIContainer.pack(playButton);

    GUI::Button*  exitButton = new GUI::Button;
    exitButton->setPosition(100, 900);
    exitButton->setText("Exit");
    exitButton->setCallback([this] ()
                            {
                                requestStackPop();
                            });
    mGUIContainer.pack(playButton);
    mGUIContainer.pack(exitButton);
    mTexture.loadFromFile("Media/cover.png");
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