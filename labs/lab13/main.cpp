#include <graphics.h>
#include <conio.h>
#include <math.h>

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");

    float t;
    float x, y, prevX, prevY;

    int x0 = 100, y0 = 300;
    int x1 = 200, y1 = 100;
    int x2 = 300, y2 = 100;
    int x3 = 400, y3 = 300;

    setcolor(WHITE);

    // Initial point
    prevX = x0;
    prevY = y0;

    for(t = 0.0; t <= 1.0; t += 0.01)
    {
        x = pow(1-t,3)*x0 +
            3*t*pow(1-t,2)*x1 +
            3*pow(t,2)*(1-t)*x2 +
            pow(t,3)*x3;

        y = pow(1-t,3)*y0 +
            3*t*pow(1-t,2)*y1 +
            3*pow(t,2)*(1-t)*y2 +
            pow(t,3)*y3;

        // Draw small line segments instead of pixels
        line(prevX, prevY, x, y);

        prevX = x;
        prevY = y;
    }

 
    getch();
    closegraph();

    return 0;
}
