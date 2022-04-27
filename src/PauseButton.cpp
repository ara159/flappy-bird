#include "PauseButton.hpp"
#include <iostream>
#include "TextureFactory.hpp"

PauseButton::PauseButton() : MyGameObject()
{
    TextureFactory tx = TextureFactory();
    txPauseButton = tx.pauseButton();
    
    spPauseButton = new Sprite();
    spPauseButton->setTexture(*txPauseButton);
    spPauseButton->setPosition(20, 20);
    spPauseButton->setScale(Vector2f(scale, scale));
    
    paused = false;
}

PauseButton::~PauseButton() {
    free(txPauseButton);
    free(spPauseButton);
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
            paused = !paused;
            if (paused)
                status.toScreen = PAUSE;
            else
                status.toScreen = GAMEPLAY;
        }
    }
}
