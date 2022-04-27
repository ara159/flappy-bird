#include "Tube.hpp"
#include <iostream>

Tube::Tube(bool upsidedown, int spaceBetween, int offset) : MyGameObject()
{
    offset = offset * scale;
    spaceBetween = spaceBetween * scale;
    
    txTube = txFactory.tube(upsidedown ? 1 : 0);
    spTube = new Sprite(*txTube);
    spTube->setScale(sf::Vector2f(scale, scale));
    spTube->setOrigin(sf::Vector2f(txTube->getSize().x / 2, 0));
    
    int spawnX = screenSize.x + 100 * scale;
    
    if (! upsidedown)
    {
        int minY = 68 * scale;
        spTube->setPosition(spawnX, minY);
        spTube->move(0, spaceBetween);
    }
    else
    {
        int minY = 0;
        spTube->setPosition(spawnX, minY);
        spTube->move(0, - spaceBetween);
    }
    
    spTube->move(0, offset);
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

void Tube::update()
{
    if (!active)
        return;
    
    spTube->move(1 * scale * -1, 0);
    
    if (spTube->getPosition().x < -100)
    {
        active = false;
    }
}

FloatRect Tube::getGlobalBounds()
{
    return spTube->getGlobalBounds();
}

bool Tube::isActive() {
    return active;
}