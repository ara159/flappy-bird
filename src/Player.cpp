#include "Player.hpp"
#include <iostream>
#include <math.h>

Player::Player() : MyGameObject()
{
    init();
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

void Player::init() {
    Image tileset = Image();
    tileset.loadFromFile("flappy-birdy-sprites.png");

    for (int i = 0; i < 9; i++)
    {
        txPlayer[i] = new Texture();
    }

    // skin 1
    txPlayer[0]->loadFromImage(tileset, IntRect(3, 491, 17, 12));
    txPlayer[1]->loadFromImage(tileset, IntRect(31, 491, 17, 12));
    txPlayer[2]->loadFromImage(tileset, IntRect(59, 491, 17, 12));

    // skin 2
    txPlayer[3]->loadFromImage(tileset, IntRect(87, 491, 17, 12));
    txPlayer[4]->loadFromImage(tileset, IntRect(115, 329, 17, 12));
    txPlayer[5]->loadFromImage(tileset, IntRect(115, 355, 17, 12));

    // skin 3
    txPlayer[6]->loadFromImage(tileset, IntRect(115, 381, 17, 12));
    txPlayer[7]->loadFromImage(tileset, IntRect(115, 407, 17, 12));
    txPlayer[8]->loadFromImage(tileset, IntRect(115, 433, 17, 12));

    spPlayer = new Sprite();

    maxVelocity *= scale;
    gravity *= scale;
    impulse *= scale;
    initialOffset.x = screenSize.x * 1/4;
    initialOffset.y = screenSize.y * 1/5;

    soundBuffer = new SoundBuffer();
    soundBuffer->loadFromFile("flappy-birdy-audios.wav");
    sound = new Sound(*soundBuffer);
}

void Player::draw(RenderWindow* window)
{
    if (!status.paused && !collGround && animationCooldown-- == 0)
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
        spPlayer->rotate(1.50);
    }
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
    if (collTube) return;
    // sound->setPlayingOffset(Time());
    // sound->play();
    collTube = true;
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
