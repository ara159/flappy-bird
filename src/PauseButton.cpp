#include "PauseButton.hpp"

PauseButton::PauseButton() : MyGameObject()
{
    init();
}

void PauseButton::init() {
    Image tileset = Image();
    tileset.loadFromFile("flappy-birdy-sprites.png");
    
    txPauseButton = new Texture();
    txPauseButton->loadFromImage(tileset, IntRect(121, 306, 13, 14));
}

void PauseButton::draw(RenderWindow * window)
{
    auto sprite = Sprite();
    sprite.setTexture(*txPauseButton);
    sprite.setPosition(20, 20);
    sprite.setScale(Vector2f(scale, scale));
    window->draw(sprite);
}