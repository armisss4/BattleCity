#pragma once
#include "Tank.h"
#include <Windows.h>

using namespace std;

class Player :public Tank
{
public:
	Player(int x, int y, Screen *scr)
	{
		this->respawnY = y;
		this->respawnX = x;

		this->x = x;
		this->y = y;
		this->scr = scr;
		set_color(0xAA);
		this->lives = 2;
		this->bot = false;
	}
	void action();

protected:

private:

	

};