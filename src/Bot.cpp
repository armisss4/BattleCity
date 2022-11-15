#include "Bot.h"
#include <random>

void Bot::action()
{
	
	if (!moving) {
		if (rand() % 100 > 33) { if (bullet == NULL)fire(); }
		else {

			int direction = rand() % 4;
			switch (direction)
			{
			case 0:
				rotate(0);
				if (!getCollision())
				{
					subY--;
					moving = true;
				}
				break;
			case 1:
				rotate(2);
				if (!getCollision())
				{
					subY++;
					moving = true;
				}
				break;
			case 2:
				rotate(3);
				if (!getCollision())
				{
					subX++;
					moving = true;
				}
				break;
			case 3:
				rotate(1);
				if (!getCollision())
				{
					subX--;
					moving = true;
				}
				break;
			}
		}
	}
	else
	{
		if (subX < 0)subX--;
		if (subX > 0)subX++;
		if (subY < 0)subY--;
		if (subY > 0)subY++;
		if (abs(subX) == 7) {
			x += (subX / 7);
			subX = 0;
			moving = false;
		}
		if (abs(subY) == 7) {
			y += (subY / 7);
			subY = 0;
			moving = false;
		}
	}
}
