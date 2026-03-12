#include <graphics.h>
#include <conio.h>

int main()
{
   int gd = DETECT, gm;
   initgraph(&gd, &gm, "");

   // House base
   rectangle(200, 250, 400, 400);

   // Roof
   line(200, 250, 300, 180);
   line(300, 180, 400, 250);

   // Door
   rectangle(280, 320, 320, 400);

   // Left window
   rectangle(220, 280, 260, 320);

   // Right window
   rectangle(340, 280, 380, 320);

   // Window lines
   line(220, 300, 260, 300);
   line(240, 280, 240, 320);

   line(340, 300, 380, 300);
   line(360, 280, 360, 320);

   getch();
   closegraph();
   return 0;
}
