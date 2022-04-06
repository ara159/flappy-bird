#ifndef PLAYER_H
#define PLAYER_H 1
#include <SFML/Graphics.hpp>
#include <vector>
#include "MyGameObject.hpp"

using namespace sf;

class Player : public MyGameObject
{
private:
    Texture* txPlayer;
    Sprite* spPlayer;
    Vector2f velocity;
    RectangleShape* collRect;
    bool collGround = false;
    bool collTube = false;
    void init();
    float maxVelocity = 8;
    float gravity = 0.15;
    float impulse = -4;
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