#pragma once

#include <Box2D\Box2D.h>

class Ball
{
public:
	Ball(float dx,float dy,b2World* world);
	~Ball(void);

	void configB2Body(b2World* world);
	void update();

	float x;
    float y;

	float scale;

	//////////// parametros BOX2D //////////////////////
		b2Body* body;

		b2BodyType body_type;
		
	    bool fixedRotation;
		
		float32 density;
		float32 friction;
		float32 restitution;
};

