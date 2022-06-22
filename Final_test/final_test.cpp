#include<GLUT/glut.h>
#include <stdlib.h>

void myinit(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClearDepth(1.0);
	glShadeModel(GL_SMOOTH); //独立的处理图元中各个顶点的颜色,对于多边形图元，多边形内部区域的颜色将根据所有顶点的颜色差值得到

	GLfloat mat_diffuse[] = { 0.75, 0.35, 0.35, 1.0 };  //漫反射系数 
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 0.9, 0.9, 0.9, 1.0 }; //镜面反射系数 
	GLfloat mat_shininess[] = { 50.0 };

	glEnable(GL_LIGHTING);//启用灯源
	glEnable(GL_LIGHT0);//启用0号灯
	glEnable(GL_DEPTH_TEST);//启用深度测试
	glEnable(GL_BLEND);//启用颜色混合。用于实现半透明效果
	glDepthFunc(GL_LESS);//指定深度缓冲比较值,如果输入的深度值小于参考值，则通过
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//显示模式将适用于物体的所有面;面，多边形采用填充形式

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);//环境光系数和漫反射光系数,设置为相同
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);//镜面光反射  
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//设置材料反射指数  
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//光源位置
}

void mydisplay(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);     
	glPushMatrix();              

	glutSolidTeapot(1.0);
	
	glPopMatrix();                
	glutSwapBuffers();
}

void myreshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);  
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	gluLookAt(-2.0, 2.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.5, 30.0);
}

void main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Teapot");

	myinit();
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myreshape);
	glutMainLoop();
}
