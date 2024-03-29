#pragma once

#include "shapes/circle.h"
#include "shapes/rectangle.h"
#include "shapes/octagon.h"
#include "shapes/ring.h"
#include "shapes/line.h"
#include "shapes/triangle.h"

#include "utilities/color_definitions.h"

#include <stdint.h>
#include <stdlib.h>
#include <string>

using std::string;

class Canvas
{
public:
    Canvas(size_t aHeight, size_t aWidth);
    Canvas(size_t aHeight, size_t aWidth, uint32_t aColor);
    Canvas(string fileName);
    ~Canvas();

    void fill(uint32_t aColor);
    void draw(const Rectangle &aRectangle);
    void draw(const Circle &aCircle);
    void draw(const Octagon &aOctagon);
    void draw(const Ring &aRing);
    void draw(const Line &aLine);
    void draw(const Triangle &aTriangle);


    void saveToPPM(string file);
    void saveToPNG(string file);

private:
    inline bool pointInBounds(int y, int x) const;
    inline bool pointInsideRadius(int a, int b, float r) const;
    inline bool containsExtension(const string &file, const string &extension) const;

    void blendColor(uint32_t &base, uint32_t top);

    string getFileExtension(string fileName) const;

    void loadFromPPM(string fileName);

private:
    uint32_t *pixels;
    size_t height;
    size_t width;
};