#pragma once

#include <stdint.h>
#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(size_t aPosY, size_t aPosX, size_t aHeight, size_t aWidth, uint32_t RGBA);
    ~Rectangle();

    size_t getHeight() const;
    size_t getWidth() const;

    void setHeight(size_t aHeight);
    void setWidth(size_t aWidth);
private:
    size_t height;
    size_t width;
};