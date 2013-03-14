#include "SDL.h"
#include "SDL_image.h"
#include <string>


#pragma once
 class Sprite
{ 
	public:
	Sprite();

	void setImage(SDL_Surface * image1);

	void blitTheImage(int x, int y, SDL_Surface * s, SDL_Surface * t);

	SDL_Surface * returnImage();

	void applyImage(std::string theImage);


	private:
		SDL_Surface * anImage;
		SDL_Rect * aSquare;
		SDL_Surface * accessImage;
		
};