/*
* Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
*  Projeto inicial com a Box 2D -- Física para Jogos 2011-2
*  Iniciado por Rossana B. Queiroz (baseado nos projetos de exemplo da biblioteca)
*/

//#include "Render.h"
//#include <GL/glut.h>

#include <Box2D/Box2D.h>

#include "SDL.h" 

#include <cstdio>
#include <iostream>


int32 framePeriod = 16; //milliseconds
int32 mainWindow;


int height=450, width=450;
float32 timeStep;
int32 velocityIterations ;
int32 positionIterations ;

int tx, ty, tw, th;
b2Vec2 viewCenter(0.0f, 0.0f);

// O objeto World serve para armazenar os dados da simulação
b2World *world;

//Um corpo rígido
b2Body *object;

//outro corpo rígido
b2Body *object2;

//Objeto "chão"
b2Body* ground;



//Função de inicialização da Box2D
void InitBox2D()
{
	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -9.8f);

	// Permite que os objetos 'durmam'. Melhora o desempenho
	bool doSleep = true;

	// Inicializa a biblioteca Box2D
	world = new b2World(gravity, doSleep);

	// Define os parâmetro para a simulação
	// Quanto maior, mais preciso, porém, mais lento
    velocityIterations = 8;
    positionIterations = 3;
	timeStep = 1.0f / 60.0f;
		
}

// ===========================================
// Função de Execução da Simulação
// ===========================================
void RunBox2D()
{
	world->Step(timeStep, velocityIterations, positionIterations);
	world->ClearForces();
}


// ===========================================
// Função que imprime todos os objetos  
// armazenados na Box2D
// ===========================================
void PrintBodies()
{
	b2Body *b;
	float ang;
	b2Vec2 pos;
	for(b = world->GetBodyList(); b; b=b->GetNext())
	{
		pos = b->GetPosition();
		ang = b->GetAngle();
		printf("%4.2f %4.2f %4.2f\n", pos.x, pos.y, ang);	
	}
}


void DrawShape(b2Fixture* fixture, b2Color color)
	{
		
		const b2Transform& xf = fixture->GetBody()->GetTransform();

		switch (fixture->GetType())
		{
		case b2Shape::e_circle:
			{
				b2CircleShape* circle = (b2CircleShape*)fixture->GetShape();

				b2Vec2 center = b2Mul(xf, circle->m_p);
				float32 radius = circle->m_radius;

				//renderer.DrawCircle(center, radius, color);
			}
			break;

		case b2Shape::e_polygon:
			{
				b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
				int32 vertexCount = poly->m_vertexCount;
				b2Assert(vertexCount <= b2_maxPolygonVertices);
				b2Vec2 vertices[b2_maxPolygonVertices];

				for (int32 i = 0; i < vertexCount; ++i)
				{
					vertices[i] = b2Mul(xf, poly->m_vertices[i]);
				}

				//renderer.DrawPolygon(vertices, vertexCount, color);
			}
			break;
		case b2Shape::e_edge:
			{
				b2EdgeShape* edge = (b2EdgeShape*)fixture->GetShape();
				int32 vertexCount;
				
				b2Vec2 vertices[b2_maxPolygonVertices];
				int i=0;

				if (edge->m_hasVertex0) 
				{
						vertices[i] = b2Mul(xf, edge->m_vertex0);
						i++;
				}
				vertices[i] = b2Mul(xf, edge->m_vertex1); i++;
				vertices[i] = b2Mul(xf, edge->m_vertex2); i++;
				if (edge->m_hasVertex3) 
				{
						vertices[i] = b2Mul(xf, edge->m_vertex3);
						i++;
				}
				
				vertexCount = i;
				//renderer.DrawPolygon(vertices, vertexCount, color);
			}
		
			break;
			case b2Shape::e_chain:
		{
			b2ChainShape* chain = (b2ChainShape*)fixture->GetShape();
			int32 count = chain->GetVertexCount();
			const b2Vec2* vertices = chain->GetVertices();

			b2Vec2 v1 = b2Mul(xf, vertices[0]);
			for (int32 i = 1; i < count; ++i)
			{
				b2Vec2 v2 = b2Mul(xf, vertices[i]);
				//renderer.DrawSegment(v1, v2, color);
				//renderer.DrawCircle(v1, 0.05f, color);
				v1 = v2;
			}
		}
		break;
			
		}
	
	}



void SimulationLoop()
{

	//Chama a rotina que chama o passo da simulação
	RunBox2D();

	//Uma rotina que imprime
	//PrintBodies();

	b2Color color; color.r = 1.0; color.g = 0.0; color.b = 0.0;
	
	DrawShape(object->GetFixtureList(),color);

	DrawShape(ground->GetFixtureList(),color);

	if (object2)
		DrawShape(object2->GetFixtureList(),color);


}

void Keyboard(unsigned char key, int x, int y)
{

	B2_NOT_USED(x);
	B2_NOT_USED(y);

	switch (key)
	{
	case 27:
		exit(0);
		break;

	}
}

/*
int main(int argc, char** argv)
{
	
	char title[32];
	sprintf(title, "Box2D Version %d.%d.%d", b2_version.major, b2_version.minor, b2_version.revision);
	

	//Rotina com a inicialização do mundo
	InitBox2D();

	//Cria uma cena muito simples com uma caixa e uma linha (chão)

	// Cria as definicoes do CORPO rígido.
	b2BodyDef bodyDef;
	bodyDef.position.Set(0,10);
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = false;

	// Cria um novo corpo a partir das informações da bodyDef
	// Nunca use NEW ou MALLOC para criar um corpo
	//No caso aqui, estamos usando uma forma de poligono, que pode ter até 8 vértices
	b2PolygonShape forma;
	b2FixtureDef fix;

	forma.SetAsBox(5,5);

	fix.shape = &forma;
	fix.density = 10.0;
	//fix.friction = 0.5;
	//fix.restitution = 0.5;

	object =  world->CreateBody(&bodyDef);	
	object->CreateFixture(&fix);

	//Cria o chão
	b2BodyDef bd;
	ground = world->CreateBody(&bd);
	
	//Forma do chão: edge
	b2EdgeShape shape;
	shape.Set(b2Vec2(-20.0f, -20.0f), b2Vec2(20.0f, -20.0f));
	ground->CreateFixture(&shape,0.0);

	//Cria um círculo
	//b2BodyDef bd2;
	//bd2.position.Set(-3.0,0.0);
	//object2 = world->CreateBody(&bd2);

	//b2CircleShape circle;
	//circle.m_radius = 1.0;
	//object2->CreateFixture(&circle,1.0);

	//Start SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	system("pause");

	//Quit SDL
	SDL_Quit();


	return 0;
}

*/