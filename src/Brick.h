#pragma once
#include "Block.h"
using namespace std;

class Brick : public Block
{
public:
	int* get_sprite();
	Brick(int x, int y)
	{
		this->x = x;
		this->y = y;
		this->strength = 0;
	}

	
protected:

private:
	int sprite[49] =
	{
		136,136,136,136,136,136,136,
		204,204,204,204,204,136,204,
		102,102,102,102,102,136,204,
		136,136,136,136,136,136,136,
		136,204,204,204,204,204,204,
		136,204,102,102,102,102,102,
		136,204,102,102,102,102,102
	};

};