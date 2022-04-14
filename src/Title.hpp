#ifndef TITLE_H
#define TITLE_H 1
#include <SFML/Graphics.hpp>
#include "MyGameObject.hpp"

using namespace sf;

class Title : public MyGameObject
{
private:
    Texture* txTitle;
    Sprite* spTitle;
    Texture* txBtnStart;
    Sprite* spBtnStart;
    Texture* txBtnRanking;
    Sprite* spBtnRanking;
    bool started;
public:
    Title();
    ~Title();
    void start();
    void update();
    void draw(RenderWindow*);
    void handleEvent(Event, RenderWindow*);
};

#endif