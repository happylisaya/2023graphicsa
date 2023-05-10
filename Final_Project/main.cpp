///week12-5_TRT_keyboard_mouse 要用 keyboard mouse 來操控
#include <stdio.h>
#include <GL/glut.h>
FILE * fout = NULL; ///step02-2 一開始,檔案沒有開, NULL
FILE * fin = NULL; ///step02-2 要讀檔用的指標, 一開始也是 NULL
float teapotX=0, teapotY=0; ///幫我們看移動值
float angle=0, angle2=0, angle3=0;///step03-2 擺動作
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        ///glTranslatef(teapotX, teapotY, 0);
        ///glTranslatef(????); ///step03-2 擺動作
        glRotatef(angle, 0, 0, 1);///step03-2 擺動作
        glTranslatef(0.400000, -0.060000, 0);///step03-2
        ///glTranslatef(teapotX, teapotY, 0);///step03-2 擺動作
        glutSolidTeapot( 0.3 );
    glPopMatrix();
    glutSwapBuffers();
}
void mouse(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN){
        teapotX = (x-150)/150.0;
        teapotY = (150-y)/150.0;
        angle = x;
        printf("glTranslatef(%f, %f, 0);\n", teapotX, teapotY);
        if(fout==NULL) fout = fopen("file4.txt", "w"); ///step02-2 沒開檔,就開
        ///fprintf(fout, "%f %f\n", teapotX, teapotY); ///step02-2 要再存座標
    }
    display();
}
void keyboard(unsigned char key, int x, int y) ///step02-2 keyboard函式
{
    if(fin==NULL){ ///step02-2 如果檔案還沒 fopen(), 就開它
        fclose(fout); ///前面mouse會開fout指標, 所以要關掉
        fin = fopen("file4.txt", "r"); ///step02-2 沒開檔,就開
    }
    ///fscanf(fin, "%f %f", &teapotX, &teapotY); ///step02-2 真的讀檔
    display(); ///step02-2 重畫畫面
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week12");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard); ///step02-2 keyboard要做事囉(開檔、讀檔)

    glutMainLoop();
}
