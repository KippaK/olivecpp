#include "circle.h"

class Ring : public Circle
{
public:
    Ring(size_t aPosY, size_t aPosX, float aR, size_t aThickness, uint32_t aColor);
    ~Ring();

    void setThickness(size_t aThickness);
    size_t getThickness() const;

private:
    size_t thickness;
};