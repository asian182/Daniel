#include "Ship.h"
#include "Background.h"
//#include "EnemyShip.h"
//#include "enemyShip.h"




/* 10/24/2012 note to self move the load file and load image to the main instead and see what comesfrom it
maybe its not thebest idea to put them into the sprite class, but hey this is only the 2nd project give this 
a try and see what comes within the future*/
const int width = 640;
const int height = 480;
const int bpp = 32;

SDL_Surface * screen = NULL;


int locationX = 320;
int locationY = 240;
SDL_Event event;

//Prototypes
bool init();
void putBackgroundIntoScreen(SDL_Surface * backgroundVariable, int locX, int locY);
SDL_Surface * load_Image(std::string fileName);
void putPlayerShipIntoScreen(SDL_Surface * shipVariable);

int main(int argc, char *argv[])
{
	Sprite * someSprite = new Sprite();
	Background * background = new Background();

	SDL_Surface * bg = IMG_Load("Galaga.png");
	SDL_Surface * pShip = IMG_Load("galagaship.png");
	//so somebackground cannot be null
	//make note of the others 

	int locX = 0;
	int locY = 0;

	
	
	bool quit = false;

	 //Initialize
    if( init() == false )
    {
        return 1;
    }

	

	  //While the user hasn't quit
    while( quit == false )
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
			locY -= -5;
			//11/3/2012 work on this
			//the scrolling hasn't been able to 
			//update the background effectively
			
			putBackgroundIntoScreen(bg,locX,locY);
			putPlayerShipIntoScreen(pShip);
			
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
				
                //Quit the program
                quit = true;
            }

			if( SDL_Flip( screen ) == -1 )
			{			
				return 1;
			}
        }
		
    }

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
    screen = SDL_SetVideoMode( width, height, bpp, SDL_SWSURFACE );
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

		//Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );

        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}


bool load_File(SDL_Surface * loadSomething)
{
	
	loadSomething = load_Image("GalagaBackground.png");
	//make another function for this loaded image
	//once its loaded call it here
	//thanks frank

    //If there was an problem loading the sprite map
    if( (loadSomething) == NULL )
    {
        return false;
    }

    //If eveything loaded fine
    return true;
}


void setTheBackground(SDL_Surface * backgroundVariable, std::string backgroundImage)
{                                                                                                                                                         
	backgroundVariable = load_Image(backgroundImage.c_str());
	load_File(backgroundVariable);
	

}

void putBackgroundIntoScreen(SDL_Surface * backgroundVariable, int bgX, int bgY)
{
	//success ok it would seem that the variable wasn't set 
	//because using 2 constructors acutally created
	//2 separate instances
	//so 1 constuctor should be fine.
	Background * configureBackground = new Background();
	setTheBackground(backgroundVariable,"Galaga.png");
	configureBackground->startTimer();
	configureBackground->setBackground(backgroundVariable);
	//configureBackground->applyBackground(screen,bgX,bgY);
	/*configureBackground->applyBackground(screen,200,0);
	configureBackground->applyBackground(screen,300,0);
	configureBackground->applyBackground(screen,0,130);
	configureBackground->applyBackground(screen,200,130);
	configureBackground->applyBackground(screen,300,130);*/
	//bg moving test
	
	//buffer seems to be tearing look into it
	//note try to break it into smaller images
	configureBackground->applyBackground(screen,bgX,bgY);
    configureBackground->applyBackground(screen,bgX,bgY + backgroundVariable->h);
	if( bgY <= -backgroundVariable->h )
	{
		 //Reset the offset
		 bgY = 0;
	}
			
	/*configureBackground->applyBackground(screen,200,0 + bgY);
    configureBackground->applyBackground(screen,200, bgY+ backgroundVariable->w);
	configureBackground->applyBackground(screen,300,bgY);
    configureBackground->applyBackground(screen,200, bgY+ backgroundVariable->w);
	configureBackground->applyBackground(screen,0,130 +bgY);
    configureBackground->applyBackground(screen,0, 130+ backgroundVariable->w);
	configureBackground->applyBackground(screen,200,130);
    configureBackground->applyBackground(screen,200, 130+ backgroundVariable->w);
	configureBackground->applyBackground(screen,300,130);
    configureBackground->applyBackground(screen,300, 130+ backgroundVariable->w);*/
	//end test

}

void setPlayerShip(SDL_Surface * shipVariable, std::string shipImage)
{
	shipVariable = load_Image(shipImage.c_str());
	load_File(shipVariable);
}

void putPlayerShipIntoScreen(SDL_Surface * shipVariable)
{
	Ship * playerShip = new Ship();
	setPlayerShip(shipVariable,"galagaship.png");
	playerShip->setShip(shipVariable);
	playerShip->applyShip(screen,240,360);
}

void Ship::applyShip(SDL_Surface * intoTheScreen,int x, int y)
{
	someShip.blitTheImage(x,y,returnShip(),intoTheScreen);
}

//void handle_input()
//{
//    //If a key was pressed
//    if( event.type == SDL_KEYDOWN )
//    {
//        //Adjust the velocity
//        switch( event.key.keysym.sym )
//        {
//  				case SDLK_SPACE: 
//				{
//					//shootit = true;
//				} break;
//
//            case SDLK_UP: yVel -= DOT_HEIGHT / 2; break;
//            case SDLK_DOWN: yVel += DOT_HEIGHT / 2; break;
//            case SDLK_LEFT: xVel -= DOT_WIDTH / 2; break;
//            case SDLK_RIGHT: xVel += DOT_WIDTH / 2; break;
//        }
//    }
//    //If a key was released
//    else if( event.type == SDL_KEYUP )
//    {
//        //Adjust the velocity
//        switch( event.key.keysym.sym )
//        {
//   			case SDLK_SPACE: 
//				{
//					shootit = false;
//				} break;
//			case SDLK_UP: yVel = 0; break;
//            case SDLK_DOWN: yVel = 0; break;
//            case SDLK_LEFT: xVel = 0; break;
//            case SDLK_RIGHT: xVel = 0; break;
//        }
//    }
//}