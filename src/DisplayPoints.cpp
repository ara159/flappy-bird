#include "DisplayPoints.hpp"
#include "TextureFactory.hpp"

DisplayPoints::DisplayPoints() : MyGameObject()
{
    TextureFactory tx = TextureFactory();
    for (int i = 0; i < 10; i++)
    {
        txNumbers[i] = tx.pointNumber(i);
    }
}

DisplayPoints::~DisplayPoints()
{
    for (int i = 0; i < 10; i++)
    {
        free(txNumbers[i]);
    }
}

void DisplayPoints::draw(RenderWindow* window)
{
    auto strPoints = std::to_string(points);
    Sprite sprites[strPoints.length()];
    for (int i = 0; i < strPoints.length(); i++)
    {
        auto number = strPoints.substr(i, 1);
        sprites[i] = Sprite();
        sprites[i].setTexture(*txNumbers[std::stoi(number)]);
        sprites[i].setScale(Vector2f(scale, scale));
    }
    auto totalW = 0;
    for (int i = 0; i < strPoints.length(); i++)
    {
        if (i > 0)
        {
            auto lastBounds = sprites[i-1].getGlobalBounds();
            sprites[i].setPosition(lastBounds.left + lastBounds.width, 0);
        }
        totalW += sprites[i].getGlobalBounds().width;
    }
    for (int i = 0; i < strPoints.length(); i++)
    {
        sprites[i].move(screenSize.x/2 - totalW/2, 20);
        window->draw(sprites[i]);
    }
}

void DisplayPoints::start()
{
    points = 0;
}

void DisplayPoints::update()
{
    points += 1;
}

int DisplayPoints::getPoints()
{
    return points;
}