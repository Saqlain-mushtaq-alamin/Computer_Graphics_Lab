/*
 * Lab 04: Midpoint Ellipse Drawing Algorithm
 *
 * The midpoint ellipse algorithm uses the ellipse equation:
 *   (x/a)^2 + (y/b)^2 = 1
 * and exploits 4-fold symmetry to compute one quadrant and mirror
 * it to draw the complete ellipse.
 *
 * It is split into two regions:
 *   Region 1: slope < -1  (x increases faster)
 *   Region 2: slope >= -1 (y decreases faster)
 *
 * Time Complexity: O(a + b)
 */

#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>

void plot_ellipse_points(int cx, int cy, int x, int y) {
    putpixel(cx + x, cy + y, WHITE);
    putpixel(cx - x, cy + y, WHITE);
    putpixel(cx + x, cy - y, WHITE);
    putpixel(cx - x, cy - y, WHITE);
}

void midpoint_ellipse(int cx, int cy, int a, int b) {
    long a2 = (long)a * a;
    long b2 = (long)b * b;
    long x = 0, y = b;
    long d;

    /* Region 1 */
    d = b2 - a2 * b + (long)(0.25 * a2);
    long dx = 2 * b2 * x;
    long dy = 2 * a2 * y;

    while (dx < dy) {
        plot_ellipse_points(cx, cy, (int)x, (int)y);

        if (d < 0) {
            x++;
            dx += 2 * b2;
            d += dx + b2;
        } else {
            x++;
            y--;
            dx += 2 * b2;
            dy -= 2 * a2;
            d += dx - dy + b2;
        }
    }

    /* Region 2 */
    d = b2 * ((long)(x + 0.5) * (x + 0.5)) + a2 * ((y - 1) * (y - 1)) - (long)a2 * b2;

    while (y >= 0) {
        plot_ellipse_points(cx, cy, (int)x, (int)y);

        if (d > 0) {
            y--;
            dy -= 2 * a2;
            d += a2 - dy;
        } else {
            y--;
            x++;
            dx += 2 * b2;
            dy -= 2 * a2;
            d += dx - dy + a2;
        }
    }
}

int main() {
    int gd = DETECT, gm;
    int cx, cy, a, b;

    printf("Enter center (cx, cy): ");
    scanf("%d %d", &cx, &cy);
    printf("Enter semi-major axis (a) and semi-minor axis (b): ");
    scanf("%d %d", &a, &b);

    initgraph(&gd, &gm, "");

    settitle("Midpoint Ellipse Drawing Algorithm");

    /* Draw reference axes */
    setcolor(DARKGRAY);
    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());

    /* Draw ellipse */
    setcolor(WHITE);
    midpoint_ellipse(cx + getmaxx() / 2, getmaxy() / 2 - cy, a, b);

    /* Display information */
    setcolor(YELLOW);
    outtextxy(10, 10, "Midpoint Ellipse Drawing Algorithm");
    char info[100];
    sprintf(info, "Center (%d,%d), a=%d, b=%d", cx, cy, a, b);
    outtextxy(10, 30, info);
    outtextxy(10, getmaxy() - 20, "Press any key to exit...");

    getch();
    closegraph();
    return 0;
}
