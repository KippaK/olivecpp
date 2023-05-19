#include "../include/canvas.h"

#include <stdlib.h>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <algorithm>

using std::string;
using std::abs;
using std::pow;
using std::sqrt;
using std::min;
using std::max;
using std::swap;

#define sqrt2 1.41421356

bool Canvas::pythagoreanCheck(int a, int b, float c) const {
    if (a * a + b * b > c * c) { return false; }
    return true;
}

bool Canvas::containsExtension(const std::string& file) const {
    size_t dotPos = file.rfind('.');
    return (dotPos != std::string::npos && dotPos != file.length() - 1);
}

Canvas::Canvas(size_t aHeight, size_t aWidth)
{
    Canvas(aHeight, aWidth, 0x000000FF);
}

Canvas::Canvas(size_t aHeight, size_t aWidth, uint32_t aColor)
{
    height = aHeight;
    width = aWidth;
    pixels = new uint32_t[height * width];
    fill(aColor);
}

Canvas::~Canvas() {}

void Canvas::fill(uint32_t aColor)
{
    for (int i = 0; i < height * width; i++) {
        pixels[i] = aColor;
    }
}

void Canvas::saveToPPM(string fileName)
{
    FILE *file = NULL;
    {
        file = fopen(fileName.c_str(), "wb");
        if (file == NULL) { return; }

        fprintf(file, "P6\n%zu %zu 255\n", width, height);
        if (ferror(file)) { return; }

        for (size_t i = 0; i < width * height; i++) {
            uint32_t pixel = pixels[i];
            uint8_t bytes[3] = {
                (pixel>>(8*3))&0xFF,
                (pixel>>(8*2))&0xFF,
                (pixel>>(8*1))&0xFF
            };
            fwrite(bytes, sizeof(bytes), 1, file);
            if (ferror(file)) { return; }
        }
    }
    return;
}
bool Canvas::pointInBounds(int y, int x) const
{
    return 0 <= x && x < width && 0 <= y && y < height;
}

void Canvas::draw(const Rectangle &aRectangle)
{ 
    int x1 = aRectangle.getPosX() - (int) aRectangle.getWidth();
    int x2 = aRectangle.getPosX() + (int) aRectangle.getWidth();
    int y1 = aRectangle.getPosY() - (int) aRectangle.getHeight();
    int y2 = aRectangle.getPosY() + (int) aRectangle.getHeight();
    
    for (int y = y1; y <= y2; y++) 
    {
        if (y < 0 || y >= height) { continue; }
        for (int x = x1; x <= x2; x++)
        {
            if (x < 0 || x >= width) { continue; }
            pixels[y * width + x] = aRectangle.getColor();
        }
    }
}

void Canvas::draw(const Circle &aCircle)
{
    int x1 = aCircle.getPosX() - (int) aCircle.getRadius();
    int x2 = aCircle.getPosX() + (int) aCircle.getRadius();
    int y1 = aCircle.getPosY() - (int) aCircle.getRadius();
    int y2 = aCircle.getPosY() + (int) aCircle.getRadius();

    for (int y = y1; y <= y2; y++) 
    {
        if (y < 0 || y >= height) { continue; }
        for (int x = x1; x <= x2; x++)
        {
            if (x < 0 || x >= width) { continue; }
            if (pixels[y*width+x] == aCircle.getColor()) { continue; }
            int dx = abs(x - aCircle.getPosX());
            int dy = abs(y - aCircle.getPosY()); 
            if (pythagoreanCheck(dy, dx, (int) aCircle.getRadius())) {
                pixels[y * width + x] = aCircle.getColor();
            }
        }
    }
}

