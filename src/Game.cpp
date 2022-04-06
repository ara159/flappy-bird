#include "Game.hpp"

Game::Game() : MyGameObject()
{
    init();
}

Game::Game(float scale) : MyGameObject(scale)
{
    init();
}

void Game::init() {
    flapBird = new FlapBird(scale);
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
    flapBird->start();
    run();
}

void Game::run()
{
    while (window->isOpen())
    {
        draw();
        flapBird->eventHandler(window);
        flapBird->run(window);
    }
}

void Game::draw()
{
    window->clear(Color{52, 119, 235});
    flapBird->draw(window);
    window->display();
}
