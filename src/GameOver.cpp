#include "GameOver.hpp"

GameOver::GameOver()
{
    Image tileset = Image();
    tileset.loadFromFile("flappy-birdy-sprites.png");

    rect = new RectangleShape(Vector2f(screenSize));
    rect->setPosition(0, 0);
    started = false;

    txGameOverPhrase = new Texture();
    txGameOverPhrase->loadFromImage(tileset, IntRect(395, 59, 96, 21));
    spGameOverPhrase = new Sprite(*txGameOverPhrase);
    spGameOverPhrase->setOrigin(Vector2f(96/2, 0));
    spGameOverPhrase->setScale(Vector2f(scale, scale));

    txOkButton = new Texture();
    txOkButton->loadFromImage(tileset, IntRect(462, 42, 40, 14));

    spOkButton = new Sprite(*txOkButton);
    spOkButton->setOrigin(Vector2f(40/2, 0));
    spOkButton->setScale(Vector2f(scale, scale));
    
    txShareButton = new Texture();
    txShareButton->loadFromImage(tileset, IntRect(292, 142, 40, 14));

    spShareButton = new Sprite(*txShareButton);
    spShareButton->setOrigin(Vector2f(40/2, 0));
    spShareButton->setScale(Vector2f(scale, scale));
    
    txScore = new Texture();
    txScore->loadFromImage(tileset, IntRect(3, 259, 113, 57));

    spScore = new Sprite(*txScore);
    spScore->setOrigin(Vector2f(113/2, 0));
    spScore->setScale(Vector2f(scale, scale));
}

GameOver::~GameOver()
{
    free(txGameOverPhrase);
    free(spGameOverPhrase);
    free(txOkButton);
    free(spOkButton);
    free(txScore);
    free(spScore);
    free(txShareButton);
    free(spShareButton);
}

void GameOver::draw(RenderWindow* window)
{
    if (!started) return;
    auto color = rect->getFillColor();
    if (cooldownBegin > 0)
    {
        cooldownBegin -= 1;
        if (color.a >= 4)
            color.a -= 4;
        rect->setFillColor(color);
        window->draw(*rect);
        return;
    }

    spGameOverPhrase->setPosition(screenSize.x/2, 15 * scale);
    color = spGameOverPhrase->getColor();
    if (color.a < 255)
    {
        color.a += 15;
        spGameOverPhrase->setColor(color);
        window->draw(*spGameOverPhrase);
        return;
    }
    window->draw(*spGameOverPhrase);

    auto pos = spScore->getPosition();
    if (pos.y > 51 * scale)
    {
        spScore->move(0, -8 * scale);
        window->draw(*spScore);
        return;
    }
    window->draw(*spScore);
    window->draw(*spOkButton);
    window->draw(*spShareButton);
    buttonActive = true;
}

void GameOver::start()
{
    if (started) return;
    status.gameOver = true;
    started = true;
    cooldownBegin = 64;
    cooldownEnd = 64;
    buttonActive = false;
    rect->setFillColor(Color::White);
    spGameOverPhrase->setColor(Color{255,255,255,0});
    spScore->setPosition(screenSize.x/2, screenSize.y + 57 * scale);
    spOkButton->setPosition(screenSize.x/2, 128 * scale);
    spOkButton->move(-40 * 2/3 * scale, 0);
    spShareButton->setPosition(screenSize.x/2, 128 * scale);
    spShareButton->move(40 * 2/3 * scale, 0);
}

void GameOver::handleEvent(Event event, RenderWindow* window)
{
    if (!buttonActive) return;
    if (event.type == Event::MouseButtonPressed)
    {
        auto clickPosition = Mouse::getPosition(*window);
        auto pauseBtnBounds = spOkButton->getGlobalBounds();

        if (pauseBtnBounds.intersects(FloatRect(clickPosition.x, clickPosition.y, 1, 1)))
        {
            status.gameOver = false;
            started = false;
        }
    }
}
