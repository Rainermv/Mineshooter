#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "math.h"
#include "Box2D\Box2D.h"
#include "CSurface.h"
#include <SDL.h>

#include "Suporte.h"



class Projectile {

    public:
        Projectile(float dx, float dy, b2World* world, Tipo dtiro);

		void configB2Body(b2World* world);

        void shoot(b2Vec2 vector);
		void update();
		void setType();
		void ativaEfeito();

		float getLinearVelocity();

        float x;
        float y;

		Tipo tipo;
        
        float damage;

		float timer;
		

		SDL_Surface*	surface;
		

    public:
		float scale;
		//////////// parametros BOX2D //////////////////////
		b2Body* body;
	
	    bool fixedRotation;
		
		float32 density;
		float32 friction;
		float32 restitution;

};

#endif
