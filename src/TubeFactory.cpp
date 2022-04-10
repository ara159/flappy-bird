#include "TubeFactory.hpp"
#include "Checkpoint.hpp"

TubeFactory::TubeFactory() : MyGameObject()
{
    init();
}

TubeFactory::~TubeFactory()
{
    clear();
}

void TubeFactory::clear()
{
    for (auto tube : tubes)
        free(tube);    
    
    for (auto checkpoint : checkpoints)
        free(checkpoint);
    
    tubes.clear();
    checkpoints.clear();
}

void TubeFactory::init()
{
}

void TubeFactory::start()
{
    cooldown = 0;
    maxCooldown = 60 * 2;
    minCooldown = 60;
    decay = 1;
    clear();
}

void TubeFactory::draw(RenderWindow* window)
{
    for (auto tube : tubes)
    {
        tube->draw(window);
    }
    for (auto checkpoint : checkpoints)
    {
        checkpoint->draw(window);
    }
}

void TubeFactory::destroyInactive()
{
    auto _tubes = std::vector<Tube*>();
    for (auto tube : tubes)
    {
        if (tube->isActive())
            _tubes.push_back(tube);
        else
            free(tube);
    }
    tubes = _tubes;
    
    auto _checkpoints = std::vector<Checkpoint*>();
    for (auto checkpoint : checkpoints)
    {
        if (checkpoint->isActive())
            _checkpoints.push_back(checkpoint);
        else
            free(checkpoint);
    }
    checkpoints = _checkpoints;
}

void TubeFactory::createNewOnes()
{
    if (cooldown-- != 0) return;
    
    maxCooldown -= decay;
    cooldown = maxCooldown;

    auto space = 92; // fixed difference
    space += 60; // fixed space to pass through

    auto offset = rand() % 67; // how can slide vertically
    offset *= rand() % 2 == 0 ? 1 : -1; // decides if slide will be up or down

    tubes.push_back(new Tube(false, space/2, offset));
    tubes.push_back(new Tube(true, space/2, offset));
    checkpoints.push_back(new Checkpoint());
}

void TubeFactory::update(float velocity)
{
    for (auto tube : tubes)
        tube->update(velocity);
    
    for (auto checkpoint : checkpoints)
        checkpoint->update(velocity);
    
    destroyInactive();
    createNewOnes();
}

std::vector<Tube*> TubeFactory::getTubes()
{
    return tubes;
}

std::vector<Checkpoint*> TubeFactory::getCheckpoints()
{
    return checkpoints;
}