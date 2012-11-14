#include "Sprite.h"

const int FRAMES_PER_SECOND = 20;
class Background: public Sprite
{

public:
	//constructor
	Background();
	//set,return, apply background functions
	void setBackground(SDL_Surface * setTheBackground);
	SDL_Surface * returnBackground();
	void applyBackground(SDL_Surface * onToScreen,int x, int y);

	//**Timer functions**
	void startTimer();
	void stopTimer();
	void pause();
	void unPause();
	//**FrameRate Function**
	void setFrames();
	int getFrameTicks();

private:
	SDL_Surface * someBackground;
	SDL_Surface * thisBackground;
	Sprite backGroundSprite;

	//**Timer**
	int startClock;
	int stopClock;

	int pauseClock;
	int clickClock;
	
	bool startTheTimer;
	bool stopTheTimer;

	bool pauseTimer;
	bool unpauseTimer;

	
};