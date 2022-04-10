#include "Checkpoint.hpp"

Checkpoint::Checkpoint()
{
    init();
}

Checkpoint::~Checkpoint()
{
    init();
}

void Checkpoint::init()
{
    collRect = new RectangleShape(Vector2f(1, screenSize.y));
    collRect->setPosition(screenSize.x + 100, 0);
}

void Checkpoint::update(float velocity)
{
    if (!active) return;
    collRect->move(-velocity * scale, 0);
    if (collRect->getPosition().x < -100)
        active = false;
}

void Checkpoint::draw(RenderWindow* window)
{
    collRect->setFillColor(Color::Green);
    window->draw(*collRect);
}

bool Checkpoint::isActive()
{
    return active;
}

FloatRect Checkpoint::getGlobalBounds()
{
    return collRect->getGlobalBounds();
}

void Checkpoint::collideWithPlayer() {
    active = false;
}
