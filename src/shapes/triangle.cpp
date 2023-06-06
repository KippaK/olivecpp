#include "../../include/shapes/triangle.h"

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