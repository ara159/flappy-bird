#ifndef FLAP_BIRD_H
#define FLAP_BIRD_H 1
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Background.hpp"
#include "Ground.hpp"
#include <vector>

using namespace sf;

class FlapBird
{
private:
    Player player;
    Background background;
    Ground ground;
public:
    FlapBird();
    ~FlapBird();
    void start();
    void run(RenderWindow * window);
    void draw(RenderWindow * window);
    void eventHandler(RenderWindow * window);
};

#endif