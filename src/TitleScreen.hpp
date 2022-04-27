#ifndef TITLE_SCREEN
#define TITLE_SCREEN 1
#include "MyGameObject.hpp"

class TitleScreen : public MyGameObject
{
private:
    Texture* txTitle;
    Texture* txBtnStart;
    Texture* txBtnRank;
    Sprite* spTitle;
    Sprite* spBtnStart;
    Sprite* spBtnRank;
public:
    TitleScreen();
    ~TitleScreen();
    void start();
    void update();
    void draw(RenderWindow*);
    void handleEvent(Event, RenderWindow*);
};

#endif