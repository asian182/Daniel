#include "Ship.h"
#include "Background.h"
#include "Bullet.h"
#include <iostream>
using namespace std;
//#include "EnemyShip.h"
//#include "enemyShip.h"


/* 10/24/2012 note to self move the load file and load image to the main instead and see what comesfrom it
maybe its not thebest idea to put them into the sprite class, but hey this is only the 2nd project give this 
a try and see what comes within the future*/
const int width = 1024;
const int height = 780;
const int bpp = 32;

SDL_Surface * screen = NULL;

Ship * playerShip = new Ship();
Ship * enemyShip = new Ship();
Bullet * shipBullet = new Bullet();
Bullet * enemyBullet = new Bullet();
SDL_Event event;

//Prototypes
bool init();
void putBackgroundIntoScreen(SDL_Surface * backgroundVariable, int& locX, int& locY);
bool check_collision( SDL_Rect A, SDL_Rect B );
//player ships and input
void putPlayerShipIntoScreen( SDL_Surface * ship, int &xPosition, int &yPosition);
void handle_input(int &xVel, int &yVel, int &xChange, int &yChange, bool & bulletfire, bool &isFired, int posX, int posY);
void updatePosition(int &xPosition, int &yPosition, int &xVelocity, int &yVelocity);
//enemy ships 
void putEnemyShipIntoScreen(SDL_Surface * eShip, int &startX, int &startY);
void enemyFormations(SDL_Surface * eShip, int &startX, int &startY, int &changeSpeed,bool fire, bool letFly, SDL_Surface * EXPLOSIONS_NOISE);
//bullets for enemy and ship
void putBulletIntoScreen(SDL_Surface * bullet, int startPositionX, int startPositionY, int &speed);
void putEnemyBulletIntoScreen(SDL_Surface * eBullet,int eLocationX, int eLocationY, int &eSpeed);
//image loading
SDL_Surface * load_Image(std::string fileName);
//score system
void scoreSystem(bool isShot, int points);
//prototypes end






int main(int argc, char *argv[])
{
	SDL_Surface * enemyAmmo = IMG_Load("bullet(1).png");


	
	//location of the background
	int locX = 0;
	int locY = -500;

	int locX2 = 350;
	int locY2 = -500;
		
	//player start position
	int startPosX = 240;//240
	int startPosY = 360;//360
	int startsize = 10;
	
	//eShip start position
	int eStartX = 100;
	int eStartY = 100;

	//start speed
	int xVelocity = 0;
	int yVelocity = 0;

	//change in speed
	int xShift = 15;
	int yShift = 15;

	//shoot checks
	//**players**
	bool bulletFired = false;
	bool flyingBullet = false;
	bool isBulletOutOfScreen = false;
	//**enemies
	bool fireAtPlayer = false;
	bool flyingBulletEnemy = false;
	//bulletSpeed
	int yShift2 =10;

	
	
	bool quit = false;

	
	//Initialize
    if( init() == false )
    {
		
        return 1;
    }
	
	SDL_Surface * pShip = load_Image("galagaship.png");
	SDL_Surface * bg = load_Image("galaga2.png");
	SDL_Surface * eShip = load_Image("enemy_ship_1.png");
	SDL_Surface * bullets = load_Image("bullet(1).png" /*"galagaship.png"*/);
	SDL_Surface * TORGUE = load_Image("explosion.png");

	  //While the user hasn't quit
	
    while( quit == false )
    {
		//bullet position
		 int bulletPosX = startPosX;
		 int bulletPosY = startPosY;
		
		int newBulletPosX = bulletPosX;
		//background	
		putBackgroundIntoScreen(bg,locX,locY);
		//putBackgroundIntoScreen(bg,locX2,locY2);
		

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {		
			handle_input(xVelocity, yVelocity, xShift, yShift, bulletFired, flyingBullet, bulletPosX, bulletPosY);
			
			//If the user has Xed out the window
			if( event.type == SDL_QUIT )
            {
				
                //Quit the program
                quit = true;
            }
		}
		
			// 11/22/2012 the positions are not changed for the image so it doesn't work hmm will need to fix this
			// 11/26/2012 the loop is going into the handle_input and updateposition functions
			// but the values aren't staying changed at all
			// 11/30/2012 problem solved use & instead because we're working with pointers
			// going into the loop
 
			//updateShipPosition
			updatePosition(startPosX, startPosY,xVelocity,yVelocity);
					
            putPlayerShipIntoScreen(pShip,startPosX,startPosY);	
			
			shipBullet->updateBullet();	
			
			putBulletIntoScreen(bullets,shipBullet->getXBullet(), shipBullet->getYBullet(), yShift2);
			

			//enemyPosition
			enemyFormations(eShip,eStartX, eStartY, yVelocity,fireAtPlayer,flyingBulletEnemy,TORGUE);
			//enemyBullet->updateBullet();
			putEnemyBulletIntoScreen(enemyAmmo,enemyBullet->getXBullet(),enemyBullet->getYBullet()/*eStartX, eStartY*/, yShift2);
			if(check_collision(enemyShip->getCollisionBox(),playerShip->getCollisionBox() ) || check_collision(shipBullet->returnBulletBox(),enemyShip->getCollisionBox() ))
				putEnemyShipIntoScreen(TORGUE,eStartX,eStartY);
			
			
			
			//cout << startPosX - xSpeed << endl;
			if( SDL_Flip( screen ) == -1 )
			{	
							
				return 1;
			}	
	
	
	}
	//free the surfaces
	SDL_FreeSurface(eShip);
	SDL_FreeSurface(bg);
	SDL_FreeSurface(pShip);
	SDL_FreeSurface(bullets);
	SDL_FreeSurface(enemyAmmo);
	return 0;
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( width, height, bpp, SDL_SWSURFACE|SDL_HWSURFACE );
	//test screen
	SDL_FillRect(screen,NULL,0x000000FF);
    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Galaga", NULL );

    //If everything initialized fine
    return true;
}

