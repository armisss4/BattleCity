#pragma once
#include "Block.h"
using namespace std;

class Metal : public Block
{
public:
	int* get_sprite();
	Metal(int x, int y)
	{
		this->x = x;
		this->y = y;
		this->strength = 1;
	}

protected:

private:
	int sprite[49] =
	{
		119,119,119,119,119,119,119,
		119,119,119,119,119,119,136,
		119,119,255,255,255,136,136,
		119,119,255,255,255,136,136,
		119,119,255,255,255,136,136,
		119,119,136,136,136,136,136,
		119,136,136,136,136,136,136
	};

};