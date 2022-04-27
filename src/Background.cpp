#include "Background.hpp"
#include "TextureFactory.hpp"

Background::Background() : MyGameObject() {
    TextureFactory tx = TextureFactory();
    
    txBackground[0] = tx.background1();
    txBackground[1] = tx.background2();

    spBackground = new Sprite();
    spBackground->setScale(sf::Vector2f(scale, scale));
    spBackground->setPosition(0, 0);

    animation = true;
}

void Background::start() {
    spBackground->setTexture(*txBackground[rand() % 2]);
    animation = true;
}

Background::~Background() {
    free(spBackground);
    for (int i = 0; i < 2; i++)
    {
        free(txBackground[i]);
    }
}

void Background::update()
{

}

void Background::draw(RenderWindow* window)
{
    if (animation && cooldown-- == 0)
    {
        auto last = spBackground->getTextureRect();
        cooldown = 6 / scale;
        spBackground->setTextureRect(IntRect(last.left + 1, 0, 512 * scale, 432 * scale));
    }
    window->draw(*spBackground);
}

void Background::setAnimation(bool animation)
{
    this->animation = animation;
}
