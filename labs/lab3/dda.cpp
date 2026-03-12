#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

void ddaPrintAndDraw(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    float xinc = (float)dx / steps;
    float yinc = (float)dy / steps;

    float x = x1, y = y1;

    // ---- Print all points ----
    printf("\n  DDA Line from (%d,%d) to (%d,%d)\n", x1, y1, x2, y2);
    printf("  Total steps : %d\n", steps);
    printf("  Xinc = %.4f   Yinc = %.4f\n\n", xinc, yinc);
    printf("  %-8s  %-10s  %-10s\n", "Step", "  X", "  Y");
    printf("  --------------------------------\n");
    for (int i = 0; i <= steps; i++)
    {
        printf("  %-8d  %-10d  %-10d\n", i, (int)(x + 0.5f), (int)(y + 0.5f));
        x += xinc;
        y += yinc;
    }

    printf("\n  Press any key to draw the line...");
    getch();

    // ---- Open graphics and draw ----
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Labels
    setcolor(WHITE);
    outtextxy(10, 10, "DDA Line Drawing Algorithm");

    char info[80];
    sprintf(info, "From (%d,%d)  to  (%d,%d)", x1, y1, x2, y2);
    outtextxy(10, 25, info);

    // Draw the DDA line pixel by pixel
    setcolor(YELLOW);

    // Recompute for drawing
    dx = x2 - x1;
    dy = y2 - y1;
    steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    xinc = (float)dx / steps;
    yinc = (float)dy / steps;
    x = x1;
    y = y1;

    for (int i = 0; i <= steps; i++)
    {
        putpixel((int)(x + 0.5f), (int)(y + 0.5f), YELLOW);
        x += xinc;
        y += yinc;
    }

    // Draw endpoint markers
    setcolor(RED);
    circle(x1, y1, 3);
    circle(x2, y2, 3);

    outtextxy(10, getmaxy() - 20, "Press any key to exit...");
    getch();
    closegraph();
}

int main()
{
    int x1, y1, x2, y2;

 

    printf("  Enter starting point (x1 y1) : ");
    scanf("%d %d", &x1, &y1);

    printf("  Enter ending   point (x2 y2) : ");
    scanf("%d %d", &x2, &y2);

    ddaPrintAndDraw(x1, y1, x2, y2);

    return 0;
}
