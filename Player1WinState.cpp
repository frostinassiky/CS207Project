//
// Created by Mengmeng Xu on 11/27/17.
//

#include "Player1WinState.h"
#include "Utility.h"

//display player 1 wins information
Player1WinState::Player1WinState(StateStack &stack, Context context)
        : State(stack, context), mBackgroundSprite(), mPausedText(), mInstructionText() {
    sf::Vector2f viewSize = context.window->getView().getSize();

    mFont.loadFromFile("../Media/GODOFWAR.TTF");

    mPausedText.setFont(mFont);
    mPausedText.setString("Right Player Wins!");
    mPausedText.setColor(sf::Color::Green);
    mPausedText.setCharacterSize(140);
    centerOrigin(mPausedText);
    mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

    mInstructionText.setFont(mFont);
    mInstructionText.setString("(Press Backspace or Escape to return to the main menu)");
    centerOrigin(mInstructionText);
    mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void Player1WinState::draw() {
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(mPausedText);
    window.draw(mInstructionText);
}

bool Player1WinState::update(sf::Time) {
    return false;
}

bool Player1WinState::handleEvent(const sf::Event &event) {
    if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::BackSpace) {
        // Escape pressed, remove itself to return to the game
        requestStateClear();
        requestStackPush(StatesID::Menu);
    }


    return false;
}