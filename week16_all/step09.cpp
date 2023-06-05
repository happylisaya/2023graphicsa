#include <stdio.h>
#include <opencv/highgui.h> ///ʹ�� OpenCV 2.1 ���^����, ֻҪ�� High GUI ����
#include <opencv/cv.h>
#include <GL/glut.h>
#include "glm.h"

GLMmodel * head = NULL;
GLMmodel * body = NULL;
GLMmodel * left_arm = NULL;
GLMmodel * left_foot = NULL;
GLMmodel * right_arm = NULL;
GLMmodel * right_foot = NULL;
GLMmodel * leg = NULL;

int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCV�x�D
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV�Dɫ�� (��Ҫcv.h)
    glEnable(GL_TEXTURE_2D); ///1. �_���N�D����
    GLuint id; ///�ʂ�һ�� unsigned int ����, �� �N�DID
    glGenTextures(1, &id); /// �a��Generate �N�DID
    glBindTexture(GL_TEXTURE_2D, id); ///����bind �N�DID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// �N�D����, ���^���b�Ĺ��DT, ���ظ��N�D
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// �N�D����, ���^���b�Ĺ��DS, ���ظ��N�D
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// �N�D����, �Ŵ�r�ăȲ�, ������c
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// �N�D����, �sС�r�ăȲ�, ������c
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}

float teapotX=0, teapotY=0, angle=0, angle2=0, oldX=0, oldY=0;
void mouse(int button, int state, int x, int y) {
    oldX = x;
    oldY = y;
}

void motion(int x, int y) {
    teapotX += (x - oldX)/10.0;
    teapotY += (oldY - y)/10.0;
    angle += x - oldX;
    angle2 += y - oldY;
    oldX = x;
    oldY = y;
    printf("glTranslatef(%.3f , %.3f , 0 );\n", teapotX, teapotY);
    glutPostRedisplay();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glColor3f(1,1,1);
        glScalef(0.03, 0.03, 0.03);
        //glRotatef(angle, 0, 1, 0);
        glmDraw(body, GLM_MATERIAL | GLM_TEXTURE);
        glPushMatrix();
            glTranslatef(+0.000 , +4.100 , 0 );
            glRotatef(angle, 0, 1, 0);
            glRotatef(angle2, 1, 0, 0);
            glTranslatef(-0.000 , -4.100 , 0 );
            //glTranslatef(teapotX, teapotY, 0);
            glmDraw(head, GLM_MATERIAL | GLM_TEXTURE);   //�����D
        glPopMatrix();


    glPopMatrix();

    glColor3f(0,1,0);
    glutSolidTeapot( 0.01 );

    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week17");

    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);

    head = glmReadOBJ("model/head.obj");
    body = glmReadOBJ("model/body.obj"); ///gundam = glmReadOBJ("model/gundam.obj");
    left_arm = glmReadOBJ("model/left_arm.obj");
    left_foot = glmReadOBJ("model/left_foot.obj");
    right_arm = glmReadOBJ("model/right_arm.obj");
    right_foot = glmReadOBJ("model/right_foot.obj");
    leg = glmReadOBJ("model/leg.obj");

    myTexture("model/Diffuse.jpg");
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}
