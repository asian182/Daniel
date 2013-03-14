#include "Background.h"

Background::Background()
{
	
}

void Background::setBackground(SDL_Surface * setTheBackground)
{
	someBackground = setTheBackground;
	backGroundSprite.setImage(someBackground);
}


SDL_Surface * Background::returnBackground()
{
	return someBackground;
}



void Background::applyBackground(SDL_Surface * onToScreen,int x, int y)
{
	backGroundSprite.blitTheImage(x,y,returnBackground(),onToScreen);
}

//***Timer***

void Background::startTimer()
{
	pauseClock = false;
	startTheTimer = true;
	startClock = 0;
	startClock = SDL_GetTicks();
}

void Background::stopTimer()
{
	//Stop the timer
    startTheTimer = false;

    //Unpause the timer
    pauseClock = false;
}

void Background::pause()
{
	 //If the timer is running and isn't already paused
    if( ( startTheTimer == true ) && ( pauseClock == false ) )
    {
        //Pause the timer
        pauseClock = true;

        //Calculate the paused ticks
        pauseClock= SDL_GetTicks() - startClock;
    }

}

void Background::unPause()
{
	if( pauseTimer == true )
    {
        //Unpause the timer
        pauseTimer = false;

        //Reset the starting ticks
        startClock = SDL_GetTicks() - pauseClock;

        //Reset the paused ticks
        pauseClock = 0;
    }
}

int Background::getFrameTicks()
{
    //If the timer is running
    if( startTheTimer == true )
    {
        //If the timer is paused
        if( pauseTimer == true )
        {
            //Return the number of ticks when the timer was paused
            return pauseClock;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startClock;
        }
    }

    //If the timer isn't running
    return 0;
}




