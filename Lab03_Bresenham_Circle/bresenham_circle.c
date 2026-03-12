/*
 * Lab 03: Bresenham's Circle Drawing Algorithm
 *
 * Bresenham's circle algorithm uses integer arithmetic and exploits
 * the 8-fold symmetry of a circle to compute only one octant and
 * mirror it to produce the full circle.
 *
 * Time Complexity: O(r) where r is the radius
 */

#include <graphics.h>
#include <stdio.h>
#include <conio.h>

void plot_circle_points(int cx, int cy, int x, int y) {
    putpixel(cx + x, cy + y, WHITE);
    putpixel(cx - x, cy + y, WHITE);
    putpixel(cx + x, cy - y, WHITE);
    putpixel(cx - x, cy - y, WHITE);
    putpixel(cx + y, cy + x, WHITE);
    putpixel(cx - y, cy + x, WHITE);
    putpixel(cx + y, cy - x, WHITE);
    putpixel(cx - y, cy - x, WHITE);
}

void bresenham_circle(int cx, int cy, int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r; /* Initial decision parameter */

    plot_circle_points(cx, cy, x, y);

    while (y >= x) {
        x++;

        if (d > 0) {
            /* Move to (x+1, y-1) */
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            /* Move to (x+1, y) */
            d = d + 4 * x + 6;
        }

        plot_circle_points(cx, cy, x, y);
    }
}

int main() {
    int gd = DETECT, gm;
    int cx, cy, r;

    printf("Enter center (cx, cy): ");
    scanf("%d %d", &cx, &cy);
    printf("Enter radius: ");
    scanf("%d", &r);

    initgraph(&gd, &gm, "");

    settitle("Bresenham's Circle Drawing Algorithm");

    /* Draw reference axes */
    setcolor(DARKGRAY);
    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());

    /* Draw circle */
    setcolor(WHITE);
    bresenham_circle(cx + getmaxx() / 2, getmaxy() / 2 - cy, r);

    /* Display information */
    setcolor(YELLOW);
    outtextxy(10, 10, "Bresenham's Circle Drawing Algorithm");
    char info[100];
    sprintf(info, "Center (%d,%d), Radius = %d", cx, cy, r);
    outtextxy(10, 30, info);
    outtextxy(10, getmaxy() - 20, "Press any key to exit...");

    getch();
    closegraph();
    return 0;
}
