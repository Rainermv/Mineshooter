#ifndef MAP_H
#define MAP_H

#include <Box2D\Box2D.h>

#include <vector>
using std::vector;

#include "Block.h"
#include "Cannon.h"
#include "Projectile.h"
#include "Ball.h"


class Map {

    public:
        Map(int dsize_x, int dsize_y);
		Map(int dsize_x, int dsize_y, b2Vec2 gravity, bool doSleep); // inicia com fisica
		//Map::~Map(void);
		
		//// Cannon ////
        void addCannon(float dx, float dy, int res); 
		Cannon* getCannon();

		//// Projectile ////
        Projectile* addProjectile(float dx, float dy, b2Vec2 vector, Tipo tipo);
		Projectile* getProjectile(int);
        int getProjectile_vectorSize();
		void destroyProjectile(int ind);

		//// Block ////
        void addBlock(float x, float y, Tipo tipo, int res);
        Block* getBlock(int);
        int getBlock_vectorSize();
		void destroyBlock(int ind);

		//// Ball ////
		void addBall(float x, float y);
		Ball* getBall(int);
        int getBall_vectorSize();

        int getSize_x();
        int getSize_y();

		void configB2World(b2Vec2 gravity, bool doSleep);
		void configB2Body(b2Body* body, b2Vec2 begin, b2Vec2 end);

		// cria joints
		void createDistJoint(b2Body* body1, b2Body* body2, b2DistanceJoint* dJoint);
		void createRevJoint(b2Body* body1, b2Body* body2, b2RevoluteJoint* rJoint);

		void addBlockdJoint(float x, float y);
		void addBlockrJoint(float x, float y);

		void ativaEfeito(Projectile* ptr_proj);

		b2Contact* getListaContatos();

		void updateObjects();

		



    public:

        vector<Block> block_vector; // blocks
        vector<Projectile> projectile_vector; // projectiles
		vector<Ball> ball_vector;
        Cannon* cannon; // cannon

        int size_x; 
        int size_y;

		// parametros box2d

		b2World* world; // mundo de simulacao
		b2Body* walls[3]; // limites
		int nwalls;


};

#endif
