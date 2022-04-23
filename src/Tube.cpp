#include "Tube.hpp"
#include <iostream>

Tube::Tube(bool upsidedown, int spaceBetween, int offset) : MyGameObject()
{
    this->upsidedown = upsidedown;
    this->offset = offset * scale;
    this->spaceBetween = spaceBetween * scale;
    init();
}

void Tube::init() {
    Image tileset = Image();
    tileset.loadFromFile("flappy-birdy-sprites.png");
    
    txTube = new Texture();

    if (!upsidedown)
        txTube->loadFromImage(tileset, IntRect(84, 323, 26, 160));
    else
        txTube->loadFromImage(tileset, IntRect(56, 323, 26, 160));

    spTube = new Sprite(*txTube);
    spTube->setScale(sf::Vector2f(scale, scale));
    spTube->setOrigin(sf::Vector2f(txTube->getSize().x/2, 0));
    
    int spawnX = screenSize.x + 100 * scale;
    
    if (!upsidedown)
    {
        int minY = 68 * scale;
        spTube->setPosition(spawnX, minY);
        spTube->move(0, spaceBetween);
    }
    else
    {
        int minY = 0;
        spTube->setPosition(spawnX, minY);
        spTube->move(0, -spaceBetween);
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
    if (!active) return;
    spTube->move(status.velocity * scale * -1, 0);
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