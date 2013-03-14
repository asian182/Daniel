#include "Sprite.h"

Sprite::Sprite()
{
	//anImage = NULL;
}

//void Sprite::squareSize(int width, int height)
//{
//	aSquare->w = width;
//	aSquare->h = height;
//
//}



void Sprite::blitTheImage(int x, int y, SDL_Surface * s, SDL_Surface * t)
{
	SDL_Rect holdSquare;
	
	holdSquare.x = x;
    holdSquare.y = y;
	//squareSize(10,10);

	//shows it here
	//surface s is the destination applied to t is the surface thats being put on
	//10/4/12 blitsurface aSquare has not been set to anything
	//exceeding array so too many pixels
	SDL_BlitSurface( s, /*aSquare*/NULL , t, &holdSquare );
}


void Sprite::setImage(SDL_Surface * image1)
{
	anImage = image1;
}

SDL_Surface * Sprite::returnImage()
{
	return anImage;
}

void Sprite::applyImage(std::string theImage)
{
	setImage(anImage);
	
}