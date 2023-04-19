#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;

int line_co_ordinates[4],i=0;

void BSA_Algo(int xi,int yi,int xf,int yf){
    int P;
    int dx=xf-xi;
    int dy=yf-yi;
    int x=xi;
    int y=yi;
    if(dx<0){
        dx=-dx;
    }
    if(dy<0){
        dy=-dy;
    }
    int x_change=1;
    int y_change=1;
    if(xi>xf){
        x_change=-1;
    }
    if(yi>yf){
        y_change=-1;
    }
    glVertex2i(x,y);
    if(dx==0){
        glBegin(GL_POINTS);
        for(int i=1;i<dy;i++){
            y=y+y_change;
            glVertex2i(x,y);
        }
        glEnd();
        return;
    }
    if(dy==0){
        glBegin(GL_POINTS);
        for(int i=1;i<dx;i++){
            x=x+x_change;
            glVertex2i(x,y);
        }
        glEnd();
        return;
    }
    glBegin(GL_POINTS);
    if(dx>dy){
        P=2*dy-dx;
        for(int i=0;i<dx;i++){
            if(P>0){
                y+=y_change;
                P=P+2*(dy-dx);
            }
            else{
                P=P+2*dy;
            }
            x+=x_change;
            glVertex2i(x,y);
        }
    }
    else{
        P=2*dx-dy;
        for(int i=0;i<dy;i++){
            if(P>0){
                x+=x_change;
                P=P+2*(dx-dy);
            }
            else{
                P=P+2*dx;
            }
            y+=y_change;
            glVertex2i(x,y);
        }
    }
    glEnd();
}

void mouse_input(int button,int state,int x,int y){
    if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN&&i<4){
        line_co_ordinates[i]=x;
        i=i+1;
        line_co_ordinates[i]=500-y;
        i=i+1;
    }
    if(i==4){
        glColor3f(1.0,0.0,0.0);
        BSA_Algo(line_co_ordinates[0],line_co_ordinates[1],line_co_ordinates[2],line_co_ordinates[3]);
        glutSwapBuffers();
        i=0;
    }
}

void render_function(){
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    gluOrtho2D(0,500,0,500);
    glBegin(GL_POINTS);
    BSA_Algo(0,250,500,250);
    BSA_Algo(250,0,250,500);
    glEnd();
    glFlush();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Mouse Input (Bresenham)");
    glutDisplayFunc(render_function);
    glutMouseFunc(mouse_input);
    glutMainLoop();
    return 0;
}