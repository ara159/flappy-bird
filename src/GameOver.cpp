#include "GameOver.hpp"

GameOver::GameOver()
{
    this->points = points;
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

    IntRect numbersRects[10] = {
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

    for (int i = 0; i < 10; i++)
    {
        txScoreNumbers[i] = new Texture();
        txScoreNumbers[i]->loadFromImage(tileset, numbersRects[i]);
    }
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
    for (auto number : spScoreNumbers) free(number);
    for (int i = 0; i < 10; i++) free(txScoreNumbers[i]);
}

void GameOver::draw(RenderWindow* window)
{
    if (!started) return;
    window->draw(*rect);
    window->draw(*spGameOverPhrase);
    window->draw(*spScore);
    window->draw(*spOkButton);
    window->draw(*spShareButton);
    for (auto number : spScoreNumbers)
        window->draw(*number);
} 

void GameOver::start(int points)
{
    if (started) return;
    this->points = points;
    started = true;
    cooldownBegin = 64;
    cooldownEnd = 64;
    buttonActive = false;
    
    rect->setFillColor(Color::White);
    
    spGameOverPhrase->setColor(Color{255,255,255,0});
    spGameOverPhrase->setPosition(screenSize.x/2, 15 * scale);
    
    spScore->setPosition(screenSize.x/2, screenSize.y + 57 * scale);
    
    spOkButton->setPosition(screenSize.x/2, 128 * scale);
    spOkButton->move(-40 * 2/3 * scale, 0);
    spOkButton->setColor(Color::Transparent);
    
    spShareButton->setPosition(screenSize.x/2, 128 * scale);
    spShareButton->move(40 * 2/3 * scale, 0);
    spShareButton->setColor(Color::Transparent);

    for (auto number : spScoreNumbers) free(number);
    spScoreNumbers.clear();
    
    std::string strPoints = std::to_string(points);
    auto scoreBounds = spScore->getGlobalBounds();

    for (int i = 0; i < strPoints.length(); i++)
    {
        auto number = strPoints.substr(strPoints.length() - 1 - i, 1);
        auto txNumber = txScoreNumbers[std::stoi(number)];
        auto spNumber = new Sprite(*txNumber);
        
        spNumber->setOrigin(txNumber->getSize().x, 0);
        spNumber->setScale(Vector2f(scale, scale));
        spNumber->setPosition(scoreBounds.left + scoreBounds.width - 11 * scale, scoreBounds.top + 17 * scale);

        for (int j = 0; j < i; j++)
        {
            spNumber->move(-spScoreNumbers[i -1]->getGlobalBounds().width - 1 * scale, 0);
        }

        spScoreNumbers.push_back(spNumber);
    }
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
        }
    }
}

void GameOver::update()
{
    if (!started) return;
    Color color;
    Vector2f pos;

    color = rect->getFillColor();
    if (color.a > 0)
    {
        color.a -= 15;
        rect->setFillColor(color);
        return;
    }

    color = spGameOverPhrase->getColor();
    if (color.a < 255)
    {
        color.a += 15;
        spGameOverPhrase->setColor(color);
        return;
    }

    int i = 0;
    for (i = 0; i < 8; i++)
    {
        if (spScore->getPosition().y < 50 * scale)
            break;
        
        spScore->move(0, -1);

        for (auto number : spScoreNumbers)
            number->move(0, -1);
    }
    if (i > 0) return;

    spOkButton->setColor(Color{255,255,255,255});
    spShareButton->setColor(Color{255,255,255,255});
    buttonActive = true;
}