 #include <graphics.h>
#include <conio.h>

int main()
{
    int gd = DETECT, gm;

 
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    // Star coordinates
    int points[] = {
        200,100,
        220,160,
        280,160,
        230,200,
        250,260,
        200,220,
        150,260,
        170,200,
        120,160,
        180,160
    };

    // Set fill color
    setfillstyle(SOLID_FILL, YELLOW);

    // Draw and fill the star
    fillpoly(10, points);

    getch();
    closegraph();
    return 0;
}
