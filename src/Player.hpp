#ifndef PLAYER_H
#define PLAYER_H 1
#include <SFML/Graphics.hpp>
#include <vector>
#include "MyGameObject.hpp"

using namespace sf;

class Player : public MyGameObject
{
private:
    Texture* txPlayer[9];
    Sprite* spPlayer;
    Vector2f velocity;
    int skin = 0;
    int animationCooldown = 0;
    const int animationCooldownMax = 30;
    int currentTx = 0;
    bool collGround = false;
    bool collTube = false;
    float maxVelocity = 8;
    float gravity = 0.15;
    float impulse = -3;
    Vector2i initialOffset;
    void init();
public:
    Player();
    Player(float scale);
    ~Player();
    void draw(RenderWindow* window);
    void update();
    void onMouseButtonPressed();
    FloatRect getGlobalBounds();
    void collideWithGround();
    void collideWithTube();
    void start();
};

#endif