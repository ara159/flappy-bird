#ifndef TUBE_H
#define TUBE_H 1
#include <SFML/Graphics.hpp>
#include "MyGameObject.hpp"

using namespace sf;

class Tube : public MyGameObject
{
private:
    Texture* txTube;
    Sprite* spTube;
    bool active = true;
public:
    Tube(bool upsidedown, int spaceBetween, int offset);
    ~Tube();
    void draw(RenderWindow* window);
    void update();
    FloatRect getGlobalBounds();
    bool isActive();
};

#endif