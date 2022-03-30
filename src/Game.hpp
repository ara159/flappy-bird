#ifndef GAME_H
#define GAME_H 1
#include <SFML/Graphics.hpp>
#include "FlapBird.hpp"

using namespace sf;

class Game
{
private:
    RenderWindow * window;
    void run();
    void draw();
    FlapBird flapBird;
public:
    Game();
    ~Game();
    void start();
};

#endif