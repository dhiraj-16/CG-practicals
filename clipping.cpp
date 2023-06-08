#include <stdio.h>
#include <GL/glut.h>
#define outcode int
double xmin = 50, ymin = 50, xmax = 100, ymax = 100; // Window boundaries
double xvmin = 150, yvmin = 150, xvmax = 400, yvmax = 400; // Viewport
boundaries
// bit codes for the right, left, top, & bottom
const int RIGHT = 8;
const int LEFT = 2;
const int TOP = 4;
const int BOTTOM = 1;
void putPixel(float x, float y)
{
glColor3f(1,1,1);
glBegin(GL_POINTS);
glVertex2f(x,y);
glEnd();
glFlush();
}
// used to compute bit codes of a point
outcode ComputeOutCode(double x, double y);
void clip(double x0, double y0, double x1, double y1)
{
outcode outcode0, outcode1, outcodeOut;
bool accept = false, done = false;
outcode0 = ComputeOutCode(x0, y0);
outcode1 = ComputeOutCode(x1, y1);
do
{
if (!(outcode0 | outcode1)) // logical or is 0 Trivially accept &

exit
{
accept = true;
done = true;
}
else if (outcode0 & outcode1)
done = true;
else

{
double x, y;
outcodeOut = outcode0 ? outcode0 : outcode1;
// Now find the intersection point;
// use formulas y = y0 + slope * (x - x0) & x = x0 +

(1/slope)* (y - y0)

if (outcodeOut & TOP)
// point is above the clip rectangle
{
x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
y = ymax;
}
else if (outcodeOut & BOTTOM)
// point is below the clip rectangle
{
x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
y = ymin;
}
else if (outcodeOut & RIGHT)
// point is to the right of clip rectangle
{
y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
x = xmax;
}
else
// point is to the left of clip rectangle
{
y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
x = xmin;
}
if (outcodeOut == outcode0)
{
x0 = x;
y0 = y;
outcode0 = ComputeOutCode(x0, y0);
}
else
{
x1 = x;
y1 = y;

outcode1 = ComputeOutCode(x1, y1);
}
}
} while (!done);
if (accept)
{ // Window to viewport
mappings

double sx = (xvmax - xvmin) / (xmax - xmin); // Scale parameters
double sy = (yvmax - yvmin) / (ymax - ymin);
double vx0 = xvmin + (x0 - xmin) * sx;
double vy0 = yvmin + (y0 - ymin) * sy;
double vx1 = xvmin + (x1 - xmin) * sx;
double vy1 = yvmin + (y1 - ymin) * sy; // draw a red colored

viewport

glColor3f(1.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(xvmin, yvmin);
glVertex2f(xvmax, yvmin);
glVertex2f(xvmax, yvmax);
glVertex2f(xvmin, yvmax);
glEnd();
glColor3f(1.0, 1.0, 0.0); // draw blue colored clipped line
glBegin(GL_LINES);
glVertex2d(vx0, vy0);
glVertex2d(vx1, vy1);
glEnd();
}
}
outcode ComputeOutCode(double x, double y)
{
outcode code = 0;
if (y > ymax) // above the clip window
code |= TOP;
else if (y < ymin) // below the clip window
code |= BOTTOM;
if (x > xmax) // to the right of clip window
code |= RIGHT;
else if (x < xmin) // to the left of clip window
code |= LEFT;
return code;

}
void display()
{
double x0 = 60, y0 = 20, x1 = 80, y1 = 120;
double x2 = 60, y2 = 20, x3 = 100, y3 = 80;
double x4 = 100, y4 = 80, x5 = 40, y5 = 80;
double x6 = 40, y6 = 80, x7 = 80, y7 = 120;
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0, 0.0, 0.0);
glLineWidth(2);
glBegin(GL_LINES);
glVertex2d(x0, y0);
glVertex2d(x1, y1);
glVertex2d(x2, y2);
glVertex2d(x3, y3);
glVertex2d(x4, y4);
glVertex2d(x5, y5);
glVertex2d(x6, y6);
glVertex2d(x7, y7);
glEnd();
// draw a blue colored window
glColor3f(1.0, 1.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(xmin, ymin);
glVertex2f(xmax, ymin);
glVertex2f(xmax, ymax);
glVertex2f(xmin, ymax);
glEnd();
clip(x0, y0, x1, y1);
clip(x2, y2, x3, y3);
clip(x4, y4, x5, y5);
clip(x6, y6, x7, y7);
glFlush();
}
void myinit()
{
glClearColor(0.0, 0.0, 0.0, 0.0);
glColor3f(1.0, 0.0, 0.0);
glPointSize(1.0);
glMatrixMode(GL_PROJECTION);

glLoadIdentity();
gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}
int main(int argc, char **argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(500, 500);
glutInitWindowPosition(0, 0);
glutCreateWindow("Cohen Suderland Line Clipping Algorithm");
glutDisplayFunc(display);
myinit();
glutMainLoop();
}
