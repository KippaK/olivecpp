#include "../../include/shapes/circle.h"

#include <cmath>

using std::abs;

Circle::Circle(
    size_t aPosY, 
    size_t aPosX, 
    float aR, 
    uint32_t aColor
) : Shape(aPosY, aPosX, aColor)
{
    r = abs(aR);
}

Circle::~Circle() {}

float Circle::getRadius() const
{
    return r;
}

void Circle::setR(float aR)
{
    r = abs(aR);
}
