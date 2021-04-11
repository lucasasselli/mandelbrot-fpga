// Configuration
#define DEBUG_TIME
/* #define DEBUG_PALETTE */
#define DEBUG_OPENGL

#define OVERSAMPLING_FACTOR 2
#define MAX_SCREEN_WIDTH 8*1024
#define MAX_SCREEN_HEIGHT 7*768
#define MEM_PIXEL_SIZE 3
#define MEM_TEXTURE_SIZE MEM_PIXEL_SIZE*MAX_SCREEN_WIDTH*MAX_SCREEN_HEIGHT*OVERSAMPLING_FACTOR

#define MULTI_THREADING 
#define THREAD_NUMBER 2

#define DEFAULT_SCREEN_WIDTH 1024
#define DEFAULT_SCREEN_HEIGHT 768

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

#include "mandelbrot.h"
#include "palette.h"

long double off_x = 1.875e-1;
long double off_y = 5.750e-1;
long double zoom  = 3.120e-2;

unsigned int screen_width   = DEFAULT_SCREEN_WIDTH;
unsigned int screen_height  = DEFAULT_SCREEN_HEIGHT;

unsigned int texture_width  = DEFAULT_SCREEN_WIDTH*OVERSAMPLING_FACTOR;
unsigned int texture_height = DEFAULT_SCREEN_HEIGHT*OVERSAMPLING_FACTOR;

unsigned char texture_data[MEM_TEXTURE_SIZE];
GLuint tex;

void generateTexture(){

    int mand_result;
    t_complex c;
    t_rgb color;

#ifdef DEBUG_TIME
    long time_mandelbroot = clock();
#endif

    int n = 0;
    for(int j=0; j<texture_height; j++){
        for(int i=0; i<texture_width; i++){
            c.x = off_x + (long double) (i-((long double) texture_height/2.0)) / ((long double) texture_height/2.0) * zoom;
            c.y = off_y + (long double) (((long double) texture_height/2.0)-j) / ((long double) texture_height/2.0) * zoom;

#ifdef DEBUG_PALETTE

            color = palette_getColor(i/(texture_width/palette_size));

            texture_data[n++] = color.red;
            texture_data[n++] = color.green;
            texture_data[n++] = color.blue;
#else


            mand_result = mand_compute(c);

            color = palette_getColor(mand_result);

            if(mand_result == mand_max_iter){
                texture_data[n++] = 0;
                texture_data[n++] = 0;
                texture_data[n++] = 0;
            }else{
                texture_data[n++] = color.red;
                texture_data[n++] = color.green;
                texture_data[n++] = color.blue;
            }
#endif
        }
    }

#ifdef DEBUG_TIME
    time_mandelbroot = clock() - time_mandelbroot;
    printf("DEBUG TIME: Mandelbroot time: %e\n", (double) time_mandelbroot / (double) CLOCKS_PER_SEC);
#endif
}

void display(){

#ifdef DEBUG_TIME
    long time_display = clock();
#endif

    generateTexture(texture_width, texture_height, palette_size);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
    glBindTexture(GL_TEXTURE_2D, 0);

    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, tex);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0); glVertex2i(0, 0);
    glTexCoord2i(0, 1); glVertex2i(0, screen_height);
    glTexCoord2i(1, 1); glVertex2i(screen_width, screen_height);
    glTexCoord2i(1, 0); glVertex2i(screen_width, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFlush(); //don't need this with GLUT_DOUBLE and glutSwapBuffers

#ifdef DEBUG_TIME
    time_display = clock() - time_display;
    printf("DEBUG TIME: Display time: %e\n", (double) time_display / (double) CLOCKS_PER_SEC);
#endif
}

void reshape (int width, int height) {

    screen_width  = width;
    screen_height = height;

    texture_width  = width*OVERSAMPLING_FACTOR;
    texture_height = height*OVERSAMPLING_FACTOR;

#ifdef DEBUG_OPENGL
    printf("DEBUG OPENGL - Screen resolution %dx%d\n", screen_width, screen_height);
#endif

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);  
    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
    glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
    gluOrtho2D( 0.0, screen_width, screen_height, 0.0);
}

void keyPressed (unsigned char key, int x, int y) {
    switch(key){
        case 'w':
            off_y += 0.2*zoom;
            break;

        case 's':
            off_y -= 0.2*zoom;
            break;

        case 'd':
            off_x += 0.2*zoom;
            break;

        case 'a':
            off_x -= 0.2*zoom;
            break;

        case 'q':
            zoom*=2.0;
            break;

        case 'e':
            zoom*=0.5;
            break;

        case 'x':
            exit(0);

    }

    printf("%Le %Le %Le\n", off_x, off_y, zoom);
    glutPostRedisplay();
}

int main(int argc, char* argv[]){
    
    int palette_size = 256;
    int mand_size = 256;

    if(argc > 1){
        mand_size = atoi(argv[1]);
    }

    if(argc > 2){
        palette_size = atoi(argv[2]);
    }

    mand_init(mand_size);
    palette_init(palette_size);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screen_width, screen_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mandelbroot");


    glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering

    glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping

    glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses

    glutMainLoop(); // Enter GLUT's main loop 

}

// vim: fdm=syntax fdl=0
