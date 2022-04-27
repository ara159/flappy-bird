#ifndef MY_GAME_OBJECT_H
#define MY_GAME_OBJECT_H 1
#include <SFML/Graphics.hpp>
#include <vector>
#include "TextureFactory.hpp"

using namespace sf;

enum FBScreens { INIT, TITLE, GET_READY, GAMEPLAY, GAMEOVER, PAUSE, NONE };

struct GameStats
{
    bool paused = false;
    bool gameOver = false;
    FBScreens toScreen = NONE;
};

class MyGameObject
{
protected:
    float scale = 3;
    Vector2i screenSize;
public:
    static GameStats status;
    static TextureFactory txFactory;
    MyGameObject();
    ~MyGameObject();
    void setScale(float scale);
};

#endif