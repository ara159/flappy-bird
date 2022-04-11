#ifndef FLAP_BIRD_H
#define FLAP_BIRD_H 1
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Background.hpp"
#include "Ground.hpp"
#include "TubeFactory.hpp"
#include "MyGameObject.hpp"
#include "Checkpoint.hpp"
#include "DisplayPoints.hpp"
#include "PauseButton.hpp"
#include "GameOver.hpp"

using namespace sf;

class FlapBird : public MyGameObject
{
private:
    Player* player;
    Background* background;
    Ground* ground;
    PauseButton* pauseButton;
    DisplayPoints* points;
    TubeFactory* tubeFactory;
    GameOver* gameOverScreen;
    int velocity;
    void init();
    void checkCollisions();
    void updateObjects();
public:
    FlapBird();
    ~FlapBird();
    void start();
    void update(RenderWindow * window);
    void draw(RenderWindow * window);
    void eventHandler(RenderWindow * window);
};

#endif