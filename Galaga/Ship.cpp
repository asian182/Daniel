#include "Ship.h"

Ship::Ship()
{

}

void Ship::setShip(SDL_Surface * setTheShip)
{
	playerShip = setTheShip;
	someShip.setImage(setTheShip);
} 

SDL_Surface * Ship::returnShip()
{
	return playerShip;
}

//added 11/7/2012
//void Ship::Dot()
//{
//    //Initialize the offsets
//    x = 0;
//    y = 0;
//	shootit = false;
//
//    //Initialize the velocity
//    xVel = 0;
//    yVel = 0;
//}
//void Ship::Dot(Dot * a)
//{
//    //Initialize the offsets
//    x = a->x;
//    y = a->y;
//
//    //Initialize the velocity
//    xVel = 5;
//    yVel = 10;
//}
//Ship::Dot(int a, int b)
//{
//    //Initialize the offsets
//    x = a;
//    y = b;
//
//    //Initialize the velocity
//    xVel = 1;
//    yVel = 1;
//}