//load image taken from Lazyfoo at http://lazyfoo.net/SDL_tutorials/lesson06/index.php
SDL_Surface * load_Image(std::string fileName)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
	loadedImage = IMG_Load(fileName.c_str());

    //If the image loaded
    if( loadedImage != NULL )
    {	

        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0xFF, 0xFF, 0xFF ) );
			
        }
    }

    //Return the optimized surface
    return optimizedImage;
}


//bool load_File(SDL_Surface * loadSomething, std::string image)
//{
//	
//	loadSomething = load_Image(image.c_str());
//	//make another function for this loaded image
//	//once its loaded call it here
//	//thanks frank
//
//    //If there was an problem loading the sprite map
//    if( (loadSomething) == NULL )
//    {
//        return false;
//    }
//
//    //If eveything loaded fine
//    return true;
//}


void putBackgroundIntoScreen(SDL_Surface * backgroundVariable, int& bgX, int& bgY/*, bool condition*/)
{

		Background * configureBackground = new Background();
		configureBackground->startTimer();
		configureBackground->setBackground(backgroundVariable);
		configureBackground->applyBackground(screen,bgX,bgY);	
		configureBackground->applyBackground(screen,bgX,bgY + backgroundVariable->h);
		bgY -= 2;
		if( bgY <= -backgroundVariable->h)
		{
			//Reset the offset
			bgY = 0;
			
		}
		
		delete configureBackground;
}


void putPlayerShipIntoScreen(SDL_Surface * shipVariable, int &startPointX, int &startPointY)
{
	//Ship * playerShip = new Ship();
	playerShip->setShip(shipVariable);
	playerShip->changeXRect(startPointX);
	playerShip->changeYRect(startPointY);
	playerShip->applyShip(screen,shipVariable,startPointX,startPointY);
	//delete playerShip;	
	
	
}

void putEnemyShipIntoScreen(SDL_Surface * eShip, int &startX, int &startY)
{
	//Ship * enemyShip = new Ship();
	enemyShip->setShip(eShip);
	enemyShip->changeXRect(startX);
	enemyShip->changeYRect(startY);
	enemyShip->applyShip(screen,eShip, startX, startY);
	//delete enemyShip;
	
}

void putBulletIntoScreen(SDL_Surface * bullet,int locationX, int locationY, int &speed)
{	
	shipBullet->applyBullet(screen,bullet);
	shipBullet->setXBoxCollision(locationX);
	shipBullet->setYBoxCollision(locationY);
}

void putEnemyBulletIntoScreen(SDL_Surface * eBullet,int eLocationX, int eLocationY, int &eSpeed)
{
	enemyBullet->applyBullet(screen,eBullet);
}


