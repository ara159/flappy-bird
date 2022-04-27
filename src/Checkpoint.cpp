#include "Checkpoint.hpp"

Checkpoint::Checkpoint()
{
    collRect = new RectangleShape(Vector2f(1, screenSize.y));
    collRect->setPosition(screenSize.x + 100 * scale, 0);
}

Checkpoint::~Checkpoint()
{
    free(collRect);
}

void Checkpoint::update()
{
    if (!active)
        return;
    
    collRect->move(- 1 * scale, 0);
    
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
