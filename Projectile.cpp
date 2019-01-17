#include "Projectile.h"


 Projectile::Projectile(float dx, float dy, b2World* world, Tipo dtipo)
 {
	timer = 500;

    x = dx;
    y = dy;
	
    tipo = dtipo;

	switch (tipo)
	{
	case (PORCO):
		{
		surface = CSurface::onLoad("./bmp/pig.bmp");
		damage = 1;
		scale = 0.2;
		density = 3;
		friction = 0.5;
		restitution = 0.5;
		break;
		}
	case (VACA):
		{
		surface = CSurface::onLoad("./bmp/vaca.bmp");
		damage = 5;
		scale = 0.4;
		density = 2;
		friction = 1;
		restitution = 0.2;
		break;
		}
	case (OVELHA):
		{
		surface = CSurface::onLoad("./bmp/ovelha.bmp");
		density = 3;
		scale = 0.3;
		friction = 0.5;
		restitution = 0.6;
		damage = 2;
		break;
		}
	case (POVELHA):
		{
		surface = CSurface::onLoad("./bmp/ovelha.bmp");
		damage = 2;
		scale = 0.1;
		density = 1;
		friction = 0.5;
		restitution = 0.6;
		break;
		}
	default:
		surface = CSurface::onLoad("./bmp/bullet.bmp");
		damage = 2;
		scale = 0.2;
		density = 3;
		friction = 0.5;
		restitution = 0.8;
	}

	CSurface::transparent(surface, 255, 0, 255);
	
	configB2Body(world);

 }



void Projectile::configB2Body(b2World* world)
{
	if (world != NULL)
	{
		b2BodyDef bodyDef;
		bodyDef.bullet = true;
		bodyDef.position.Set(x,y);
		bodyDef.type = b2_dynamicBody;
		

		b2CircleShape circle_shape;
		b2PolygonShape poly_shape;
		b2FixtureDef fix;
		if (tipo == VACA)
		{
				poly_shape.SetAsBox(scale,scale);
				fix.shape = &poly_shape;
				bodyDef.fixedRotation = true;
		}
		else 
			
		{
				circle_shape.m_radius = scale;
				fix.shape = &circle_shape;
				bodyDef.fixedRotation = false;
		}

		
		
		fix.density = density;
		fix.friction = friction;
		fix.restitution = restitution;

		body = world->CreateBody(&bodyDef);
		body->CreateFixture(&fix);
	}
		
}

void Projectile::shoot(b2Vec2 vector)
 {

	 body->ApplyForceToCenter(vector);


   
 }

void Projectile::update()
{
	x = body->GetPosition().x;
	y = body->GetPosition().y;

	timer -= 1.0;
}

float Projectile::getLinearVelocity()
{
	b2Vec2 v = body->GetLinearVelocity();
	return sqrt(v.x*v.x+v.y*v.y);
}

