#ifndef BACKGROUND_H
#define BACKGROUND_H 1
#include <SFML/Graphics.hpp>
#include "MyGameObject.hpp"

using namespace sf;

class Background : public MyGameObject
{
private:
    Texture* txBackground[2];
    Sprite* spBackground;
    int cooldown = 0;
    bool animation;
public:
    Background();
    ~Background();
    void start();
    void update();
    void draw(RenderWindow * window);
    void setAnimation(bool);
};

#endif