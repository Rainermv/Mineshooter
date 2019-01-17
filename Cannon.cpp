#include "Cannon.h"

Cannon::Cannon(){

}

Cannon::Cannon(float dx,float dy,  int dresistence, b2World* world)
{

x = dx;
y = dy;

resistence = dresistence;

scale = 0.45;

can_shoot = true;



	    fixedRotation = true;
		density = 10.0;
		friction = 1;
		restitution = 0.5;
// configura parametros da box2d
configB2Body(world);

vetor_tiro = b2Vec2(500,-500);

}

void Cannon::configB2Body(b2World* world)
{
	if (world != NULL)
	{
		b2BodyDef bodyDef;
		bodyDef.position.Set(x,y);
		bodyDef.type = b2_dynamicBody;
		bodyDef.fixedRotation = fixedRotation;

		b2PolygonShape shape;
		shape.SetAsBox(scale,scale);

		b2FixtureDef fix;
		fix.shape = &shape;
		fix.density = density;
		fix.friction = friction;
		fix.restitution = restitution;

		body = world->CreateBody(&bodyDef);
		body->CreateFixture(&fix);

		
	}
		
}

void Cannon::update()
{
	x = body->GetPosition().x;
	y = body->GetPosition().y;
}

