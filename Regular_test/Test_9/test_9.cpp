#include <GLUT/glut.h>
#include <math.h>
#include<Windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
using namespace std;
float	rtri=0.0;
float	rtri2;
GLfloat points0[5][3] = { { 0, 1,  0}, {-1, -1, 1}, { 1, -1, 1}, {	1, -1, -1},{-1, -1,-1} };
GLfloat points1[8][3] = { { 1, 1, -1 }, {-1, 1, -1}, {-1, 1, 1}, { 1, 1, 1},
    { 1, -1, 1 }, {-1, -1, 1}, {-1,-1,-1}, { 1, -1, -1} };
GLfloat Colors0[4][3] = { {1,0,0},{0,1,0}, {0,0,1},{1,1,0} };	//四棱锥的颜色

int vertice0[4][3] = { {0,1,2},{0,2,3},{0,3,4},{0,4,1} };	//四棱锥的顶点号序列

void InitGL(GLvoid)
{
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_COLOR_MATERIAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
void CreatePyramid()
{
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 4; i++)
    {
        glColor3fv(Colors0[i]);
        for (int j = 0; j < 3; j++)
        {
            int VtxId = vertice0[i][j];
            glVertex3fv(points0[VtxId]);
        }
    }
    glEnd();
    glBegin(GL_QUADS); 	//构建底面
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < 4; i++)
        glVertex3fv(points0[i]);
    glEnd();
}

void display(void)
{
    
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.5f, 0.0f, -6.0f);	//平移至左侧
    glRotatef(rtri+0.2f, 0.0f, 1.0f, 0.0f);	//旋转一个角度
    CreatePyramid();	//创建三角塔

    glLoadIdentity();	//将矩阵归一化回原样    
    glTranslatef(1.5f, 0.0f, -6.0f);	//平移到右侧
    glRotatef(rtri-1.2f, 0.0f, 1.0f, 0.0f);	//旋转一个角度
    CreatePyramid();	//创建三角塔
    glPopMatrix();

    glutSwapBuffers();
}
void reshape(int width, int height)
{
    if (height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Pyramid");
    InitGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
}