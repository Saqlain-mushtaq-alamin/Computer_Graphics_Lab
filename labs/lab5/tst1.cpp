
#include <graphics.h>
#include <stdio.h>
#include <conio.h> // Required for getch() and clrscr()

int main(void)
{

    int gdriver = DETECT, gmode;
    int x1 = 100, y1 = 100;
    int x2 = 400, y2 = 200;
    initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");

    setcolor(RED);
    setfillstyle(SOLID_FILL, GREEN);
    bar(80,110,350,300);


    setfillstyle(1,RED);
    fillellipse(210,200,50,50);


    getch();
    closegraph();
    return 0;
}
