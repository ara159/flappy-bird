#ifndef GROUND_H
#define GROUND_H 1
#include <SFML/Graphics.hpp>

using namespace sf;

class Ground
{
private:
    RectangleShape* shapes[2];
    Texture* textures[2];
public:
    Ground();
    ~Ground();
    void run(int velocity);
    void draw(RenderWindow * window);
    FloatRect getGlobalBounds();
};

#endif