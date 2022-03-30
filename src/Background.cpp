#include "Background.hpp"

Background::Background() {
    Image tileset = Image();
    tileset.loadFromFile("bg.png");
    
    txBackground = new Texture();
    txBackground->loadFromImage(tileset, IntRect(1546, 894, 512, 432));
    txBackground->setRepeated(true);

    spBackground = new Sprite(*txBackground);
    spBackground->setPosition(0, -200);
}

Background::~Background() {
    free(spBackground);
    free(txBackground);
}

void Background::run(int velocity)
{
    if (--cooldown > 0) return;
    cooldown = 5;

    auto last = spBackground->getTextureRect();
    spBackground->setTextureRect(IntRect(last.left + velocity, 0, 512, 432));
}

void Background::draw(RenderWindow* window)
{
    window->draw(*spBackground);
}