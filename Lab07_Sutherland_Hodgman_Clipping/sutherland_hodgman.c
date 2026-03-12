/*
 * Lab 07: Sutherland-Hodgman Polygon Clipping Algorithm
 *
 * The Sutherland-Hodgman algorithm clips a polygon against each edge
 * of a convex clipping window (rectangle), one edge at a time.
 * For each clip edge, it processes the polygon vertices and produces
 * a new polygon that is the intersection of the input polygon with
 * the half-plane defined by the clip edge.
 *
 * The algorithm handles four cases for consecutive vertex pairs (s, p):
 *   1. Both inside  -> output p
 *   2. s inside, p outside -> output intersection
 *   3. Both outside -> output nothing
 *   4. s outside, p inside -> output intersection then p
 */

#include <graphics.h>
#include <stdio.h>
#include <conio.h>

#define MAX_VERTICES 20

typedef struct {
    float x, y;
} Point;

int cx, cy;

void to_screen(float mx, float my, int *sx, int *sy) {
    *sx = (int)(mx + cx);
    *sy = (int)(cy - my);
}

/* Clipping window */
float xmin_c, xmax_c, ymin_c, ymax_c;

/* Compute intersection of segment (a->b) with a clip edge */
Point intersect(Point a, Point b, int edge) {
    Point p;
    float dx = b.x - a.x;
    float dy = b.y - a.y;

    switch (edge) {
        case 0: /* Left edge: x = xmin_c */
            p.x = xmin_c;
            p.y = a.y + dy * (xmin_c - a.x) / dx;
            break;
        case 1: /* Right edge: x = xmax_c */
            p.x = xmax_c;
            p.y = a.y + dy * (xmax_c - a.x) / dx;
            break;
        case 2: /* Bottom edge: y = ymin_c */
            p.y = ymin_c;
            p.x = a.x + dx * (ymin_c - a.y) / dy;
            break;
        case 3: /* Top edge: y = ymax_c */
            p.y = ymax_c;
            p.x = a.x + dx * (ymax_c - a.y) / dy;
            break;
        default:
            p.x = a.x; p.y = a.y;
    }
    return p;
}

/* Check if a point is inside a clip edge */
int inside(Point p, int edge) {
    switch (edge) {
        case 0: return p.x >= xmin_c; /* Left */
        case 1: return p.x <= xmax_c; /* Right */
        case 2: return p.y >= ymin_c; /* Bottom */
        case 3: return p.y <= ymax_c; /* Top */
        default: return 0;
    }
}

/* Clip polygon against one edge */
int clip_polygon_by_edge(Point in[], int in_count, Point out[], int edge) {
    int out_count = 0;
    for (int i = 0; i < in_count; i++) {
        Point s = in[(i - 1 + in_count) % in_count];
        Point p = in[i];
        int s_inside = inside(s, edge);
        int p_inside = inside(p, edge);

        if (p_inside) {
            if (!s_inside) {
                out[out_count++] = intersect(s, p, edge);
            }
            out[out_count++] = p;
        } else if (s_inside) {
            out[out_count++] = intersect(s, p, edge);
        }
    }
    return out_count;
}

/* Draw a polygon */
void draw_polygon(Point pts[], int n, int color) {
    setcolor(color);
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        to_screen(pts[i].x, pts[i].y, &x1, &y1);
        to_screen(pts[(i + 1) % n].x, pts[(i + 1) % n].y, &x2, &y2);
        line(x1, y1, x2, y2);
    }
}

int main() {
    int gd = DETECT, gm;
    int n;
    Point polygon[MAX_VERTICES];
    Point clipped[MAX_VERTICES];
    Point temp[MAX_VERTICES];
    int count;
    float wx1, wy1, wx2, wy2;

    printf("Enter clipping window (xmin ymin xmax ymax): ");
    scanf("%f %f %f %f", &wx1, &wy1, &wx2, &wy2);

    printf("Enter number of polygon vertices (max %d): ", MAX_VERTICES);
    scanf("%d", &n);
    printf("Enter vertices (x y) one per line:\n");
    for (int i = 0; i < n; i++) {
        scanf("%f %f", &polygon[i].x, &polygon[i].y);
    }

    xmin_c = wx1; ymin_c = wy1;
    xmax_c = wx2; ymax_c = wy2;

    /* Apply Sutherland-Hodgman algorithm */
    for (int i = 0; i < n; i++) clipped[i] = polygon[i];
    count = n;

    for (int edge = 0; edge < 4; edge++) {
        count = clip_polygon_by_edge(clipped, count, temp, edge);
        for (int i = 0; i < count; i++) clipped[i] = temp[i];
        if (count == 0) break;
    }

    initgraph(&gd, &gm, "");
    settitle("Sutherland-Hodgman Polygon Clipping");

    cx = getmaxx() / 2;
    cy = getmaxy() / 2;

    /* Draw axes */
    setcolor(DARKGRAY);
    line(0, cy, getmaxx(), cy);
    line(cx, 0, cx, getmaxy());

    /* Draw clipping window */
    int sx1, sy1, sx2, sy2;
    to_screen(wx1, wy1, &sx1, &sy1);
    to_screen(wx2, wy2, &sx2, &sy2);
    setcolor(RED);
    rectangle(sx1, sy2, sx2, sy1);

    /* Draw original polygon */
    draw_polygon(polygon, n, WHITE);

    /* Draw clipped polygon */
    if (count > 0) {
        draw_polygon(clipped, count, GREEN);
    }

    setcolor(YELLOW);
    outtextxy(10, 10, "Sutherland-Hodgman Polygon Clipping");
    setcolor(WHITE);
    outtextxy(10, 30, "White = original polygon");
    setcolor(GREEN);
    outtextxy(10, 50, "Green = clipped polygon");
    setcolor(RED);
    outtextxy(10, 70, "Red = clipping window");
    outtextxy(10, getmaxy() - 20, "Press any key to exit...");

    getch();
    closegraph();
    return 0;
}
