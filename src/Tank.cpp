#include "Tank.h"
#include <algorithm>
#include <iterator>

void Tank::set_color(int color)
{
	for (int i = 0; i < 196; i++)
	{
		if (sprite[i] == -1)sprite[i] = color;
	}
}

int Tank::get_xTrue()
{
	if (moving && subX != 0)
	{
		if (currentRotation == 1)return x - 1;
		if (currentRotation == 3)return x + 1;
	}
	return x;
}

int Tank::get_yTrue()
{
	if (moving && subY != 0)
	{
		if (currentRotation == 0)return y - 1;
		if (currentRotation == 2)return y + 1;
	}
	return y;
}

int Tank::get_x1True()
{
	if (moving && subX != 0)
	{
		if (currentRotation == 1)return x;
		if (currentRotation == 3)return x + 2;
	}
	return x + 1;
}

int Tank::get_y1True()
{
	if (moving && subY != 0)
	{
		if (currentRotation == 0)return y;
		if (currentRotation == 2)return y + 2;
	}
	return y+1;
}

void Tank::kill()
{
	x = respawnX;
	y = respawnY;
	lives--;
	moving = false;
	subX = 0;
	subY = 0;
	bullet = NULL;
}

void Tank::rotate(int dir)
{
	while (dir != currentRotation)
	{
		rotate();
		currentRotation = ++currentRotation % 4;
	}

}

void Tank::fire()
{
	
	bullet = move(new Bullet(x, y, currentRotation, scr));
	if (isBot())bullet->setFriendly(true);
	else bullet->setFriendly(false);
	bullet->action();
	bullet->action();
	bullet->action();
}

bool Tank::getCollision()
{
	if (scr->isNotBlank(x, y, currentRotation))return true;
	return false;
}

void Tank::rotate()
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
