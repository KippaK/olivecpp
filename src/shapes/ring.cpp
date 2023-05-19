#include "../../include/shapes/ring.h"

Ring::Ring(
    size_t aPosY,
    size_t aPosX,
    float aR,
    float aThickness,
    uint32_t aColor
    ) : Circle(aPosY, aPosX, aR, aColor)
{
    thickness = aThickness;
    if (aThickness > aR) {
        thickness = aR;
    }
}

Ring::~Ring() {}

void Ring::setThickness(float aThickness)
{
    thickness = aThickness;
    if (aThickness > r) {
        thickness = r;
    }
}

float Ring::getThickness() const
{
    return thickness;
}
