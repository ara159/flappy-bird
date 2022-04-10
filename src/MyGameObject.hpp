#ifndef MY_GAME_OBJECT_H
#define MY_GAME_OBJECT_H 1
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class MyGameObject
{
protected:
    float scale = 1;
    Vector2i screenSize;
public:
    MyGameObject();
    ~MyGameObject();
    void setScale(float scale);
};

#endif