#include "shape.h"

class Octagon : public Shape
{
public:
    Octagon(size_t aPosY, size_t aPosX, size_t aSize, uint32_t RGBA);
    ~Octagon();

    void setSize(size_t aSize);
    size_t getSize() const;

private:
    size_t size;
};
