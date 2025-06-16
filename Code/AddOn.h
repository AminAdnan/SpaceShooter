#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include<string.h>
using namespace std;
using namespace sf;

 

class AddOn
{
public:
	float x, y;
	string type;
	Sprite Icon_spr;
	
	Texture Icon;
	
	AddOn()
	{
		
	}
	virtual ~AddOn()
	{
		//cout << "PowerUP deleleted" << endl;
	}


	virtual void Ability(Bullet& b) {}
	virtual void Fall() = 0;

};

class Fire: public AddOn
{
public:
	Texture FireTex;
	Fire(int xx, int yy) 
	{
		type = "fire";
		x = xx;
		y = yy;
		Icon_spr.setPosition(x, y);
		Icon.loadFromFile("img/PNG/Power-ups/powerupRed_bolt.png");
		FireTex.loadFromFile("img/PNG/Effects/fire00.png");
		Icon_spr.setTexture(Icon);
		Icon_spr.setScale(0.75, 0.75);
	}

	void Fall()
	{
		y += 0.05;
		Icon_spr.setPosition(x, y);
	}

	void Ability(Bullet &b)
	{
		b.bullet_spr.setTexture(FireTex);
		b.bullet_spr.setScale(0.75, 2);
		b.damage = 10;
		
	}

};

class Danger : public AddOn
{
public:

	Danger(int xx, int yy)
	{
		type = "danger";
		x = xx;
		y = yy;
		Icon.loadFromFile("img/PNG/Power-ups/powerupRed.png");
		Icon_spr.setTexture(Icon);
		Icon_spr.setPosition(x, y);
		Icon_spr.setScale(0.75, 0.75);
	}
	
	void Fall()
	{
		y += 0.07;
		Icon_spr.setPosition(x, y);
	}
};

class ExtraLive: public AddOn
{
public:

	ExtraLive(int xx, int yy)
	{
		type = "lives";
		x = xx;
		y = yy;
		Icon.loadFromFile("img/PNG/UI/playerLife1_red.png");
		Icon_spr.setTexture(Icon);
		Icon_spr.setPosition(x, y);
		Icon_spr.setScale(1, 1);
	}

	void Fall()
	{
		y += 0.06;
		Icon_spr.setPosition(x, y);
	}

};

class PowerUP : public AddOn
{
public:
	PowerUP(int xx, int yy)
	{
		type = "power";
		x = xx;
		y = yy;
		Icon_spr.setPosition(x, y);
		Icon.loadFromFile("img/PNG/Power-ups/powerupRed_star.png");
		Icon_spr.setTexture(Icon);
		Icon_spr.setScale(0.75, 0.75);
	}


	void Fall()
	{
		y += 0.05;
		Icon_spr.setPosition(x, y);
	}

};



