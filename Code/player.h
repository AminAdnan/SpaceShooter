#include <SFML/Graphics.hpp>
#include<string.h>
#include "Bullet.h"
#include "AddOn.h"
#include <cmath>
using namespace sf;
class Player{
public:
	
	Bullet* b;
	Bullet* powerBullets[7];
Texture tex;
Sprite sprite;
Texture Shield;
Sprite shield;
float speed=0.1;
//int Bullet_count = 0;
//int Max_bullets;
int x,y;
int lives;
AddOn* addon;
Player(std::string png_path) : addon(nullptr)
{
	for (int i = 0; i < 7; ++i)
	{
		powerBullets[i] = nullptr;
	}
	lives = 3;
	tex.loadFromFile(png_path);
	Shield.loadFromFile("img/PNG/Effects/shield2.png");
	shield.setTexture(Shield);
	shield.setScale(1, 1);

	sprite.setTexture(tex);
	x=340;y=700;

	sprite.setPosition(x,y);
	sprite.setScale(0.75,0.75);
	b = nullptr;
}

void setAddOn(AddOn* add)
{
	addon = add;
}
void fire()
{
	//cout << "1";
	if (b != nullptr ) // if player shoots fast that it replaces previous bullet, delete it.
	{
		delete b;
		b = nullptr;
	}
	
	//b = new Bullet("img/PNG/Lasers/laserBlue02.png",sprite.getPosition().x+30, sprite.getPosition().y);
	if (addon != nullptr)
	{
		if (addon->type == "power")
		{
			
			for (int i = 0; i < 7; ++i)
			{
				powerBullets[i] = new Bullet("img/PNG/Effects/fire10.png", sprite.getPosition().x + 30, sprite.getPosition().y);
				
			}
			powerBullets[1]->dir_x = 0.2;
			powerBullets[2]->dir_x = 0.4;
			powerBullets[3]->dir_x = 0.6;
			powerBullets[4]->dir_x = -0.2;
			powerBullets[5]->dir_x = -0.4;
			powerBullets[6]->dir_x = -0.6;
		}
		else
		{
			b = new Bullet("img/PNG/Lasers/laserBlue02.png", sprite.getPosition().x + 30, sprite.getPosition().y);
			addon->Ability(*b);
		}
		
	
	}
	else
	{
		b = new Bullet("img/PNG/Lasers/laserBlue02.png",sprite.getPosition().x+30, sprite.getPosition().y);
	}
	
}


void Bullet_recycle()
{
	if (b!= nullptr &&b->bullet_spr.getPosition().y < -20)
	{
		delete b;
		b = nullptr;

	}
	for (int i = 0; i < 7; ++i)
	{
		if (powerBullets[i] != nullptr)
		{
			if (powerBullets[i]->bullet_spr.getPosition().y < -20)
			{
				delete powerBullets[i];
				powerBullets[i] = nullptr;
			}
		}
	}

}


void RotateSprite()
{

	/*
	float angle = 45.f; // Rotation angle in degrees
	float rad = angle * 3.14159f / 180.f; // Convert angle to radians
	// Get the 4 corners of the sprite
	float left = -sprite.getOrigin().x;
	float right = sprite.getLocalBounds().width - sprite.getOrigin().x;
	float top = -sprite.getOrigin().y;
	float bottom = sprite.getLocalBounds().height - sprite.getOrigin().y;
	// Rotate each corner around the sprite's origin
	float new_left = left * cos(rad) - top * sin(rad);
	float new_top = left * sin(rad) + top * cos(rad);

	float new_right = right * cos(rad) - top * sin(rad);
	float new_bottom = right * sin(rad) + top * cos(rad);

	float new_right2 = right * cos(rad) - bottom * sin(rad);
	float new_bottom2 = right * sin(rad) + bottom * cos(rad);

	float new_left2 = left * cos(rad) - bottom * sin(rad);
	float new_top2 = left * sin(rad) + bottom * cos(rad);
	*/
}

void wrapAround() 
{
	if (sprite.getPosition().x < -40)
	{
		sprite.setPosition(750, sprite.getPosition().y);
	}

	else if(sprite.getPosition().x > 750)
	{
		sprite.setPosition(-40, sprite.getPosition().y);
	}

	if (sprite.getPosition().y < -40)
	{
		sprite.setPosition(sprite.getPosition().x, 750);
	}
	else if (sprite.getPosition().y > 750)
	{
		sprite.setPosition(sprite.getPosition().x, -40);
	}

}



void move(std::string s){
float delta_x=0,delta_y=0;
if (s == "l")
{
	delta_x = -1;
	
//	x += delta_x;
}

else if (s == "r")
{
	delta_x = 1;

//	x += delta_x;
}
if (s == "u")
{
	delta_y = -1;
//	y += delta_y;
}
else if (s == "d")
{
	delta_y = 1;
//	y += delta_y;
}

delta_x*=speed;
delta_y*=speed;

sprite.move(delta_x, delta_y);

}


bool Collision(int x, int y, int r)
{
	
	int xpos = sprite.getPosition().x + sprite.getGlobalBounds().width / 2; //gets center x coordinate of ship
	int ypos = sprite.getPosition().y + sprite.getGlobalBounds().height / 2; // gets center y  // //
	
	// so these positions are the center of the ship
	
	// now ill make a circle around that with a radius, and check if any bullet comes in that circle

	 // got radius by trial and error // r
	//calculate distance between the point and the center of the hitbox

	float dist = sqrt(pow(x - xpos, 2) + pow(y - ypos, 2));

	if (dist <= r)
	{
		return true;
	}
	/*
	FloatRect shipHitbox = sprite.getGlobalBounds();

	// Check if the coordinates of the projectile are within the hitbox of the ship
	if (x >= shipHitbox.left && x <= shipHitbox.left + shipHitbox.width &&
		y >= shipHitbox.top && y <= shipHitbox.top + shipHitbox.height)
	{
		cout << "GOT HIT" << endl;
		return true;
	}
	*/
	return false;
}


};
