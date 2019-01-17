#include "Ball.h"


Ball::Ball(float dx,float dy,b2World* world)
{
	x = dx;
	y = dy;


scale = 0.2;

		density = 20;
		friction = 0.2;
		restitution = 0.2;

fixedRotation = false;
		
// configura parametros da box2d
configB2Body(world);
}


Ball::~Ball(void)
{
}

void Ball::configB2Body(b2World* world)
{
	if (world != NULL)
	{
		b2BodyDef bodyDef;
		bodyDef.bullet = true;
		bodyDef.position.Set(x,y);
		bodyDef.type = b2_dynamicBody;
		bodyDef.fixedRotation = false;

		b2CircleShape shape;
		//shape.SetAsBox(scale/2,scale/2);
		shape.m_radius = scale;

		b2FixtureDef fix;
		fix.shape = &shape;
		fix.density = density;
		fix.friction = friction;
		fix.restitution = restitution;

		body = world->CreateBody(&bodyDef);
		body->CreateFixture(&fix);
	}
		
}

void Ball::update()
{
	x = body->GetPosition().x;
	y = body->GetPosition().y;
}