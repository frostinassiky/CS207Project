//
// Created by Yang on 18/11/2017.
//
#include <menu.h>
#include "Button.h"
#include "ConfirmState.h"
#include "Utility.h"
ConfirmState::ConfirmState(StateStack& stack, Context context)
        : State(stack, context)
        , mOptions()
        , mOptionIndex(0)
        , mGUIContainer()
        , mPausedText()

{
    GUI::Button* playButton = new GUI::Button();
    playButton->setPosition(1000, 700);
    playButton->setText("Back");
    playButton->setCallback([this] ()
                            {
                                requestStateClear();
                                requestStackPush(StatesID::Menu);
                            });
    mGUIContainer.pack(playButton);

    GUI::Button*  exitButton = new GUI::Button;
    exitButton->setPosition(1000, 950);
    exitButton->setText("Yes!");
    exitButton->setCallback([this] ()
                            {
                                requestStackPop();
                                //if(stack.isEmpty())
                                exit(0);
                                //requestStackPop();
                            });
    mGUIContainer.pack(exitButton);
    mTexture.loadFromFile("../Media/cover.png");

    mFont.loadFromFile("../Media/GODOFWAR.TTF");
    mPausedText.setFont(mFont);
    mPausedText.setString("Are you sure to exit?");
    mPausedText.setCharacterSize(70);
    centerOrigin(mPausedText);
    sf::Vector2f viewSize = context.window->getView().getSize();

    mPausedText.setPosition(0.5f * viewSize.x, 0.35f * viewSize.y);
}

void ConfirmState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 200));
    backgroundShape.setSize(window.getView().getSize());


    mBackgroundSprite.setTexture(mTexture);
    window.draw(mBackgroundSprite);

    window.draw(backgroundShape);
    window.draw(mGUIContainer);
    window.draw(mPausedText);

}

bool ConfirmState::update(sf::Time)
{

    return true;
}

bool ConfirmState::handleEvent(const sf::Event& event)
{
    mGUIContainer.handleEvent(event);
    return false;
}