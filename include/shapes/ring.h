#include "circle.h"

class Ring : public Circle
{
public:
    Ring(size_t aPosY, size_t aPosX, float aR, float aThickness, uint32_t aColor);
    ~Ring();

    void setThickness(float aThickness);
    float getThickness() const;

private:
    float thickness;
};