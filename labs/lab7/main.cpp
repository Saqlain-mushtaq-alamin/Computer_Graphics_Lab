#include <graphics.h>
#include <conio.h>

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");

    int tx = 80, ty = 50;

    // Original cube
    rectangle(150,200,250,300);
    rectangle(180,170,280,270);
    line(150,200,180,170);
    line(250,200,280,170);
    line(150,300,180,270);
    line(250,300,280,270);
  

    // Translated cube
    rectangle(150+tx,200+ty,250+tx,300+ty);
    rectangle(180+tx,170+ty,280+tx,270+ty);
    line(150+tx,200+ty,180+tx,170+ty);
    line(250+tx,200+ty,280+tx,170+ty);
    line(150+tx,300+ty,180+tx,270+ty);
    line(250+tx,300+ty,280+tx,270+ty);
   

    getch();
    closegraph();
    return 0;
}
