#pragma once

#include "shape.h"
#include <stdlib.h>

class Circle : public Shape
{
public:
    Circle(size_t aPosY, size_t aPosX, float aR, uint32_t aColor);
    ~Circle();

    float getRadius() const;

    void setR(float aR);

protected:
    float r;
};