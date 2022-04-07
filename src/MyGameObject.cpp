#include "MyGameObject.hpp"

MyGameObject::MyGameObject(float scale)
{
    if (scale > 0) this->scale = scale;
    screenSize.x = 144 * scale;
    screenSize.y = 256 * scale;
}

MyGameObject::MyGameObject()
{
    screenSize.x = 144 * scale;
    screenSize.y = 256 * scale;
}

MyGameObject::~MyGameObject()
{
}