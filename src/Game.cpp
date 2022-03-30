#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::start()
{
    window = new RenderWindow(VideoMode(256, 224), "Flap Bird");
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);
    flapBird.start();
    run();
}

void Game::run()
{
    while (window->isOpen())
    {
        draw();
        flapBird.eventHandler(window);
        flapBird.run(window);
    }
}

void Game::draw()
{
    window->clear(Color{52, 119, 235});
    flapBird.draw(window);
    window->display();
}
