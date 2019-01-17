#include "Shooter.h"

void Shooter::onEvent(SDL_Event* event)
{
   CEvent::onEvent(event);
}

void Shooter::onLButtonDown(int mx, int mY){
	if (interface_state == GAME)
	   switch (aim_state){
		 case (OK):
			 {
			 _interface.setPosicaoObjeto("target1",mx,mY);
			 _interface.setVisivel("target1",true);
			 _interface.setPosicaoObjeto("target2",mx,mY);
			 _interface.setVisivel("target2",true);
			 aim_state = MIRANDO;
			 break;
			 }
		 case (MIRANDO):
			 {
				break;
			 }
		 case (VOANDO):
			 {
			 map_vector[imap].ativaEfeito(tiro_atual);
			 aim_state = OK;
			 break;
			 }

	}


	if (interface_state == START)
	{
		if (_interface.clickObject(mx,mY,"start_button"))
		{	
			interface_state = GAME;
			_interface.setVisivel("start_button",false);
			this->generateMap();
		}

	}

}
void Shooter::onLButtonUp(int mx, int mY){
  if (interface_state == GAME)
  {
	switch (aim_state){
		case (OK):
		   {
			   
			
			  break;

		   }
	   case (MIRANDO):
		   {
			   Map* ptr_map = (&map_vector[imap]); 
			   Cannon* ptr_cannon = (ptr_map->getCannon());
			   tiro_atual = ptr_map->addProjectile(ptr_cannon->x + 0.6, ptr_cannon->y - 0.6,
							          angulo_tiro,  municao);
			
			  
			 _interface.setVisivel("target1",false);
			 _interface.setVisivel("target2",false);
			 angulo_tiro.SetZero();
			 if (municao != PORCO)
			   aim_state = VOANDO;
			 else
				aim_state = OK;
			   break;
		   }
	   case (VOANDO):
		   {
			   break;
		   }
	}

  }
	 

}

void Shooter::onMouseMove(int mX, int mY, int relX, int relY, bool left, bool right, bool middle)
{
  if (interface_state == GAME){
	Map* ptr_map = (&map_vector[imap]); 
    Cannon* ptr_cannon = (ptr_map->getCannon());

	switch (aim_state){
	   case (OK):
		   {
			 break;
		   }
	   case (MIRANDO):
		   {
			   if (left)
			   {
				_interface.setPosicaoObjeto("target2",mX,mY);
				angulo_tiro.x -= relX * poder_tiro;
				angulo_tiro.y -= relY * poder_tiro;
			   }
			   break;
		   }
	   case (VOANDO):
		   {
			   break;
		   }
	}
  }
}

void Shooter::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode){

	Map* ptr_map = (&map_vector[imap]); 
	Cannon* ptr_cannon = (ptr_map->getCannon());

	
	if (sym == 'z')
		municao = PORCO;
	if (sym == 'x')
		municao = VACA;
	if (sym == 'c')
		municao = OVELHA;
			


}

void Shooter::onRButtonDown(int mx, int mY){
}


void Shooter::onExit(){
    running = false;
}
