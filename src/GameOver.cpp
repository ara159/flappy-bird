#include "GameOver.hpp"

GameOver::GameOver()
{
    rect = new RectangleShape(Vector2f(screenSize));
    rect->setPosition(0, 0);

    started = false;

    txGameOverPhrase = txFactory.gameOverPhrase();
    txOkButton = txFactory.gameOverOkButton();
    txShareButton = txFactory.gameOverShareButton();
    txScore = txFactory.gameOverScore();

    spGameOverPhrase = new Sprite(*txGameOverPhrase);
    spGameOverPhrase->setOrigin(Vector2f(96/2, 0));
    spGameOverPhrase->setScale(Vector2f(scale, scale));

    spOkButton = new Sprite(*txOkButton);
    spOkButton->setOrigin(Vector2f(40/2, 0));
    spOkButton->setScale(Vector2f(scale, scale));

    spShareButton = new Sprite(*txShareButton);
    spShareButton->setOrigin(Vector2f(40/2, 0));
    spShareButton->setScale(Vector2f(scale, scale));
    
    spScore = new Sprite(*txScore);
    spScore->setOrigin(Vector2f(113/2, 0));
    spScore->setScale(Vector2f(scale, scale));

    for (int i = 0; i < 10; i++)
    {
        txScoreNumbers[i] = txFactory.gameOverScoreNumber(i);
    }

    for (int i = 0; i < 4; i++)
    {
        txMedals[i] = txFactory.gameOverMedal(i);
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
    for (int i = 0; i < 4; i++) free(txMedals[i]);
    free(spMedal);
}

void GameOver::draw(RenderWindow* window)
{
    window->draw(*rect);
    window->draw(*spGameOverPhrase);
    window->draw(*spScore);
    window->draw(*spOkButton);
    window->draw(*spShareButton);
    window->draw(*spMedal);
    for (auto number : spScoreNumbers)
        window->draw(*number);
} 

void GameOver::start(int points)
{
    if (started) return;

    this->points = points;

    status.gameOver = true;
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

    for (auto number : spScoreNumbers)
        free(number);
    
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

    int medalIndex = 0;
    
    if (points > 5)
        medalIndex++;
    if (points > 10)
        medalIndex++;
    if (points > 20)
        medalIndex++;

    spMedal = new Sprite(*txMedals[medalIndex]);
    spMedal->setPosition(scoreBounds.left + 13 * scale, scoreBounds.top + 21 * scale);
    spMedal->setScale(Vector2f(scale, scale));
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
            status.toScreen = GET_READY;
            started = false;
        }
    }
}

void GameOver::update()
{
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

        spMedal->move(0, -1);
    }
    if (i > 0) return;

    spOkButton->setColor(Color{255,255,255,255});
    spShareButton->setColor(Color{255,255,255,255});
    buttonActive = true;
}