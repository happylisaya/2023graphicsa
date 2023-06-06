#include <stdio.h>
#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可
#include <opencv/cv.h>
#include <GL/glut.h>
#include "glm.h"

GLMmodel * head = NULL;
GLMmodel * body = NULL;
GLMmodel * left_arm = NULL;
GLMmodel * right_arm = NULL;
GLMmodel * leg = NULL;
GLMmodel * left_foot = NULL;
GLMmodel * right_foot = NULL;

int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename);
    cvCvtColor(img,img, CV_BGR2RGB);
    glEnable(GL_TEXTURE_2D);
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}

FILE * fin = NULL;
FILE * fout = NULL;
float teapotX=0, teapotY=0, oldX=0, oldY=0;
float angle[12]={}, angle2[12]={};
float OldAngle[12]={}, NewAngle[12]={};
float OldAngle2[12]={}, NewAngle2[12]={};
int ID = 0;   //0:head, 1:body, 2,3:left right arm, 4:leg, 5,6:left right foot
void timer(int t) {
    printf("t:%d\n", t);
    glutTimerFunc(12, timer, t+1);
    if(t%50==0){
        if(fin==NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<12; i++){
            OldAngle[i] = NewAngle[i];
            OldAngle2[i] = NewAngle2[i];
            fscanf(fin, "%f", &NewAngle[i] );
            fscanf(fin, "%f", &NewAngle2[i] );
        }
    }
    float alpha = (t%50) / 50.0;
    for(int i=0; i<12; i++){
        angle[i] = alpha * NewAngle[i] + (1-alpha) * OldAngle[i];
        angle2[i] = alpha * NewAngle2[i] + (1-alpha) * OldAngle2[i];
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if(key=='0') ID=0;
    if(key=='1') ID=1;
    if(key=='2') ID=2;
    if(key=='3') ID=3;
    if(key=='4') ID=4;
    if(key=='5') ID=5;
    if(key=='6') ID=6;
    if(key=='s'){
        if(fout==NULL) fout = fopen("motion.txt", "w");
        for(int i=0; i<12; i++){
            fprintf(fout, "%.2f ", angle[i] );
            fprintf(fout, "%.2f ", angle2[i] );
        }
        fprintf(fout, "\n");
        printf("你寫了1行\n");
    }
    if(key=='r'){
        if(fin==NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<12; i++){
            fscanf(fin, "%f", &angle[i] );
            fscanf(fin, "%f", &angle2[i] );
        }
        glutPostRedisplay();
    }
    if(key=='p'){
        glutTimerFunc(0, timer, 0);
    }
}

void mouse(int button, int state, int x, int y) {
    oldX = x;
    oldY = y;
}

void motion(int x, int y) {
    teapotX += (x - oldX)/10.0;
    teapotY += (oldY - y)/10.0;
    angle[ID] += x - oldX;
    angle2[ID] += y - oldY;
    oldX = x;
    oldY = y;
    //printf("glTranslatef(%.3f , %.3f , 0 );\n", teapotX, teapotY);
    glutPostRedisplay();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            glScalef(6, 6, 6);
            glTranslatef(0 , -0.05, 0);
            glPushMatrix();
                glColor3f(1,1,1);
                glScalef(0.03, 0.03, 0.03);
                glRotatef(angle[6], 0, 1, 0);
                glRotatef(0, 0, 1, 0);
                glmDraw(body, GLM_MATERIAL | GLM_TEXTURE);

                ///head
                glPushMatrix();
                    glTranslatef(+0.000 , +4.100 , 0 );
                    glRotatef(angle[0], 0, 1, 0);  //左右轉
                    glRotatef(angle2[0], 1, 0, 0);  //上下轉
                    glTranslatef(-0.000 , -4.100 , 0 );
                    glmDraw(head, GLM_MATERIAL | GLM_TEXTURE);
                glPopMatrix();

                ///left_arm
                glPushMatrix();
                    glTranslatef(-1.300 , +4.700 , 0 );
                    glRotatef(angle[1], 0, 1, 0);
                    glRotatef(angle2[1], 0, 0, 1);
                    glTranslatef(+1.300 , -4.700 , 0 );
                    glmDraw(left_arm, GLM_MATERIAL | GLM_TEXTURE);
                glPopMatrix();

                ///right_arm
                glPushMatrix();
                    glTranslatef(+1.300 , +4.700 , 0 );
                    glRotatef(angle[2], 0, 1, 0);
                    glRotatef(angle2[2], 1, 0, 0);
                    glTranslatef(-1.300 , -4.700 , 0 );
                    //glTranslatef(teapotX, teapotY, 0);
                    glmDraw(right_arm, GLM_MATERIAL | GLM_TEXTURE);
                glPopMatrix();

                ///leg
                glPushMatrix();
                    glTranslatef(0.000 , +2.800 , 0 );
                    glRotatef(angle[3], 0, 1, 0);
                    glTranslatef(0.000 , -2.800 , 0 );
                    //glTranslatef(teapotX, teapotY, 0);
                    glmDraw(leg, GLM_MATERIAL | GLM_TEXTURE);
                glPopMatrix();

                ///left_foot
                glPushMatrix();
                    glTranslatef(-0.500 , +0.700 , -0.3 );
                    glRotatef(angle[4], 0, 1, 0);
                    glRotatef(angle2[4], 1, 0, 0);
                    glTranslatef(+0.500 , -0.700 , +0.3 );
                    //glTranslatef(teapotX, teapotY, 0);
                    glmDraw(left_foot, GLM_MATERIAL | GLM_TEXTURE);
                glPopMatrix();

                ///right_foot
                glPushMatrix();
                    glTranslatef(+0.500 , +0.700 , -0.3 );
                    glRotatef(angle[5], 0, 1, 0);
                    glRotatef(angle2[5], 1, 0, 0);
                    glTranslatef(-0.500 , -0.700 , +0.3 );
                    //glTranslatef(teapotX, teapotY, 0);
                    glmDraw(right_foot, GLM_MATERIAL | GLM_TEXTURE);
                glPopMatrix();


            glPopMatrix();
            glColor3f(0,1,0);
            glutSolidTeapot( 0.01 );
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
    body = glmReadOBJ("model/body.obj");
    left_arm = glmReadOBJ("model/left_arm.obj");
    right_arm = glmReadOBJ("model/right_arm.obj");
    leg = glmReadOBJ("model/leg.obj");

    left_foot = glmReadOBJ("model/left_foot.obj");
    right_foot = glmReadOBJ("model/right_foot.obj");

    myTexture("model/color2.jpg");
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}
