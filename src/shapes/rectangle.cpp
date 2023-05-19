#include "../../include/shapes/rectangle.h"

Rectangle::Rectangle(
    size_t aPosY, 
    size_t aPosX, 
    size_t aHeight, 
    size_t aWidth, 
    uint32_t RGBA
) : Shape(aPosY, aPosX, RGBA)
{
    height = aHeight;
    width = aWidth;
}

Rectangle::~Rectangle() {}



size_t Rectangle::getHeight() const
{
    return height;
}

size_t Rectangle::getWidth() const
{
    return width;
}

void Rectangle::setHeight(size_t aHeight)
{
    height = aHeight;
}

void Rectangle::setWidth(size_t aWidth)
{
    width = aWidth;
}