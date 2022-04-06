#include "Tube.hpp"

Tube::Tube() : MyGameObject()
{
    init();
}

Tube::Tube(float scale) : MyGameObject(scale)
{
    init();
}

void Tube::init() {
    Image tileset = Image();
    tileset.loadFromFile("tubular.png");
    
    txTube = new Texture();
    txTube->loadFromImage(tileset, IntRect(256, 336, 32, 96));
    
    spTube = new Sprite(*txTube);
    spTube->setPosition(screenSize.x + 100, screenSize.y - 96 * scale);
    spTube->setScale(sf::Vector2f(scale, scale));
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
    spTube->move(-velocity * scale, 0);
    if (spTube->getPosition().x < -100)
    {
        spTube->setPosition(screenSize.x + 100, spTube->getPosition().y);
    }
}

FloatRect Tube::getGlobalBounds()
{
    return spTube->getGlobalBounds();
}
