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

enum FBScreens { INIT, GET_READY, GAMEPLAY, GAMEOVER };

class FlapBird : public MyGameObject
{
private:
    static FBScreens screen;
    Player* player;
    Background* background;
    Ground* ground;
    PauseButton* pauseButton;
    DisplayPoints* points;
    TubeFactory* tubeFactory;
    GameOver* gameOverScreen;
    Texture* txGetReady;
    Texture* txInstructions;
    void checkCollisions();
    void updateObjects();
    void changeScreen(FBScreens screen);
    bool isScreen(FBScreens screen);
public:
    FlapBird();
    ~FlapBird();
    void start();
    void update(RenderWindow * window);
    void draw(RenderWindow * window);
    void eventHandler(RenderWindow * window);
};

#endif