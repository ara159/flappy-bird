#ifndef PAUSE_BUTTON_H
#define PAUSE_BUTTON 1
#include <SFML/Graphics.hpp>
#include "MyGameObject.hpp"

using namespace sf;

class PauseButton : public MyGameObject
{
private:
    Texture* txPauseButton;
    bool paused = false;
    void init();
public:
    PauseButton();
    ~PauseButton();
    void draw(RenderWindow* window);
};

#endif