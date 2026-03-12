/*
 * Lab 06: Cohen-Sutherland Line Clipping Algorithm
 *
 * The Cohen-Sutherland algorithm clips a line segment to a rectangular
 * clipping window. Each endpoint is assigned a 4-bit region code:
 *
 *   Bit 3: Above top edge    (y > ymax)
 *   Bit 2: Below bottom edge (y < ymin)
 *   Bit 1: Right of right edge (x > xmax)
 *   Bit 0: Left of left edge (x < xmin)
 *
 * Cases:
 *   Both codes = 0000 -> line is completely inside (trivially accept)
 *   Codes AND != 0    -> line is completely outside (trivially reject)
 *   Otherwise         -> clip against the edge where the code bit is set
 */

#include <graphics.h>
#include <stdio.h>
#include <conio.h>

/* Region code bits */
#define INSIDE 0
#define LEFT   1
#define RIGHT  2
#define BOTTOM 4
#define TOP    8

typedef struct {
    float x, y;
} Point;

/* Clipping window boundaries (screen coordinates) */
int xmin, xmax, ymin, ymax;
int cx, cy;

/* Convert math coords to screen coords */
void to_screen(float mx, float my, int *sx, int *sy) {
    *sx = (int)(mx + cx);
    *sy = (int)(cy - my);
}

/* Compute the region code for a point */
int compute_code(float x, float y) {
    int code = INSIDE;
    if      (x < xmin) code |= LEFT;
    else if (x > xmax) code |= RIGHT;
    if      (y < ymin) code |= BOTTOM;
    else if (y > ymax) code |= TOP;
    return code;
}

/* Cohen-Sutherland clipping */
void cohen_sutherland_clip(float x1, float y1, float x2, float y2) {
    int code1 = compute_code(x1, y1);
    int code2 = compute_code(x2, y2);
    int accept = 0;

    while (1) {
        if (!(code1 | code2)) {
            /* Both inside */
            accept = 1;
            break;
        } else if (code1 & code2) {
            /* Both outside the same region */
            break;
        } else {
            /* Partially inside: clip against an edge */
            float x, y;
            int code_out = code1 ? code1 : code2;

            if (code_out & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = (float)ymax;
            } else if (code_out & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = (float)ymin;
            } else if (code_out & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = (float)xmax;
            } else { /* LEFT */
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = (float)xmin;
            }

            if (code_out == code1) {
                x1 = x; y1 = y;
                code1 = compute_code(x1, y1);
            } else {
                x2 = x; y2 = y;
                code2 = compute_code(x2, y2);
            }
        }
    }

    if (accept) {
        int sx1, sy1, sx2, sy2;
        to_screen(x1, y1, &sx1, &sy1);
        to_screen(x2, y2, &sx2, &sy2);
        setcolor(GREEN);
        line(sx1, sy1, sx2, sy2);
        outtextxy(10, 50, "Line clipped (green = accepted part)");
    } else {
        outtextxy(10, 50, "Line completely outside - rejected");
    }
}

int main() {
    int gd = DETECT, gm;
    float lx1, ly1, lx2, ly2;
    int wx_min, wy_min, wx_max, wy_max;

    printf("Enter clipping window (xmin ymin xmax ymax): ");
    scanf("%d %d %d %d", &wx_min, &wy_min, &wx_max, &wy_max);
    printf("Enter line endpoints (x1 y1 x2 y2): ");
    scanf("%f %f %f %f", &lx1, &ly1, &lx2, &ly2);

    initgraph(&gd, &gm, "");
    settitle("Cohen-Sutherland Line Clipping");

    cx = getmaxx() / 2;
    cy = getmaxy() / 2;

    xmin = wx_min; xmax = wx_max;
    ymin = wy_min; ymax = wy_max;

    /* Draw axes */
    setcolor(DARKGRAY);
    line(0, cy, getmaxx(), cy);
    line(cx, 0, cx, getmaxy());

    /* Draw clipping window */
    int sx1, sy1, sx2, sy2;
    to_screen((float)xmin, (float)ymin, &sx1, &sy1);
    to_screen((float)xmax, (float)ymax, &sx2, &sy2);
    setcolor(RED);
    rectangle(sx1, sy2, sx2, sy1);

    /* Draw original line in white */
    to_screen(lx1, ly1, &sx1, &sy1);
    to_screen(lx2, ly2, &sx2, &sy2);
    setcolor(WHITE);
    line(sx1, sy1, sx2, sy2);

    /* Clip and draw */
    cohen_sutherland_clip(lx1, ly1, lx2, ly2);

    setcolor(YELLOW);
    outtextxy(10, 10, "Cohen-Sutherland Line Clipping");
    setcolor(RED);
    outtextxy(10, 70, "Red rectangle = clipping window");
    setcolor(WHITE);
    outtextxy(10, 90, "White = original line");
    outtextxy(10, getmaxy() - 20, "Press any key to exit...");

    getch();
    closegraph();
    return 0;
}
