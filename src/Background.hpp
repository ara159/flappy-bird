#ifndef BACKGROUND_H
#define BACKGROUND_H 1
#include <SFML/Graphics.hpp>

using namespace sf;

class Background
{
private:
    Texture* txBackground;
    Sprite* spBackground;
    float velocity = 1;
    int cooldown = 0;
public:
    Background();
    ~Background();
    void run(RenderWindow * window);
    void draw(RenderWindow * window);
};

#endif