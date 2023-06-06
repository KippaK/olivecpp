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
    string file = "output";
    Example::Canvas *canvas = new Example::Canvas(HEIGHT, WIDTH, DARKGREY);
    //  canvas->drawSnowman(HEIGHT/2, WIDTH/2, 400);
    //  canvas->drawStopSign(HEIGHT/2, WIDTH/2, 300);
    //  canvas->drawOlympicRings(HEIGHT/2, WIDTH/2, 100);
    canvas->draw(Line(50, 50, 100, 200, 5, 0xFFFFFFFF));
    canvas->draw(Circle(50, 250, 40, 0xFFFFFFFF));
    canvas->draw(Ring(50, 400, 40, 5, 0xFFFFFFFF));
    canvas->draw(Triangle(300, 400, 400, 500, 450, 300, WHITE));
    canvas->drawOlympicRings(250, 200, 50);
    canvas->drawStopSign(400, 200, 100);
    canvas->drawSnowman(HEIGHT/2, 600, 400);
    canvas->saveToPPM(file + ".ppm");
    canvas->saveToPNG(file + ".png");
    Canvas *canvasCopy = new Canvas("output.ppm");
    canvasCopy->saveToPPM("output_copy.ppm");
    return 0;
}