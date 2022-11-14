#include "Player.h"

void Player::action()
{

	if (!moving) {
		if (GetAsyncKeyState(' '))
		{
			if (bullet == NULL)fire();
		}
		else if (GetAsyncKeyState('W'))
		{
			rotate(0);
			if (!getCollision())
			{
				subY--;
				moving = true;
			}
		}
		else if (GetAsyncKeyState('S'))
		{
			rotate(2);
			if (!getCollision())
			{
				subY++;
				moving = true;
			}
		}
		else if (GetAsyncKeyState('D'))
		{
			rotate(3);
			if (!getCollision())
			{
				subX++;
				moving = true;
			}
		}
		else if (GetAsyncKeyState('A'))
		{
			rotate(1);
			if (!getCollision())
			{
				subX--;
				moving = true;
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
		GetAsyncKeyState('W');
		GetAsyncKeyState('A');
		GetAsyncKeyState('S');
		GetAsyncKeyState('D');

	}
}
