#include "TitleScreen.hpp"
#include "TextureFactory.hpp"

TitleScreen::TitleScreen() : MyGameObject()
{
    TextureFactory tx = TextureFactory();
    
    txTitle = tx.titlePhrase();
    txBtnStart = tx.titleStartButton();
    txBtnRank = tx.titleRankButton();

    spTitle = new Sprite(*txTitle);
    spBtnStart = new Sprite(*txBtnStart);
    spBtnRank = new Sprite(*txBtnRank);    
    
    spTitle->setOrigin(txTitle->getSize().x/2, 0);
    spTitle->setPosition(screenSize.x * 0.5, screenSize.y * 0.3);
    spTitle->setScale(Vector2f(scale, scale));

    auto titleBounds = spTitle->getGlobalBounds();

    spBtnStart->setOrigin(txBtnStart->getSize().x/2, 0);
    spBtnStart->setPosition(spTitle->getPosition().x, titleBounds.top + (24 + 10) * scale);
    spBtnStart->setScale(Vector2f(scale, scale));
 
    spBtnRank->setOrigin(txBtnRank->getSize().x/2, 0);
    spBtnRank->setPosition(spTitle->getPosition().x, titleBounds.top + (24 + 10) * scale);
    spBtnRank->setScale(Vector2f(scale, scale));

    spBtnStart->move(28 * -1 * scale, 0);
    spBtnRank->move(28 * scale, 0);
}

TitleScreen::~TitleScreen()
{
    free(txTitle);
    free(txBtnStart);
    free(txBtnRank);
}

void TitleScreen::start()
{
    
}

void TitleScreen::update()
{
    
}

void TitleScreen::draw(RenderWindow* window)
{
    window->draw(*spTitle);
    window->draw(*spBtnStart);
    window->draw(*spBtnRank);
}

void TitleScreen::handleEvent(Event event, RenderWindow* window)
{
    if (event.type == Event::MouseButtonPressed)
    {
        auto clickPosition = Mouse::getPosition(*window);
        auto spBtnStartBounds = spBtnStart->getGlobalBounds();
        auto spBtnRankBounds = spBtnRank->getGlobalBounds();

        if (spBtnStartBounds.intersects(FloatRect(clickPosition.x, clickPosition.y, 1, 1)))
        {
            status.toScreen = GET_READY;
        }

        if (spBtnRankBounds.intersects(FloatRect(clickPosition.x, clickPosition.y, 1, 1)))
        {
            
        }
    }
}