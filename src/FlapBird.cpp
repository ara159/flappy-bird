#include "FlapBird.hpp"
#include <iostream>

FBScreens FlapBird::screen = FBScreens::INIT;

FlapBird::FlapBird() : MyGameObject()
{
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

void FlapBird::changeScreen(FBScreens screen)
{
    if (isScreen(FBScreens::INIT) && screen == FBScreens::GET_READY)
    {
        status.velocity = 1;
    }
    if (isScreen(FBScreens::GET_READY) && screen == FBScreens::GAMEPLAY)
    {
        status.velocity = 1;
    }
    if (isScreen(FBScreens::GAMEPLAY) && screen == FBScreens::GAMEOVER)
    {
        status.velocity = 0;
        gameOverScreen->start(points->getPoints());
    }
    if (isScreen(FBScreens::GAMEOVER) && screen == FBScreens::GET_READY)
    {
        status.velocity = 1;
        player->start();
        tubeFactory->start();
        points->start();
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
    free(txGetReady);
    free(txInstructions);
}

void FlapBird::start()
{
    changeScreen(FBScreens::GET_READY);
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
    background->update();
    ground->update();
    
    if (isScreen(FBScreens::GAMEPLAY))
    {
        player->update();
        tubeFactory->update();
    }
    if (isScreen(FBScreens::GAMEOVER))
    {
        player->update();
        gameOverScreen->update();
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
            changeScreen(FBScreens::GAMEOVER);
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
        changeScreen(FBScreens::GAMEOVER);
    }
}

void FlapBird::draw(RenderWindow * window)
{
    background->draw(window);
    tubeFactory->draw(window);
    ground->draw(window);
    player->draw(window);
    
    if (isScreen(FBScreens::GET_READY) || isScreen(FBScreens::GAMEPLAY))
    {
        points->draw(window);
        pauseButton->draw(window);
    }
    if (isScreen(FBScreens::GET_READY))
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
    if (isScreen(FBScreens::GAMEOVER))
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
        
        auto gameOver = status.gameOver;

        if (status.gameOver)
        {
            gameOverScreen->handleEvent(event, window);
        }
        if (gameOver && !status.gameOver)
        {
            changeScreen(FBScreens::GET_READY);
            return;
        }

        auto paused = status.paused;

        if (isScreen(FBScreens::GAMEPLAY))
        {
            pauseButton->handleEvent(event, window);
        }
        if (isScreen(FBScreens::GET_READY))
        {
            if (event.type == Event::MouseButtonPressed)
                changeScreen(FBScreens::GAMEPLAY);
        }
        if (!paused && !status.paused) // check if is paused before and after handle pause button
        {
            player->handleEvent(event, window);
        }
    }
}