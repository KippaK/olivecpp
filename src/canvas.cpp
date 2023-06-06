#include "../include/canvas.h"

#include "lodepng.h"

#include <stdlib.h>
#include <cstdio>
#include <cstring>

#include <string>
using std::string;

#include <cmath>
using std::abs;
using std::pow;
using std::sqrt;
using std::min;
using std::max;

#include <fstream>
using std::ifstream;

#include <algorithm>
using std::swap;

#include <vector>
using std::vector;

#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include <exception>
using std::exception;
using std::runtime_error;


#define sqrt2 1.41421356

inline bool Canvas::pointInsideRadius(int a, int b, float r) const {
    if (a * a + b * b > r * r) { return false; }
    return true;
}

inline bool Canvas::containsExtension(const string &file, const string &extension) const {
    return (file.rfind(extension) != std::string::npos && file.rfind(extension) != file.length() - 1);
}

string Canvas::getFileExtension(string fileName) const
{
    if (fileName.rfind('.') == string::npos) { return ""; }
    uint16_t extPos = fileName.rfind('.') + 1;
    return fileName.substr(extPos, fileName.length() - extPos);
}

void Canvas::loadFromPPM(string fileName)
{
    ifstream file(fileName, std::ios::binary);
    if (!file) {
        throw runtime_error("ERROR: Could not open file " + fileName);
    }
    string format;
    size_t maxColorValue;
    file >> format >> width >> height >> maxColorValue;
    if (format != "P6") {
        throw runtime_error("ERROR: Unsupported PPM format");
    }
    if (maxColorValue != 255) {
        throw runtime_error("ERROR: Unsupported PPM color depth");
    }
    pixels = new uint32_t[width * height];
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    uint8_t bytes[3];
    for (size_t i = 0; i < width * height; ++i)
    {
        for (int j = 0; j < 3; j++) { file >> bytes[j]; } 
        for (int j = 0; j < 3; j++) {
            pixels[i] = pixels[i]<<8 | bytes[j];
        }
        pixels[i] = pixels[i]<<8 | 0xFF;
    }
}

void Canvas::blendColor(uint32_t &base, uint32_t top)
{
    uint32_t r1 = (base>>(3*8))&(0xFF);
    uint32_t g1 = (base>>(2*8))&(0xFF);
    uint32_t b1 = (base>>(1*8))&(0xFF);
    uint32_t a1 = (base>>(0*8))&(0xFF);
    uint32_t r2 = (top>>(3*8))&(0xFF);
    uint32_t g2 = (top>>(2*8))&(0xFF);
    uint32_t b2 = (top>>(1*8))&(0xFF);
    uint32_t a2 = (top>>(0*8))&(0xFF);
    if (a1 == 0x00 || a2 == 0xFF) {
        base = top;
        return;
    }
    if (a2 == 0x00) {
        return;
    }
    r1 = (r1*(255 - a2) + r2*a2)/255; if (r1 > 255) r1 = 255;
    g1 = (g1*(255 - a2) + g2*a2)/255; if (g1 > 255) g1 = 255;
    b1 = (b1*(255 - a2) + b2*a2)/255; if (b1 > 255) b1 = 255;
    a1 = a2 + (a1 * (255 - a2) + 127) / 255;
    base = (r1<<(3*8)) | (g1<<(2*8)) | (b1<<(1*8)) | (a1<<(0*8));
    return;
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

Canvas::Canvas(string fileName)
{
    height = 0;
    width = 0;
    pixels = nullptr;
    string extension = getFileExtension(fileName);
    if (extension == "") {
        cerr << "ERROR: file name " << fileName << " does not contain extension" << endl;
    }
    else if (extension == "ppm") {
        try {
            loadFromPPM(fileName);
        } catch (const exception& e) {
            cerr << e.what() << endl;
        }
    }
    else {
        cerr << "ERROR: This file type is not supported " << fileName << endl;
    }
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
    if (!containsExtension(fileName, ".ppm")) {
        fileName += ".ppm";
    }
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
void Canvas::saveToPNG(string fileName)
{
    if (!containsExtension(fileName, ".png")) {
        fileName += ".png";
    }
    vector<unsigned char> image;
    image.reserve(width * height * 4);

    for (int i = 0; i < width * height; ++i) {
        uint32_t pixel = pixels[i];
        image.push_back((pixel >> (3*8)) & 0xFF); // Red
        image.push_back((pixel >> (2*8)) & 0xFF);  // Green
        image.push_back((pixel >> (1*8)) & 0xFF);         // Blue
        image.push_back((pixel >> (0*8)) & 0xFF); // Alpha
    }

    unsigned error = lodepng::encode(fileName, image, width, height);

    if (error) {
        cout << "PNG encoding error: " << lodepng_error_text(error) << endl;
    } else {
        cout << "PNG saved successfully as " << fileName << endl;
    }
}

inline bool Canvas::pointInBounds(int y, int x) const
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
            blendColor(pixels[y*width+x], aRectangle.getColor());
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
            if (pointInsideRadius(dy, dx, (int) aCircle.getRadius())) {
                blendColor(pixels[y*width+x], aCircle.getColor());
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
            bool insideOuterEdge = pointInsideRadius(dy, dx, radius);
            bool insideInnerEdge = pointInsideRadius(dy, dx, radius - thickness);
            if (insideOuterEdge && !insideInnerEdge) {
                blendColor(pixels[y*width+x], aRing.getColor());
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
                blendColor(pixels[y*width+x], aOctagon.getColor());
            }
        }
    }
}

void Canvas::draw(const Triangle &aTriangle)
{
    int x1 = aTriangle.getMinX();
    int x2 = aTriangle.getMaxX();
    int y1 = aTriangle.getMinY();
    int y2 = aTriangle.getMaxY();
    for (int y = y1; y <= y2; y++){
        if (y < 0 || y >= height) { continue; }
        for (int x = x1; x <= x2; x++) {
            if (x < 0 || x >= width) { continue; }
            if (aTriangle.pointIsInside(x, y)) {
                blendColor(pixels[y*width+x], aTriangle.getColor());
            }
        }
    }
}

// Mostly copied from the olive.c library, don't fully know how it works
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