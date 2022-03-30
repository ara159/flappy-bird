#include "Ground.hpp"

Ground::Ground()
{
    shapes[0] = new RectangleShape(Vector2f(256, 8));
    shapes[1] = new RectangleShape(Vector2f(256, 16));

    Image tileset = Image();
    tileset.loadFromFile("tiles.png");
    
    textures[0] = new Texture();
    textures[0]->loadFromImage(tileset, IntRect(536, 64, 16, 8));
    textures[0]->setRepeated(true);

    textures[1] = new Texture();
    textures[1]->loadFromImage(tileset, IntRect(696, 56, 16, 16));
    textures[1]->setRepeated(true);

    shapes[0]->setTexture(textures[0]);
    shapes[1]->setTexture(textures[1]);
    
    shapes[0]->setPosition(0, 224 - 16 - 8);
    shapes[1]->setPosition(0, 224 - 16);
    
    shapes[0]->setTextureRect(IntRect(0, 0, 256, 8));
    shapes[1]->setTextureRect(IntRect(0, 0, 256, 16));
}

Ground::~Ground()
{
    free(textures[0]);
    free(textures[1]);
    free(shapes[0]);
    free(shapes[1]);
}

void Ground::run(int velocity)
{
    IntRect last;
    
    last = shapes[0]->getTextureRect();
    shapes[0]->setTextureRect(IntRect(last.left + velocity, 0, 256, 8));
    
    last = shapes[1]->getTextureRect();
    shapes[1]->setTextureRect(IntRect(last.left + velocity, 0, 256, 16));
}

void Ground::draw(RenderWindow* window)
{
    window->draw(*shapes[0]);
    window->draw(*shapes[1]);
}

FloatRect Ground::getGlobalBounds()
{
    return shapes[0]->getGlobalBounds();
}
