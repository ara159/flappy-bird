#include "Title.hpp"
#include <iostream>

Title::Title() : MyGameObject()
{
    Image tileset = Image();
    tileset.loadFromFile("flappy-birdy-sprites.png");
    txTitle = new Texture();
    txTitle->loadFromImage(tileset, IntRect(351, 91, 89, 24));
    
    spTitle = new Sprite(*txTitle);
    spTitle->setPosition(screenSize.x/2, screenSize.y/2);
    spTitle->setOrigin(Vector2f(89/2, 24/2));
    spTitle->setScale(scale, scale);

    txBtnStart = new Texture();
    txBtnStart->loadFromImage(tileset, IntRect(354, 118, 52, 29));

    spBtnStart = new Sprite(*txBtnStart);
    spBtnStart->setPosition(screenSize.x/2 - 51 * scale - 3 * scale, screenSize.y/2 + 30 * scale);
    spBtnStart->setScale(scale, scale);

    txBtnRanking = new Texture();
    txBtnRanking->loadFromImage(tileset, IntRect(414, 118, 52, 29));

    spBtnRanking = new Sprite(*txBtnRanking);
    spBtnRanking->setPosition(screenSize.x/2 + 3 * scale, screenSize.y/2 + 30 * scale);
    spBtnRanking->setScale(scale, scale);
}

Title::~Title()
{
}


void Title::draw(RenderWindow* window)
{
    
    window->draw(*spTitle);
    window->draw(*spBtnStart);
    window->draw(*spBtnRanking);
}

void Title::start()
{
    
}

void Title::handleEvent(Event event, RenderWindow* window)
{
    if (event.type == Event::MouseButtonPressed) {
        
        auto clickPosition = Mouse::getPosition(*window);
        auto startBtnBounds = spBtnStart->getGlobalBounds();
        auto clickBounds = FloatRect(clickPosition.x, clickPosition.y, 1, 1);
        
        if (startBtnBounds.intersects(clickBounds))
        {
            scene = GameScreen::GetReady_S;
        }
    }
}

void Title::update()
{
}