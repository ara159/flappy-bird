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
    bool upsidedown = false;
    int closest = 0;
    void init();
public:
    Tube();
    Tube(float scale, bool upsidedown, int closest);
    ~Tube();
    void draw(RenderWindow* window);
    void update(float velocity);
    FloatRect getGlobalBounds();
    bool isActive();
};

#endif