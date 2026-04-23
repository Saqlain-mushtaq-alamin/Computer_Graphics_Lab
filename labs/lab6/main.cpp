#include <graphics.h>
#include <conio.h>

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");

    rectangle(200,200,300,300);
    rectangle(240,160,340,260);

    line(200,200,240,160);
    line(300,200,340,160);
    line(200,300,240,260);
    line(300,300,340,260);

 

    getch();
    closegraph();

    return 0;
}
