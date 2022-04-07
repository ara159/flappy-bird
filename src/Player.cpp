#include "Player.hpp"
#include <iostream>
#include <math.h>

Player::Player() : MyGameObject()
{
    init();
}

Player::Player(float scale) : MyGameObject(scale)
{
    init();
}

Player::~Player() {
    free(spPlayer);

    for (int i = 0; i < 3; i++)
    {
        free(txPlayer[i]);
    }
}

void Player::init() {
    Image tileset = Image();
    tileset.loadFromFile("flappy-birdy-sprites.png");

    for (int i = 0; i < 3; i++)
    {
        txPlayer[i] = new Texture();
    }
    
    txPlayer[0]->loadFromImage(tileset, IntRect(3, 491, 17, 12));
    txPlayer[1]->loadFromImage(tileset, IntRect(31, 491, 17, 12));
    txPlayer[2]->loadFromImage(tileset, IntRect(59, 491, 17, 12));
    
    spPlayer = new Sprite(*txPlayer[1]);
    auto s = spPlayer->getGlobalBounds();
    spPlayer->setOrigin(Vector2f(s.width/2, s.height/2));
    spPlayer->setScale(sf::Vector2f(scale, scale));

    maxVelocity *= scale;
    gravity *= scale;
    impulse *= scale;
    initialOffset.x = screenSize.x * 1/4;
    initialOffset.y = screenSize.y * 1/5;

    start();
}

void Player::draw(RenderWindow* window)
{
    window->draw(*spPlayer);
}

void Player::update()
{
    if (collGround) { return; }

    spPlayer->move(velocity);

    auto angle = spPlayer->getRotation();
    
    if (velocity.y < maxVelocity)
    {
        velocity.y += gravity;
    }
    if (angle > 270 || angle < 90)
    {
        spPlayer->rotate(1.50);
    }
    if (animationCooldown-- == 0)
    {
        animationCooldown = animationCooldownMax;
        currentTx = (currentTx + 1) % 3;
        spPlayer->setTexture(*txPlayer[currentTx]);
    }
}

void Player::onMouseButtonPressed()
{
    if (collGround || collTube) { return; }
    
    velocity.y = impulse;
    spPlayer->setRotation(-45);
}

FloatRect Player::getGlobalBounds()
{
    return spPlayer->getGlobalBounds();
}

void Player::collideWithGround()
{
    collGround = true;
}

void Player::collideWithTube()
{
    collTube = true;
}

void Player::start()
{
    spPlayer->setPosition(initialOffset.x, initialOffset.y);
    spPlayer->setRotation(0);
    velocity = Vector2f(0, 0);
    collGround = false;
    collTube = false;
    animationCooldown = animationCooldownMax;
}