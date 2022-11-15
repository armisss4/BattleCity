#include "Bullet.h"
#include <algorithm>
#include <iterator>
#include <cmath>
bool Bullet::action()
{
    if (!live)return true;
    if (scr->isNotBlank(x, y, dir)) {
        switch (dir)
        {
        case 0:
            y--;
            x1 = x + 1;
            y1 = y;
            break;
        case 1:
            x--;
            x1 = x;
            y1 = y + 1;
            break;
        case 2:
            y+=2;
            x1 = x + 1;
            y1 = y;
            break;
        case 3:
            x+=2;
            x1 = x;
            y1 = y + 1;
            break;
        }
        live = false;
        return true;
    }
    switch (dir)
    {
    case 0:
        subY-=2;
        break;
    case 1:
        subX-=2;
        break;
    case 2:
        subY+=2;
        break;
    case 3:
        subX+=2;
        break;
    }

    if (abs(subY) >= 7) {
        y += subY / 7; subY %= 7;
        //        if (scr->isNotBlank(x, y, dir)) {}
    }
    if (abs(subX) >= 7) {
        x += subX / 7; subX %= 7;
    }
    return false;

}

void Bullet::rotate()
{
        int temp[16];
        copy(sprite, sprite + 16, temp);

        for (int i = 0; i < 4; i++)
        {
            for (int ii = 0; ii < 4; ii++)
            {
                sprite[i + ii * 4] = temp[(3 - ii) + i * 4];
            }
        }

}
