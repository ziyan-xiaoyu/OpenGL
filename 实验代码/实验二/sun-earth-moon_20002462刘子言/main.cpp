#include <gl/glut.h>
#include <iostream>
#include <time.h>
using namespace std;

static int angle = 0;    //表示旋转的角度

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//让太阳、地球、月亮有近大远小的透视效果
	glMatrixMode(GL_PROJECTION);    //指定当前操作投影矩阵堆栈
	glLoadIdentity();               //重置投影矩阵
	gluPerspective(75, 1, 0.001f, 1000000000000.0f); //指定透视投影的观察空间
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 2, 0, 0, -1, 0.0f, 1.0f, 0.0f); //视点转换（头位置，眼睛看向的位置，头顶朝向位置）

	//太阳
	glPushMatrix();
	glColor3ub(255, 128, 0);  //用ub后缀，设置255为颜色最大值
	glutSolidSphere(0.22, 200, 200);  //绘制太阳
	glPopMatrix();

	//地球
	glPushMatrix();
    glColor3ub(50, 205, 255);
	glRotated(angle, 1.0, 1.0, 1.0);  //公转
	glTranslatef(0.5, 0.5, -0.5);     //平移
	glutSolidSphere(0.1, 200, 200);   //绘制地球
	glPopMatrix();

	//月亮
	glPushMatrix();
	glColor3ub(255, 235, 205);
	glRotated(angle, 1.0, 1.0, 1.0);  //移动到地球旁边旋转
	glTranslatef(0.5, 0.5, -0.5);     //平移
	glRotated(angle, 1.0, 1.0, 1.0);  //假设原点为地球旋转
	glTranslatef(-0.15, -0.15, 0.15); //平移
	glutSolidSphere(0.05, 200, 200);  //绘制月亮
	glPopMatrix();

	glutSwapBuffers();
}

//计时增加角度
void angleAdd(void)
{
	static int m = 0;
	m++;
	if(m % 300000 == 0)
    {
		++angle;
		if(angle >= 360)
            angle = 0;
		Display();
	}
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("sun-earth-moon 20002462");
	glutDisplayFunc(Display);

	//表示在CPU空闲的时间调用某一函数
	glutIdleFunc(&angleAdd);
    glEnable(GL_DEPTH_TEST);
	//因为在OpenGL中默认深度检测是未开启的，所以后绘制的物体会覆盖先绘制的物体。
    //为了避免有时候月亮本应该被地球挡住但是却显示在地球上面，需要启动深度测试，解决z方向上的问题
	glutMainLoop();
	return 0;
}
