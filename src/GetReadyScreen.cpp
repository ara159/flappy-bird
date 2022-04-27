#include "GetReadyScreen.hpp"
#include "TextureFactory.hpp"

GetReadyScreen::GetReadyScreen() : MyGameObject()
{
    TextureFactory tx = TextureFactory();
    txGetReady = tx.getReadyPhrase();
    txInstructions = tx.getReadyInstructions();
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
