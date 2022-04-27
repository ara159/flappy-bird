#ifndef GAME_H
#define GAME_H 1
#include <SFML/Graphics.hpp>
#include "FlappyBird.hpp"
#include "MyGameObject.hpp"

using namespace sf;

class Game : public MyGameObject
{
private:
    RenderWindow * window;
    void run();
    void draw();
    FlapBird* flapBird;
    void init();
public:
    Game();
    ~Game();
    void start();
};

#endif