#ifndef GAME_OVER_H
#define GAME_OVER_H 1
#include "MyGameObject.hpp"

class GameOver : public MyGameObject
{
private:
    int cooldownBegin;
    int cooldownEnd;
    RectangleShape* rect;
    Texture* txGameOverPhrase;
    Sprite* spGameOverPhrase;
    Texture* txOkButton;
    Sprite* spOkButton;
    Texture* txShareButton;
    Sprite* spShareButton;
    Texture* txScore;
    Sprite* spScore;
    bool started;
public:
    GameOver();
    ~GameOver();
    void draw(RenderWindow*);
    void start();
    void handleEvent(Event, RenderWindow*);
};

#endif