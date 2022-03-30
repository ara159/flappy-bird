#ifndef TUBE_H
#define TUBE_H 1
#include <SFML/Graphics.hpp>

using namespace sf;

class Tube
{
private:
    Texture* txTube;
    Sprite* spTube;
public:
    Tube();
    ~Tube();
    void draw(RenderWindow* window);
    void update(float velocity);
    FloatRect getGlobalBounds();
};

#endif