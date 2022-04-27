#ifndef PLAYER_H
#define PLAYER_H 1
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "MyGameObject.hpp"

using namespace sf;

class Player : public MyGameObject
{
private:
    SoundBuffer* soundBuffer[4];
    Sound* sound[4];
    Texture* txPlayer[9];
    Sprite* spPlayer;
    Vector2f velocity;
    int skin = 0;
    int animationCooldown = 0;
    const int animationCooldownMax = 10;
    int currentTx = 0;
    bool collGround = false;
    bool collTube = false;
    float maxVelocity = 8;
    float gravity = 0.15;
    float impulse = -3;
    Vector2i initialOffset;
    bool animation = true;
public:
    Player();
    ~Player();
    void draw(RenderWindow* window);
    void update();
    FloatRect getGlobalBounds();
    void collideWithGround();
    void collideWithTube();
    void collideWithCheckpoint();
    void start();
    void handleEvent(Event, RenderWindow*);
    void setAnimation(bool);
};

#endif