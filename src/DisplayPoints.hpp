#ifndef DISPLAY_POINTS_H
#define DISPLAY_POINTS_H 1
#include "MyGameObject.hpp"

class DisplayPoints : public MyGameObject
{
private:
    void init();
    int points;
    Texture* txNumbers[10];
public:
    DisplayPoints();
    DisplayPoints(float scale);
    ~DisplayPoints();
    void draw(RenderWindow*  window);
    void update();
    void start();
};

#endif