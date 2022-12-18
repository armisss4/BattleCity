#include "Screen.h"
#include <windows.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <string>

#include <algorithm>
#include <math.h>
#include <iterator>




Screen::Screen()
{
	screenBuf = new CHAR_INFO[screenWidth * screenHeight];
	screenBufCache = new CHAR_INFO[screenWidth * screenHeight];

	memset(screenBuf, 0, sizeof(CHAR_INFO) * screenWidth * screenHeight);
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleInput = GetStdHandle(STD_INPUT_HANDLE);
	window = { 0,0,1,1 };
	COORD coord = { (short)screenWidth, (short)screenHeight };
	CONSOLE_FONT_INFOEX cfi;
	cfi.dwFontSize.X = symbolWidth;
	cfi.dwFontSize.Y = symbolHeight;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

	SetConsoleScreenBufferSize(console, coord);
	SetConsoleActiveScreenBuffer(console);
	SetCurrentConsoleFontEx(console, false, &cfi);
	window = { 0,0,(short)screenWidth - 1, (short)screenHeight - 1 };
	SetConsoleWindowInfo(console, true, &window);
	SetConsoleWindowInfo(console, true, &window);
	SetConsoleWindowInfo(console, true, &window);
	SetConsoleTitle(L"Battle City - FPS:");

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(console, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(console, &cursorInfo);

	DWORD prev_mode;
	GetConsoleMode(consoleInput, &prev_mode);
	SetConsoleMode(consoleInput, ENABLE_EXTENDED_FLAGS |
		(prev_mode & ~ENABLE_QUICK_EDIT_MODE));

	consoleWindow = GetConsoleWindow();
	std::ios_base::sync_with_stdio(false);

}

void Screen::clear()
{
	memset(screenBuf, 0, sizeof(CHAR_INFO) * screenWidth * screenHeight);

//	for (int i = 0; i < screenWidth * screenHeight; i++) {
//		screenBuf[i].Char.UnicodeChar = pixel_clear;
//		screenBuf[i].Attributes = 0x00;
//	}
}

void Screen::updateCache()
{
	memcpy(screenBufCache, screenBuf, sizeof(CHAR_INFO) * screenWidth * screenHeight);
}

void Screen::recallCache()
{
	memcpy(screenBuf, screenBufCache, sizeof(CHAR_INFO) * screenWidth * screenHeight);

}



void Screen::drawLine(int x1, int x2, int y1, int y2, int color, int pixel) //Bresenham
{
	//int x1 = test.get_x(0).first, x2 = test.get_x(0).second, y1 = test.get_y(0).first, y2 = test.get_y(0).second;
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1; dy = y2 - y1;

	if (dx == 0) //vertical
	{
		if (y2 < y1) std::swap(y1, y2);
		for (y = y1; y <= y2; y++) { screenBuf[x1 + (y * screenWidth)].Char.UnicodeChar = pixel; screenBuf[x1 + (y * screenWidth)].Attributes = color; }
		return;
	}

	if (dy == 0) //horizontal
	{
		if (x2 < x1) std::swap(x1, x2);
		for (x = x1; x <= x2; x++) { screenBuf[x + (y1 * screenWidth)].Char.UnicodeChar = pixel;  screenBuf[x + (y1 * screenWidth)].Attributes = color; }
		return;
	}

	dx1 = abs(dx); dy1 = abs(dy);
	px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1; y = y1; xe = x2;
		}
		else
		{
			x = x2; y = y2; xe = x1;
		}

		screenBuf[x + (y * screenWidth)].Char.UnicodeChar = pixel;
		screenBuf[x + (y * screenWidth)].Attributes = color;

		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0)
				px = px + 2 * dy1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
				px = px + 2 * (dy1 - dx1);
			}
			screenBuf[x + (y * screenWidth)].Char.UnicodeChar = pixel;
			screenBuf[x + (y * screenWidth)].Attributes = color;
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1; y = y1; ye = y2;
		}
		else
		{
			x = x2; y = y2; ye = y1;
		}

		screenBuf[x + (y * screenWidth)].Char.UnicodeChar = pixel;
		screenBuf[x + (y * screenWidth)].Attributes = color;

		for (i = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0)
				py = py + 2 * dx1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
				py = py + 2 * (dx1 - dy1);
			}
			screenBuf[x + (y * screenWidth)].Char.UnicodeChar = pixel;
			screenBuf[x + (y * screenWidth)].Attributes = color;
		}
	}

}

