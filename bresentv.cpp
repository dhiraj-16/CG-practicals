#include <GL/freeglut.h>
#include <GL/gl.h>
#define sign(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))
void putpixel(float x, float y){
    glPointSize(3);
    glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}

void bresenham(float x1,float y1,float x2,float y2){
    float dx,dy,xc,yc,temp,swap=0,p,x,y;
    dx = abs(x2-x1);
    dy = abs(y2-y1);
    // xc = sign(x2 - x1);
    // yc = sign(y2 - y1);
    if(x2-x1>=0){
        xc = 1;
    }else{
        xc = -1;
    }
    if(y2-y1>=0){
        yc = 1;
    }else{
        yc = -1;
    }
    if(dy>dx){
        temp = dx;
        dx = dy;
        dy = temp;
        swap=1;
    }
    p = 2*dy - dx ;
    x = x1;
    y = y1;
    for(int i = 1;i<=dx;i++){
        
        
        putpixel(x,y);
        if(p>=0){
            if(swap){
                x+=xc;
            }else{
                y+=yc;
            }
            p=p+ 2*(-dx);
        }
        if(swap){
            y+=yc;
        }
        else{
            x+=xc;
        }
        p+=2*dy;
    }

}
void menu(){
    glColor3f(1.0, 1.0, 0.0);
    bresenham(-200,0,-50,0);
    bresenham(-50,0,-80,-50);
    bresenham(-80,-50,80,-50);
    bresenham(80,-50,50,0);
    bresenham(50,0,200,0);
    bresenham(200,0,200,150);
    bresenham(-200,150,200,150);
    bresenham(-200,150,-200,0);
    glColor3f(1.0, 0.0, 0.0);
    bresenham(-180,20,180,20);
    bresenham(180,20,180,130);
    bresenham(180,130,-180,130);
    bresenham(-180,130,-180,20);
}
void draw(){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,0.0);
    gluOrtho2D(-300, 250, -300, 250);
    menu();
    glFlush();
    

}

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(100,80);
    glutInitWindowSize(800,800);
    glutCreateWindow("Bresenham");
    glutDisplayFunc(draw);
    glutMainLoop();


}
