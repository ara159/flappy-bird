#include "FlapBird.hpp"
#include <iostream>

FBScreens FlapBird::screen = INIT;

FlapBird::FlapBird() : MyGameObject()
{
    player = new Player();
    ground = new Ground();
    background = new Background();
    points = new DisplayPoints();
    pauseButton = new PauseButton();
    tubeFactory = new TubeFactory();
    gameOverScreen = new GameOver();
    titleScreen = new TitleScreen();
    getReadyScreen = new GetReadyScreen();
}

void FlapBird::changeScreen(FBScreens screen)
{
    if (isScreen(INIT) && screen == TITLE)
    {
        status.velocity = 1;
        titleScreen->start();
    }
    if (isScreen(TITLE) && screen == GET_READY)
    {
        getReadyScreen->start();
    }
    if (isScreen(GET_READY) && screen == GAMEPLAY)
    {
        status.velocity = 1;
    }
    if (isScreen(GAMEPLAY) && screen == GAMEOVER)
    {
        status.velocity = 0;
        gameOverScreen->start(points->getPoints());
    }
    if (isScreen(GAMEOVER) && screen == GET_READY)
    {
        status.velocity = 1;
        player->start();
        tubeFactory->start();
        points->start();
    }
    if (isScreen(GAMEPLAY) && screen == PAUSE)
    {
        player->setAnimation(false);
    }
    if (isScreen(PAUSE) && screen == GAMEPLAY)
    {
        player->setAnimation(true);
    }
    this->screen = screen;
}

bool FlapBird::isScreen(FBScreens screen)
{
    return this->screen == screen;
}

FlapBird::~FlapBird()
{
    free(player);
    free(background);
    free(ground);
    free(pauseButton);
    free(points);
    free(tubeFactory);
    free(gameOverScreen);
    free(titleScreen);
    free(getReadyScreen);
}

void FlapBird::start()
{
    changeScreen(TITLE);
    player->start();
    background->start();
    points->start();
    tubeFactory->start();
}

void FlapBird::update(RenderWindow * window)
{
    if (status.toScreen != NONE)
    {
        changeScreen(status.toScreen);
        status.toScreen = NONE;
    }

    if (!isScreen(PAUSE))
    {
        checkCollisions();
        updateObjects();
    }
}

void FlapBird::updateObjects()
{
    background->update();
    ground->update();
    
    if (isScreen(GET_READY))
    {
        getReadyScreen->update();
    }

    if (isScreen(GAMEPLAY))
    {
        player->update();
        tubeFactory->update();
    }
    if (isScreen(GAMEOVER))
    {
        player->update();
        gameOverScreen->update();
    }
    if (isScreen(TITLE))
    {
        titleScreen->update();
    }
}

void FlapBird::checkCollisions()
{
    auto p = player->getGlobalBounds();
    
    for (auto tube : tubeFactory->getTubes())
    {
        if (p.intersects(tube->getGlobalBounds()))
        {
            player->collideWithTube();
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
    }
}

void FlapBird::draw(RenderWindow * window)
{
    background->draw(window);
    tubeFactory->draw(window);
    ground->draw(window);
    
    if (isScreen(GET_READY) || isScreen(GAMEPLAY) || isScreen(PAUSE))
    {
        points->draw(window);
        pauseButton->draw(window);
        player->draw(window);
    }
    if (isScreen(GET_READY))
    {
        getReadyScreen->draw(window);
    }
    if (isScreen(GAMEOVER))
    {
        player->draw(window);
        gameOverScreen->draw(window);
    }
    if (isScreen(TITLE))
    {
        titleScreen->draw(window);
    }
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

        if (isScreen(GAMEOVER))
        {
            gameOverScreen->handleEvent(event, window);
        }

        if (isScreen(GAMEPLAY) || isScreen(PAUSE))
        {
            pauseButton->handleEvent(event, window);
        }

        if (isScreen(GET_READY))
        {
            getReadyScreen->handleEvent(event, window);
            player->handleEvent(event, window);
        }
        
        if (isScreen(TITLE))
        {
            titleScreen->handleEvent(event, window);
        }

        if (status.toScreen == NONE)
        {
            if (isScreen(GAMEPLAY))
            {
                player->handleEvent(event, window);
            }
        }
    }
}