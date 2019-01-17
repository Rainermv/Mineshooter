#ifndef _CSURFACE_H_
#define _CSURFACE_H_

#include <SDL.H>

class CSurface
{
    public:
        CSurface();

    public:
        static SDL_Surface* onLoad(char* file);

        static bool onDraw(SDL_Surface* surf_dest, SDL_Surface* surf_src, int x, int y);

        static bool onDraw(SDL_Surface* surf_dest, SDL_Surface* surf_src, int x, int y,
                           int x2, int y2, int w,int h);

        static bool transparent(SDL_Surface* Surf_Dest, int r, int g, int b);
};

#endif
