

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
    setfillstyle(1,RED);
    fillellipse(195,200,50,50);


    setfillstyle(4, WHITE);


    bar(30, 200, 80, 300);


    bar(100, 150, 150, 300);


    bar(170, 80, 220, 300);


    bar(240, 150, 290, 300);


    bar(310, 200, 360, 300);

    setcolor(RED);
    setlinestyle(SOLID_LINE, 0, 10);
    line(0, 300, 400, 300);

    setcolor(BROWN);
    line(10, 300, 10, 30);







    getch();
    closegraph();
    return 0;
}
