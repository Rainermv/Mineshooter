#include "CSurface.h"

CSurface::CSurface()
{

}

SDL_Surface* CSurface::onLoad(char* file)
{
    SDL_Surface* surf_temp = NULL;
    SDL_Surface* surf_return = NULL;

    if ((surf_temp = SDL_LoadBMP(file)) == NULL)
    {
        return NULL;
    }

    surf_return = SDL_DisplayFormat(surf_temp);
    SDL_FreeSurface(surf_temp);

    return surf_return;
}

bool CSurface::onDraw(SDL_Surface* surf_dest, SDL_Surface* surf_src, int x, int y)
{


    if(surf_dest ==NULL || surf_src == NULL)
    {
        return false;
    }

    SDL_Rect destR;

    destR.x = x;
    destR.y = y;

    SDL_BlitSurface(surf_src, NULL, surf_dest, &destR);

    return true;
}

bool CSurface::onDraw(SDL_Surface* surf_dest, SDL_Surface* surf_src, int x, int y,
                      int x2, int y2, int w, int h)
    {
        if (surf_dest == NULL || surf_src == NULL)
        {
            return false;
        }

        SDL_Rect destRect;

        destRect.x = x;
        destRect.y = y;

        SDL_Rect srcRect;

        srcRect.x = x2;
        srcRect.y = y2;
        srcRect.w = w;
        srcRect.h = h;

        SDL_BlitSurface(surf_src, &srcRect, surf_dest, &destRect);

        return true;


}

bool CSurface::transparent(SDL_Surface* Surf_Dest, int r, int g, int b){
    if (Surf_Dest == NULL){
        return false;
    }

    SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL,
                    SDL_MapRGB(Surf_Dest->format, r, g, b));

    return true;

}
