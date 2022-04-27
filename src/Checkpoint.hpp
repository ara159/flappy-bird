#ifndef CHECKPOINT_H
#define CHECKPOINT_H 1

#include <SFML/Graphics.hpp>
#include "MyGameObject.hpp"

using namespace sf;

class Checkpoint : MyGameObject
{
private:
    RectangleShape* collRect;
    bool active = true;
public:
    Checkpoint();
    ~Checkpoint();
    void update();
    void draw(RenderWindow* window);
    bool isActive();
    FloatRect getGlobalBounds();
    void collideWithPlayer();
};

#endif