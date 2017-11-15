//
// Created by Mengmeng Xu on 11/15/17.
//

#include "Button.h"

GUI::Button::Button() {
    mTexture.loadFromFile("Texture/Button.jpg");
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect( sf::IntRect( 0, 0, mTexture.getSize().x ,mTexture.getSize().y/3) );
    mText.setPosition(sf::Vector2f(mTexture.getSize() / 2u )); // put text in the center

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
