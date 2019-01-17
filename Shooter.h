////////////////////////////////////////////////////////////////////////////////////
//
// Shooter Engine, by Rainer Mansan Vieira //
// student of Universidade do Vale do Rio dos Sinos - UNISINOS  //
//
//
///////////////////////////////////////////////////////////////////////////////////// 


#ifndef _SHOOTER_H_
#define _SHOOTER_H_

// BOX 2D
#include <Box2D/Box2D.h>

// SDL
#include <SDL.H>

#include <iostream>

#include "CEvent.h"
#include "CSurface.h"
#include "Map.h"
#include "Interface.h"
#include "Suporte.h"

#include <time.h>


#include <vector>
using std::vector;

#include "time.h"


#define WINDOW_H 650
#define WINDOW_W 1000

#define BLOCK_SIZE 50

//int duh;

enum Aim_State {OK, VOANDO, MIRANDO};
enum Interface_State {START, GAME, END};


class Shooter : public CEvent{

    private:
        Interface _interface;
        bool            running;
        SDL_Surface*    surf_display;

        vector<Map> map_vector;
        unsigned short int bLin;
        unsigned short int bCol;
        
        int imap;
        
    private:
        SDL_Surface*    surf_tileset;
        SDL_Surface*    surf_background;
		SDL_Surface*    surf_p1cannon;
        SDL_Surface*    surf_target1;
        SDL_Surface*    surf_target2;
		SDL_Surface*    surf_apointer;

		
		

	private:
     // parametros Box 2d
		float32 timeStep;
		int32 velocityIterations;
		int32 positionIterations;
		b2Vec2 gravity;
		bool doSleep;


	//controles do jogo
	Aim_State aim_state;
	int pontos;
	int shots_left;
	int cakes_left;
	b2Vec2 angulo_tiro;
	float poder_tiro;
	Tipo municao; 
	Projectile* tiro_atual;

	int world_width;
	int world_height;

	Interface_State interface_state;
	
    public:

        Shooter();
        int onExecute();

		// funcoes de suporte
		void configBodyEdge(b2Body* body, b2Vec2 begin, b2Vec2 end);
		void configBodyBox(b2Body* body);

    public:



        bool onInit();
               bool load_media();
			                
			   void initBox2D(); // inicia a Box2d

			   void initObjects();
			   void initInterface();
			   void initParametros();
			   void generateMap();
               
        void onEvent(SDL_Event* Event);
                void onLButtonDown(int mX, int mY);
				void onLButtonUp(int mx, int mY);
                void onRButtonDown(int mX, int mY);
                void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
				
                void onMouseMove(int mX, int mY, int relX, int relY, bool left, bool right, bool middle);
                void onExit();
        void onLoop();
				void checkInterface();
				void box2dLoop();
				void update();
                void checkColision();
                void checkDestroyed();

				void pegaCake(int points);
                
        void onRender();
				void drawBackground();
				void drawVerts(b2Body* body);
				void drawObjects();
				void drawInterface();
				int calculaRanhuras(float res, float max_res);
        void onCleanup();
                
};

#endif
