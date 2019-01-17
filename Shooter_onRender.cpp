
#include "Shooter.h"

using std::vector;

void Shooter::onRender()
{
	drawBackground();

	if ((interface_state == GAME) || (interface_state == END))
		drawObjects();

	drawInterface();

    SDL_Flip(surf_display);

}

void Shooter::drawBackground()
{
	// draw background
    CSurface::onDraw(surf_display, surf_background, 0, 0);
}

void Shooter::drawObjects()
{
	

    // map pointer
    Map* ptr_map = &map_vector[imap];

    // draw blocks
    for (unsigned short int i = 0; i < (ptr_map->getBlock_vectorSize()); i++)
    {
        Block* block = ptr_map->getBlock(i);
		if (block->body != NULL)
        CSurface::onDraw(surf_display, surf_tileset, block->x * (float)BLOCK_SIZE -(BLOCK_SIZE * block->scale),  
													 block->y * (float)BLOCK_SIZE -(BLOCK_SIZE *block->scale),
                       block->ind_x, block->ind_y, BLOCK_SIZE,BLOCK_SIZE);

		
		
		
		// DESENHA RANHURAS
		if (block->resistence < block->max_resistence)
			CSurface::onDraw(surf_display, surf_tileset, block->x * (float)BLOCK_SIZE -(BLOCK_SIZE * block->scale),  
													 block->y * (float)BLOCK_SIZE -(BLOCK_SIZE *block->scale),
                       calculaRanhuras(block->resistence, block->max_resistence) * BLOCK_SIZE,
					   750, BLOCK_SIZE,BLOCK_SIZE);


		//drawVerts(block->body);
		

    }

    // draw cannon
	
	
	Cannon* cannon = ptr_map->getCannon();
	
	if (cannon != NULL)
		CSurface::onDraw(surf_display, surf_p1cannon,
                     (cannon->x* (float)BLOCK_SIZE - (BLOCK_SIZE * cannon->scale)),
                     (cannon->y* (float)BLOCK_SIZE - (BLOCK_SIZE * cannon->scale)));
	

	//drawVerts(ptr_map->getCannon()->body);

  

    // draw projectiles

    for (int i = 0; i < ptr_map->getProjectile_vectorSize(); i++){
		Projectile* ptr_projectile = ptr_map->getProjectile(i);

		if (ptr_projectile->body != NULL)
		CSurface::onDraw(surf_display, ptr_projectile->surface,
                         ptr_projectile->x* (float)BLOCK_SIZE-(BLOCK_SIZE * ptr_projectile->scale),
                         ptr_projectile->y* (float)BLOCK_SIZE-(BLOCK_SIZE * ptr_projectile->scale));
		//drawVerts(ptr_projectile->body);
	}

	// draw balls
	for (int i = 0; i < ptr_map->getBall_vectorSize(); i++){
		Ball* ptr_ball = ptr_map->getBall(i);

		if (ptr_ball->body != NULL)

        CSurface::onDraw(surf_display, surf_apointer,
                         ptr_ball->x* (float)BLOCK_SIZE-(BLOCK_SIZE * ptr_ball->scale),
                         ptr_ball->y* (float)BLOCK_SIZE-(BLOCK_SIZE * ptr_ball->scale));


    }
}

void Shooter::drawInterface()
{
	int t = _interface.getObjetosSize();
	
	for (int i = 0; i < _interface.getObjetosSize(); i++)
	{	
		ObjInterface* ptr_objeto = &_interface.objetos[i];
		if (ptr_objeto->visivel) // se o objeto e visivel
			CSurface::onDraw(surf_display, ptr_objeto->surface, 
							 ptr_objeto->posicao.x - ptr_objeto->anchor.x, 
							 ptr_objeto->posicao.y - ptr_objeto->anchor.y);
	}
}

void Shooter::drawVerts(b2Body* body)
{
	b2Fixture* fixture = body->GetFixtureList();
		const b2Transform& xf = fixture->GetBody()->GetTransform();

		b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
		int32 vertexCount = poly->m_vertexCount;
		b2Assert(vertexCount <= b2_maxPolygonVertices);
		b2Vec2 vertices[b2_maxPolygonVertices];
		
		for (int32 i = 0; i < vertexCount; ++i)
		{
			vertices[i] = b2Mul(xf, poly->m_vertices[i]);
			CSurface::onDraw(surf_display, surf_apointer, vertices[i].x * (float)BLOCK_SIZE,
														  vertices[i].y * (float)BLOCK_SIZE);
		}
}

int Shooter::calculaRanhuras(float res, float max_res)
{
	float result = res / max_res;
		if (result <= 0.1)			return 9;
		else if(result <= 0.2)		return 8;
		else if(result <= 0.3)		return 7;
		else if(result <= 0.4)		return 6;
		else if(result <= 0.5)		return 5;
		else if(result <= 0.6)		return 4;
		else if(result <= 0.7)		return 3;
		else if(result <= 0.8)		return 2;
		else if(result <= 0.9)		return 1;
		else						return 0;
		 
}