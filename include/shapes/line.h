#include <stdint.h>

class Line
{
public:
    Line();
    ~Line();

    Line(
        int aY1, 
        int aX1,
        int aY2, 
        int aX2,
        float aWidth,
        uint32_t aColor
    );

    void setY1(int aY1);
    void setX1(int aX1);
    void setY2(int aY2);
    void setX2(int aX2);

    int getY1() const;
    int getX1() const;
    int getY2() const;
    int getX2() const;

    void setWidth(float aWidth);
    float getWidth() const;

    void setColor(uint32_t aColor);
    uint32_t getColor() const;

private:
    int y1;
    int x1;

    int y2;
    int x2;

    float width;

    uint32_t color;
};