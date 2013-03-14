#include "Ship.h"

Ship::Ship()
{
	shipWidth = 0;
	shipHeight = 0;
	shipBox.x = 0;
	shipBox.y = 0;
	shipBox.w = widthOfImage;
	shipBox.h = heightOfImage;
}

Ship::~Ship()
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

void Ship::setShipVelX(int w)
{
	shipWidth = w;
	
}

void Ship::setShipVelY(int h)
{
	shipHeight = h;
	
}

int Ship::getShipVelX()
{
	return shipWidth;
}

int Ship::getShipVelY()
{
	return shipHeight;
}

void Ship::applyShip(SDL_Surface * intoTheScreen,SDL_Surface * shipImage,int x, int y)
{
	someShip.blitTheImage(x,y,returnShip(),intoTheScreen);
	//when applied onto screen the image is set into a rectangular box
	//of the image's sizae
	shipBox.x = x;
	shipBox.y = y;
}

SDL_Rect Ship::getCollisionBox()
{
	return shipBox;
}

void Ship::changeXRect(int newXLocation)
{
	shipBox.x = newXLocation;
}

int Ship::getXRect()
{
	return shipBox.x;
}

int Ship::getYRect()
{
	return shipBox.y;
}

void Ship::changeYRect(int newYLocation)
{
	shipBox.y = newYLocation;
}



