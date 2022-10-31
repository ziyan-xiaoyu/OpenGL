#include <gl/glut.h>
#include <iostream>
#include <time.h>
using namespace std;

static int angle = 0;    //��ʾ��ת�ĽǶ�

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//��̫�������������н���ԶС��͸��Ч��
	glMatrixMode(GL_PROJECTION);    //ָ����ǰ����ͶӰ�����ջ
	glLoadIdentity();               //����ͶӰ����
	gluPerspective(75, 1, 0.001f, 1000000000000.0f); //ָ��͸��ͶӰ�Ĺ۲�ռ�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 2, 0, 0, -1, 0.0f, 1.0f, 0.0f); //�ӵ�ת����ͷλ�ã��۾������λ�ã�ͷ������λ�ã�

	//̫��
	glPushMatrix();
	glColor3ub(255, 128, 0);  //��ub��׺������255Ϊ��ɫ���ֵ
	glutSolidSphere(0.22, 200, 200);  //����̫��
	glPopMatrix();

	//����
	glPushMatrix();
    glColor3ub(50, 205, 255);
	glRotated(angle, 1.0, 1.0, 1.0);  //��ת
	glTranslatef(0.5, 0.5, -0.5);     //ƽ��
	glutSolidSphere(0.1, 200, 200);   //���Ƶ���
	glPopMatrix();

	//����
	glPushMatrix();
	glColor3ub(255, 235, 205);
	glRotated(angle, 1.0, 1.0, 1.0);  //�ƶ��������Ա���ת
	glTranslatef(0.5, 0.5, -0.5);     //ƽ��
	glRotated(angle, 1.0, 1.0, 1.0);  //����ԭ��Ϊ������ת
	glTranslatef(-0.15, -0.15, 0.15); //ƽ��
	glutSolidSphere(0.05, 200, 200);  //��������
	glPopMatrix();

	glutSwapBuffers();
}

//��ʱ���ӽǶ�
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

	//��ʾ��CPU���е�ʱ�����ĳһ����
	glutIdleFunc(&angleAdd);
    glEnable(GL_DEPTH_TEST);
	//��Ϊ��OpenGL��Ĭ����ȼ����δ�����ģ����Ժ���Ƶ�����Ḳ���Ȼ��Ƶ����塣
    //Ϊ�˱�����ʱ��������Ӧ�ñ�����ס����ȴ��ʾ�ڵ������棬��Ҫ������Ȳ��ԣ����z�����ϵ�����
	glutMainLoop();
	return 0;
}
