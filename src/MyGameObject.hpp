#ifndef MY_GAME_OBJECT_H
#define MY_GAME_OBJECT_H 1
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

enum GameScreen { Title_S, GetReady_S, GamePlay_S, Pause_S, GameOver_S };

struct GameStats
{
    bool paused = false;
    bool gameOver = false;
    bool gameStarted = false;
    bool getReady = false;
    GameScreen scene = GameScreen::Title_S;
};

class MyGameObject
{
protected:
    static float scale;
    static Vector2i screenSize;
    static GameScreen scene;
public:
    static GameStats status;
    MyGameObject();
    ~MyGameObject();
};

#endif