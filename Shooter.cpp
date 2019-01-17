#include "Shooter.h"

using std::vector;

Shooter::Shooter()
{
    map_vector.clear();
    surf_background = NULL;
    surf_tileset = NULL;
    surf_p1cannon = NULL;
    

    surf_target1 = NULL;
    surf_target2 = NULL;
    surf_apointer = NULL;

    surf_display = NULL;

	
    imap = 0;

    

}


int Shooter::onExecute()
{
    if(onInit() == false)
    {
        return -1;
    }

    SDL_Event event;

    while(running)
    {
        while (SDL_PollEvent(&event))
            {
                onEvent(&event);
            }
            onLoop();
            onRender();

            //SDL_Delay(20);
            //Sleep(300);
    }

    onCleanup();

    return 0;
}

// funcoes de suporte
void Shooter::configBodyEdge(b2Body* body, b2Vec2 begin, b2Vec2 end){

	

}

void Shooter::configBodyBox(b2Body* body)
{
}




int main(int argc, char* argv[])
{
    Shooter game;

    return game.onExecute();
}


