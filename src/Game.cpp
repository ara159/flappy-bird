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
    window = new RenderWindow(VideoMode(screenSize.x, screenSize.y), "Flappy Bird");
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
        flapBird->update(window);
    }
}

void Game::draw()
{
    window->clear(Color{52, 119, 235});
    flapBird->draw(window);
    window->display();
}
