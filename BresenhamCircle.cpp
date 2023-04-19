#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>

// Function to set a pixel using coordinates
void setPixel( int x, int y ) {
    glBegin( GL_POINTS );
        glVertex2f(x, y);
    glEnd();
    glFlush();
}

// Function to execute Bresenham's Circle Algo
void bresenhamCircle( int xc, int yc, int r ) {
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Bresengam Circle");
    glClearColor(0.0, 0.0, 0.0, 0.0);
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
	gluOrtho2D(0.0, 1000.0, 0.0, 1000.0);

    // int xc = 500, yc = 500, r = 200;
    // Calculating initial decision parameter
    int d = 3 - 2 * r;

    int x = 0, y = r;

    while( x <= y ) {
        // Plotting points of circle in all 8 octants
        setPixel( xc + x, yc + y );
        setPixel( xc + y, yc + x );
        setPixel( xc + y, yc - x );
        setPixel( xc + x, yc - y );
        setPixel( xc - x, yc - y );
        setPixel( xc - y, yc - x );
        setPixel( xc - y, yc + x );
        setPixel( xc - x, yc + y );

        // Updating value of decision parameter
        if( d < 0 ) {
            d += 4 * x + 6;
        } else if( d > 0 ) {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

int main(int argc, char** argv) {
    glutInit( &argc, argv );
    bresenhamCircle( 500, 500, 100 );
    glutMainLoop();
    return 0;
}