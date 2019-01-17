#include "Map.h"

using std::vector;

Map::Map(int dsize_x, int dsize_y)
{

    size_x = dsize_x;
    size_y = dsize_y;
	
	world = NULL;
	nwalls = 3;
	for (int i = 0; i < nwalls; i++ )
		walls[i] = NULL;

}

Map::Map(int dsize_x, int dsize_y, b2Vec2 gravity, bool doSleep)
{
	size_x = dsize_x;
    size_y = dsize_y; 

	float x = (float)size_x;
	float y = (float)size_y;
	
	configB2World(gravity, doSleep);

	
	configB2Body(walls[0],b2Vec2(0,0), b2Vec2(0,y)); // esquerda
	configB2Body(walls[0],b2Vec2(x,0), b2Vec2(x,y)); // direita
	configB2Body(walls[0],b2Vec2(0,y+0.5), b2Vec2(x,y+0.5)); //fundo

}

void Map::addCannon(float dx, float dy, int res){

   cannon = new Cannon(dx,dy,res, world);

}

Projectile* Map::addProjectile(float dx, float dy, b2Vec2 vector, Tipo tipo){
    Projectile* ptr_projectile = new Projectile(dx, dy, world, tipo);

    projectile_vector.push_back(*ptr_projectile);

	ptr_projectile->shoot(vector);
	
    return ptr_projectile;
}

Projectile* Map::getProjectile(int ind){

    return &projectile_vector[ind];
}


int Map::getProjectile_vectorSize(){

    return projectile_vector.size();

}

void Map::addBlock(float x, float y, Tipo tipo, int res){

    Block* ptr_block = new Block (x,y, tipo, world); // cria bloco com fisica
    
    block_vector.push_back(*ptr_block);
    delete ptr_block;

}

void Map::addBall(float x, float y){

    Ball* ptr_ball = new Ball (x,y, world); // cria ball com fisica
    
    ball_vector.push_back(*ptr_ball);
    delete ptr_ball;

}

Block* Map::getBlock(int ind){

    return &block_vector[ind];
}

Ball* Map::getBall(int ind){

    return &ball_vector[ind];
}

int Map::getBlock_vectorSize(){
    return block_vector.size();
}

int Map::getBall_vectorSize(){
    return ball_vector.size();
}

Cannon* Map::getCannon()
{
	return cannon;
}


int Map::getSize_x(){
    return size_x;
}
int Map::getSize_y(){
    return size_y;
}

void Map::updateObjects()
{
	for (int i = 0; i < block_vector.size(); i++)
		{		block_vector[i].update();   	}
	for (int i = 0; i < projectile_vector.size(); i++)
		{		projectile_vector[i].update();   	}
	for (int i = 0; i < ball_vector.size(); i++)
		{		ball_vector[i].update();   	}
	cannon->update();


}

//////////////////////////////////////// metodos box2D //////////////////////////////////

void Map::configB2World(b2Vec2 gravity, bool doSleep)
{
	
	// Inicializa o mundo
	world = new b2World(gravity, doSleep);
}

void Map::configB2Body(b2Body* body, b2Vec2 begin, b2Vec2 end)
{
	if (world != NULL)
	{
		b2BodyDef bodyDef;
		body = world->CreateBody(&bodyDef);

		b2EdgeShape shape;
		shape.Set(b2Vec2(begin),b2Vec2(end));
		body->CreateFixture(&shape,0.0);
	}

}

void Map::createDistJoint(b2Body* body1, b2Body* body2, b2DistanceJoint* dJoint)
{
	b2Vec2 worldAnchorOnBody1 = body1->GetWorldCenter(); 
	b2Vec2 worldAnchorOnBody2 = body2->GetWorldCenter(); 

	b2DistanceJointDef dJointDef;
	dJointDef.Initialize(body1, body2,worldAnchorOnBody1,worldAnchorOnBody2);
	dJointDef.collideConnected = true;
	dJointDef.length = 1.0;

	dJoint = (b2DistanceJoint*)world->CreateJoint(&dJointDef);

}

void Map::createRevJoint(b2Body* body1, b2Body* body2, b2RevoluteJoint* rJoint)
{
			b2Vec2 worldAnchorOnBody1 = body1->GetWorldPoint(b2Vec2(0,0)); 
			//b2Vec2 worldAnchorOnBody1 = body1->GetWorldCenter(); 

			b2RevoluteJointDef rJointDef;
			rJointDef.Initialize(body1, body2,worldAnchorOnBody1);
			rJointDef.collideConnected = false;

			//Para criar um motor
			rJointDef.maxMotorTorque = 100.0f; //N-m
			rJointDef.motorSpeed = 2.0f; //radianos por segundo 
			rJointDef.enableMotor = true;

			rJoint = (b2RevoluteJoint*)world->CreateJoint(&rJointDef);

}

void Map::addBlockdJoint(float x, float y)
{
	
	Block* ptr_block = new Block (x,y, JOINT, world); // cria bloco com fisica
	Ball* ptr_ball = new Ball (x,y+1, world); // cria ball com fisica
    
	createDistJoint(ptr_block->body, ptr_ball->body, ptr_block->dJoint);

	block_vector.push_back(*ptr_block);
	ball_vector.push_back(*ptr_ball);
}

void Map::addBlockrJoint(float x, float y)
{
	
	Block* ptr_block = new Block (x,y, JOINT, world); // cria bloco com fisica
	Ball* ptr_ball = new Ball (x,y+1, world); // cria ball com fisica
    
	createRevJoint(ptr_block->body, ptr_ball->body, ptr_block->rJoint);

	block_vector.push_back(*ptr_block);
	ball_vector.push_back(*ptr_ball);
}

b2Contact* Map::getListaContatos()
{
	b2Contact* contact = world->GetContactList();
	return contact;
}

void Map::ativaEfeito(Projectile* ptr_proj)
{
	if (ptr_proj != NULL)
	switch (ptr_proj->tipo)
	{
	case (PORCO):
		{
			
		return;
		}
	case (VACA):
		{
			b2Vec2 vec = ptr_proj->body->GetLinearVelocity();
			addProjectile(ptr_proj->x+0.5, ptr_proj->y, vec, PORCO);
			addProjectile(ptr_proj->x-0.5, ptr_proj->y, vec, PORCO);
			addProjectile(ptr_proj->x, ptr_proj->y-0.5, vec, PORCO);
			return;
		}
	case (OVELHA):
		{
			ptr_proj->body->ApplyLinearImpulse(b2Vec2(0,300),b2Vec2(0.5,0.5));
			
			return;
		}

	default:
		{
		return;
		}
	}
}

void Map::destroyBlock(int ind)
{
	world->DestroyBody(block_vector[ind].body);
	block_vector.erase(block_vector.begin()+ind);
		
}

void Map::destroyProjectile(int ind)
{
	world->DestroyBody(projectile_vector[ind].body);
	projectile_vector.erase(projectile_vector.begin()+ind);
	
}
