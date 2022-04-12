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

    Image tileset = Image();
    tileset.loadFromFile("flappy-birdy-sprites.png");
    txGetReady = new Texture();
    txGetReady->loadFromImage(tileset, IntRect(295, 59, 92, 25));

    txInstructions = new Texture();
    txInstructions->loadFromImage(tileset, IntRect(292, 91, 57, 49));
}

void FlapBird::start()
{
    started = false;
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
    if (started)
    {
        player->update();
        tubeFactory->update(velocity);
    }
    gameOverScreen->update();
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
            gameOverScreen->start(points->getPoints());
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
        gameOverScreen->start(points->getPoints());
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
    if (!started)
    {
        Sprite spGetReady(*txGetReady);
        spGetReady.setOrigin(spGetReady.getGlobalBounds().width/2, 0);
        spGetReady.setScale(Vector2f(scale, scale));
        spGetReady.setPosition(screenSize.x/2, 50 * scale);
        window->draw(spGetReady);

        Sprite spInstructions(*txInstructions);
        spInstructions.setOrigin(spInstructions.getGlobalBounds().width/2, 0);
        spInstructions.setScale(Vector2f(scale, scale));
        spInstructions.setPosition(screenSize.x/2, screenSize.y/2 * 1.25);
        window->draw(spInstructions);
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

        if (started)
            pauseButton->handleEvent(event, window);

        if (!started)
        {
            if (event.type == Event::MouseButtonPressed)
                started = true;
        }
        if (!paused && !status.paused) // check if is paused before and after handle pause button
        {
            player->handleEvent(event, window);
        }
    }
}