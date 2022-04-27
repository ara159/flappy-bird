#include "MyGameObject.hpp"

GameStats MyGameObject::status = GameStats();
TextureFactory MyGameObject::txFactory = TextureFactory();

MyGameObject::MyGameObject()
{
    screenSize.x = 144 * scale;
    screenSize.y = 256 * scale;
}

MyGameObject::~MyGameObject()
{
}

void MyGameObject::setScale(float scale)
{
    this->scale = scale;
}
