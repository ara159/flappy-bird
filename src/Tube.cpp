#include "Tube.hpp"

Tube::Tube() : MyGameObject()
{
    init();
}

Tube::Tube(float scale, bool upsidedown, int closest) : MyGameObject(scale)
{
    this->upsidedown = upsidedown;
    this->closest = closest * scale;
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

    int min = 45 * scale;

    if (!upsidedown)
    {
        spTube->setOrigin(sf::Vector2f(txTube->getSize().x/2, 0));
        spTube->setPosition(screenSize.x + 100, screenSize.y/2 + closest + min/2);
    }
    else
    {
        spTube->setOrigin(sf::Vector2f(txTube->getSize().x/2, txTube->getSize().y));
        spTube->setPosition(screenSize.x + 100, screenSize.y/2 - closest - min/2);
    }
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
    if (!active) return;
    spTube->move(-velocity * scale, 0);
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