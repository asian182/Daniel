#include "Sprite.h"

const int widthOfBullet = 10;
const int heightOfBullet = 10;
class Bullet
{
	public:
		Bullet();
		~Bullet();
		void setBullet(SDL_Surface * myBullet);
		SDL_Surface * returnBullet();
		void setXBullet(int posX);
		void setYBullet(int posY);
		int getXBullet();
		int getYBullet();
		void applyBullet(SDL_Surface * screen,SDL_Surface * thisImage);
		void updateBullet();
		void fireBullet(int posX, int posY, int speedOfBullet);

		//collision section
		void setXBoxCollision(int newLocationX);
		void setYBoxCollision(int newLocationY);
		int returnXBoxCollision();
		int returnYBoxCollision();
		SDL_Rect returnBulletBox();

	private:

		SDL_Surface * bulletImage;
		Sprite spriteBullet;
		int x;
		int y;
		int ySpeed;
		bool shot;
		SDL_Rect bulletBox;
};