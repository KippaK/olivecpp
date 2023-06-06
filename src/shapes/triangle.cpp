#include "../../include/shapes/triangle.h"
#include <cmath>
#include <algorithm>

using std::abs;
using std::min;
using std::max;

Triangle::Triangle()
{
    x1 = 0;
    y1 = 0;
    x2 = 0;
    y2 = 0;
    x3 = 0;
    y3 = 0;
    color = 0x00000000;
}

Triangle::Triangle(int aX1, int aY1, int aX2, int aY2, int aX3, int aY3, uint32_t aColor)
{
    x1 = aX1;
    y1 = aY1;
    x2 = aX2;
    y2 = aY2;
    x3 = aX3;
    y3 = aY3;
    color = aColor;
}

Triangle::~Triangle()
{
}

float Triangle::area(int x1, int y1, int x2, int y2, int x3, int y3) const
{
    return abs(x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2));
}

bool Triangle::pointIsInside(int x, int y) const
{
   const float A = area(x1, y1, x2, y2, x3, y3);
   const float A1 = area(x, y, x2, y2, x3, y3);
   const float A2 = area(x1, y1, x, y, x3, y3);
   const float A3 = area(x1, y1, x2, y2, x, y);
   return (A == A1 + A2 + A3);
}

int Triangle::getMinX() const
{
    return min(min(x1, x2), x3);
}

int Triangle::getMinY() const
{
    return min(min(y1, y2), y3);
}

int Triangle::getMaxX() const
{
    return max(max(x1, x2), x3);
}

int Triangle::getMaxY() const
{
    return max(max(y1, y2), y3);
}


int Triangle::getX1() const
{
    return x1;
}

void Triangle::setX1(int aX1)
{
    x1 = aX1;
}

int Triangle::getY1() const
{
    return y1;
}

void Triangle::setY1(int aY1)
{
    y1 = aY1;
}

int Triangle::getX2() const
{
    return x2;
}

void Triangle::setX2(int aX2)
{
    x2 = aX2;
}

int Triangle::getY2() const
{
    return y2;
}

void Triangle::setY2(int aY2)
{
    y2 = aY2;
}

int Triangle::getX3() const
{
    return x3;
}

void Triangle::setX3(int aX3)
{
    x3 = aX3;
}

int Triangle::getY3() const
{
    return y3;
}

void Triangle::setY3(int aY3)
{
    y3 = aY3;
}

uint32_t Triangle::getColor() const
{
    return color;
}

void Triangle::setColor(uint32_t aColor)
{
    color = aColor;
}