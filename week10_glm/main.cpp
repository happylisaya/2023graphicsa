///請把之前的 10行 GLUT程式拿來用
#include <GL/glut.h>
#include "glm.h" ///下載 source.zip 有 glm.h 放 week10_glm 目錄裡
///glm.c 改檔名成 glm.cpp 放在 week10_glm 目錄裡
///把 glm.cpp 加到專案裡
///把模型檔 (ex. Al.obj Al.mtl ... ) 複製到 工作執行目錄
/// Build log 最後一行會說它在哪裡 (in C:\Users\.....\freeglut\bin)
///最後, 把模型檔畫出來....
GLMmodel * pmodel = NULL;///有一個模型的指標,先是空的!
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if(pmodel==NULL){
        pmodel = glmReadOBJ("Al.obj");
        glmUnitize(pmodel);
        glmFacetNormals(pmodel);
        glmVertexNormals(pmodel, 90);
    }
    glmDraw(pmodel, GLM_MATERIAL);
    ///glutSolidTeapot( 0.3 );
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week10");

    glutDisplayFunc(display);
    glutMainLoop();
}
