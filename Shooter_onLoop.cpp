
#include "Shooter.h"


void Shooter::onLoop() {

	checkInterface();

	if ((interface_state == GAME) || (interface_state == END))
	{
		box2dLoop();
		update();
		checkColision();
		checkDestroyed();
	}
    
}

void Shooter::checkInterface()
{
	switch (interface_state)
	{
	case (START):
		{
			break;
		}
	case (GAME):
		{
			if (cakes_left <= 0)
				interface_state = END;
			break;
		}
	case (END):
		{
			_interface.setVisivel("end",true);
			break;
		}
	}
}

void Shooter::box2dLoop()
{
	map_vector[imap].world->Step(timeStep, velocityIterations, positionIterations);
	map_vector[imap].world->ClearForces();
}

void Shooter::update()
{
	map_vector[imap].updateObjects();
}



void Shooter::checkColision(){
   
	Map* ptr_map = &map_vector[imap];
	b2Contact* contact = ptr_map->getListaContatos();

	for (int i=0; i < ptr_map->world->GetContactCount(); i++)
	{
		b2WorldManifold worldManifold;
		contact->GetWorldManifold(&worldManifold);
		b2Vec2 pontos = worldManifold.points[0];

		b2Body *bodyA, *bodyB;
		bodyA = contact->GetFixtureA()->GetBody();
		bodyB = contact->GetFixtureB()->GetBody();

		//Tipo tipoA, tipoB;

		bool foundA = false;
		bool foundB = false;

		Block* block_contacted = NULL;
		Projectile* projectile_contacted = NULL;

		////////////// detecta os tipos dos objetos que colidiram ////////////
		
		// somente colisoes projetil > bloco sao consideradas

		for (int i = 0; i < (ptr_map->getBlock_vectorSize()); i++)
		{	
			Block* ptr_block = ptr_map->getBlock(i);
			  if (!foundA)
				if ((ptr_block->body) == bodyA)
					{
					block_contacted = ptr_block;
					foundA = true;
					//break;
					}
			  if (!foundB)	
				if ((ptr_block->body) == bodyB)
					{
					block_contacted = ptr_block;
					foundB = true;
					//break;
					}
			
		}

		for (int i = 0; i < ptr_map->getProjectile_vectorSize(); i++){
		{
			Projectile* ptr_projectile = ptr_map->getProjectile(i);
			if (!foundA)
				if ((ptr_projectile->body) == bodyA)
					{
					projectile_contacted = ptr_projectile;
					foundA = true;
					//continue;
					}
			if (!foundB)	
				if ((ptr_projectile->body) == bodyB)
					{
					projectile_contacted = ptr_projectile;
					foundB = true;
					//continue;
					}
			
		}


		///////////////// trata os objetos que colidiram///////////////////

		// trata projeteis
		float dano_causado = 0; // dano causado

		if (projectile_contacted != NULL)
			switch (projectile_contacted->tipo){
				default:
					{
						float speed = projectile_contacted->getLinearVelocity();
						if (speed >= 5)
						{
							dano_causado = ( speed*projectile_contacted->damage
											 *projectile_contacted->body->GetMass()/100);

						}
						break;
					}

			}

		// trata blocos
		if (block_contacted != NULL)
			switch (block_contacted->tipo_bloco){
				case (TNT):
					{
						block_contacted->explode();
						block_contacted->causa_dano(dano_causado);
						
						break;
					}
				case (CAKE):
					{
						block_contacted->causa_dano(1);
						
					}
				default:
					{
						block_contacted->causa_dano(dano_causado);
						break;
					}
					

			}
		
		}

	}

}

void Shooter::checkDestroyed()
{
	
	/// destroi blocos se a vida for menor que 0 ou "cairem" do mundo
	for (int i = 0; i < map_vector[imap].block_vector.size(); i++ )
	{
		Block* bloco = &map_vector[imap].block_vector[i];
		if ((bloco->resistence <= 0) || (bloco->y >= world_height+5) || (bloco->y <= -world_height))
		{
			switch (bloco->tipo_bloco)
			{
			case (CAKE):
				pegaCake(5);
			}

			map_vector[imap].destroyBlock(i);
			
		}
	}

	// destroi projeteis se o timer for menor que 0 ou "cairem" do mundo
	for (int i = 0; i < map_vector[imap].projectile_vector.size(); i++ )
	{
		Projectile* proj = &map_vector[imap].projectile_vector[i];
		if ((proj->timer <= 0)|| (proj->y >= world_height+5) || (proj->y <= -world_height))
		{
			switch (proj->tipo)
			{
			case (PORCO):
				{
				}
				//pegaCake(5);
			}
			map_vector[imap].destroyProjectile(i);
		}
		
			
	}

	
	
	
}

void Shooter::pegaCake(int points)
{
	pontos += points;
	cakes_left--;
	_interface.subtractCake();
}