void Screen::fillShape(int x, int y, int color, int pixel)
{
	screenBuf[x + (y * screenWidth)].Attributes = color;
	screenBuf[x + (y * screenWidth)].Char.UnicodeChar = pixel;
	for (int i = 0; i < screenWidth; i++)
	{
		for (int ii = 0; ii < screenHeight; ii++)
		{
			if (screenBuf[i + 1 + (ii * screenWidth)].Attributes == color or
				screenBuf[i - 1 + (ii * screenWidth)].Attributes == color or
				screenBuf[i + ((ii + 1) * screenWidth)].Attributes == color or
				screenBuf[i + ((ii - 1) * screenWidth)].Attributes == color)
			{
				if (screenBuf[i + (ii * screenWidth)].Attributes != 0x00 && screenBuf[i + (ii * screenWidth)].Attributes != 0x70 && screenBuf[i + (ii * screenWidth)].Attributes != color)
				{
					screenBuf[i + (ii * screenWidth)].Attributes = color;
					screenBuf[i + (ii * screenWidth)].Char.UnicodeChar = pixel;
					if (ii > 0)ii--;
					if (i > 0)i--;
				}
			}
		}
	}
}


void Screen::drawSprite7x7(int x, int y, int sprite[])
{
	//x -= 3;
	//y -= 3;
	for (int i = x; i < x + 7; i++)
	{
		for (int ii = y; ii < y + 7; ii++)
		{

				screenBuf[ii * screenWidth + i].Char.UnicodeChar = pixel_full;
				screenBuf[ii * screenWidth + i].Attributes = sprite[int((i - x) + (ii - y) * 7)];

		}
	}
}

void Screen::drawSprite14x14(int x, int y, int sprite[])
{
	//x -= 3;
	//y -= 3;
	for (int i = x; i < x + 14; i++)
	{
		for (int ii = y; ii < y + 14; ii++)
		{

			screenBuf[ii * screenWidth + i].Char.UnicodeChar = pixel_full;
			screenBuf[ii * screenWidth + i].Attributes = sprite[int((i - x) + (ii - y) * 14)];

		}
	}
}

void Screen::drawBullet(int x, int y, int sprite[])
{
	for (int i = x; i < x + 4; i++)
	{
		for (int ii = y; ii < y + 4; ii++)
		{

			screenBuf[ii * screenWidth + i].Char.UnicodeChar = pixel_full;
			screenBuf[ii * screenWidth + i].Attributes = sprite[int((i - x) + (ii - y) * 4)];

		}
	}
}

void Screen::drawLetter5x5(int letter, int x, int y, int color, bool highVisibility)
{
	int temp;
	for (int i = 0; i < 5; i++)
	{
		temp = 1;
		for (int ii = 0; ii < 6; ii++)
		{
			if (temp & alphabet[letter][i])
			{
				screenBuf[(x + ii) + (screenWidth * (y + i))].Char.UnicodeChar = pixel_full;
				screenBuf[(x + ii) + (screenWidth * (y + i))].Attributes = color;
			}
			else if (highVisibility)
			{
				screenBuf[(x + ii) + (screenWidth * (y + i))].Char.UnicodeChar = pixel_full;
				screenBuf[(x + ii) + (screenWidth * (y + i))].Attributes = 0x00;
			}
			temp = temp << 1;
		}
	}

}

void Screen::drawString(std::string text, int x, int y, int color, int highVisibility, int border)
{
	for (int i = 0; i < text.length(); i++)
	{
		drawLetter5x5(text[i], x + (6 * i), y, color, highVisibility);
	}
	for (int i = 1; i <= border; i++)
	{
		drawLine(x - i, x + (text.length() * 6 + i) - 2, y - i, y - i, 0x00, pixel_full);
		drawLine(x - i, x + (text.length() * 6 + i) - 2, y + 4 + i, y + 4 + i, 0x00, pixel_full);
		drawLine(x - i, x - i, y - i, y + 4 + i, 0x00, pixel_full);
		drawLine(x + (text.length() * 6 + i) - 2, x + (text.length() * 6 + i) - 2, y - i, y + 4 + i, 0x00, pixel_full);
	}

}

void Screen::draw()
{
	WriteConsoleOutput(console, screenBuf, { (short)screenWidth, (short)screenHeight }, { 0,0 }, &window);
	
	updateTitle();

}



