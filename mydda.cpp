#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>

using namespace std;

void putpixel(float x, float y)
{   glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}

void dda(float x1,float y1,float x2,float y2){
    float x,y;
    
    float dx,dy;
    dx = x2-x1;
    dy = y2-y1;
    float step;
    if(abs(dx)>abs(dy)){
        step = abs(dx);
    }else{
        step = abs(dy);
    }
    float xinc = dx/step;
    float yinc = dy/step;
    x = x1;
    y = y1;
    int i=1;
    while(i<=step){
        putpixel(x,y);
        i++;
        x = x+xinc;
        y = y+yinc;
    }
}

void menu(){
    float x1,y1,x2,y2;
    dda(-100,0,100,0);

}
void draw(){
    glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	gluOrtho2D(-200, 250, -200, 250);

    menu();
    glFlush();
}


int main(int argc,char **argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(100,80);
    glutCreateWindow("DDA");
    glutDisplayFunc(draw);
    glutMainLoop();

    
}
