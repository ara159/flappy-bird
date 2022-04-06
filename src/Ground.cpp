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
    tileset.loadFromFile("tiles.png");
    
    shapes[0] = new RectangleShape(Vector2f(screenSize.x, 8 * scale));
    shapes[1] = new RectangleShape(Vector2f(screenSize.x, 16 * scale));

    textures[0] = new Texture();
    textures[0]->loadFromImage(tileset, IntRect(536, 64, 16, 8));
    textures[0]->setRepeated(true);

    textures[1] = new Texture();
    textures[1]->loadFromImage(tileset, IntRect(696, 56, 16, 16));
    textures[1]->setRepeated(true);

    shapes[0]->setTexture(textures[0]);
    shapes[1]->setTexture(textures[1]);
    
    shapes[0]->setPosition(0, screenSize.y - 16 * scale - 8 * scale);
    shapes[1]->setPosition(0, screenSize.y - 16 * scale);
    
    shapes[0]->setTextureRect(IntRect(0, 0, screenSize.x, 8 * scale));
    shapes[1]->setTextureRect(IntRect(0, 0, screenSize.x, 16 * scale));

    shapes[0]->setScale(sf::Vector2f(scale, scale));
    shapes[1]->setScale(sf::Vector2f(scale, scale));

}

Ground::~Ground()
{
    for (int i = 0; i < 2; i++)
    {
        free(textures[i]);
        free(shapes[i]);
    }
}

void Ground::run(int velocity)
{
    IntRect last;
    
    last = shapes[0]->getTextureRect();
    shapes[0]->setTextureRect(IntRect(last.left + velocity, 0, screenSize.x, 8 * scale));
    
    last = shapes[1]->getTextureRect();
    shapes[1]->setTextureRect(IntRect(last.left + velocity, 0, screenSize.x, 16 * scale));
}

void Ground::draw(RenderWindow* window)
{
    for (int i = 0; i < 2; i++)
        window->draw(*shapes[i]);
}

FloatRect Ground::getGlobalBounds()
{
    return shapes[0]->getGlobalBounds();
}