void enemyFormations(SDL_Surface * eShip, int &startX, int &startY, int &changeSpeed, bool fire, bool letFly, SDL_Surface * explosion)
{
	//start positions in case ships get EXPOLODED!!!
	/*const int initialStartPositionX = startX;
	const int intinalStartPositionY = startY;*/

	int randomFormation = rand() % 2 + 1;
	int randShot = rand() % 2 + 1;
	if(randomFormation == 1)
	{
		putEnemyShipIntoScreen(eShip,startX,startY);
		//startX += 5;
		/*if(check_collision( shipBullet->returnBulletBox(),enemyShip->getCollisionBox() ) )
			putEnemyShipIntoScreen(explosion,startX, startY);*/
		if(randShot == 1)
		{
			fire = true;				
			letFly = true;				
			enemyBullet->fireBullet(startX,startY,changeSpeed);//position where bullet spawns
			enemyBullet->updateBullet();
			if(fire == true && letFly == true)
			{
				fire = false;
				letFly = false;
			}
		}

		if(startX >= width || check_collision(playerShip->getCollisionBox(),enemyShip->getCollisionBox() ) || check_collision(shipBullet->returnBulletBox(),enemyShip->getCollisionBox() ))
		{
			//startX = 0;
			cout << " ow, stop pokinhg me" <<endl;
		}
	}

	if(randomFormation == 2) 
	{
		putEnemyShipIntoScreen(eShip,startX,startY);
		//startX += 3;
		//startY += 2;
		int randomNumAgain = rand() % 2 + 1;
		if(randomNumAgain == 1)
		{
			//startY -= 4;
			if(randShot == 1)
			{
				/*cout << "shot2" << endl;
				fire = true;
				letFly = true;*/
				
				
			}

		}

		//if(startX >= width || check_collision( playerShip->getCollisionBox(),enemyShip->getCollisionBox()) )
		//{
		//	//startX = 0;
		//	//startY = 100;
		//	putEnemyShipIntoScreen(explosion,startX, startY);
		//}
		//if(startY >= height || check_collision( playerShip->getCollisionBox(),enemyShip->getCollisionBox() ) )
		//{
		//	//startX = 0;
		//	//startY = 100;
		//	putEnemyShipIntoScreen(explosion,startX, startY);
		//}
	}
	
}


void handle_input(int &x, int &y, int &xChange, int &yChange , bool & weaponsFree, bool &isFired, int positionX, int positionY)
{
	
	//moved here as of 11/a12/2012
	
		//If a key was pressed
		if( event.type == SDL_KEYDOWN )
		{
			
			//Adjust the velocity
			switch( event.key.keysym.sym )
			{
				case SDLK_SPACE:
					weaponsFree = false;
					isFired = false;
					shipBullet->fireBullet(positionX,positionY,yChange);
					break;
				
				case SDLK_UP: 
					y  -=  (yChange )/ 2; 
					//int holdYValue = y;
					
					break;
				case SDLK_DOWN: 
					y +=   (yChange )/2;
					
					
					break;
				case SDLK_LEFT: 
					x -=  (xChange )/ 2;
					
					
					break;
				case SDLK_RIGHT: 
					x +=   (xChange )/ 2; 

					
					break;
			}
		}
	

		else if( event.type == SDL_KEYUP )
		{
			//Adjust the velocity
			switch( event.key.keysym.sym )
			{
   				case SDLK_SPACE: 
				{
					isFired = true;
					weaponsFree = true;
					//positionY += yChange;
				}	break;

				case SDLK_UP:  y += (yChange)/2; break;
				case SDLK_DOWN:  y -= (yChange)/2; break;
				case SDLK_LEFT:  x += (xChange)/2; break;
				case SDLK_RIGHT:  x -= (xChange)/2; break;
			}
		}
		
}


void updatePosition(int &positionX, int &positionY, int &xVel, int &yVel)
{
	
	//Move the dot left or right
    positionX += xVel;
    //If the dot went too far to the left or right
	//if( ( positionX < 0 ) || ( positionX + xVel > width ) || check_collision(playerShip->getCollisionBox(),enemyShip->getCollisionBox()) )
	if( ( playerShip->getXRect() < 0 ) || ( playerShip->getXRect() + xVel > width ) || (check_collision(playerShip->getCollisionBox(),enemyShip->getCollisionBox() )))
    {
        //move back
        //positionX -= xVel;
		int holdxValue = playerShip->getXRect();//temp variable
		holdxValue -= xVel;
		
    }

    //Move the dot up or down
    positionY += yVel;
	
    //If the dot went too far up or down
    //if( ( positionY < 0 ) || ( positionY + yVel > height ) || check_collision(playerShip->getCollisionBox(),enemyShip->getCollisionBox()) )
	if( ( playerShip->getYRect() < 0 ) || ( playerShip->getYRect() + yVel > height ) || (check_collision(playerShip->getCollisionBox(),enemyShip->getCollisionBox() )) )
    {

        //move back
        //positionY -= yVel;
		int holdyValue = playerShip->getYRect();//temp variable
		holdyValue -= yVel;
    }

}

//collision detection again from sal
bool check_collision( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB || topA >= bottomB)
    {
        return false;
    }

    /*if( topA >= bottomB )
    {
        return false;
    }
	*/
    if( rightA <= leftB || leftA >= rightB )
    {
        return false;
    }

   /* if( leftA >= rightB )
    {
        return false;
    }
	*/
    //If none of the sides from A are outside B
    return true;
}


void scoreSystem(bool isShot, int points)
{

}


