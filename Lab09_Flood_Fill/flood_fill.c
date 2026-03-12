/*
 * Lab 09: Flood Fill Algorithm
 *
 * The Flood Fill algorithm fills a region starting from a seed pixel
 * and spreading to all adjacent pixels that have the same original color
 * (interior color), replacing them with the fill color.
 *
 * This implementation uses a 4-connected (4-directional) iterative approach
 * with an explicit stack to avoid stack overflow for large regions:
 *   - Up, Down, Left, Right
 *
 * This program draws a polygon and then flood fills it.
 */

#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_STACK 100000

typedef struct { int x; int y; } StackPoint;

/* Iterative 4-connected flood fill using an explicit stack */
void flood_fill(int x, int y, int fill_color, int old_color) {
    if (old_color == fill_color) return;

    StackPoint *stack = (StackPoint *)malloc(MAX_STACK * sizeof(StackPoint));
    if (!stack) return;

    int top = 0;
    stack[top].x = x;
    stack[top].y = y;
    top++;

    while (top > 0) {
        top--;
        int cx = stack[top].x;
        int cy = stack[top].y;

        if (cx < 0 || cy < 0 || cx > getmaxx() || cy > getmaxy()) continue;
        if (getpixel(cx, cy) != old_color) continue;

        putpixel(cx, cy, fill_color);

        if (top + 4 <= MAX_STACK) {
            stack[top].x = cx + 1; stack[top].y = cy;     top++;
            stack[top].x = cx - 1; stack[top].y = cy;     top++;
            stack[top].x = cx;     stack[top].y = cy + 1; top++;
            stack[top].x = cx;     stack[top].y = cy - 1; top++;
        }
    }

    free(stack);
}

int main() {
    int gd = DETECT, gm;
    int seed_x, seed_y;

    initgraph(&gd, &gm, "");
    settitle("Flood Fill Algorithm");

    /* Draw a closed polygon (quadrilateral) */
    setcolor(WHITE);
    int pts[] = {200, 150, 400, 100, 500, 300, 150, 350, 200, 150};
    drawpoly(5, pts);

    /* Display instructions */
    setcolor(YELLOW);
    outtextxy(10, 10, "Flood Fill Algorithm");
    outtextxy(10, 30, "A polygon has been drawn.");
    outtextxy(10, 50, "Enter seed point inside the polygon.");
    outtextxy(10, getmaxy() - 20, "Press any key after fill...");

    printf("Enter seed point inside the polygon (x y): ");
    scanf("%d %d", &seed_x, &seed_y);

    /* Perform flood fill */
    int old_color = getpixel(seed_x, seed_y);
    flood_fill(seed_x, seed_y, CYAN, old_color);

    setcolor(YELLOW);
    outtextxy(10, 70, "Fill complete! (Cyan = filled region)");

    getch();
    closegraph();
    return 0;
}
