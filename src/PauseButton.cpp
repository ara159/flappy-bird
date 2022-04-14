#include "PauseButton.hpp"
#include <iostream>

PauseButton::PauseButton() : MyGameObject()
{
    init();
}

PauseButton::~PauseButton() {
    free(txPauseButton);
    free(spPauseButton);
}

void PauseButton::init() {
    Image tileset = Image();
    tileset.loadFromFile("flappy-birdy-sprites.png");
    
    txPauseButton = new Texture();
    txPauseButton->loadFromImage(tileset, IntRect(121, 306, 13, 14));
    
    spPauseButton = new Sprite();
    spPauseButton->setTexture(*txPauseButton);
    spPauseButton->setPosition(20, 20);
    spPauseButton->setScale(Vector2f(scale, scale));
}

void PauseButton::draw(RenderWindow * window)
{
    
    window->draw(*spPauseButton);
}

void PauseButton::handleEvent(Event event, RenderWindow* window)
{
    if (event.type == Event::MouseButtonPressed)
    {
        auto clickPosition = Mouse::getPosition(*window);
        auto pauseBtnBounds = spPauseButton->getGlobalBounds();

        if (pauseBtnBounds.intersects(FloatRect(clickPosition.x, clickPosition.y, 1, 1)))
        {
        }
    }
}
