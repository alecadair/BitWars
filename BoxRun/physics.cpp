#include "physics.h"

Physics::Physics(){
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
    myBodyDef.position.Set(0, 0); //set the starting position
    myBodyDef.angle = 0; //set the starting angle

    b2Vec2 gravity(0, 9.8);
    myWorld = new b2World(gravity);

    myWorld->SetContactListener(this);

    dynamicBody = myWorld->CreateBody(&myBodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,1);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    dynamicBody->CreateFixture(&boxFixtureDef);

    dynamicBody->SetTransform( b2Vec2( 10, 20 ), 1 );

    dynamicBody->SetLinearVelocity( b2Vec2( -50, 5 ) ); //moving up and left 5 units per second
    dynamicBody->SetAngularVelocity( -3.1415/2 ); //90 degrees per second clockwise


    // Make ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0, -10.0);

    //groundBody = myWorld->CreateBody(&groundBodyDef);

    //b2PolygonShape groundBox;
    //groundBox.setAsBox(50.0, 10.0);
    //groundBody->CreateFixture(&groundBox, 0.0);//0.0 for density since it's a non-moving (static) fixture
    b2MassData bData;
    bData.center = b2Vec2(0, 0);
    bData.I = 1.0;
    bData.mass = 1.0;
    dynamicBody->SetMassData(&bData);


    float32 timeStep = 1.0 / 60.0;
    int32 velocityIterations = 10;//delete all this
    int32 positionIterations = 8;
    myWorld->Step(timeStep, velocityIterations, positionIterations);

    dynamicBody->SetActive(true);
    //dynamicBody->SetAwake(true);

    const b2Vec2 force(40, 40);
    const b2Vec2 point(0, 0);

    //dynamicBody->ApplyForce(force, point, true);

}

double Physics::getX(){
    return dynamicBody->GetPosition().x;
}

double Physics::getY(){
    return dynamicBody->GetPosition().y;
}

void Physics::step(){
    float32 timeStep = 1.0 / 1.0;
    int32 velocityIterations = 10;
    int32 positionIterations = 8;
    myWorld->Step(timeStep, velocityIterations, positionIterations);
}
