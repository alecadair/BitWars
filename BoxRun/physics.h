#ifndef PHYSICS_H
#define PHYSICS_H

#include "Box2D/Box2D.h"

class Physics : b2ContactListener{
private:
    b2World* myWorld;
    b2Body* dynamicBody;
    b2Body* groundBody;

public:
    Physics();
    double getX();
    double getY();
    void step();
};

#endif // PHYSICS_H
