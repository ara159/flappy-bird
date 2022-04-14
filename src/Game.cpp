#include "Game.hpp"

Game::Game() : MyGameObject()
{
    init();
}

void Game::init() {
    flapBird = new FlapBird();
}

Game::~Game()
{
    free(flapBird);
}

void Game::start()
{
    window = new RenderWindow(VideoMode(screenSize.x, screenSize.y), "Flap Bird");
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);
    run();
}

void Game::run()
{
    flapBird->start();
    while (window->isOpen())
    {
        window->clear(Color{52, 119, 235});
        flapBird->run(window);
        window->display();
    }
}
