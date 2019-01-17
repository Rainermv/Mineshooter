#include "Shooter.h"

using std::vector;
using std::cerr;


bool Shooter::onInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    if ((surf_display = SDL_SetVideoMode(WINDOW_W,WINDOW_H,32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    {
        return false;
    }

    if (load_media() == NULL){

        return false;
    }

	initBox2D(); // inicia Box 2D
	initParametros(); // inicia parametros do jogo

	initObjects(); // inicia objetos
	initInterface(); //inicia interface


    return true;
}

void Shooter::initParametros()
{
	pontos = 0;
	shots_left = 10;
	cakes_left = 3;
	aim_state = OK;
	poder_tiro = 10;
	angulo_tiro.SetZero();
	municao = PORCO;

	tiro_atual = NULL;

	world_width = 20;
	world_height = 13;

	interface_state = START;
}


bool Shooter::load_media(){

        // load block tile set
    if ((surf_tileset = CSurface::onLoad("./bmp/blocktileset.bmp")) == NULL)
    {
        return false;
    }

        // load background
    if ((surf_background = CSurface::onLoad("./bmp/background.bmp")) == NULL)
    {
        return false;
    }

        // load p1 cannon
    if ((surf_p1cannon = CSurface::onLoad("./bmp/p1cannon.bmp")) == NULL)
    {
        return false;
    }

 

    
        // load power bar
        if ((surf_target1 = CSurface::onLoad("./bmp/target1.bmp")) == NULL)
    {
        return false;
    }
       

        // Ppointer
        if ((surf_target2 = CSurface::onLoad("./bmp/target2.bmp")) == NULL)
    {
        return false;
    }
      

        // apointer
        if ((surf_apointer = CSurface::onLoad("./bmp/bullet.bmp")) == NULL)
    {
        return false;
    }

	        
    CSurface::transparent(surf_tileset, 255, 0, 255);

	CSurface::transparent(surf_p1cannon, 255, 0, 255);
   

    CSurface::transparent(surf_target1, 255, 0, 255);
    
	CSurface::transparent(surf_target1, 255, 0, 255);
    CSurface::transparent(surf_target2, 255, 0, 255);
    
    CSurface::transparent(surf_apointer, 255, 0, 255);


    return true;
}

void Shooter::initObjects(){
	
    // cria mapa
    Map* ptr_map = new Map(world_width, world_height, gravity, doSleep); // inicia com fisica
    map_vector.push_back(*ptr_map);

	//generateMap();
	   
	delete ptr_map;
}

void Shooter::generateMap()
{
	
    float cr = 0.5;
	int factor = 50;
	srand ( time(NULL) );

	map_vector[imap].addCannon(cr,cr,10);
	map_vector[imap].addBlock(cr,1+cr,TIJOLO,1);
	map_vector[imap].addBlock(cr,2+cr,TIJOLO,1);
	map_vector[imap].addBlock(cr,2-cr,TIJOLO,1);

	

	// cria cakes
	for (int i = 0; i < cakes_left; i++)
		{
			int type = rand() % world_width;
			map_vector[imap].addBlock(cr+type,0+cr,CAKE,1);
		}
	
		
    

	// cria blocos
      for (int x = 0; x < map_vector[imap].getSize_x(); x++){
			map_vector[imap].addBlock((float)x+cr,4.0, GRAMA,1);
			for (int y = 5; y < map_vector[imap].getSize_y(); y++){

				int type = rand() % 100;
				
									
				if ((x <= 3) && (y >= 8))
				{
					
					if ((type > factor-20) && (type <=100)) 
						map_vector[imap].addBlock((float)x+cr,(float)y-cr,TERRA,1);
					else if ((type <= factor) && (y >= 12))
						map_vector[imap].addBlock((float)x+cr,(float)y-cr,PEDRA,1);

				}

				else if (x > 3)
				{
				  
					if ((type > 95) && (type <=100)) 
						map_vector[imap].addBlock((float)x+cr,(float)y-cr,TNT,1);
					if ((type > factor) && (type <=95)) 
						map_vector[imap].addBlock((float)x+cr,(float)y-cr,TERRA,1);
					else if ((type <= factor) && (y >= 12))
							map_vector[imap].addBlock((float)x+cr,(float)y-cr,PEDRA,1);
				  
				 
				}
					 
			}
		}

	  // cria joints
	  
	   for (int x = 5; x < map_vector[imap].getSize_x(); x++){
		   int type = rand() % 100;
		   if (type > 90)
				map_vector[imap].addBlockdJoint(x, 1);
		   else if (type < 10)
				map_vector[imap].addBlockrJoint(x,3);
			   
				

	   }
			


}



void Shooter::initBox2D()
{
	// Define the gravity vector.
	gravity = b2Vec2(0.0f, 20.0f); // valor positivo do Y. em SDL, o Y0 esta em cima.

	// Permite que os objetos 'durmam'. Melhora o desempenho
	doSleep = true;

	// Define os parâmetro para a simulação
	// Quanto maior, mais preciso, porém, mais lento
    velocityIterations = 8;
    positionIterations = 3;
	timeStep = 1.0f / 100.0f;
		
}

void Shooter::initInterface()
{
	_interface.addObjeto(IntVec2(WINDOW_W/2,32),IntVec2(1000,64),true,CSurface::onLoad("./bmp/top_bar.bmp"), "top_bar");
	_interface.addObjeto(IntVec2(WINDOW_W/2,WINDOW_H - 16),IntVec2(1000,32),true,CSurface::onLoad("./bmp/bot_bar.bmp"), "bot_bar");
	_interface.addObjeto(IntVec2(0,0),IntVec2(64,64),false,CSurface::onLoad("./bmp/Target1.bmp"), "target1");
	_interface.addObjeto(IntVec2(0,0),IntVec2(16,16),false,CSurface::onLoad("./bmp/Target2.bmp"), "target2");

	_interface.addCakes(cakes_left, CSurface::onLoad("./bmp/cake.bmp"));

	_interface.addObjeto(IntVec2(WINDOW_W/2,WINDOW_H/3),IntVec2(400,200),true,CSurface::onLoad("./bmp/Start.bmp"), "start_button");
	_interface.addObjeto(IntVec2(WINDOW_W/2,WINDOW_H/3),IntVec2(400,200),false,CSurface::onLoad("./bmp/END.bmp"), "end");
}


