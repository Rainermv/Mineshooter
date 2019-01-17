#pragma once

#include "Suporte.h"


#include <SDL.H>
#include "CSurface.h"

#include <string>
using std::string;

class ObjInterface
{
public:
	ObjInterface(void);
	ObjInterface(IntVec2 dposicao, IntVec2 dtamanho, bool dvisivel, SDL_Surface* dsurface, string did);

	~ObjInterface(void);

	IntVec2 posicao;
	IntVec2 tamanho;
	IntVec2 anchor;

	string id;
	

	bool visivel;

	SDL_Surface* surface;


};

