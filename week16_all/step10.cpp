#include <stdio.h>
#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可
#include <opencv/cv.h>
#include <GL/glut.h>
#include "glm.h"
GLMmodel * head = NULL;
GLMmodel * body = NULL; ///GLMmodel * gundam = NULL;
GLMmodel * arm1 = NULL, * arm2 = NULL;
int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}

float teapotX=0, teapotY=0, angle=0, angle2=0, oldX=0, oldY=0;  ///有不同
void mouse(int button, int state, int x, int y) {
    oldX = x;
    oldY = y;
}

void motion(int x, int y) {
    teapotX += (x - oldX)/10.0; ///有不同
    teapotY += (oldY - y)/10.0; ///有不同
    angle += x - oldX;
    angle2 += y - oldY; ///有不同
    oldX = x;
    oldY = y; ///有不同
    printf("glTranslatef(%.3f , %.3f , 0 );\n", teapotX, teapotY);
    glutPostRedisplay();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glScalef(2,2,2);
        glTranslatef(0, -0.4, 0);
        glPushMatrix();
            glColor3f(1,1,1);///glColor3f(1,0,0);
            glScalef(0.03, 0.03, 0.03);
            ///glRotatef(angle, 0, 1, 0);
            glmDraw(body, GLM_MATERIAL | GLM_TEXTURE); ///glmDraw(gundam, GLM_MATERIAL | GLM_TEXTURE);

            glPushMatrix();
                glTranslatef(0.000 , +22.300 , 0 );
                //glRotatef(angle, 0, 1, 0);
                //glRotatef(angle2, 1, 0, 0);
                glTranslatef(0.000 , -22.300 , 0 );
                ///glTranslatef(teapotX, teapotY, 0);
                glmDraw(head, GLM_MATERIAL | GLM_TEXTURE);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(teapotX, teapotY, 0);
                glmDraw(arm1, GLM_MATERIAL | GLM_TEXTURE);
            glPopMatrix();

        glPopMatrix();
        glColor3f(0,1,0);///中心點的位置
        glutSolidTeapot( 0.01 );///中心點的位置
    glPopMatrix();

    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week16");

    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);

    head = glmReadOBJ("model/head.obj");
    body = glmReadOBJ("model/body.obj"); ///gundam = glmReadOBJ("model/gundam.obj");
    arm1 = glmReadOBJ("model/arm1.obj");
    arm2 = glmReadOBJ("model/arm1.obj");
    myTexture("model/Diffuse.jpg");
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}
