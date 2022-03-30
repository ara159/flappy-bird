#ifndef BACKGROUND_H
#define BACKGROUND_H 1
#include <SFML/Graphics.hpp>

using namespace sf;

class Background
{
private:
    Texture* txBackground;
    Sprite* spBackground;
    int cooldown = 0;
public:
    Background();
    ~Background();
    void run(int velocity);
    void draw(RenderWindow * window);
};

#endif