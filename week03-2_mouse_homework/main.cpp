#include <GL/glut.h>
#include <stdio.h>
void display()
{
    glBegin(GL_LINE_LOOP);
    {
        glVertex2f(-0.104, 0.240);
        glVertex2f(-0.140, 0.308);
        glVertex2f(-0.168, 0.336);
        glVertex2f(-0.216, 0.356);
        glVertex2f(-0.252, 0.356);
        glVertex2f(-0.296, 0.336);
        glVertex2f(-0.336, 0.304);
        glVertex2f(-0.348, 0.268);
        glVertex2f(-0.364, 0.224);
        glVertex2f(-0.340, 0.144);
        glVertex2f(-0.308, 0.100);
        glVertex2f(-0.260, 0.060);
        glVertex2f(-0.204, 0.024);
        glVertex2f(-0.172, -0.020);
        glVertex2f(-0.124, -0.052);
        glVertex2f(-0.104, -0.060);
        glVertex2f(-0.084, -0.072);
        glVertex2f(-0.080, -0.076);
        glVertex2f(-0.048, -0.072);
        glVertex2f(-0.004, -0.044);
        glVertex2f(0.044, 0.016);
        glVertex2f(0.088, 0.056);
        glVertex2f(0.124, 0.112);
        glVertex2f(0.172, 0.204);
        glVertex2f(0.188, 0.292);
        glVertex2f(0.188, 0.340);
        glVertex2f(0.156, 0.372);
        glVertex2f(0.108, 0.380);
        glVertex2f(0.056, 0.380);
        glVertex2f(0.024, 0.372);
        glVertex2f(-0.036, 0.336);
        glVertex2f(-0.060, 0.272);
        glVertex2f(-0.076, 0.220);
    }
    glEnd();
    glutSwapBuffers();
}

void mouse (int button, int state, int x, int y)
{
    float X =  ( x-250 ) / 250.0 ;
    float Y = -( y-250 ) / 250.0 ;
    if(state==GLUT_DOWN){
        printf("    glVertex2f(%.3f, %.3f);\n", X, Y);
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("week03");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
}
