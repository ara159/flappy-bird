#include "FlapBird.hpp"

FlapBird::FlapBird()
{
}

FlapBird::~FlapBird()
{
}

void FlapBird::start()
{
    bgVelocityFactor = 1;
    gameOverCooldown = 60 * 3;
    gameOver = false;
    tubes.clear();
    tubes.push_back(new Tube());
}

void FlapBird::run(RenderWindow * window)
{
    if (gameOver) {
        if(--gameOverCooldown == 0)
        {
            start();
            player.start();
        }
        return;
    }

    player.update();
    auto p = player.getGlobalBounds();

    for (auto tube : tubes)
    {
        if (p.intersects(tube->getGlobalBounds()))
        {
            bgVelocityFactor = 0;
            player.collideWithTube();
            break;
        }
    }

    if (p.intersects(ground.getGlobalBounds()))
    {
        player.collideWithGround();
        bgVelocityFactor = 0;
        gameOver = true;
    }

    for (auto tube : tubes)
    {
        tube->update(bgVelocityFactor);
    }

    background.run(bgVelocityFactor);
    ground.run(bgVelocityFactor);
}

void FlapBird::draw(RenderWindow * window)
{   
    background.draw(window);
    
    for (auto tube : tubes)
        tube->draw(window);
    
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