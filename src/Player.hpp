#ifndef PLAYER_H
#define PLAYER_H 1
#include <SFML/Graphics.hpp>
#include <vector>
#include "WithCollision.hpp"

using namespace sf;

class Player : public WithCollision
{
private:
    Texture* txPlayer;
    Sprite* spPlayer;
    Vector2f velocity;
    Vector2f direction;
public:
    Player();
    ~Player();
    void draw(RenderWindow* window);
    void update();
    void onMouseButtonPressed();
    std::string getName();
    void onCollision();
};

#endif