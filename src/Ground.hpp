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
    void init();
public:
    Ground();
    ~Ground();
    void run(int velocity);
    void draw(RenderWindow * window);
    void start();
    FloatRect getGlobalBounds();
};

#endif