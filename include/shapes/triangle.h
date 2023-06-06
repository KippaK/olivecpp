#include <stdint.h>

class Triangle
{
public:
    Triangle();
    Triangle(int aX1, int aY1, int aX2, int aY2, int aX3, int aY3, uint32_t aColor);
    ~Triangle();

    int getX1() const;
    void setX1(int aX1);
    int getY1() const;
    void setY1(int aY1);
    int getX2() const;
    void setX2(int aX2);
    int getY2() const;
    void setY2(int aY2);
    int getX3() const;
    void setX3(int aX3);
    int getY3() const;
    void setY3(int aY3);
    uint32_t getColor() const;
    void setColor(uint32_t aColor);

private:
    int x1, y1, x2, y2, x3, y3;
    uint32_t color;
};