//
// Created by Mengmeng Xu on 11/15/17.
//

#include "Button.h"


GUI::Button::Button() : mFont(), mSprite(),  mText(), mCallback(), mIsToggle(false)
{
    mFont.loadFromFile("../Media/GODOFWAR.TTF");
    mTexture.loadFromFile("../Media/Button.png");
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect( sf::IntRect( 0, 0, mTexture.getSize().x ,mTexture.getSize().y/3) );
    mText.setFont(mFont);
    mText.setPosition(sf::Vector2f(mTexture.getSize() / 2u )); // put text in the center
    mText.setCharacterSize(72);
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mText.setPosition(bounds.width / 4.f + 48, bounds.height / 2.f - 48);

}

void GUI::Button::select() {
    Component::select();
    mSprite.setTextureRect(sf::IntRect( 0, mTexture.getSize().y/3, mTexture.getSize().x ,mTexture.getSize().y/3));

}

void GUI::Button::deselect() {
    Component::deselect();
    mSprite.setTextureRect(sf::IntRect( 0, 0, mTexture.getSize().x ,mTexture.getSize().y/3));

}

void GUI::Button::activate() {
    Component::activate();
    if (mIsToggle)
        mSprite.setTextureRect(sf::IntRect( 0, mTexture.getSize().y/3*2, mTexture.getSize().x ,mTexture.getSize().y/3));
    if (mCallback) mCallback();
    if (!mIsToggle) deactivate();
}

void GUI::Button::deactivate() {
    Component::deactivate();
    Component::deactivate();
    if (mIsToggle)
        if (isSelected())
            mSprite.setTextureRect(sf::IntRect( 0, mTexture.getSize().y/3, mTexture.getSize().x ,mTexture.getSize().y/3));
        else
            mSprite.setTextureRect(sf::IntRect( 0, 0, mTexture.getSize().x ,mTexture.getSize().y/3));
}

void GUI::Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
    target.draw(mText, states);
}

void GUI::Button::setText(const std::string &text, const sf::Color color) {
    mText.setString(text);
    mText.setColor(color);

}
