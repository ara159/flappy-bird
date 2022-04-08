#include "FlapBird.hpp"

FlapBird::FlapBird() : MyGameObject()
{
    init();
}

FlapBird::FlapBird(float scale) : MyGameObject(scale)
{
    init();
}

FlapBird::~FlapBird()
{
    free(player);
    free(background);
    free(ground);
    for (auto tube : tubes)
    {
        free(tube);
    }
}

void FlapBird::init() {
    player = new Player(scale);
    ground = new Ground(scale);
    background = new Background(scale);
    points = new DisplayPoints(scale);
    font = new Font();
    font->loadFromFile("FlappyBirdy.ttf");
}

void FlapBird::start()
{
    velocity = 1;
    gameOverCooldown = gameOverCooldownMax;
    gameOver = false;
    tubeParams = FlapBird::TubeCreationParams{0, 60 * 2, 60, 1};
    player->start();
    background->start();
    points->start();
    for (auto tube : tubes) free(tube);    
    tubes.clear();
    for (auto checkpoint : checkpoints) free(checkpoint);    
    checkpoints.clear();
}

void FlapBird::run(RenderWindow * window)
{
    if (gameOver) {
        if(--gameOverCooldown == 0) start();
        return;
    }
    
    checkCollisions();
    updateObjects();
    clearInactiveTube();

    int range = 30;
    if (tubeParams.cooldown-- == 0)
    {
        tubeParams.maxCooldown -= tubeParams.decay;
        tubeParams.cooldown = tubeParams.maxCooldown;
        tubes.push_back(new Tube(scale, false, rand() % range));
        tubes.push_back(new Tube(scale, true, rand() % range));
        checkpoints.push_back(new Checkpoint(scale));
    }
}

void FlapBird::updateObjects()
{
    for (auto tube : tubes)
    {
        tube->update(velocity);
    }
    for (auto checkpoint : checkpoints)
    {
        checkpoint->update(velocity);
    }
    background->run(velocity);
    ground->run(velocity);
    player->update();
}

void FlapBird::checkCollisions()
{
    auto p = player->getGlobalBounds();

    for (auto tube : tubes)
    {
        if (p.intersects(tube->getGlobalBounds()))
        {
            velocity = 0;
            player->collideWithTube();
            break;
        }
    }

    for (auto checkpoint : checkpoints)
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
        gameOver = true;
    }
}

void FlapBird::clearInactiveTube()
{
    auto nTubes = std::vector<Tube*>();
    for (auto tube : tubes)
    {
        if (tube->isActive())
            nTubes.push_back(tube);
        else
            free(tube);
    }
    tubes = nTubes;
    
    auto nCheckpoints = std::vector<Checkpoint*>();
    for (auto checkpoint : checkpoints)
    {
        if (checkpoint->isActive())
            nCheckpoints.push_back(checkpoint);
        else
            free(checkpoint);
    }
    checkpoints = nCheckpoints;
}

void FlapBird::draw(RenderWindow * window)
{   
    background->draw(window);
    
    for (auto tube : tubes)
    {
        tube->draw(window);
    }
    for (auto checkpoint : checkpoints)
    {
        checkpoint->draw(window);
    }
    ground->draw(window);
    player->draw(window);
    points->draw(window);
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
            player->onMouseButtonPressed();
        }
    }
}