#include "../../include/shapes/line.h"

#include <cmath>

using std::abs;

Line::Line() {}

Line::Line(int aY1, int aX1, int aY2, int aX2, float aWidth, uint32_t aColor)
{
    y1 = aY1;
    x1 = aX1;
    y2 = aY2;
    x2 = aX2;
    width = abs(aWidth);
    color = aColor;
}

Line::~Line() {}

void Line::setY1(int aY1)
{
    y1 = aY1;
}

void Line::setX1(int aX1)
{
    x1 = aX1;
}

void Line::setY2(int aY2)
{
    y2 = aY2;

}

void Line::setX2(int aX2)
{
    y2 = aX2;
}

int Line::getY1() const
{
    return y1;
}

int Line::getX1() const
{
    return x1;
}

int Line::getY2() const
{
    return y2;
}

int Line::getX2() const
{
    return x2;
}
float Line::getWidth() const
{
    return width;
}
void Line::setWidth(float aWidth)
{
    width = abs(aWidth);
}

void Line::setColor(uint32_t aColor)
{
    color = aColor;
}

uint32_t Line::getColor() const
{
    return color;
}