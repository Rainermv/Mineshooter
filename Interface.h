#pragma once

#include <SDL.h>

#include "Suporte.h"
#include "ObjInterface.h"

#include <Vector>
using std::vector;

#include <string>
using std::string;


class Interface
{
public:

	Interface(void);
	~Interface(void);

	void addObjeto(IntVec2 dposicao, IntVec2 dtamanho, bool dvisivel, SDL_Surface* dsurface, string did);
	int getObjetosSize();

	void removeObjeto(string _id);
	ObjInterface* getObjetoByID(string id);

	bool setPosicaoObjeto(string id, int x, int y);
	bool setVisivel(string id, bool visivel);

	void addCakes(int dcakes, SDL_Surface* dsurface);
	void subtractCake();

	bool clickObject(int x, int y, string id);

	
	vector<ObjInterface> objetos;
};

