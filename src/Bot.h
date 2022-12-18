#pragma once
#include "Tank.h"
using namespace std;

class Bot :public Tank
{
public:
	Bot(int x, int y, Screen *scr)
	{
		this->respawnY = y;
		this->respawnX = x;
		this->x = x;
		this->y = y;
		this->scr = scr;
		set_color(0x88);
		this->lives = 4;
		this->bot = true;
	}
	void action();


protected:

private:


};