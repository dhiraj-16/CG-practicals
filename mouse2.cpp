#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#define xpix 500
#include <cstring>
using namespace std;

int i = 0, x[100], y[100];

void mouse(int button, int state, int mousex, int mousey)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        x[i] = mousex;
        y[i] = 480 - mousey;

        i++;

    }

    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)//undo(clear)the drawing
    {
        glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    glutPostRedisplay();
}
void display(void)
{
    glColor3f(1, 0, 1); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);

    for (int k = 0; k <= i; k++)
    {
        glBegin(GL_LINES);
            glVertex2f(x[k], y[k]);
            glVertex2f(x[k + 1], y[k + 1]);
        glEnd();

    }
    glFlush();     // flushes the frame buffer to the screen
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 1000);   
    glutInitWindowPosition(10, 10); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Line Drawing");

    glClearColor(1, 1, 1, 0); 
    glClear(GL_COLOR_BUFFER_BIT); 

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
