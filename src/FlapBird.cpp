#include "FlapBird.hpp"

FlapBird::FlapBird()
{
}

FlapBird::~FlapBird()
{}

void FlapBird::start()
{
}

void FlapBird::run(RenderWindow * window)
{
    background.run(window);
    player.update();
    ground.run(window);
}

void FlapBird::draw(RenderWindow * window)
{   
    background.draw(window);
    player.draw(window);
    ground.draw(window);
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
        if (event.type == Event::MouseButtonPressed)
        {
            player.onMouseButtonPressed();
        }
    }
}