#ifndef GROUND_H
#define GROUND_H 1
#include <SFML/Graphics.hpp>

using namespace sf;

class Ground
{
private:
    RectangleShape* shapes[2];
    Texture* textures[2];
    float velocity = 1;
public:
    Ground();
    ~Ground();
    void run(RenderWindow * window);
    void draw(RenderWindow * window);
};

#endif