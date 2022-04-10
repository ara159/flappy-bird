#include "Background.hpp"

Background::Background() : MyGameObject() {
    init();
}

void Background::init() {
    Image tileset = Image();
    tileset.loadFromFile("flappy-birdy-sprites.png");
    
    for (int i = 0; i < 2; i++)
    {
        txBackground[i] = new Texture();
        txBackground[i]->setRepeated(true);
    }

    txBackground[0]->loadFromImage(tileset, IntRect(0, 0, 144, 256));
    txBackground[1]->loadFromImage(tileset, IntRect(146, 0, 144, 256));

    spBackground = new Sprite();
    spBackground->setScale(sf::Vector2f(scale, scale));
    spBackground->setPosition(0, 0);
}

void Background::start() {
    spBackground->setTexture(*txBackground[rand() % 2]);
}

Background::~Background() {
    free(spBackground);
    free(txBackground);
}

void Background::run(int velocity)
{
    if (--cooldown > 0 || velocity == 0) return;
    cooldown = 6 / scale;

    auto last = spBackground->getTextureRect();
    spBackground->setTextureRect(IntRect(last.left + 1, 0, 512 * scale, 432 * scale));
}

void Background::draw(RenderWindow* window)
{
    window->draw(*spBackground);
}