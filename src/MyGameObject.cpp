#include "MyGameObject.hpp"

GameStats MyGameObject::status = GameStats();
GameScreen MyGameObject::scene = GameScreen::Title_S;
float MyGameObject::scale = 3;
Vector2i MyGameObject::screenSize = Vector2i(144 * MyGameObject::scale, 256 * MyGameObject::scale);

MyGameObject::MyGameObject()
{
}

MyGameObject::~MyGameObject()
{
}
