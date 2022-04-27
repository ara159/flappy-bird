#include "GetReadyScreen.hpp"

GetReadyScreen::GetReadyScreen() : MyGameObject()
{
    Image tileset = Image();
    tileset.loadFromFile("flappy-birdy-sprites.png");
    
    txGetReady = new Texture();
    txGetReady->loadFromImage(tileset, IntRect(295, 59, 92, 25));

    txInstructions = new Texture();
    txInstructions->loadFromImage(tileset, IntRect(292, 91, 57, 49));
}

GetReadyScreen::~GetReadyScreen()
{
    free(txGetReady);
    free(txInstructions);
}

void GetReadyScreen::start()
{
    
}

void GetReadyScreen::draw(RenderWindow* window)
{
    Sprite spGetReady(*txGetReady);
    spGetReady.setOrigin(spGetReady.getGlobalBounds().width/2, 0);
    spGetReady.setScale(Vector2f(scale, scale));
    spGetReady.setPosition(screenSize.x/2, 50 * scale);
    window->draw(spGetReady);

    Sprite spInstructions(*txInstructions);
    spInstructions.setOrigin(spInstructions.getGlobalBounds().width/2, 0);
    spInstructions.setScale(Vector2f(scale, scale));
    spInstructions.setPosition(screenSize.x/2, screenSize.y/2 * 1.25);
    window->draw(spInstructions);
}

void GetReadyScreen::update()
{

}

void GetReadyScreen::handleEvent(Event event, RenderWindow* window)
{
    if (event.type == Event::MouseButtonPressed)
    {
        status.toScreen = GAMEPLAY;
    }
}
