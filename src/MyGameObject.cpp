#include "MyGameObject.hpp"

MyGameObject::MyGameObject(float scale)
{
    if (scale > 0) this->scale = scale;
    screenSize.x = 256 * scale;
    screenSize.y = 224 * scale;
}

MyGameObject::MyGameObject()
{
    screenSize.x = 256 * scale;
    screenSize.y = 224 * scale;
}

MyGameObject::~MyGameObject()
{
}