#include "../../include/shapes/shape.h"

Shape::Shape(int aPosY, int aPosX, uint32_t RGBA)
{
    posX = aPosX;
    posY = aPosY;
    color = RGBA;
    gradient.color1 = RGBA;
    gradient.color2 = RGBA;
}

Shape::Shape(int aPosY, int aPosX, uint32_t RGBA1, uint32_t RGBA2)
{
    posX = aPosX;
    posY = aPosY;
    gradient.color1 = RGBA1;
    gradient.color2 = RGBA2;
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

uint32_t Shape::getColor(float gradientPos) const
{
    uint8_t c1[3] = {
        // TODO
    };
    uint8_t c1[3] = {
        // TODO
    };
    int16_t cd[3] = {
        // TODO
    };
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

void Shape::setColor(uint32_t aColor1, uint32_t aColor2)
{
    gradient.color1 = aColor1;
    gradient.color2 = aColor2;
}