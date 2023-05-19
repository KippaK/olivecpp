#include "include/canvas.h"

namespace Example
{
    class Canvas : public ::Canvas
    {
    public:
        Canvas(size_t aHeight, size_t aWidth, uint32_t aColor);
        ~Canvas();
        void drawStopSign(int aPosY, int aPosX, size_t aSize);
        void drawSnowman(int aPosY, int aPosX, size_t aSize);
        void drawOlympicRings(int aPosY, int aPosX, size_t aRingSize);
    };
}
