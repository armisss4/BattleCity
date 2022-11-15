#pragma once
#include "Block.h"
using namespace std;

class Eagle : public Block
{
public:
	int* get_sprite();
	Eagle(int x, int y)
	{
		this->x = x;
		this->y = y;
		this->strength = -1;
	}
	int get_spriteSize() { return 14; };

protected:

private:
	int sprite[196] =
	{
		136,136,0,0,0,0,0,0,0,0,0,0,136,136,
		0,136,136,0,0,136,136,136,0,0,0,136,136,0,
		136,136,136,136,0,0,136,68,136,0,136,136,136,136,
		0,136,136,136,0,0,136,136,0,0,136,136,136,0,
		136,136,136,136,136,136,136,136,136,136,136,136,136,136,
		0,0,136,68,136,136,136,136,136,136,68,136,0,0,
		0,136,136,136,68,136,136,136,136,68,136,136,136,0,
		0,0,136,136,136,68,136,136,68,136,136,136,0,0,
		0,0,0,136,136,136,136,136,136,136,136,0,0,0,
		0,0,0,0,136,0,136,136,0,136,0,0,0,0,
		0,0,0,0,0,0,136,136,0,0,0,0,0,0,
		0,0,0,0,0,136,136,136,136,0,0,0,0,0,
		0,0,0,136,136,136,136,136,136,136,136,0,0,0,
		0,0,0,136,136,0,136,136,0,136,136,0,0,0
	};

};