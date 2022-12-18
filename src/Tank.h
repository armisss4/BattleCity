#pragma once
#include "Screen.h"
#include "Bullet.h"
using namespace std;

class Tank
{
public:
	int* get_sprite() { return sprite; };
	int get_x() { return x; }
	int get_y() { return y; }
	int get_xTrue();
	int get_yTrue();
	int get_x1True();
	int get_y1True();
	int get_lives() { return lives; }

	int get_subX() { return subX; }
	int get_subY() { return subY; }
	Bullet* get_bullet() { return bullet; }
	void destroy_bullet() { bullet = NULL; }
	void kill();
	bool isBot() { return bot; }
	virtual void action() {};
	void set_color(int color)
	{
		for (int i = 0; i < 196; i++)
		{
			if (sprite[i] == -1)sprite[i] = color;
		}
	}

	void rotate()
	{

		int temp[196];
		copy(sprite, sprite + 196, temp);

		for (int i = 0; i < 14; i++)
		{
			for (int ii = 0; ii < 14; ii++)
			{
				sprite[i + ii * 14] = temp[(13 - ii) + i * 14];
			}

		}


	}


protected:
	bool bot;
	void rotate(int dir);
	void fire();
	bool getCollision();
	int x, y;
	int respawnX, respawnY;
	bool moving = false;
	int subX = 0;
	int subY = 0;
	Screen* scr;
	Bullet* bullet = NULL;
	int lives;

private:
	
	int currentRotation = 0;
	//void rotate();
	int sprite[196] =
	{
		000,000,000,000,000,000,136,136,000,000,000,000,000,000,
		000,000,000,000,000,000,136,136,000,000,000,000,000,000,
		255,-1,-1,0,0,0,136,136,0,0,0,-1,-1,-1,
		-1,255,119,0,0,0,136,136,0,0,0,-1,255,255,
		-1,-1,119,0,-1,-1,136,136,-1,-1,0,-1,-1,-1,
		-1,255,119,119,119,255,255,255,255,255,255,-1,255,255,
		-1,-1,119,119,255,255,-1,-1,-1,255,255,-1,-1,-1,
		-1,255,119,119,255,119,255,255,-1,255,255,-1,255,255,
		-1,-1,119,119,255,119,255,255,-1,255,255,-1,-1,-1,
		-1,255,119,119,255,119,119,119,255,255,255,-1,255,255,
		-1,-1,119,255,119,255,255,255,255,255,255,-1,-1,-1,
		-1,255,119,0,119,119,255,255,255,255,0,-1,255,255,
		-1,-1,-1,0,0,0,0,0,0,0,0,255,-1,-1,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};
};