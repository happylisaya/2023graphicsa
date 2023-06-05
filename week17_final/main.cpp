#include <stdio.h>
#include <opencv/highgui.h>
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
FILE * fin = NULL;
FILE * fout = NULL;
float teapotX=0, teapotY=0, oldX=0, oldY=0;  ///有不同
float angle[20]={}, angle2[20]={};
int ID=0; ///0:head, 1:body, 2,3:left arm foot, 4,5:right arm foot, 6:leg
void keyboard(unsigned char key, int x, int y) {
    if(key=='0') ID=0;
    if(key=='1') ID=1;
    if(key=='2') ID=2;
    if(key=='3') ID=3;
    if(key=='4') ID=4;
    if(key=='5') ID=5;
    if(key=='6') ID=6;
    if(key=='s'){ ///save
        if(fout==NULL) fout = fopen("motion.txt", "w");
        for(int i=0; i<20; i++){
            fprintf(fout, "%.2f ", angle[i] );
            fprintf(fout, "%.2f ", angle2[i] );
        }
        fprintf(fout, "\n");
        printf("你寫了1行\n");
    }
    if(key=='r'){ ///read
        if(fin==NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<20; i++){
            fscanf(fin, "%f", &angle[i] );
            fscanf(fin, "%f", &angle2[i] );
        }
        glutPostRedisplay();
    }
}
void mouse(int button, int state, int x, int y) {
    oldX = x;
    oldY = y;
}

void motion(int x, int y) {
    teapotX += (x - oldX)/10.0; ///有不同
    teapotY += (oldY - y)/10.0; ///有不同
    angle[ID] += x - oldX;
    angle2[ID] += y - oldY; ///有不同
    oldX = x;
    oldY = y; ///有不同
    ///printf("glTranslatef(%.3f , %.3f , 0 );\n", teapotX, teapotY);
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
            glRotatef(180, 0, 1, 0);
            glmDraw(body, GLM_MATERIAL | GLM_TEXTURE); ///glmDraw(gundam, GLM_MATERIAL | GLM_TEXTURE);

            glPushMatrix();
                glTranslatef(0.000 , +22.300 , 0 );
                glRotatef(angle[0], 0, 1, 0);
                glRotatef(angle2[0], 1, 0, 0);
                glTranslatef(0.000 , -22.300 , 0 );
                glmDraw(head, GLM_MATERIAL | GLM_TEXTURE);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(-3.800 , +21.200 , 0 );
                glRotatef(angle[1], 0, 1, 0);
                glRotatef(angle2[1], 1, 0, 0);
                glTranslatef(3.800 , -21.200 , 0 );
                glmDraw(arm1, GLM_MATERIAL | GLM_TEXTURE);
                glPushMatrix();
                    glTranslatef(-4.300 , +18.600 , 0 );
                    glRotatef(angle[2], 0, 1, 0);
                    glRotatef(angle2[2], 1, 0, 0);
                    glTranslatef(4.300 , -18.600 , 0 );
                    glmDraw(hand1, GLM_MATERIAL | GLM_TEXTURE);
                glPopMatrix();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(+3.800 , +21.200 , 0 );
                glRotatef(angle[3], 0, 1, 0);
                glRotatef(angle2[3], 1, 0, 0);
                glTranslatef(-3.800 , -21.200 , 0 );
                glmDraw(arm2, GLM_MATERIAL | GLM_TEXTURE);
                glPushMatrix();
                    glTranslatef(+4.300 , +18.600 , 0 );
                    glRotatef(angle[4], 0, 1, 0);
                    glRotatef(angle2[4], 1, 0, 0);
                    glTranslatef(-4.300 , -18.600 , 0 );
                    glmDraw(hand2, GLM_MATERIAL | GLM_TEXTURE);
                glPopMatrix();
            glPopMatrix();

            glmDraw(bot, GLM_MATERIAL | GLM_TEXTURE);

            glPushMatrix();///左大腿
                glTranslatef(-2.000 , +14.100 , 0 );
                glRotatef(angle[5], 0, 1, 0);
                glRotatef(angle2[5], 1, 0, 0);
                glTranslatef(2.000 , -14.100 , 0 );
                glmDraw(leg1, GLM_MATERIAL | GLM_TEXTURE);

                glPushMatrix();
                    glTranslatef(-2.000 , +10.500 , 0 );
                    glRotatef(angle[6], 0, 1, 0);
                    glRotatef(angle2[6], 1, 0, 0);
                    glTranslatef(2.000 , -10.500 , 0 );
                    glmDraw(knee1, GLM_MATERIAL | GLM_TEXTURE);

                    glPushMatrix();
                        glTranslatef(-2.000 , +3.000 , 0 );
                        glRotatef(angle[7], 0, 1, 0);
                        glRotatef(angle2[7], 1, 0, 0);
                        glTranslatef(2.000 , -3.000 , 0 );
                        glmDraw(foot1, GLM_MATERIAL | GLM_TEXTURE);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();

            glPushMatrix();///右大腿
                glTranslatef(+2.000 , +14.100 , 0 );
                glRotatef(angle[8], 0, 1, 0);
                glRotatef(angle2[8], 1, 0, 0);
                glTranslatef(-2.000 , -14.100 , 0 );
                glmDraw(leg2, GLM_MATERIAL | GLM_TEXTURE);

                glPushMatrix();
                    glTranslatef(+2.000 , +10.500 , 0 );
                    glRotatef(angle[9], 0, 1, 0);
                    glRotatef(angle2[9], 1, 0, 0);
                    glTranslatef(-2.000 , -10.500 , 0 );
                    glmDraw(knee2, GLM_MATERIAL | GLM_TEXTURE);

                    glPushMatrix();
                        glTranslatef(+2.000 , +3.000 , 0 );
                        glRotatef(angle[10], 0, 1, 0);
                        glRotatef(angle2[10], 1, 0, 0);
                        glTranslatef(-2.000 , -3.000 , 0 );
                        glmDraw(foot2, GLM_MATERIAL | GLM_TEXTURE);
                    glPopMatrix();
                glPopMatrix();
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
    glutCreateWindow("week17");

    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

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
