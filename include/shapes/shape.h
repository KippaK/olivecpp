#pragma once

#include <stdint.h>

class Shape
{
public:

    Shape(int aPosY, int aPosX, uint32_t RGBA);
    ~Shape();

    int getPosY() const ;
    int getPosX() const ;
    uint32_t getColor() const;

    void setPosY(int aPosY);
    void setPosX(int aPosX);
    void setColor(uint32_t aColor);

protected:
    int posX;
    int posY;
    uint32_t color;
};