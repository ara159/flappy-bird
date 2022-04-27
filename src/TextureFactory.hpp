#ifndef TEXTURE_FACTORY
#define TEXTURE_FACTORY 1
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class TextureFactory
{
private:
    Image tileset;
    Texture* loadTexture(IntRect);
public:
    TextureFactory();
    ~TextureFactory();

    Texture* background1();
    Texture* background2();
    Texture* ground();
    Texture* pointNumber(int);
    Texture* gameOverPhrase();
    Texture* gameOverOkButton();
    Texture* gameOverShareButton();
    Texture* gameOverScore();
    Texture* gameOverScoreNumber(int);
    Texture* gameOverMedal(int);
    Texture* getReadyPhrase();
    Texture* getReadyInstructions();
    Texture* pauseButton();
    Texture* player(int);
    Texture* titlePhrase();
    Texture* titleStartButton();
    Texture* titleRankButton();
    Texture* tube(int);
};

#endif