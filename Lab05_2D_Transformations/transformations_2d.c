/*
 * Lab 05: 2D Transformations
 *
 * This program demonstrates the following 2D geometric transformations
 * on a triangle using homogeneous coordinates (3x3 matrices):
 *
 *   1. Translation
 *   2. Scaling
 *   3. Rotation
 *   4. Reflection (about X-axis, Y-axis, and origin)
 *
 * Homogeneous coordinate representation:
 *   [x']   [a b tx] [x]
 *   [y'] = [c d ty] [y]
 *   [1 ]   [0 0  1] [1]
 */

#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>

#define MAX_VERTICES 10
#define PI 3.14159265358979323846

typedef struct {
    float x, y;
} Point;

int cx, cy; /* Screen center */

/* Convert from math coords to screen coords */
void to_screen(float mx, float my, int *sx, int *sy) {
    *sx = (int)(mx + cx);
    *sy = (int)(cy - my);
}

/* Draw a polygon given its vertices */
void draw_polygon(Point pts[], int n, int color) {
    setcolor(color);
    int x1, y1, x2, y2;
    for (int i = 0; i < n; i++) {
        to_screen(pts[i].x, pts[i].y, &x1, &y1);
        to_screen(pts[(i + 1) % n].x, pts[(i + 1) % n].y, &x2, &y2);
        line(x1, y1, x2, y2);
    }
}

/* Apply translation */
void translate(Point pts[], int n, float tx, float ty, Point result[]) {
    for (int i = 0; i < n; i++) {
        result[i].x = pts[i].x + tx;
        result[i].y = pts[i].y + ty;
    }
}

/* Apply scaling (about origin) */
void scale(Point pts[], int n, float sx, float sy, Point result[]) {
    for (int i = 0; i < n; i++) {
        result[i].x = pts[i].x * sx;
        result[i].y = pts[i].y * sy;
    }
}

/* Apply rotation by angle_deg degrees counter-clockwise about origin */
void rotate(Point pts[], int n, float angle_deg, Point result[]) {
    float angle = angle_deg * PI / 180.0f;
    float cos_a = (float)cos(angle);
    float sin_a = (float)sin(angle);
    for (int i = 0; i < n; i++) {
        result[i].x = pts[i].x * cos_a - pts[i].y * sin_a;
        result[i].y = pts[i].x * sin_a + pts[i].y * cos_a;
    }
}

/* Apply reflection about the X-axis */
void reflect_x(Point pts[], int n, Point result[]) {
    for (int i = 0; i < n; i++) {
        result[i].x =  pts[i].x;
        result[i].y = -pts[i].y;
    }
}

/* Apply reflection about the Y-axis */
void reflect_y(Point pts[], int n, Point result[]) {
    for (int i = 0; i < n; i++) {
        result[i].x = -pts[i].x;
        result[i].y =  pts[i].y;
    }
}

int main() {
    int gd = DETECT, gm;
    int choice;
    float param1, param2;

    /* Original triangle */
    Point original[] = {{50, 50}, {100, 50}, {75, 100}};
    Point result[MAX_VERTICES];
    int n = 3;

    printf("2D Transformations\n");
    printf("==================\n");
    printf("1. Translation\n");
    printf("2. Scaling\n");
    printf("3. Rotation\n");
    printf("4. Reflection about X-axis\n");
    printf("5. Reflection about Y-axis\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter tx and ty: ");
            scanf("%f %f", &param1, &param2);
            translate(original, n, param1, param2, result);
            break;
        case 2:
            printf("Enter sx and sy: ");
            scanf("%f %f", &param1, &param2);
            scale(original, n, param1, param2, result);
            break;
        case 3:
            printf("Enter rotation angle (degrees): ");
            scanf("%f", &param1);
            rotate(original, n, param1, result);
            break;
        case 4:
            reflect_x(original, n, result);
            break;
        case 5:
            reflect_y(original, n, result);
            break;
        default:
            printf("Invalid choice.\n");
            return 1;
    }

    initgraph(&gd, &gm, "");
    settitle("2D Transformations");

    cx = getmaxx() / 2;
    cy = getmaxy() / 2;

    /* Draw axes */
    setcolor(DARKGRAY);
    line(0, cy, getmaxx(), cy);
    line(cx, 0, cx, getmaxy());

    /* Draw original polygon in white */
    draw_polygon(original, n, WHITE);
    setcolor(WHITE);
    outtextxy(10, 10, "Original (white)");

    /* Draw transformed polygon in cyan */
    draw_polygon(result, n, CYAN);
    setcolor(CYAN);
    outtextxy(10, 30, "Transformed (cyan)");

    outtextxy(10, getmaxy() - 20, "Press any key to exit...");
    getch();
    closegraph();
    return 0;
}
