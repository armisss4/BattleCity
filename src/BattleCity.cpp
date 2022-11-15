#include "Screen.h"
#include "Brick.h"
#include "Tank.h"
#include "Player.h"
#include "Eagle.h"
#include "Metal.h"
#include "Block.h"
#include "Bot.h"
#include "Bullet.h"
#include <iostream>
#include <list>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>

using namespace std;
int sprite[] = { 0,0,0,1,0,1,0,0,1,1,1,1,1,0,1,0,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0 };
int colorList[] = { 0x11,0x66,0xDD };



int main()
{
	srand(time(NULL));
	Screen scr;
	vector <Block*> blocks;
	vector <Tank*> tanks;
	int state = -1;
	bool blockBroken = true;
	bool eagleDestroyed = false;

	while (state == -1)
	{
		state = scr.drawMenu();
	}
	if (state == 3)return 0;

	ifstream fin;
	fin.open("map.txt");
	for (int i = 0; i < 26; i++)
	{
		for (int ii = 0; ii < 26; ii++)
		{
			int type;
			if (!fin.eof()) {
				fin >> type;
				switch (type) {
				case 0: //empty
					break;
				case 1: //brick
					blocks.push_back(new Brick(ii, i));
					break;
				case 2: //metal
					blocks.push_back(new Metal(ii, i));
					break;
				case 10: //eagle
					blocks.push_back(new Eagle(ii, i));
					break;
				case 11: //playerSpawn
					tanks.push_back(new Player(ii, i, &scr));
					break;
				case 12: //botSpawn
					tanks.push_back(new Bot(ii, i, &scr));
					break;
				}
			}


		}

	}
	while (1) {

		if (blockBroken)
		{
			scr.clear();
			scr.drawRect(19, 202, 19, 202, 0xFF, 0xFF, false);
			for (auto block : blocks)
			{
				if (block->get_spriteSize() == 7) scr.drawSprite7x7(20 + block->get_x() * 7, 20 + block->get_y() * 7, block->get_sprite());
				else scr.drawSprite14x14(20 + block->get_x() * 7, 20 + block->get_y() * 7, block->get_sprite());
			}
			scr.updateCache();
			blockBroken = false;
		}
		else
		{
			scr.recallCache();
		}
		for (auto tank : tanks)
		{
			tank->action();
			scr.drawSprite14x14(20 + tank->get_x() * 7 + tank->get_subX(), 20 + tank->get_y() * 7 + tank->get_subY(), tank->get_sprite());
			/*if (tank->get_bullet() != NULL) {
				tank->get_bullet()->action();
				scr.drawBullet(25 + tank->get_bullet()->get_subX() + tank->get_bullet()->get_x() * 7, 25 + tank->get_bullet()->get_subY() + tank->get_bullet()->get_y() * 7, tank->get_bullet()->get_sprite());
			}*/
			//HITBOX                scr.drawRect(20 + tank->get_xTrue() * 7, 27 + tank->get_x1True()*7, 20 + tank->get_yTrue()*7, 27 + tank->get_y1True()*7, 0x44, 0x00, false);

		}
		for (auto tank : tanks)
		{
			if (tank->get_bullet() != NULL) {
				if (tank->get_bullet()->action())
				{
					for (auto it = blocks.begin(); it != blocks.end(); it++)
					{
						if ((*it)->get_strength() > 0) { continue; }
						else if ((*it)->get_strength() == -1)
						{
							if ((*it)->get_x() + 1 == tank->get_bullet()->get_x() && (*it)->get_y() == tank->get_bullet()->get_y())
							{
								eagleDestroyed = true;
								blocks.erase(it);
								blockBroken = true;
							}
							if ((*it)->get_x() + 1 == tank->get_bullet()->get_x() && (*it)->get_y() == tank->get_bullet()->get_y1())
							{
								eagleDestroyed = true;
								blocks.erase(it);
								blockBroken = true;
							}
						}

						if ((*it)->get_x() == tank->get_bullet()->get_x() && (*it)->get_y() == tank->get_bullet()->get_y())
						{
							if ((*it)->get_strength() == -1)eagleDestroyed = true;
							if (it != blocks.end()-1)blocks.erase(it);
							else {
								blocks.pop_back();
								it = blocks.end()-1;
							}
							blockBroken = true;
						}
						if ((*it)->get_x() == tank->get_bullet()->get_x1() && (*it)->get_y() == tank->get_bullet()->get_y1())
						{
							if (it != blocks.end()-1)blocks.erase(it);
							else {
								blocks.pop_back();
								it = blocks.end()-1;
							}
							blockBroken = true;
						}
					}

					for (auto it = tanks.begin(); it != tanks.end(); it++)
					{
						if ((*it)->isBot() && tank->get_bullet()->isFriendly())continue;
						if ((*it)->get_xTrue() <= tank->get_bullet()->get_x() &&
							(*it)->get_x1True() >= tank->get_bullet()->get_x() &&
							(*it)->get_yTrue() <= tank->get_bullet()->get_y() &&
							(*it)->get_y1True() >= tank->get_bullet()->get_y()) {
							if ((*it)->get_lives() > 0)(*it)->kill();
							else it = tanks.erase(it);
							continue;
						}
						if ((*it)->get_xTrue() <= tank->get_bullet()->get_x1() &&
							(*it)->get_x1True() >= tank->get_bullet()->get_x1() &&
							(*it)->get_yTrue() <= tank->get_bullet()->get_y1() &&
							(*it)->get_y1True() >= tank->get_bullet()->get_y1()) {
							if ((*it)->get_lives() > 0)(*it)->kill();
							else it = tanks.erase(it);
							continue;
						}
					}

					tank->destroy_bullet();
				}
				else scr.drawBullet(25 + tank->get_bullet()->get_subX() + tank->get_bullet()->get_x() * 7, 25 + tank->get_bullet()->get_subY() + tank->get_bullet()->get_y() * 7, tank->get_bullet()->get_sprite());

			}
		}

		int count = 0;
		int lives = 0;
		for (auto tank : tanks)
		{
			if (tank->isBot())count += tank->get_lives() + 1;
			if (!tank->isBot())lives = tank->get_lives() + 1;
		}
		scr.drawString("ENEMIES", 222, 50, 0xFF, 0, 0);
		scr.drawString(to_string(count), 222, 60, 0xFF, 0, 0);
		scr.drawString("LIVES", 222, 150, 0xFF, 0, 0);
		scr.drawString(to_string(lives), 222, 160, 0xFF, 0, 0);


		scr.draw();
		if (count == 0) {
			scr.clear();
			scr.drawRect(19, 202, 19, 202, 0xFF, 0xFF, false);
			scr.drawString("YOU WIN", 88, 110, 0xFF, 0, 0);
			scr.draw();
			break;
		}
		if (lives == 0)
		{
			scr.clear();
			scr.drawRect(19, 202, 19, 202, 0xFF, 0xFF, false);
			scr.drawString("YOU LOSE", 82, 110, 0xFF, 0, 0);
			scr.draw();
			break;
		}
		if (eagleDestroyed)
		{
			scr.clear();
			scr.drawRect(19, 202, 19, 202, 0xFF, 0xFF, false);
			scr.drawString("YOU LOSE", 82, 110, 0xFF, 0, 0);
			scr.draw();
			break;
		}
	}

	return 0;
}
