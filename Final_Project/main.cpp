#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"
GLMmodel * head = NULL;
GLMmodel * body = NULL;
GLMmodel * uparmR = NULL;
GLMmodel * lowarmR = NULL;
int show[4] = {0, 1, 1, 0};
int ID = 2;
void keyboard(unsigned char key, int x, int y) {
    if(key=='0') ID = 0;
    if(key=='1') ID = 1;
    if(key=='2') ID = 2;
    if(key=='3') ID = 3;
    glutPostRedisplay();
}
FILE * fout = NULL;
FILE * fin = NULL;
float teapotX=0, teapotY=0;
float angle=0, angle2=0, angle3=0;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glScalef(0.2, 0.2, 0.2);
        if(body==NULL){
            head = glmReadOBJ("model/head.obj");
            body = glmReadOBJ("model/body.obj");
            uparmR = glmReadOBJ("model/uparmR.obj");
            lowarmR = glmReadOBJ("model/lowarmR.obj");
        }
        if(ID==0) glColor3f(1, 0, 0);
        else glColor3f(1,1,1);
        if(show[0]) glmDraw(head, GLM_MATERIAL);

        if(ID==1) glColor3f(1, 0, 0);
        else glColor3f(1,1,1);
        if(show[1]) glmDraw(body, GLM_MATERIAL);
        glTranslatef(-1.200000, +0.453333, 0);
        glRotatef(angle, 0, 0, 1);
        glTranslatef(1.200000, -0.453333,0);

        if(ID==2) glColor3f(1, 0, 0);
        else glColor3f(1,1,1);
        if(show[2]) glmDraw(uparmR, GLM_MATERIAL);

        if(ID==3) glColor3f(1, 0, 0);
        else glColor3f(1,1,1);
        if(show[3]) glmDraw(lowarmR, GLM_MATERIAL);
        glTranslated(teapotX, teapotY, 0);

        glPopMatrix();
        glColor3f(0, 1, 0);
        glutSolidTeapot( 0.02 );
    glutSwapBuffers();
}
int oldX = 0, oldY = 0;
void motion(int x, int y){
    teapotX += (x - oldX)/150.0;
    teapotY -= (y - oldY)/150.0;
    oldX = x;
    oldY = y;
    angle = x;
    printf("glTranslatef(%f, %f, 0);\n", teapotX, teapotY);
    glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN){
        oldX = x;
        oldY = y;
        angle = x;
    }
    display();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week14");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}
