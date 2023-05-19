#include "include/canvas.h"
#include "examples.h"

#include <iostream>
#include <conio.h>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;


int main() {
    const size_t WIDTH = 800;
    const size_t HEIGHT = 600;
    Example::Canvas *canvas = new Example::Canvas(HEIGHT, WIDTH, BLACK);
    //  canvas->drawSnowman(HEIGHT/2, WIDTH/2, 400);
    //  canvas->drawStopSign(HEIGHT/2, WIDTH/2, 300);
    //  canvas->drawOlympicRings(HEIGHT/2, WIDTH/2, 100);
    canvas->draw(Line(100, 100, 200, 400, 0xFFFFFFFF));
    canvas->saveToPPM("output.ppm");
    return 0;
}