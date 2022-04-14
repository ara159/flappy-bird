#include "GetReady.hpp"

GetReady::GetReady() : MyGameObject()
{
    Image tileset = Image();
    tileset.loadFromFile("flappy-birdy-sprites.png");
    
    txGetReady = new Texture();
    txGetReady->loadFromImage(tileset, IntRect(295, 59, 92, 25));

    txInstructions = new Texture();
    txInstructions->loadFromImage(tileset, IntRect(292, 91, 57, 49));

    spGetReady = new Sprite(*txGetReady);
    spGetReady->setOrigin(spGetReady->getGlobalBounds().width/2, 0);
    spGetReady->setScale(Vector2f(scale, scale));
    spGetReady->setPosition(screenSize.x/2, 50 * scale);

    spInstructions = new Sprite(*txInstructions);
    spInstructions->setOrigin(spInstructions->getGlobalBounds().width/2, 0);
    spInstructions->setScale(Vector2f(scale, scale));
    spInstructions->setPosition(screenSize.x/2, screenSize.y/2 * 1.25);

    canClose = false;
    cooldown = 60;
}

GetReady::~GetReady()
{
}


void GetReady::draw(RenderWindow* window)
{
    window->draw(*spGetReady);
    window->draw(*spInstructions);
}

void GetReady::start()
{
    
}

void GetReady::handleEvent(Event event, RenderWindow* window)
{
    if (!canClose) return;
    if (event.type == Event::MouseButtonPressed)
    {
        scene = GameScreen::GamePlay_S;
    }
}

void GetReady::update()
{
    if (cooldown > 0)
        cooldown--;
    canClose = true;
}
