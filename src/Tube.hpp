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
    void init();
public:
    Tube();
    Tube(float scale);
    ~Tube();
    void draw(RenderWindow* window);
    void update(float velocity);
    FloatRect getGlobalBounds();
};

#endif