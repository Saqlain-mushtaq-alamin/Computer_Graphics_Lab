/*
 * Lab 10: Boundary Fill Algorithm
 *
 * The Boundary Fill algorithm fills a region starting from a seed pixel
 * and spreading to all adjacent pixels that are NOT the boundary color.
 * It differs from Flood Fill in that it checks for a boundary color
 * rather than an interior color.
 *
 * Two variants are provided:
 *   - 4-connected: fills only up/down/left/right neighbors
 *   - 8-connected: fills all 8 neighbors (includes diagonals)
 *
 * Both implementations use an explicit stack to avoid stack overflow
 * for large regions.
 *
 * This program draws a circle boundary and then boundary fills it.
 */

#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_STACK 100000

typedef struct { int x; int y; } StackPoint;

/* Iterative 4-connected boundary fill using an explicit stack */
void boundary_fill_4(int x, int y, int fill_color, int boundary_color) {
    StackPoint *stack = (StackPoint *)malloc(MAX_STACK * sizeof(StackPoint));
    if (!stack) return;

    int top = 0;
    stack[top].x = x; stack[top].y = y; top++;

    int dx4[] = {1, -1, 0,  0};
    int dy4[] = {0,  0, 1, -1};

    while (top > 0) {
        top--;
        int cx = stack[top].x;
        int cy = stack[top].y;

        if (cx < 0 || cy < 0 || cx > getmaxx() || cy > getmaxy()) continue;
        int current = getpixel(cx, cy);
        if (current == boundary_color || current == fill_color) continue;

        putpixel(cx, cy, fill_color);

        if (top + 4 <= MAX_STACK) {
            for (int i = 0; i < 4; i++) {
                stack[top].x = cx + dx4[i];
                stack[top].y = cy + dy4[i];
                top++;
            }
        }
    }

    free(stack);
}

/* Iterative 8-connected boundary fill using an explicit stack */
void boundary_fill_8(int x, int y, int fill_color, int boundary_color) {
    StackPoint *stack = (StackPoint *)malloc(MAX_STACK * sizeof(StackPoint));
    if (!stack) return;

    int top = 0;
    stack[top].x = x; stack[top].y = y; top++;

    int dx8[] = {1, -1,  0,  0, 1, -1,  1, -1};
    int dy8[] = {0,  0,  1, -1, 1,  1, -1, -1};

    while (top > 0) {
        top--;
        int cx = stack[top].x;
        int cy = stack[top].y;

        if (cx < 0 || cy < 0 || cx > getmaxx() || cy > getmaxy()) continue;
        int current = getpixel(cx, cy);
        if (current == boundary_color || current == fill_color) continue;

        putpixel(cx, cy, fill_color);

        if (top + 8 <= MAX_STACK) {
            for (int i = 0; i < 8; i++) {
                stack[top].x = cx + dx8[i];
                stack[top].y = cy + dy8[i];
                top++;
            }
        }
    }

    free(stack);
}

int main() {
    int gd = DETECT, gm;
    int seed_x, seed_y, choice;

    printf("Boundary Fill Algorithm\n");
    printf("1. 4-connected\n");
    printf("2. 8-connected\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    initgraph(&gd, &gm, "");
    settitle("Boundary Fill Algorithm");

    /* Draw a closed shape using a white boundary */
    setcolor(WHITE);

    /* Draw a circle as the boundary */
    circle(320, 240, 100);

    /* Display instructions */
    setcolor(YELLOW);
    outtextxy(10, 10, "Boundary Fill Algorithm");
    char msg[100];
    sprintf(msg, "Mode: %s", (choice == 2) ? "8-connected" : "4-connected");
    outtextxy(10, 30, msg);
    outtextxy(10, 50, "A circle has been drawn.");
    outtextxy(10, getmaxy() - 20, "Press any key after fill...");

    printf("Enter seed point inside the circle (x y): ");
    scanf("%d %d", &seed_x, &seed_y);

    /* Perform boundary fill */
    if (choice == 2) {
        boundary_fill_8(seed_x, seed_y, CYAN, WHITE);
    } else {
        boundary_fill_4(seed_x, seed_y, CYAN, WHITE);
    }

    setcolor(YELLOW);
    outtextxy(10, 70, "Fill complete! (Cyan = filled region)");

    getch();
    closegraph();
    return 0;
}
