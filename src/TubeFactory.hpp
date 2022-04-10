#ifndef PAUSE_BUTTON_H
#define PAUSE_BUTTON 1
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
    void init();
    void start();
    TubeFactory();
    ~TubeFactory();
    void draw(RenderWindow* window);
    void update(float velocity);
    std::vector<Tube*> getTubes();
    std::vector<Checkpoint*> getCheckpoints();
};

#endif