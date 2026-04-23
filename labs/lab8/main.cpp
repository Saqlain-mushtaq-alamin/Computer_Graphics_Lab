#include <graphics.h>
#include <conio.h>
#include <stdio.h>

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");

    int xmin = 200, ymin = 150, xmax = 400, ymax = 300;
    int x1 = 150, y1 = 100, x2 = 450, y2 = 350;

    rectangle(xmin, ymin, xmax, ymax);

    setcolor(RED);
    line(x1, y1, x2, y2);
   

    setcolor(GREEN);
    line(220, 170, 380, 280);
   
    getch();
    closegraph();

    return 0;
}
