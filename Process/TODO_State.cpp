//
// Created by Yang on 18/11/2017.
//


#include "TODO_State.h"
#include "Utility.h"

TODO_State::TODO_State(StateStack& stack, Context context)
        : State(stack, context)
        , mBackgroundSprite()
        , mPausedText()
        , mInstructionText()
{
    //sf::Font& font = context.fonts->get(Fonts::Main);
    sf::Vector2f viewSize = context.window->getView().getSize();

    mFont.loadFromFile("../Media/GODOFWAR.TTF");

    mPausedText.setFont(mFont);
    mPausedText.setString("Functionality under Construction");
    mPausedText.setCharacterSize(70);
    centerOrigin(mPausedText);
    mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

    mInstructionText.setFont(mFont);
    mInstructionText.setString("(Press Backspace or Escape to return to the main menu)");
    centerOrigin(mInstructionText);
    mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void TODO_State::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(mPausedText);
    window.draw(mInstructionText);
}

bool TODO_State::update(sf::Time)
{
    return false;
}

bool TODO_State::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::Escape||event.key.code == sf::Keyboard::BackSpace)
    {
        // Escape pressed, remove itself to return to the game
        requestStackPop();
        //requestStackPush(StatesID::Menu);
    }



    return false;
}