#ifndef PAUSE_BUTTON_H
#define PAUSE_BUTTON_H 1
#include <SFML/Graphics.hpp>
#include "MyGameObject.hpp"

using namespace sf;

class PauseButton : public MyGameObject
{
private:
    Texture* txPauseButton;
    Sprite* spPauseButton;
    bool paused;
public:
    PauseButton();
    ~PauseButton();
    void draw(RenderWindow* window);
    void handleEvent(Event, RenderWindow*);
};

#endif