void Canvas::draw(const Ring &aRing)
{
    int x1 = aRing.getPosX() - ceil(aRing.getRadius());
    int x2 = aRing.getPosX() + ceil(aRing.getRadius());
    int y1 = aRing.getPosY() - ceil(aRing.getRadius());
    int y2 = aRing.getPosY() + ceil(aRing.getRadius());

    for (int y = y1; y <= y2; y++) 
    {
        if (y < 0 || y >= height) { continue; }
        for (int x = x1; x <= x2; x++)
        {
            if (x < 0 || x >= width) { continue; }
            if (pixels[y*width+x] == aRing.getColor()) { continue; }
            int dx = abs(x - aRing.getPosX());
            int dy = abs(y - aRing.getPosY());
            float radius = aRing.getRadius();
            float thickness = aRing.getThickness();
            bool insideOuterEdge = pythagoreanCheck(dy, dx, radius);
            bool insideInnerEdge = pythagoreanCheck(dy, dx, radius - thickness);
            if (insideOuterEdge && !insideInnerEdge) {
                pixels[y * width + x] = aRing.getColor();
            }
        }
    }
}

void Canvas::draw(const Octagon &aOctagon)
{
    int x1 = aOctagon.getPosX() - (int) floor(aOctagon.getSize() / 2);
    int x2 = aOctagon.getPosX() + (int) ceil(aOctagon.getSize() / 2);
    int y1 = aOctagon.getPosY() - (int) floor(aOctagon.getSize() / 2);
    int y2 = aOctagon.getPosY() + (int) ceil(aOctagon.getSize() / 2);

    for (int y = y1; y <= y2; y++) 
    {
        if (y < 0 || y >= height) { continue; }
        for (int x = x1; x <= x2; x++)
        {
            if (x < 0 || x >= width) { continue; }
            int dy = abs(aOctagon.getPosY() - y);
            int dx = abs(aOctagon.getPosX() - x);
            if (dy + dx <= aOctagon.getSize() / 2 * sqrt2) {
                pixels[y * width + x] = aOctagon.getColor();
            }
        }
    }
}


#define ENABLE_CUSTOM_LINE_DRAW 1
// Mostly copied from the olive.c library, don't fully know how it works
// Doesn't take into consideration the width of a line.
#if !ENABLE_CUSTOM_LINE_DRAW
void Canvas::draw(const Line &aLine)
{
    int x1 = aLine.getX1();
    int x2 = aLine.getX2();
    int y1 = aLine.getY1();
    int y2 = aLine.getY2();
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (dx == 0 && dy == 0) {
        draw(Circle(y1, x1, aLine.getWidth() / 2, aLine.getColor()));
    }
    if (abs(dx) > abs(dy)) {
        if (x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
        }

        for (int x = x1; x <= x2; ++x) {
            int y = dy*(x - x1)/dx + y1;
            if (pointInBounds(y, x)) {
                pixels[y*width+x] = aLine.getColor();
            }
        }
    } else {
        if (y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
        }

        for (int y = y1; y <= y2; ++y) {
            int x = dx*(y - y1)/dy + x1;
            if (pointInBounds(y, x)) {
                pixels[y*width+x] = aLine.getColor();
            }
        }
    }
}
#elif ENABLE_CUSTOM_LINE_DRAW
void Canvas::draw(const Line &aLine)
{
    int x1 = aLine.getX1();
    int x2 = aLine.getX2();
    int y1 = aLine.getY1();
    int y2 = aLine.getY2();
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (dx == 0 && dy == 0) {
        draw(Circle(y1, x1, aLine.getWidth() / 2, aLine.getColor()));
    }
    if (abs(dx) > abs(dy)) {
        if (x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
        }

        for (int x = x1; x <= x2; ++x) {
            int y = dy*(x - x1)/dx + y1;
            if (pointInBounds(y, x)) {
                draw(Circle(y, x, aLine.getWidth() / 2, aLine.getColor()));
            }
        }
    } else {
        if (y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
        }

        for (int y = y1; y <= y2; ++y) {
            int x = dx*(y - y1)/dy + x1;
            if (pointInBounds(y, x)) {
                draw(Circle(y, x, aLine.getWidth() / 2, aLine.getColor()));
            }
        }
    }
}
#endif