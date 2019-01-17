#include "Interface.h"


Interface::Interface(void)
{
}


Interface::~Interface(void)
{
}

void Interface::addObjeto(IntVec2 dposicao, IntVec2 dtamanho, bool dvisivel, SDL_Surface* dsurface, string did)
{
	//ObjInterface* objeto = new ObjInterface(dposicao, dtamanho, dvisivel, dsurface);
	//objetos.push_back(*objeto);
	objetos.push_back(ObjInterface(dposicao, dtamanho, dvisivel, dsurface, did));
}

void Interface::removeObjeto(string _id)
{
	
	for (int i = 0; i < getObjetosSize(); i++)
	{
		if (objetos[i].id == _id)
		{
			objetos.erase(objetos.begin() + i);
			return;
		}
	}
	
}

ObjInterface* Interface::getObjetoByID(string _id)
{
	for (int i = 0; i < getObjetosSize(); i++)
	{
		ObjInterface* ptr_objeto = &objetos[i];
		if (ptr_objeto->id == _id)
			return ptr_objeto;
	}

}

int Interface::getObjetosSize()
{
	return objetos.size();
}

bool Interface::setPosicaoObjeto(string id, int x, int y)
{
	for (int i = 0; i < objetos.size(); i++){
		if (id == objetos[i].id)
		{
			objetos[i].posicao = IntVec2(x,y);
			return true;
		}
	}

	return false; //nao encontrado
}

bool Interface::setVisivel(string id, bool visivel)
{
	for (int i = 0; i < objetos.size(); i++){
		if (id == objetos[i].id)
		{
			objetos[i].visivel = visivel;
			return true;
		}
	}

	return false; //nao encontrado
}

void Interface::addCakes(int dcakes, SDL_Surface* dsurface)
{
	for (int i = 0; i < dcakes; i++)
	{
		//addObjeto(IntVec2(25*i,25), IntVec2(50,50), true, dsurface, "cake");
		addObjeto(IntVec2(25 + i * 60 ,25), IntVec2(50,50), true, dsurface, "cake");

	}
}

void Interface::subtractCake()
{
	
		removeObjeto("cake");
}

bool Interface::clickObject(int x, int y, string id)
{
	ObjInterface* obj = getObjetoByID(id);

	IntVec2 tam = obj->tamanho;
	IntVec2 anc = obj->anchor;
	IntVec2 pos = obj->posicao;

	pos.x-=anc.x;
	pos.y-=anc.y;
	
	if ((x >= pos.x) 
		&& (x <= pos.x + tam.x)
		&& (y >= pos.y)
		&& (y <= pos.y + tam.y))
		return true;
	else
		return false;

}
