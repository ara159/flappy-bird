#include "MyGameObject.hpp"

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
