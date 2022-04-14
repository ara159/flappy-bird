#ifndef GET_READY_H
#define GET_READY_H 1
#include <SFML/Graphics.hpp>
#include "MyGameObject.hpp"

using namespace sf;

class GetReady : public MyGameObject
{
private:
    Texture* txGetReady;
    Sprite* spGetReady;
    Texture* txInstructions;
    Sprite* spInstructions;
    bool canClose;
    int cooldown;
public:
    GetReady();
    ~GetReady();
    void start();
    void update();
    void draw(RenderWindow*);
    void handleEvent(Event, RenderWindow*);
};

#endif