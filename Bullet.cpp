#include "Bullet.h"


Bullet::Bullet()
{
	x = 0;
	y = 0;
	ySpeed = 0;
	shot = false;
	bulletBox.w = widthOfBullet;
	bulletBox.h = heightOfBullet;

}


Bullet::~Bullet()
{

}

void Bullet::setBullet(SDL_Surface * setTheBullet)
{
	bulletImage = setTheBullet;
	spriteBullet.setImage(setTheBullet);
} 

SDL_Surface * Bullet::returnBullet()
{
	return bulletImage;
}

void Bullet::setXBullet(int posX)
{
	x = posX;
}
void Bullet::setYBullet(int posY)
{
	y = posY;
}
int Bullet::getXBullet()
{
	return x;
}
int Bullet::getYBullet()
{
	return y;
}


void Bullet::applyBullet(SDL_Surface * intoTheScreen,SDL_Surface * BulletImage)
{
	spriteBullet.blitTheImage(x,y,BulletImage,intoTheScreen);
}

void Bullet::fireBullet(int posX, int posY, int speedOfBullet)
{
	
	if(shot == false)
	{
		x = posX;
		y = posY;
		ySpeed = speedOfBullet;
		shot = true;
	}

		
}

void Bullet::updateBullet()
{
	if(shot == true)
	{
		//y += ySpeed;		
		if(y >= -20)
		{ y += -5 * ySpeed; }
		//out of boundscheck
		//if so
		else
		{
			x = 0;
			y = 0;
			shot = false;
		}
		
	
	}
}
void Bullet::setXBoxCollision(int newLocationX)
{
	bulletBox.x = newLocationX;
} 


void Bullet::setYBoxCollision(int newLocationY)
{
	bulletBox.y = newLocationY;
}


int Bullet::returnXBoxCollision()
{
	return bulletBox.x;
}

int Bullet::returnYBoxCollision()
{
	return bulletBox.y;
}

SDL_Rect Bullet::returnBulletBox()
{
	return bulletBox;
}