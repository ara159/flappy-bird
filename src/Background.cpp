#include "Background.hpp"

Background::Background() : MyGameObject() {
    init();
}

Background::Background(float scale) : MyGameObject(scale) {
    init();
}

void Background::init() {
    Image tileset = Image();
    tileset.loadFromFile("bg.png");
    
    txBackground = new Texture();
    txBackground->loadFromImage(tileset, IntRect(1546, 894, 512, 432));
    txBackground->setRepeated(true);

    spBackground = new Sprite(*txBackground);
    spBackground->setScale(sf::Vector2f(scale, scale));
    spBackground->setPosition(0, -spBackground->getGlobalBounds().height/2);
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