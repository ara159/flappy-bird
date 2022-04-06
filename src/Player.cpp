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
    free(txPlayer);
    free(collRect);
}

void Player::init() {
    txPlayer = new Texture();
    txPlayer->loadFromFile("sprite.png");
    
    spPlayer = new Sprite(*txPlayer);
    spPlayer->setOrigin(Vector2f(txPlayer->getSize().x/2, txPlayer->getSize().y/2));
    spPlayer->setScale(sf::Vector2f(scale, scale));

    auto collSize = Vector2f(15, 10);
    collRect = new RectangleShape(collSize);
    collRect->setOrigin(collSize.x/2, collSize.y/2);
    collRect->setScale(sf::Vector2f(scale, scale));

    maxVelocity *= scale;
    gravity *= scale;
    impulse *= scale;

    // debug
    collRect->setFillColor(Color{0,0,0,0});
    collRect->setOutlineColor(Color::Green);
    collRect->setOutlineThickness(1);
    start();
}

void Player::draw(RenderWindow* window)
{
    window->draw(*spPlayer);
    window->draw(*collRect);
}

void Player::update()
{
    collRect->setPosition(spPlayer->getPosition());

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
}

void Player::onMouseButtonPressed()
{
    if (collGround || collTube) { return; }
    
    velocity.y = impulse;
    spPlayer->setRotation(-45);
}

FloatRect Player::getGlobalBounds()
{
    return collRect->getGlobalBounds();
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