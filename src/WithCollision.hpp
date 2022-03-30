#ifndef W_COLLISION_H
#define W_COLLISION_H 1
#include <string>

class WithCollision
{
public:
    virtual void onCollision() {};
    std::string getName() { return std::string(); };
};

#endif