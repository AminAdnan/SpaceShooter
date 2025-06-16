#include <SFML/Graphics.hpp>
#include<string.h>
#include "Bullet.h" // act as a bomb
#include <cmath>

using namespace sf;

class Enemy
{
public:
	Texture enemyTex;
	Sprite enemy_spr;

	int hp;
	int max_hp;
	float reloadTime;
	float x, y;
	float fireRate;
	virtual Bullet* getBomb() { return nullptr; }
	Enemy()
	{
		
	}
	Enemy(string t, int xx, int yy, int h, int f, int r)
	{
		x = xx;
		y = yy;
		reloadTime = r;
		fireRate = f;
		enemyTex.loadFromFile(t);
		enemy_spr.setTexture(enemyTex);
		enemy_spr.setPosition(x, y);
		enemy_spr.setScale(0.75, 0.75);
		max_hp = h;
		hp = max_hp;

	}
	virtual void Bomb_recycle() {}
	virtual void destroy_bomb() {}
	virtual void Attack() = 0;
	virtual bool Collision(int x, int y,int r) = 0;
	virtual bool Destroy() = 0;
	virtual void Move() {}
	
	


};


class Invader : public Enemy
{
public:
	
	Bullet* bomb;
	float startX, startY;
	bool left, right;
	Invader() : Enemy()
	{
		bomb = nullptr;
	}
	Invader(int x, int y, string t, int h,int f, int r) : Enemy(t, x, y, h,f,r)
	{
		bomb = nullptr;
		startX = x;
		startY = y;
		left = true;
		right = false;
	}
	Bullet* getBomb()
	{
		return bomb;
	}
	void Attack()
	{
		//cout << "E";
		if (bomb != nullptr)
		{
			delete bomb;
			bomb = nullptr;
		}

		bomb = new Bullet("img/PNG/Lasers/laserGreen12.png", enemy_spr.getPosition().x + 30, enemy_spr.getPosition().y);
		bomb->dir_y = 1;
		bomb->bullet_speed = 0.25;
	}
	void Bomb_recycle()
	{
		if (bomb->bullet_spr.getPosition().y > 780)
		{
			delete bomb;
			bomb = nullptr;

		}
	}

	bool Collision(int x, int y, int r)
	{

		int xpos = enemy_spr.getPosition().x + enemy_spr.getGlobalBounds().width / 2; //gets center x coordinate of ship
		int ypos = enemy_spr.getPosition().y + enemy_spr.getGlobalBounds().height / 2; // gets center y  // //
		// so these positions are the center of the ship

		// now ill make a circle around that with a radius, and check if any bullet comes in that circle

	//	int radius = 45;// got radius by trial and error
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

	void Move()
	{
		
		if (x - startX >120 || left)
		{
			x -= 0.03;
			if (abs(x - startX) >= 120)
			{
				left = false;
				right = true;
			}
			
		}
		else if(x - startX < 120 && right)
		{
			x += 0.03;
			if (abs(x - startX) >= 120)
			{
				right = false;
				left = true;
			}
			
		}
		enemy_spr.setPosition(x, y);
		
	}

	bool Destroy()
	{
		if (hp <= 0)
		{
			return true;
			
		}
		return false;
	}

	void destroy_bomb()
	{
		delete bomb;
		bomb = nullptr;
	}

	//virtual void Spawn() = 0;
	

};

class Monster : public Enemy
{
public:
	Bullet* Laser;
	Monster() : Enemy()
	{
		Laser = nullptr;
	}
	Monster(int x, int y, string t, int h, int f, int r) : Enemy(t, x, y, h, f, r)
	{
		Laser = nullptr;
	}
	Bullet* getBomb()
	{
		return Laser;
	}
	void Attack()
	{
		//cout << "pew";
		if (Laser != nullptr)
		{
			delete Laser;
			Laser = nullptr;
		}

		Laser = new Bullet("img/PNG/Lasers/laserGreen08.png", enemy_spr.getPosition().x + 110, enemy_spr.getPosition().y +80);
		Laser->bullet_spr.setScale(4, 18);
		Laser->dir_y = 0;
		Laser->bullet_speed = 0;
		
	}

	bool Destroy()
	{
		if (hp <= 0)
		{
			return true;

		}
		return false;
	}

	void destroy_bomb()
	{
		delete Laser;
		Laser = nullptr;
	}

	


	bool Collision(int x, int y, int r)
	{

		int xpos = enemy_spr.getPosition().x + enemy_spr.getGlobalBounds().width / 2; //gets center x coordinate of ship
		int ypos = enemy_spr.getPosition().y + enemy_spr.getGlobalBounds().height / 2; // gets center y  // //
		// so these positions are the center of the ship

		// now ill make a circle around that with a radius, and check if any bullet comes in that circle

	//	int radius = 45;// got radius by trial and error
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



class dragon : public Enemy
{
public:
	Bullet* flame;
	dragon() : Enemy()
	{
		flame = nullptr;
	}
	dragon(int x, int y, string t, int h, int f, int r) : Enemy(t, x, y, h, f, r)
	{
		flame = nullptr;
		enemy_spr.setScale(1.6, 1.6);
	}
	Bullet* getBomb()
	{
		return flame;
	}
	void Attack()
	{
		//cout << "wwooosh";
		if (flame != nullptr)
		{
			delete flame;
			flame = nullptr;
		}

		flame = new Bullet("img/PNG/Effects/fire00.png", enemy_spr.getPosition().x + 160, enemy_spr.getPosition().y + 220);
		flame->bullet_spr.setScale(4, 20);
		flame->dir_y = 0;
		flame->bullet_speed = 0;

	}

	bool Destroy()
	{
		if (hp <= 0)
		{
			return true;

		}
		return false;
	}

	void destroy_bomb()
	{
		delete flame;
		flame = nullptr;
	}




	bool Collision(int x, int y, int r)
	{
		
		int xpos = enemy_spr.getPosition().x + enemy_spr.getGlobalBounds().width / 2; //gets center x coordinate of ship
		int ypos = enemy_spr.getPosition().y + enemy_spr.getGlobalBounds().height / 2; // gets center y  // //
		// so these positions are the center of the ship

		// now ill make a circle around that with a radius, and check if any bullet comes in that circle

	//	int radius = 45;// got radius by trial and error
		//calculate distance between the point and the center of the hitbox
		float dist = sqrt(pow(x - xpos, 2) + pow(y - ypos, 2));

		if (dist <= r)
		{
			return true;
		}
		/*
		FloatRect shipHitbox = flame->bullet_spr.getGlobalBounds();

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
