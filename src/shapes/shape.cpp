#include "../../include/shapes/shape.h"

Shape::Shape(int aPosY, int aPosX, uint32_t RGBA)
{
    posX = aPosX;
    posY = aPosY;
    color = RGBA;
}

Shape::~Shape(){}

int Shape::getPosY() const
{
    return posY;
}

int Shape::getPosX() const
{
    return posX;
}

uint32_t Shape::getColor() const
{
    return color;
}

void Shape::setPosY(int aPosY)
{
    posY = aPosY;
}

void Shape::setPosX(int aPosX)
{
    posX = aPosX;
}

void Shape::setColor(uint32_t aColor)
{
    color = aColor;
}
