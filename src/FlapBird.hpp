#ifndef FLAP_BIRD_H
#define FLAP_BIRD_H 1
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Background.hpp"
#include "Ground.hpp"
#include "Tube.hpp"
#include <vector>
#include "MyGameObject.hpp"
#include "Checkpoint.hpp"
#include "DisplayPoints.hpp"

using namespace sf;

class FlapBird : public MyGameObject
{
private:
    struct TubeCreationParams
    {
        int cooldown;
        int maxCooldown;
        int minCooldown;
        int decay;
    };
    Font* font;
    Player* player;
    Background* background;
    Ground* ground;
    DisplayPoints* points;
    std::vector<Tube*> tubes;
    std::vector<Checkpoint*> checkpoints;
    int velocity;
    int gameOverCooldown;
    const int gameOverCooldownMax = 180;
    FlapBird::TubeCreationParams tubeParams;
    bool gameOver;
    void init();
    void clearInactiveTube();
    void checkCollisions();
    void updateObjects();
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