#include "Shooter.h"

void Shooter::onCleanup()
{
    SDL_FreeSurface(surf_tileset);
    SDL_FreeSurface(surf_background);
    SDL_FreeSurface(surf_p1cannon);
    
    for (int i = 0; i < map_vector[imap].getProjectile_vectorSize(); i++)
		SDL_FreeSurface(map_vector[imap].getProjectile(i)->surface);

	for (int i = 0; i < _interface.getObjetosSize(); i++)
		SDL_FreeSurface(_interface.objetos[i].surface);

    SDL_FreeSurface(surf_target1);
    SDL_FreeSurface(surf_target2);
    

 
    SDL_FreeSurface(surf_apointer);

    SDL_FreeSurface(surf_display);
		
    SDL_Quit();


}
