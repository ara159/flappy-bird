#ifndef GAME_OVER_H
#define GAME_OVER_H 1
#include "MyGameObject.hpp"

class GameOver : public MyGameObject
{
private:
    int cooldownBegin;
    int cooldownEnd;
    bool buttonActive;
    RectangleShape* rect;
    Texture* txGameOverPhrase;
    Sprite* spGameOverPhrase;
    Texture* txOkButton;
    Sprite* spOkButton;
    Texture* txShareButton;
    Sprite* spShareButton;
    Texture* txScore;
    Sprite* spScore;
    Texture* txScoreNumbers[10];
    std::vector<Sprite*> spScoreNumbers;
    bool started;
    int points;
public:
    GameOver();
    ~GameOver();
    void draw(RenderWindow*);
    void start(int points);
    void handleEvent(Event, RenderWindow*);
    void update();
};

#endif