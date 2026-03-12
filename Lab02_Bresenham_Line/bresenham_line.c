/*
 * Lab 02: Bresenham's Line Drawing Algorithm
 *
 * Bresenham's algorithm uses only integer arithmetic (no floating point),
 * making it faster than DDA. It uses a decision parameter to determine
 * which pixel is closer to the true line path.
 *
 * Time Complexity: O(max(|dx|, |dy|))
 */

#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>

void bresenham_line(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1) {
        putpixel(x1, y1, WHITE);

        if (x1 == x2 && y1 == y2) {
            break;
        }

        e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

int main() {
    int gd = DETECT, gm;
    int x1, y1, x2, y2;

    printf("Enter start point (x1, y1): ");
    scanf("%d %d", &x1, &y1);
    printf("Enter end point (x2, y2): ");
    scanf("%d %d", &x2, &y2);

    initgraph(&gd, &gm, "");

    settitle("Bresenham's Line Drawing Algorithm");

    /* Draw reference axes */
    setcolor(DARKGRAY);
    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());

    /* Draw the line using Bresenham's algorithm */
    setcolor(WHITE);
    bresenham_line(x1 + getmaxx() / 2, getmaxy() / 2 - y1,
                   x2 + getmaxx() / 2, getmaxy() / 2 - y2);

    /* Display information */
    setcolor(YELLOW);
    outtextxy(10, 10, "Bresenham's Line Drawing Algorithm");
    char info[100];
    sprintf(info, "From (%d,%d) to (%d,%d)", x1, y1, x2, y2);
    outtextxy(10, 30, info);
    outtextxy(10, getmaxy() - 20, "Press any key to exit...");

    getch();
    closegraph();
    return 0;
}
