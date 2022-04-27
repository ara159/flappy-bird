#include "Ground.hpp"

Ground::Ground() : MyGameObject()
{
    Image tileset = Image();
    tileset.loadFromFile("flappy-birdy-sprites.png");

    txGround = new Texture();
    txGround->loadFromImage(tileset, IntRect(292, 0, 168, 56));
    txGround->setRepeated(true);

    spGround = new Sprite(*txGround);
    spGround->setScale(sf::Vector2f(scale, scale));
    spGround->setPosition(0, 228 * scale);
    int p = spGround->getGlobalBounds().height;

    animation = true;
}

Ground::~Ground()
{
    free(spGround);
    free(txGround);
}

void Ground::update()
{
    
}

void Ground::draw(RenderWindow* window)
{
    if (animation)
    {
        IntRect last = spGround->getTextureRect();
        spGround->setTextureRect(IntRect(last.left + 1, 0, last.width, last.height));
    }
    window->draw(*spGround);
}

FloatRect Ground::getGlobalBounds()
{
    return spGround->getGlobalBounds();
}

void Ground::setAnimation(bool animation)
{
    this->animation = animation;
}