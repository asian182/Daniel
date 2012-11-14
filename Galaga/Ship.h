#include "Sprite.h"

//#pragma once
class Ship
{
public:
	Ship();
	void setShip(SDL_Surface * setTheShip);
	SDL_Surface * returnShip();
	void applyShip(SDL_Surface * intoTheScreen,int x, int y);
private:
	SDL_Surface * playerShip;
	SDL_Surface * enemyShip;
	Sprite someShip;
};