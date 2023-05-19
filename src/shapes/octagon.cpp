#include "../../include/shapes/octagon.h"

Octagon::Octagon(
    size_t aPosY, 
    size_t aPosX, 
    size_t aSize,  
    uint32_t RGBA
    ) : Shape(aPosY, aPosX, RGBA)
{
    size = aSize;
}

Octagon::~Octagon()
{}

void Octagon::setSize(size_t aSize)
{
    size = aSize;
}

size_t Octagon::getSize() const
{
    return size;
}