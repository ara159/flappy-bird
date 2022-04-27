#include "TextureFactory.hpp"
#include <iostream>

TextureFactory::TextureFactory()
{
    tileset.loadFromFile("flappy-birdy-sprites.png");
}

TextureFactory::~TextureFactory()
{
}

Texture* TextureFactory::loadTexture(IntRect position)
{
    auto texture = new Texture();
    texture->loadFromImage(tileset, position);
    return texture;
}

Texture* TextureFactory::background1()
{
    auto texture = loadTexture(IntRect(0, 0, 144, 256));
    texture->setRepeated(true);
    return texture;
}

Texture* TextureFactory::background2()
{
    auto texture = loadTexture(IntRect(146, 0, 144, 256));
    texture->setRepeated(true);
    return texture;
}

Texture* TextureFactory::ground()
{
    auto texture = loadTexture(IntRect(292, 0, 168, 56));
    texture->setRepeated(true);
    return texture;
}

Texture* TextureFactory::pointNumber(int n)
{
    IntRect positions[10] = {
        IntRect(496, 60, 12, 18),
        IntRect(136, 455, 8, 18),
        IntRect(292, 160, 12, 18),
        IntRect(306, 160, 12, 18),
        IntRect(320, 160, 12, 18),
        IntRect(334, 160, 12, 18),
        IntRect(292, 184, 12, 18),
        IntRect(306, 184, 12, 18),
        IntRect(320, 184, 12, 18),
        IntRect(334, 184, 12, 18),
    };
    return loadTexture(positions[n]);
}

Texture* TextureFactory::gameOverPhrase()
{
    return loadTexture(IntRect(395, 59, 96, 21));
}

Texture* TextureFactory::gameOverOkButton()
{
    return loadTexture(IntRect(462, 42, 40, 14));
}

Texture* TextureFactory::gameOverShareButton()
{
    return loadTexture(IntRect(292, 142, 40, 14));
}

Texture* TextureFactory::gameOverScore()
{
    return loadTexture(IntRect(3, 259, 113, 57));
}

Texture* TextureFactory::gameOverScoreNumber(int n)
{
    IntRect positions[10] = {
        IntRect(137, 306, 7, 10),
        IntRect(139, 477, 5, 10),
        IntRect(137, 489, 7, 10),
        IntRect(131, 501, 7, 10),
        IntRect(502, 0, 7, 10),
        IntRect(502, 12, 7, 10),
        IntRect(505, 26, 7, 10),
        IntRect(505, 42, 7, 10),
        IntRect(293, 242, 7, 10),
        IntRect(331, 206, 7, 10),
    };
    return loadTexture(positions[n]);
}

Texture* TextureFactory::gameOverMedal(int n)
{
    IntRect positions[4] = {
        IntRect(112, 477, 22, 22),
        IntRect(112, 453, 22, 22),
        IntRect(121, 258, 22, 22),
        IntRect(121, 282, 22, 22),
    };
    return loadTexture(positions[n]);
}

Texture* TextureFactory::getReadyPhrase()
{
    return loadTexture(IntRect(295, 59, 92, 25));
}

Texture* TextureFactory::getReadyInstructions()
{
    return loadTexture(IntRect(292, 91, 57, 49));
}

Texture* TextureFactory::pauseButton()
{
    return loadTexture(IntRect(121, 306, 13, 14));
}

Texture* TextureFactory::player(int n)
{
    IntRect positions[9] = {
        // skin 1
        IntRect(3, 491, 17, 12),
        IntRect(31, 491, 17, 12),
        IntRect(59, 491, 17, 12),
        // skin 2
        IntRect(87, 491, 17, 12),
        IntRect(115, 329, 17, 12),
        IntRect(115, 355, 17, 12),
        // skin 3
        IntRect(115, 381, 17, 12),
        IntRect(115, 407, 17, 12),
        IntRect(115, 433, 17, 12),
    };
    return loadTexture(positions[n]);
}

Texture* TextureFactory::titlePhrase()
{
    return loadTexture(IntRect(351, 91, 89, 24));
}

Texture* TextureFactory::titleStartButton()
{
    return loadTexture(IntRect(354, 118, 52, 29));
}

Texture* TextureFactory::titleRankButton()
{
    return loadTexture(IntRect(414, 118, 52, 29));
}

Texture* TextureFactory::tube(int n)
{
    IntRect positions[2] = {
        IntRect(84, 323, 26, 160),
        IntRect(56, 323, 26, 160),
    };
    return loadTexture(positions[n]);
}
