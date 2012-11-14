#include "SDL.h"
#include "SDL_image.h"
#include <string>


#pragma once
 class Sprite
{ 
	public:
	Sprite();

	//define width and height of squares
	//void squareSize(int width, int height);

	//SDL_Surface * load_Image(std::string fileName);

	//bool load_File(std::string fileName);

	void setImage(SDL_Surface * image1);

	void blitTheImage(int x, int y, SDL_Surface * s, SDL_Surface * t);

	SDL_Surface * returnImage();

	void applyImage(std::string theImage);


	private:
		SDL_Surface * anImage;
		SDL_Rect * aSquare;
		SDL_Surface * accessImage;
		
};