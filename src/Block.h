#pragma once
using namespace std;

class Block
{
public:
	int get_x() { return x; }
	int get_y() { return y; }
	int get_strength() { return strength; }
	virtual int* get_sprite() { return nullptr; };
	virtual int get_spriteSize() { return 7; };

protected:
	int x, y;
	int strength;
private:


};