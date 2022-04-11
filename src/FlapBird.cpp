#include "FlapBird.hpp"
#include <iostream>

FlapBird::FlapBird() : MyGameObject()
{
    init();
}

FlapBird::~FlapBird()
{
    free(player);
    free(background);
    free(ground);
    free(pauseButton);
    free(points);
    free(tubeFactory);
}

void FlapBird::init() {
    player = new Player();
    ground = new Ground();
    background = new Background();
    points = new DisplayPoints();
    pauseButton = new PauseButton();
    tubeFactory = new TubeFactory();
    gameOverScreen = new GameOver();
}

void FlapBird::start()
{
    velocity = 1;
    player->start();
    background->start();
    points->start();
    tubeFactory->start();
}

void FlapBird::update(RenderWindow * window)
{
    if (status.paused) return;   
    checkCollisions();
    updateObjects();
}

void FlapBird::updateObjects()
{
    background->run(velocity);
    ground->run(velocity);
    player->update();
    tubeFactory->update(velocity);
}

void FlapBird::checkCollisions()
{
    auto p = player->getGlobalBounds();

    for (auto tube : tubeFactory->getTubes())
    {
        if (p.intersects(tube->getGlobalBounds()))
        {
            velocity = 0;
            player->collideWithTube();
            gameOverScreen->start();
            break;
        }
    }

    for (auto checkpoint : tubeFactory->getCheckpoints())
    {
        if (p.intersects(checkpoint->getGlobalBounds()))
        {
            points->update();
            checkpoint->collideWithPlayer();
        }
    }

    if (p.intersects(ground->getGlobalBounds()))
    {
        player->collideWithGround();
        velocity = 0;
        gameOverScreen->start();
    }
}

void FlapBird::draw(RenderWindow * window)
{
    background->draw(window);
    tubeFactory->draw(window);
    ground->draw(window);
    player->draw(window);
    
    if (!status.gameOver) {
        points->draw(window);
        pauseButton->draw(window);
    }
    gameOverScreen->draw(window);
}

void FlapBird::eventHandler(RenderWindow * window)
{
    Event event;

    while (window->pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window->close();
        }
        
        auto gameOver = status.gameOver;

        if (status.gameOver) {
            gameOverScreen->handleEvent(event, window);
        }

        if (gameOver && !status.gameOver)
        {
            start();
            return;
        }

        auto paused = status.paused;

        pauseButton->handleEvent(event, window);

        if (!paused && !status.paused) // check if is paused before and after handle pause button
        {
            player->handleEvent(event, window);
        }
    }
}