#ifndef FLAP_BIRD_H
#define FLAP_BIRD_H 1
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Background.hpp"
#include "Ground.hpp"
#include "Tube.hpp"
#include <vector>
#include "MyGameObject.hpp"

using namespace sf;

class FlapBird : public MyGameObject
{
private:
    Player* player;
    Background* background;
    Ground* ground;
    std::vector<Tube*> tubes;
    int bgVelocityFactor;
    int gameOverCooldown;
    bool gameOver;
    void init();
public:
    FlapBird();
    FlapBird(float scale);
    ~FlapBird();
    void start();
    void run(RenderWindow * window);
    void draw(RenderWindow * window);
    void eventHandler(RenderWindow * window);
};

#endif