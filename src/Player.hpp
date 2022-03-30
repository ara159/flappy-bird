#ifndef PLAYER_H
#define PLAYER_H 1
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class Player
{
private:
    Texture* txPlayer;
    Sprite* spPlayer;
    Vector2f velocity;
    bool collGround = false;
    bool collTube = false;
public:
    Player();
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