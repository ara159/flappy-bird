#ifndef MY_GAME_OBJECT_H
#define MY_GAME_OBJECT_H 1
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

struct GameStats
{
    bool paused = false;
};


class MyGameObject
{
protected:
    float scale = 3;
    Vector2i screenSize;
public:
    static GameStats status;
    MyGameObject();
    ~MyGameObject();
    void setScale(float scale);
};

#endif