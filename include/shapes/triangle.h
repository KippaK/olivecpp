class Triangle
{
public:
    Triangle();
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3);
    ~Triangle();

private:
    struct Point
    {
        int x;
        int y;
    };
    
    Point point[3];
};