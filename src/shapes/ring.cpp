#include "../../include/shapes/ring.h"

Ring::Ring(
    size_t aPosY,
    size_t aPosX,
    float aR,
    size_t aThickness,
    uint32_t aColor
    ) : Circle(aPosY, aPosX, aR, aColor)
{
    thickness = aThickness;
}

Ring::~Ring() {}

void Ring::setThickness(size_t aThickness)
{
    thickness = aThickness;
}

size_t Ring::getThickness() const
{
    return thickness;
}
