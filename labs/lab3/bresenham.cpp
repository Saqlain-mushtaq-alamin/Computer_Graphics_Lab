#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

void bresenhamPrintAndDraw(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int x = x1, y = y1;
    int step = 0;

    // ---- Print all points ----
    printf("\n  Bresenham Line from (%d,%d) to (%d,%d)\n", x1, y1, x2, y2);
    printf("  dx = %d   dy = %d\n", dx, dy);
    printf("  Initial error = %d\n\n", err);
    printf("  %-8s  %-10s  %-10s  %-10s\n", "Step", "  X", "  Y", " Error");
 

    while (1)
    {
        printf("  %-8d  %-10d  %-10d  %-10d\n", step++, x, y, err);
        if (x == x2 && y == y2)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y += sy;
        }
    }

    printf("\n  Press any key to draw the line...");
    getch();

    // ---- Open graphics and draw ----
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Labels
    setcolor(WHITE);
    outtextxy(10, 10, "Bresenham Line Drawing Algorithm");

    char info[80];
    sprintf(info, "From (%d,%d)  to  (%d,%d)", x1, y1, x2, y2);
    outtextxy(10, 25, info);

    // Draw the Bresenham line pixel by pixel
    setcolor(CYAN);

    // Recompute for drawing
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    sx = (x1 < x2) ? 1 : -1;
    sy = (y1 < y2) ? 1 : -1;
    err = dx - dy;
    x = x1;
    y = y1;

    while (1)
    {
        putpixel(x, y, CYAN);
        if (x == x2 && y == y2)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y += sy;
        }
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

    bresenhamPrintAndDraw(x1, y1, x2, y2);

    return 0;
}
