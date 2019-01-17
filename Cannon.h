
#ifndef CANNON_H
#define CANNON_H

#include "Block.h"

class Cannon{

    public:
		
       
		Cannon();
		Cannon(float dx,float dy,  int dresistence, b2World* world);

		bool can_shoot;

		void update();

		float x;
		float y;

        int resistence;

		float scale;

		//////////// parametros BOX2D //////////////////////
		b2Body* body;
		
	    bool fixedRotation;
		
		float32 density;
		float32 friction;
		float32 restitution;

		b2Vec2 vetor_tiro;

private:
	void configB2Body(b2World* world);
	

};

#endif
