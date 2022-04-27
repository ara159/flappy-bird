#ifndef GET_READY_SCREEN
#define GET_READY_SCREEN 1
#include "MyGameObject.hpp"

class GetReadyScreen : public MyGameObject
{
private:
    Texture* txGetReady;
    Texture* txInstructions;
public:
    GetReadyScreen();
    ~GetReadyScreen();
    void start();
    void update();
    void draw(RenderWindow*);
    void handleEvent(Event, RenderWindow*);
};

#endif