#include "Ground.hpp"

Ground::Ground() : MyGameObject()
{
    init();
}

Ground::Ground(float scale) : MyGameObject(scale)
{
    init();
}

void Ground::init() {
    Image tileset = Image();
    tileset.loadFromFile("flappy-birdy-sprites.png");

    txGround = new Texture();
    txGround->loadFromImage(tileset, IntRect(292, 0, 168, 56));
    txGround->setRepeated(true);

    spGround = new Sprite(*txGround);
    spGround->setScale(sf::Vector2f(scale, scale));
    spGround->setPosition(0, screenSize.y - spGround->getGlobalBounds().height * 1/2);
}

Ground::~Ground()
{
    free(spGround);
    free(txGround);
}

void Ground::run(int velocity)
{
    IntRect last = spGround->getTextureRect();
    spGround->setTextureRect(IntRect(last.left + velocity, 0, last.width, last.height));
}

void Ground::draw(RenderWindow* window)
{
    window->draw(*spGround);
}

FloatRect Ground::getGlobalBounds()
{
    return spGround->getGlobalBounds();
}
