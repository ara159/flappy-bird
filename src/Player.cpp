#include "Player.hpp"
#include <iostream>
#include <math.h>

Player::Player()
{
    txPlayer = new Texture();
    txPlayer->loadFromFile("sprite.png");
    
    spPlayer = new Sprite(*txPlayer);
    spPlayer->setOrigin(Vector2f(txPlayer->getSize().x/2, txPlayer->getSize().y/2));
    start();
}

Player::~Player() {
    free(spPlayer);
    free(txPlayer);
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
    
    if (velocity.y < 8)
    {
        velocity.y += 0.15;
    }
    if (angle > 270 || angle < 90)
    {
        spPlayer->rotate(1.50);
    }
}

void Player::onMouseButtonPressed()
{
    if (collGround || collTube) { return; }
    
    velocity.y = -4;
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
    spPlayer->setPosition(60, 30);
    spPlayer->setRotation(0);
    velocity = Vector2f(0, 0);
    collGround = false;
    collTube = false;
}