#include "Player.hpp"
#include <iostream>
#include <math.h>

Player::Player()
{
    txPlayer = new Texture();
    txPlayer->loadFromFile("sprite.png");
    
    spPlayer = new Sprite(*txPlayer);
    spPlayer->setOrigin(Vector2f(txPlayer->getSize().x/2, txPlayer->getSize().y/2));
    spPlayer->setPosition(60, 30);
    velocity = Vector2f(0, 0);
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
    spPlayer->move(velocity);
    auto angle = spPlayer->getRotation();
    
    if (spPlayer->getPosition().y > 256 - spPlayer->getLocalBounds().height)
    {
        velocity.y = 0;
        return;
    }
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
    velocity.y = -5;
    spPlayer->setRotation(-45);
}

std::string Player::getName() { return "player"; }

void Player::onCollision() {}