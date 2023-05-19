#include "examples.h"

#include <cmath>

Example::Canvas::Canvas(
    size_t aHeight, 
    size_t aWidth, 
    uint32_t aColor
    ) : ::Canvas(aHeight, aWidth, aColor)
{}

void Example::Canvas::drawStopSign(int aPosY, int aPosX, size_t aSize)
{
    draw(Octagon(aPosY, aPosX, aSize, BLACK));
    draw(Octagon(aPosY, aPosX, aSize - 2, WHITE));
    draw(Octagon(aPosY, aPosX, aSize * 0.9, RED));
}

void Example::Canvas::drawSnowman(int aPosY, int aPosX, size_t aSize)
{
    size_t thickness = 2;
    int posY[3];
    int posX[3];
    posY[0] = aPosY - aSize / 4;
    posX[0] = aPosX;
    posY[1] = aPosY;
    posX[1] = aPosX;
    posY[2] = aPosY + aSize / 3;
    posX[2] = aPosX;

    for (int i = 0; i < 3; i++) {
        draw(Circle(
            posY[i],
            posX[i],
            aSize * (3+i) / 24,
            BLACK
        ));
    }
    for (int i = 0; i < 3; i++) {
        draw(Circle(
            posY[i], 
            posX[i],
            (aSize * (3+i) / 24) - thickness,
            WHITE
        ));
    }
    draw(Circle(
        posY[0] - ceil(aSize / 24),
        aPosX + (aSize / 24),
        ceil(aSize / 100),
        BLACK
    ));
    draw(Circle(
        posY[0] - ceil(aSize / 24),
        aPosX - (aSize / 24),
        ceil(aSize / 100),
        BLACK
    ));
    draw(Circle(
        posY[0],
        posX[0],
        aSize / 50,
        ORANGE
    ));
}

int ringPosY(int i, int posY, size_t ringRadius) {
    if (i % 2 == 0) { 
        return static_cast<int>(posY - ringRadius * 0.5); 
    }
    return static_cast<int>(posY + ringRadius * 0.5);
}

void Example::Canvas::drawOlympicRings(int aPosY, int aPosX, size_t aRingRadius)
{
    uint32_t colors[5] = {
        0x0085C7FF,
        0xF4C300FF,
        0x000000FF,
        0x009F3DFF,
        0xDF0024FF
    };
    for (int i = 0; i < 5; i++) {
        draw(Ring(
            ringPosY(i, aPosY, aRingRadius),
            aPosX + ( aRingRadius * 1.2 * (i - 2) ),
            aRingRadius,
            static_cast<int>(aRingRadius/10),
            colors[i]
        ));
    }
}