void Screen::updateTitle()
{
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::string title1 = "Battle City - FPS = ";

	title1 += std::to_string(int(1 / (double(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000)));

	std::wstring stemp = std::wstring(title1.begin(), title1.end());
	LPCWSTR sw = stemp.c_str();
	SetConsoleTitle(sw);
	begin = std::chrono::steady_clock::now();
}

bool Screen::isNotBlank(int x, int y, int dir)
{
	for (int ii = 0; ii < 7; ii++) {
		switch (dir)
		{
		case 0: //W
			for (int i = 0; i < 14; i++)
			{
				//screenBuf[20 + (x * 7) + i + (screenWidth * (19 - ii + (y * 7)))].Attributes = 0x11;
				if (screenBuf[20 + (x * 7) + i + (screenWidth * (19-ii + (y * 7)))].Attributes != 0x00)return true;
			}
			break;
		case 1: //A
			for (int i = 0; i < 14; i++)
			{
				//screenBuf[19 - ii + ((x) * 7) + (screenWidth * (20 + i + ((y) * 7)))].Attributes = 0x11;
				if (screenBuf[19-ii + ((x) * 7) + (screenWidth * (20 + i + ((y) * 7)))].Attributes != 0x00)return true;
			}
			break;
		case 2: //S
			for (int i = 0; i < 14; i++)
			{
				//screenBuf[20 + (x * 7) + i + (screenWidth * (20 + ii + ((y + 2) * 7)))].Attributes = 0x11;
				if (screenBuf[20 + (x * 7) + i + (screenWidth * (20+ii + ((y + 2) * 7)))].Attributes != 0x00)return true;
			}
			break;
		case 3: //D
			for (int i = 0; i < 14; i++)
			{
				//screenBuf[20 + ii + ((x + 2) * 7) + (screenWidth * (20 + i + ((y) * 7)))].Attributes = 0x11;
				if (screenBuf[20+ii + ((x + 2) * 7) + (screenWidth * (20 + i + ((y) * 7)))].Attributes != 0x00)return true;
			}
			break;
		}
	}

	return false;
}

int Screen::drawMenu()
{
	clear();
	fillShape(50, 50, 0x00, pixel_full);
	drawString("BATTLE CITY", screenWidth / 2 - 5 * 6, screenHeight / 2 - 10 * 6, 0xFF, 1, 5);
	drawString("PLAY", screenWidth / 2 - 2 * 6, screenHeight / 2, 0xFF, 1, 5);
	//drawString("EDIT", screenWidth / 2 - 2 * 6, screenHeight / 2 + 5 * 6, 0xFF, 1, 5);
	drawString("EXIT", screenWidth / 2 - 2 * 6, screenHeight / 2 + 10 * 6, 0xFF, 1, 5);

	POINT p;
	if (GetCursorPos(&p))
	{
		if (ScreenToClient(consoleWindow, &p))
		{
			if (p.x > 0 && p.x < screenWidth * (symbolWidth-1) && p.y>0 && p.y < screenHeight * symbolHeight)
			{
				if (p.x >= (screenWidth / 2 - 3 * 6) * (symbolWidth-1) && p.x <= (screenWidth / 2 + 3 * 6) * (symbolWidth-1))
				{
					if (p.y >= (screenHeight / 2 - 6) * symbolHeight && p.y <= (screenHeight / 2 + 12) * symbolHeight)
					{
						drawString("PLAY", screenWidth / 2 - 2 * 6, screenHeight / 2, 0xAA, 1, 5);
						if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0)return 1;
					}
				/*	if (p.y >= (screenHeight / 2 + 4 * 6) * symbolHeight && p.y <= (screenHeight / 2 + 7 * 6) * symbolHeight)
					{
						drawString("EDIT", screenWidth / 2 - 2 * 6, screenHeight / 2 + 5 * 6, 0xAA, 1, 5);
						if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0)return 2;
					}*/
					if (p.y >= (screenHeight / 2 + 9 * 6) * symbolHeight && p.y <= (screenHeight / 2 + 12 * 6) * symbolHeight)
					{
						drawString("EXIT", screenWidth / 2 - 2 * 6, screenHeight / 2 + 10 * 6, 0xAA, 1, 5);
						if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0)return 3;
					}

				}
			}
		}
	}

	draw();
	return -1;
}

void Screen::drawRect(int x1, int x2, int y1, int y2, int color, int fill, bool drawFill)
{
	drawLine(x1, x1, y1, y2, color, pixel_full);
	drawLine(x2, x2, y1, y2, color, pixel_full);
	drawLine(x1, x2, y1, y1, color, pixel_full);
	drawLine(x1, x2, y2, y2, color, pixel_full);
	if (drawFill)fillShape(x1 + 1, y1 + 1, fill, pixel_full);
}

Screen *Screen::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Screen();
	}
	return instance;
}

