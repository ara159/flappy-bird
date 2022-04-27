#include "Player.hpp"
#include <iostream>
#include <math.h>
#include "TextureFactory.hpp"

Player::Player() : MyGameObject()
{
    TextureFactory tx = TextureFactory();
    
    for (int i = 0; i < 9; i++)
    {
        txPlayer[i] = tx.player(i);
    }

    spPlayer = new Sprite();

    maxVelocity *= scale;
    gravity *= scale;
    impulse *= scale;
    initialOffset.x = screenSize.x * 0.5;
    initialOffset.y = screenSize.y * 0.5;

    soundBuffer = new SoundBuffer();
    soundBuffer->loadFromFile("flappy-birdy-audios.wav");
    sound = new Sound(*soundBuffer);
}

Player::~Player() {
    free(spPlayer);
    free(soundBuffer);
    free(sound);

    for (int i = 0; i < 3; i++)
    {
        free(txPlayer[i]);
    }
}

void Player::setAnimation(bool animation)
{
    this->animation = animation;
}

void Player::draw(RenderWindow* window)
{
    if (animation && animationCooldown-- == 0)
    {
        animationCooldown = animationCooldownMax;
        currentTx = (currentTx + 1) % 3;
        spPlayer->setTexture(*txPlayer[skin * 3 + currentTx]);
    }
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
        spPlayer->rotate(2);
    }
}

FloatRect Player::getGlobalBounds()
{
    return spPlayer->getGlobalBounds();
}

void Player::collideWithGround()
{
    collGround = true;
    animation = false;
    status.toScreen = GAMEOVER;
}

void Player::collideWithTube()
{
    collTube = true;
    animation = false;
    status.toScreen = GAMEOVER;
}

void Player::start()
{
    auto s = Vector2i(17, 12);
    skin = rand() % 3;
    spPlayer->setTexture(*txPlayer[skin * 3 + 1]);
    spPlayer->setOrigin(Vector2f(s.x/2, s.y/2));
    spPlayer->setScale(sf::Vector2f(scale, scale));

    spPlayer->setPosition(initialOffset.x, initialOffset.y);
    spPlayer->setRotation(0);
    velocity = Vector2f(0, 0);
    collGround = false;
    collTube = false;
    animationCooldown = animationCooldownMax;
    animation = true;
}

void Player::handleEvent(Event event, RenderWindow* window)
{
    if (event.type == Event::MouseButtonPressed)
    {
        if (collGround || collTube) return;
        velocity.y = impulse;
        spPlayer->setRotation(-45);
    }
}
