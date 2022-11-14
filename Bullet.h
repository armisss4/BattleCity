#pragma once
#include "Screen.h"
using namespace std;

class Bullet
{
public:
	int* get_sprite() { return sprite; };
	int get_x() { return x; }
	int get_y() { return y; }
	int get_x1() { return x1; }
	int get_y1() { return y1; }
	int get_subX() { return subX; }
	int get_subY() { return subY; }
	bool isFriendly() { return friendly; }
	void setFriendly(bool value) { friendly = value; }
	Bullet(int x, int y, int dir, Screen* scr)
	{
		this->x = x;
		this->y = y;
		this->dir = dir;
		this->scr = scr;
		/*switch (dir) {
		case 0: 
			this->y--; break;
		case 1:
			this->x--; break;
		case 2:
			this->y++; break;
		case 3:
			this->x++; break;
		}*/
		for (int i = 0; i < dir; i++)rotate();
		//action();
	}
	bool action();
	~Bullet();

protected:
private:
	bool friendly=false;
	bool live = true;
	Screen* scr;
	void rotate();
	int dir, x, y, x1, y1, subX, subY;
	int sprite[16] =
	{
		0,255,255,0,
		255,255,255,255,
		255,255,255,255,
		0,0,0,0
	};
};