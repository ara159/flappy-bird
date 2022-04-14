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
    free(gameOverScreen);
    free(titleScreen);
    free(getReady);
}

void FlapBird::init() {
    player = new Player();
    ground = new Ground();
    background = new Background();
    points = new DisplayPoints();
    pauseButton = new PauseButton();
    tubeFactory = new TubeFactory();
    gameOverScreen = new GameOver();
    titleScreen = new Title();
    getReady = new GetReady();
}

void FlapBird::start()
{
    background->start();
    velocity = 1;
    
    // if (scene == GameScreen::GamePlay_S || scene == GameScreen::GetReady_S) {
    //     player->start();
    //     points->start();
    //     tubeFactory->start();
        
    //     if (scene == GameScreen::GetReady_S)
    //     {
    //         getReady->start();
    //     }
    // }

    // if (scene == GameScreen::Title_S)
    // {
    //     titleScreen->start();
    // }
}

void FlapBird::update(RenderWindow * window)
{
    background->run(velocity);
    ground->run(velocity);

    if (scene == GameScreen::GamePlay_S)
    {
        player->update();
        tubeFactory->update(velocity);
        checkCollisions();
    }
    
    if (scene == GameScreen::GetReady_S)
    {
        getReady->update();
    }

    if (scene == GameScreen::Title_S)
    {
        titleScreen->update();
    }
    
    if (scene == GameScreen::GameOver_S)
    {
        gameOverScreen->update();
    }
}

void FlapBird::updateObjects()
{
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

    if (scene == GameScreen::Title_S)
    {
        ground->draw(window);
        titleScreen->draw(window);
        return;
    }

    tubeFactory->draw(window);
    player->draw(window);
    ground->draw(window);
    
    if (scene == GameScreen::GetReady_S)
    {
        points->draw(window);
        pauseButton->draw(window);
        getReady->draw(window);
    }
    
    if (scene == GameScreen::GamePlay_S)
    {
        points->draw(window);
        pauseButton->draw(window);
    }
    
    if (scene == GameScreen::GameOver_S)
    {
        gameOverScreen->draw(window);
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

        if (scene == GameScreen::Title_S)
        {
            titleScreen->handleEvent(event, window);
        }
        
        if (scene == GameScreen::GameOver_S)
        {
            gameOverScreen->handleEvent(event, window);
        }

        if (scene == GameScreen::GetReady_S)
        {
            getReady->handleEvent(event, window);
        }

        if (scene == GameScreen::GamePlay_S)
        {
            pauseButton->handleEvent(event, window);
        }
        
        if (scene == GameScreen::GamePlay_S)
        {
            player->handleEvent(event, window);
        }
    }
}

void FlapBird::run(RenderWindow* window)
{
    auto sceneBefore = scene;
    
    update(window);
    eventHandler(window);

    if (sceneBefore != scene)
    {
        if (scene == GameScreen::GetReady_S)
        {
            player->start();
            points->start();
            tubeFactory->start();
            getReady->start();
        }

        if (scene == GameScreen::GamePlay_S)
        {
            
        }
    }

    draw(window);
}