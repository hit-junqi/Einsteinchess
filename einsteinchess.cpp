#include "Einsteinchess.h"
Einsteinchess::Einsteinchess(){};
Einsteinchess::~Einsteinchess(){};
QString Einsteinchess::name()
{
    switch(this->id)
    {
    case 0:
        return "1";
    case 1:
        return "2";
    case 2:
        return "3";
    case 3:
        return "4";
    case 4:
        return "5";
    case 5:
        return "6";
    case 6:
        return "1";
    case 7:
        return "2";
    case 8:
        return "3";
    case 9:
        return "4";
    case 10:
        return "5";
    case 11:
        return "6";
    }
   return "错误";
}
void Einsteinchess::begin(int id)
{
    struct
    {
        int row, col;
    }
    a[12] =
    {
    {0, 0},
    {0, 1},
    {0, 2},
    {1, 0},
    {1, 1},
    {2, 0},
    {4, 2},
    {4, 3},
    {4, 4},
    {3, 3},
    {3, 4},
    {2, 4}
    };
    this->x=a[id].row;
    this->y=a[id].col;
    this->dead = false;
}
