#include <GLUT/glut.h>
#include <math.h>


struct Point {//点的位置
	GLint x; 
	GLint y;
};

struct Color {//点的颜色信息
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

void init1() {//初始化
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}

Color getPixelColor(GLint x, GLint y) {//得到点(x,y)的颜色信息
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(GLint x, GLint y, Color color) {//将点(x,y)颜色置为color
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void floodFill(GLint x, GLint y, Color oldColor, Color newColor) {
	Color color;
	color = getPixelColor(x, y);

	if (color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b)
	{
		setPixelColor(x, y, newColor);
		floodFill(x + 1, y, oldColor, newColor);
		floodFill(x, y + 1, oldColor, newColor);
		floodFill(x - 1, y, oldColor, newColor);
		floodFill(x, y - 1, oldColor, newColor);
	}
	return;
}

void draw_circle(Point pC, GLfloat radius) {//画一个圆
	GLfloat step = 1 / radius;
	GLfloat x, y;

	for (GLfloat theta = 0; theta <= 360; theta += step) {
		x = pC.x + (radius * cos(theta));
		y = pC.y + (radius * sin(theta));
		glVertex2i(x, y);
	}
}

void display(void) {
	Point pt = { 320, 240 };//圆心
	GLfloat radius = 20;    //半径

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);     //开始画圆
	draw_circle(pt, radius);
	glEnd();
	Color newColor = { 1.0f, 0.0f, 0.0f };//红色
	Color oldColor = { 1.0f, 1.0f, 1.0f };

	floodFill(320, 240, oldColor, newColor);//填充
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("种子填充");

	init1();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
