#include "Sprite.h"

//collision values
const int widthOfImage = 30;
const int heightOfImage = 30;
class Ship
{
public:
	Ship();
	~Ship();
	//ship collsion sides
	SDL_Rect sizeOfImage();
	//set and return values for playerShip
	void setShip(SDL_Surface * setTheShip);
	SDL_Surface * returnShip();
	void applyShip(SDL_Surface * intoTheScreen,SDL_Surface * shipImage,int x, int y);
	void move();
	//position of ship
	void changeXPosition(int velX);
	void changeYPosition(int velY);
	//velocities
	void setShipVelX(int setShipWidth);
	void setShipVelY(int setShipHeight);
	int getShipVelX();
	int getShipVelY();
	//get the collision box
	SDL_Rect getCollisionBox();
	void changeXRect(int newXRect);
	void changeYRect(int newYRect);
	int getXRect();
	int getYRect();
private:
	//the stars of the show
	SDL_Surface * playerShip;
	SDL_Surface * enemyShip;
	Sprite someShip;

	//ship's speed and start location
	int posX;
	int posY;

	//velocities
	int xVel;
	int yVel;

	//ship size
	int shipWidth;
	int shipHeight;

	//box for collision
	SDL_Rect shipBox;
};