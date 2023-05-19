#pragma once

#include <stdint.h>

class Shape
{
public:

    Shape(int aPosY, int aPosX, uint32_t RGBA);
    Shape(int aPosY, int aPosX, uint32_t RGBA1, uint32_t RGBA2);
    ~Shape();

    int getPosY() const ;
    int getPosX() const ;
    uint32_t getColor() const;
    uint32_t getColor(float gradientPos) const; // TODO

    void setPosY(int aPosY);
    void setPosX(int aPosX);
    void setColor(uint32_t aColor);
    void setColor(uint32_t aColor1, uint32_t aColor2);

private: 

struct Gradient
{
    uint32_t color1;
    uint32_t color2;
};

protected:
    int posX;
    int posY;
    uint32_t color;
    Gradient gradient;
};