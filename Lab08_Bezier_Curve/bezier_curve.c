/*
 * Lab 08: Bezier Curve Drawing
 *
 * A Bezier curve is a parametric curve defined by control points.
 * For n+1 control points P0, P1, ..., Pn, the curve is:
 *
 *   B(t) = sum_{i=0}^{n} C(n,i) * (1-t)^(n-i) * t^i * P_i,  0 <= t <= 1
 *
 * where C(n,i) = n! / (i! * (n-i)!) is the binomial coefficient.
 *
 * This program draws a cubic Bezier curve (4 control points).
 */

#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>

#define NUM_STEPS 1000

typedef struct {
    float x, y;
} Point;

int cx, cy;

void to_screen(float mx, float my, int *sx, int *sy) {
    *sx = (int)(mx + cx);
    *sy = (int)(cy - my);
}

/* Compute the binomial coefficient C(n, k) */
long binomial(int n, int k) {
    if (k == 0 || k == n) return 1;
    long result = 1;
    for (int i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

/* Evaluate a Bezier curve at parameter t using pre-computed coefficients */
Point bezier_point(Point ctrl[], int n, float t, float coeffs[]) {
    Point p = {0.0f, 0.0f};
    float one_minus_t = 1.0f - t;
    for (int i = 0; i <= n; i++) {
        float coeff = coeffs[i]
                    * (float)pow(one_minus_t, n - i)
                    * (float)pow(t, i);
        p.x += coeff * ctrl[i].x;
        p.y += coeff * ctrl[i].y;
    }
    return p;
}

void draw_bezier(Point ctrl[], int n) {
    /* Pre-compute binomial coefficients using a fixed-size array */
    float coeffs[4]; /* supports up to degree 3 (cubic) */
    for (int i = 0; i <= n; i++) {
        coeffs[i] = (float)binomial(n, i);
    }

    Point prev = bezier_point(ctrl, n, 0.0f, coeffs);
    int px, py, qx, qy;

    for (int step = 1; step <= NUM_STEPS; step++) {
        float t = (float)step / NUM_STEPS;
        Point curr = bezier_point(ctrl, n, t, coeffs);

        to_screen(prev.x, prev.y, &px, &py);
        to_screen(curr.x, curr.y, &qx, &qy);
        line(px, py, qx, qy);

        prev = curr;
    }
}

int main() {
    int gd = DETECT, gm;
    int n = 3; /* Cubic Bezier: n+1 = 4 control points */
    Point ctrl[4];

    printf("Cubic Bezier Curve (4 control points)\n");
    printf("Enter 4 control points (x y) one per line:\n");
    for (int i = 0; i < 4; i++) {
        printf("P%d: ", i);
        scanf("%f %f", &ctrl[i].x, &ctrl[i].y);
    }

    initgraph(&gd, &gm, "");
    settitle("Bezier Curve");

    cx = getmaxx() / 2;
    cy = getmaxy() / 2;

    /* Draw axes */
    setcolor(DARKGRAY);
    line(0, cy, getmaxx(), cy);
    line(cx, 0, cx, getmaxy());

    /* Draw control polygon */
    setcolor(DARKGRAY);
    for (int i = 0; i < n; i++) {
        int sx1, sy1, sx2, sy2;
        to_screen(ctrl[i].x, ctrl[i].y, &sx1, &sy1);
        to_screen(ctrl[i + 1].x, ctrl[i + 1].y, &sx2, &sy2);
        line(sx1, sy1, sx2, sy2);
    }

    /* Draw control points */
    setcolor(RED);
    for (int i = 0; i <= n; i++) {
        int sx, sy;
        to_screen(ctrl[i].x, ctrl[i].y, &sx, &sy);
        circle(sx, sy, 4);
    }

    /* Draw Bezier curve */
    setcolor(CYAN);
    draw_bezier(ctrl, n);

    setcolor(YELLOW);
    outtextxy(10, 10, "Bezier Curve (Cubic)");
    setcolor(RED);
    outtextxy(10, 30, "Red circles = control points");
    setcolor(DARKGRAY);
    outtextxy(10, 50, "Gray lines = control polygon");
    setcolor(CYAN);
    outtextxy(10, 70, "Cyan = Bezier curve");
    outtextxy(10, getmaxy() - 20, "Press any key to exit...");

    getch();
    closegraph();
    return 0;
}
