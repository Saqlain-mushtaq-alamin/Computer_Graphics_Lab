/*
 * Lab 01: DDA (Digital Differential Analyzer) Line Drawing Algorithm
 *
 * The DDA algorithm calculates intermediate points between two endpoints
 * by stepping along the axis with the larger delta by 1 unit at a time
 * and computing the corresponding coordinate on the other axis using
 * the line's slope.
 *
 * Time Complexity: O(max(|dx|, |dy|))
 */

#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>

void dda_line(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps;
    float x_inc, y_inc, x, y;

    /* Determine the number of steps */
    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    } else {
        steps = abs(dy);
    }

    /* Calculate increments */
    x_inc = (float)dx / steps;
    y_inc = (float)dy / steps;

    /* Start from the first point */
    x = (float)x1;
    y = (float)y1;

    /* Plot pixels along the line */
    for (int i = 0; i <= steps; i++) {
        putpixel((int)round(x), (int)round(y), WHITE);
        x += x_inc;
        y += y_inc;
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

    settitle("DDA Line Drawing Algorithm");

    /* Draw reference axes */
    setcolor(DARKGRAY);
    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());

    /* Draw the line using DDA */
    setcolor(WHITE);
    dda_line(x1 + getmaxx() / 2, getmaxy() / 2 - y1,
             x2 + getmaxx() / 2, getmaxy() / 2 - y2);

    /* Display information */
    setcolor(YELLOW);
    outtextxy(10, 10, "DDA Line Drawing Algorithm");
    char info[100];
    sprintf(info, "From (%d,%d) to (%d,%d)", x1, y1, x2, y2);
    outtextxy(10, 30, info);
    outtextxy(10, getmaxy() - 20, "Press any key to exit...");

    getch();
    closegraph();
    return 0;
}
