#include "ObjInterface.h"


ObjInterface::ObjInterface(void)
{
}

ObjInterface::ObjInterface(IntVec2 dposicao, IntVec2 dtamanho, bool dvisivel, SDL_Surface* dsurface, string did)
{
	posicao = dposicao;
	tamanho = dtamanho;
	
	anchor.x = tamanho.x/2;
	anchor.y = tamanho.y/2;

	visivel = dvisivel;

	surface = dsurface;
	CSurface::transparent(surface, 255, 0, 255); // define o magenta como transparente

	id = did;

}

ObjInterface::~ObjInterface(void)
{
}
