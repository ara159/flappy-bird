#include "Tube.hpp"

Tube::Tube()
{
    Image tileset = Image();
    tileset.loadFromFile("tubular.png");
    
    txTube = new Texture();
    txTube->loadFromImage(tileset, IntRect(256, 336, 32, 96));
    
    spTube = new Sprite(*txTube);
    spTube->setPosition(300, 224 - 96);
}

Tube::~Tube()
{
    free(spTube);
    free(txTube);
}

void Tube::draw(RenderWindow* window)
{
    window->draw(*spTube);
}

void Tube::update(float velocity)
{
    spTube->move(-velocity, 0);
    if (spTube->getPosition().x < -40)
    {
        spTube->setPosition(300, spTube->getPosition().y);
    }
}

FloatRect Tube::getGlobalBounds()
{
    return spTube->getGlobalBounds();
}
