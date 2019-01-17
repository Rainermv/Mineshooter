#include "Block.h"

Block::Block(float dx,float dy,  Tipo tipo,  int dresistence)
{

x = dx;
y = dy;


scale = 1.0;

tipo_bloco = tipo;


defineIndices(tipo);

max_resistence = resistence;
// configura parametros da box2d
body = NULL;


}

Block::Block(float dx,float dy,  Tipo tipo, b2World* world)
{

x = dx;
y = dy;
scale = 0.49;

tipo_bloco = tipo;

defineIndices(tipo);

max_resistence = resistence;

fixedRotation = true;
		
// configura parametros da box2d
configB2Body(world);


}

void Block::defineIndices(Tipo tipo)
{
	switch (tipo) // tipo do bloco
{
case GRAMA:
	{ 
		ind_x = 150;
		ind_y = 0;
		density = 10.0;
		friction = 1;
		restitution = 0;

		resistence = 1000;

		body_type = b2_dynamicBody;

		break;
	}
case TERRA:
	{
		ind_x = 100;
		ind_y = 0;
		density = 10.0;
		friction = 2 ;
		restitution = 0;

		resistence = 1000;

		body_type = b2_dynamicBody;

		break;
	}	
case PEDRA:
	{
		ind_x = 50;
		ind_y = 0;
		density = 50.0;
		friction = 1;
		restitution = 0;

		resistence = 3000;

		body_type = b2_staticBody;

		break;
	}
case TNT:
	{
		ind_x = 400;
		ind_y = 0;
		density = 30.0;
		friction = 0.6;
		restitution = 0.5;

		resistence = 1000;

		body_type = b2_dynamicBody;

		break;
	}
case TIJOLO:
	{
		ind_x = 350;
		ind_y = 0;
		density = 20.0;
		friction = 1;
		restitution = 0.1;

		resistence = 10000;

		body_type = b2_dynamicBody;

		break;
	}

case JOINT:
	{
		ind_x = 700;
		ind_y = 100;
		density = 50.0;
		friction = 1;
		restitution = 0;

		resistence = 10000;

		body_type = b2_kinematicBody;
		//body_type = b2_dynamicBody;

		break;
	}
case CAKE:
	{
		ind_x = 600;
		ind_y = 400;
		density = 2.0;
		friction = 0.2;
		restitution = 0.8;

		scale = 0.45;

		resistence = 1;

		//body_type = b2_kinematicBody;
		body_type = b2_dynamicBody;

		break;
	}
default:
	{
		ind_x = 550;
		ind_y = 0;
		density = 100.0;
		friction = 1;
		restitution = 1;

		resistence = 1;

		break;
	}
}
}

void Block::configB2Body(b2World* world)
{
	if (world != NULL)
	{
		b2BodyDef bodyDef;
		bodyDef.position.Set(x,y);
		bodyDef.type = body_type;
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

void Block::explode()
{
	body->ApplyForceToCenter(b2Vec2(0,-10000000000));
	
	//body->ApplyForceToCenter(b2Vec2(10000000000,0));
	
	//body->DestroyFixture(body->GetFixtureList());
	
}

void Block::causa_dano(float dano_causado)
{
	resistence -= dano_causado;
}
void Block::update()
{
	x = body->GetPosition().x;
	y = body->GetPosition().y;
}


