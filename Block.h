#ifndef Block_H
#define Block_H

#include <SDL.H>
#include <Box2D\Box2D.h>

#include "Suporte.h"


class Block
{
private:

	void defineIndices(Tipo tipo);
	void configB2Body(b2World* world);

public:
	void update();
	void explode();
	void causa_dano(float dano_causado);
	

    public:
		Block();
        Block(float dx,float dy, Tipo tipo, int res);
		Block(float dx,float dy, Tipo tipo, b2World* world);
		//Block::~Block(void);

		

        //b2Vec2 position;
		float x;
        float y;

		float scale;
        //unsigned short int size;

		float resistence;
		float max_resistence;

		// indice para o tilemap
        unsigned short int ind_x;
        unsigned short int ind_y;

		Tipo tipo_bloco;

		

		//////////// parametros BOX2D //////////////////////
		b2Body* body;

		b2BodyType body_type;
		
	    bool fixedRotation;
		
		float32 density;
		float32 friction;
		float32 restitution;

		// joints, caso precisem ser usadas

		b2DistanceJoint* dJoint;
		b2RevoluteJoint* rJoint;
		b2PrismaticJoint *pJoint;
		b2GearJoint *gJoint;
		b2PulleyJoint *puJoint;
		b2WheelJoint *wheelJoint1, *wheelJoint2;
        
	 
    //private:


};

#endif
