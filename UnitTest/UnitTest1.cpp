#include "pch.h"
#include "CppUnitTest.h"
#include "../BattleCity/Tank.h"
#include "../BattleCity/Brick.h"
#include "../BattleCity/Brick.cpp"
#include "../BattleCity/Metal.h"
#include "../BattleCity/Metal.cpp"
#include "../BattleCity/Eagle.h"
#include "../BattleCity/Eagle.cpp"
#include "../BattleCity/Block.h"

//#include "../BattleCity/Tank.cpp"

#include <vector>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TankColorChange)
		{
			Tank *tank = new Tank();
			auto sprite = tank->get_sprite();
			vector <int> indexes;
			for (int i = 0; i < 196; i++) {
				if (sprite[i] == -1)indexes.push_back(i);
			}
			for (int index : indexes)
			{
				Assert::AreEqual(tank->get_sprite()[index], -1);
			}

			tank->set_color(66);
			for (int index : indexes)
			{
				Assert::AreEqual(tank->get_sprite()[index], 66);
			}

		}

		TEST_METHOD(BlockStrengthAndSize)
		{
			Block *block = new Brick(0, 0);
			Assert::AreEqual(block->get_strength(),0);
			Assert::AreEqual(block->get_spriteSize(), 7);

			block = new Metal(0, 0);
			Assert::AreEqual(block->get_strength(), 1);
			Assert::AreEqual(block->get_spriteSize(), 7);

			block = new Eagle(0, 0);
			Assert::AreEqual(block->get_strength(), -1);
			Assert::AreEqual(block->get_spriteSize(), 14);

		}

		TEST_METHOD(TankRotate)
		{
			Tank* tank = new Tank();
			auto sprite = tank->get_sprite();
			vector <int> colorsTop;
			vector <int> colorsBottom;

			for (int i = 0; i < 14; i++) {
				colorsTop.push_back(sprite[i]);
				colorsBottom.push_back(sprite[i+182]);

			}
			tank->rotate(); 
			sprite = tank->get_sprite();
			int temp = 0;
			for (int i = 0; i < 14; i++) {
				Assert::AreEqual(sprite[temp], colorsTop[i]);
				Assert::AreEqual(sprite[temp+13], colorsBottom[i]);

				temp += 14;
			}


		}
	};
}
