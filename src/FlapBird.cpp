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
    font = new Font();
    font->loadFromFile("FlappyBirdy.ttf");
}

void FlapBird::start()
{
    bgVelocityFactor = 1;
    gameOverCooldown = 60 * 3;
    gameOver = false;
    tubeParams = FlapBird::TubeCreationParams{0, 60 * 2, 60, 1};
    player->start();
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

    if (tubeParams.cooldown-- == 0)
    {
        tubeParams.maxCooldown -= tubeParams.decay;
        tubeParams.cooldown = tubeParams.maxCooldown;
        int s1, s2;
        s1 = rand() % 30;
        s2 = rand() % 30;
        tubes.push_back(new Tube(scale, false, 20 + s1));
        tubes.push_back(new Tube(scale, true, 20 + s2));
        checkpoints.push_back(new Checkpoint(scale));
    }
}

void FlapBird::updateObjects()
{
    for (auto tube : tubes)
    {
        tube->update(bgVelocityFactor);
    }
    for (auto checkpoint : checkpoints)
    {
        checkpoint->update(bgVelocityFactor);
    }
    background->run(bgVelocityFactor);
    ground->run(bgVelocityFactor);
    player->update();
}

void FlapBird::checkCollisions()
{
    auto p = player->getGlobalBounds();

    for (auto tube : tubes)
    {
        if (p.intersects(tube->getGlobalBounds()))
        {
            bgVelocityFactor = 0;
            player->collideWithTube();
            break;
        }
    }

    for (auto checkpoint : checkpoints)
    {
        if (p.intersects(checkpoint->getGlobalBounds()))
        {
            points += 1;
            checkpoint->collideWithPlayer();
        }
    }

    if (p.intersects(ground->getGlobalBounds()))
    {
        player->collideWithGround();
        bgVelocityFactor = 0;
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
    player->draw(window);
    ground->draw(window);

    Text text;
    text.setFont(*font);
    text.setString(std::to_string(points));
    text.setCharacterSize(20 * scale);
    text.setPosition(screenSize.x * 1/2, screenSize.y * 1/10);
    text.setOrigin(Vector2f(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2));
    text.setFillColor(Color::White);
    text.setOutlineColor(Color::Black);
    text.setOutlineThickness(1);
    window->draw(text);
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