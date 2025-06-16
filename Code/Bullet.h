#include <iostream>
using namespace std;
using namespace sf;
#include <SFML/Graphics.hpp>
#include<string.h>
#pragma once



class Bullet
{
public:
	Sprite bullet_spr;
	Texture bullet_tex;
	float dir_x, dir_y;
	int x, y;
	float bullet_speed;
	int damage;

	Bullet(string spr, int xx, int yy)
	{
		x = xx;
		damage = 1;
		y = yy;
		dir_x = 0;
		dir_y = -1;
		bullet_speed = 0.8;
		bullet_spr.setPosition(x, y);
		bullet_tex.loadFromFile(spr);
		bullet_spr.setTexture(bullet_tex);
		bullet_spr.setScale(0.75, 0.75);
		//bullet_spr.move(0, dir_y * bullet_speed);
		
	}
	void move()
	{
		bullet_spr.move(dir_x*bullet_speed,dir_y*bullet_speed);
		
	}


	~Bullet()
	{
		//cout << "DAMN" << endl;
		
	}

};
