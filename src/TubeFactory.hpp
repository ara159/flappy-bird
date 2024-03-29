#ifndef TUBE_FACTORY_H
#define TUBE_FACTORY_H 1
#include <SFML/Graphics.hpp>
#include "MyGameObject.hpp"
#include "Tube.hpp"
#include "Checkpoint.hpp"

class TubeFactory : public MyGameObject
{
private:
    int cooldown;
    int maxCooldown;
    int minCooldown;
    int decay;
    std::vector<Tube*> tubes;
    std::vector<Checkpoint*> checkpoints;
    void clear();
    void destroyInactive();
    void createNewOnes();
public:
    void start();
    TubeFactory();
    ~TubeFactory();
    void draw(RenderWindow* window);
    void update();
    std::vector<Tube*> getTubes();
    std::vector<Checkpoint*> getCheckpoints();
};

#endif