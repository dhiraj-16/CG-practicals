#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>

using namespace std;
int p=0,q=0,r=250;
void putpixel(float x,float y){
    glColor3f(1,1,1);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
    glFlush();
}

void bresencircle(float p,float q,float r){

    float d,x,y;
    d = 3-2*r;
    x = 0;
    y = r;
    while(x<=y){

        // putpixel(x+p,y+q);
        // putpixel(x+p,-y+q);
        // putpixel(y+p,x+q);
        // putpixel(y+p,-x+q);
        // putpixel(-y+p,-x+q);
        // putpixel(-y+p,x+q);
        // putpixel(-x+p,-y+q);
        // putpixel(-x+p,y+q);
        putpixel(x+p, y+q);
        putpixel(y+p, x+q);
        putpixel(-y+p, x+q);
        putpixel(-x+p, y+q);
        putpixel(-x+p, -y+q);
        putpixel(-y+p, -x+q);
        putpixel(y+p, -x+q);
        putpixel(x+p, -y+q);
        if(d<0){
            d+=4*x+6;
        }else{
            y--;
            d+=4*(x-y)+10;
        }
        x++;
    }
    glFlush();
}
void draw(){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,0.0);
    gluOrtho2D(-500,500,-500,500);
    bresencircle(0,0,250);
    glFlush();

}

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(100,80);
    glutInitWindowSize(800,800);
    glutCreateWindow("Circle");
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}   
