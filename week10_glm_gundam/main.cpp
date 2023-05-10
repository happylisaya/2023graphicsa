///week10_glm_gundam 專案 把week10_glm 的程式, 拿來用!
#include <GL/glut.h>
#include "glm.h" ///下載 source.zip 有 glm.h 放 week10_glm_gundam 目錄裡
///glm.c 改檔名成 glm.cpp 放在 week10_glm_gundam 目錄裡
///把 glm.cpp 加到專案裡
///再把 Gundam.obj Gundam.mtl Diffuse.jpg 放到工作執行目錄
GLMmodel * pmodel = NULL;///有一個模型的指標,先是空的!
///Step03-1 再把上次week07上課教的 貼圖 拿來用
///1. OpenCV 2.1 裝好 (桌面/葉正聖老師) 記得加PATH,再重開CodeBlocks
///2. 設定咒語 Settings-Compiler
///3. 把 myTexture 的程式拿來用!
///4. 在 glutCreateWindow()之後, 加一行 myTexture("Diffuse.jpg");
///   glmDraw(pmodel, GLM_MATERIAL | GLM_TEXTURE);
#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可
#include <opencv/cv.h>
#include <GL/glut.h>
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
float angle=0;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if(pmodel==NULL){
        pmodel = glmReadOBJ("Gundam.obj");///Step03-1
        glmUnitize(pmodel);
        glmFacetNormals(pmodel);
        glmVertexNormals(pmodel, 90);
    }
    glPushMatrix();
        glRotatef(angle, 0, 1, 0);
        glmDraw(pmodel, GLM_MATERIAL | GLM_TEXTURE);
    glPopMatrix();
    angle++;
    ///glutSolidTeapot( 0.3 );
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week10");

    myTexture("Diffuse.jpg");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
}
