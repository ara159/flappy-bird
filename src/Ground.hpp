#ifndef GROUND_H
#define GROUND_H 1
#include <SFML/Graphics.hpp>
#include "MyGameObject.hpp"

using namespace sf;

class Ground : public MyGameObject
{
private:
    Texture* txGround;
    Sprite* spGround;
    bool animation;
public:
    Ground();
    ~Ground();
    void update();
    void draw(RenderWindow * window);
    void start();
    FloatRect getGlobalBounds();
    void setAnimation(bool);
};

#endif