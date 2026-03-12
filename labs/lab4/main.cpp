#include <graphics.h>
#include <conio.h>

void drawCirclePoints(int xc, int yc, int x, int y)
{
    putpixel(xc + x, yc + y, WHITE);
    putpixel(xc - x, yc + y, WHITE);
    putpixel(xc + x, yc - y, WHITE);
    putpixel(xc - x, yc - y, WHITE);
    putpixel(xc + y, yc + x, WHITE);
    putpixel(xc - y, yc + x, WHITE);
    putpixel(xc + y, yc - x, WHITE);
    putpixel(xc - y, yc - x, WHITE);
}

int main()
{
    int gd = DETECT, gm;
    int xc, yc, r;
    int x = 0, y, p;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    printf("Enter center coordinates (xc yc): ");
    scanf("%d %d", &xc, &yc);

    printf("Enter radius of circle: ");
    scanf("%d", &r);

    y = r;
    p = 1 - r;

    while (x <= y)
    {
        drawCirclePoints(xc, yc, x, y);
        x++;

        if (p < 0)
        {
            p = p + 2 * x + 1;
        }
        else
        {
            y--;
            p = p + 2 * x - 2 * y + 1;
        }
    }

    getch();
    closegraph();
    return 0;
}