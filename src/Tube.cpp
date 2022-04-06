#include "Tube.hpp"

Tube::Tube() : MyGameObject()
{
    init();
}

Tube::Tube(float scale, bool upsidedown, int closest) : MyGameObject(scale)
{
    this->upsidedown = upsidedown;
    this->closest = closest;
    init();
}

void Tube::init() {
    Image tileset = Image();
    tileset.loadFromFile("tubular.png");
    
    txTube = new Texture();
    txTube->loadFromImage(tileset, IntRect(256, 336, 32, 96));
    
    spTube = new Sprite(*txTube);
    spTube->setPosition(screenSize.x + 100, screenSize.y - 96 * scale - 16 * scale - 8 * scale + closest * scale);
    spTube->setScale(sf::Vector2f(scale, scale));

    if (upsidedown)
    {
        spTube->rotate(180);
        spTube->setPosition(screenSize.x + 100 + 32 * scale, 96 * scale - closest * scale);
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