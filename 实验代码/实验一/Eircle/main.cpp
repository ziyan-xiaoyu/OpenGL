#include <iostream>
#include<math.h>
using namespace std;
#include "onMidPointEllispe.h"

static GLsizei iMode = 0;
int iPointNum = 0;                     //��ȷ�������Ŀ
int x_1=0,x_2=0,y_1=0,y_2=0;               //ȷ������������
int screenWidth = 600, screenHeight = 400;

void Initial(void)//��ʼ������
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //���ô��ڱ�����ɫΪ��ɫ
}

void ChangeSize(int w, int h)
{
	screenWidth = w;
	screenHeight = h;
	glViewport(0, 0, w, h);                 //ָ��������ʾ����
	glMatrixMode(GL_PROJECTION);            //����ͶӰ����
	glLoadIdentity();
	gluOrtho2D(0.0,screenWidth,0.0,screenHeight);
}

void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	switch(iMode)
	{
        case 1://��Բ�˵�
            if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)//�������
            {
                if(iPointNum == 0 || iPointNum == 2)
                {
                    iPointNum = 1;
                    x_1 = xMouse;
                    y_1 = screenHeight - yMouse;
                }
                else
                {
                    iPointNum = 2;
                    x_2 = xMouse;
                    y_2 = screenHeight - yMouse;
                    glutPostRedisplay();                  //����ִ�����»��Ʋ���
                }
            }
            break;

        case 2://��Բ��������(��shift��)����ʵ�ֵĲ˵�
            if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)//�������
            {
                if(iPointNum == 0 || iPointNum == 2)
                {
                    iPointNum = 1;
                    x_1 = xMouse;
                    y_1 = screenHeight - yMouse;
                }
                else
                {
                    iPointNum = 2;//���ƹ�����
                    if( glutGetModifiers() == GLUT_ACTIVE_SHIFT)//�ж��Ƿ��а�shift��
                    {
                        x_2 = xMouse;//��x1��x2�Ĳ���ΪԲ��ֱ��
                        y_2 = y_1 - (x_2-x_1);//y��������x��ͬ����֤���Ƶ��������κ�������
                    }
                    else//����û�а�shift�ͻ��ǻ�����Բ�;���
                    {
                        x_2 = xMouse;
                        y_2 = screenHeight - yMouse;
                    }
                    glutPostRedisplay();                  //����ִ�����»��Ʋ���
                }
            }
            break;

        default: break;
	}

	if(button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)//�һ����
	{
		iPointNum = 0;
		glutPostRedisplay();                      //����ִ�����»��Ʋ���
	}
}

void PassiveMouseMove (GLint xMouse, GLint yMouse)//����ƶ�������
{
	if(iPointNum == 1)
    {
        switch(iMode)
        {
            case 1://��Բ�˵�
                x_2 = xMouse;
                y_2 = screenHeight - yMouse;
                break;
            case 2://��Բ��������(��shift��)����ʵ�ֵĲ˵�
                if( glutGetModifiers() == GLUT_ACTIVE_SHIFT)
                {
                    x_2 = xMouse;
                    y_2 = y_1 - (x_2-x_1);
                }
                else
                {
                    x_2 = xMouse;
                    y_2 = screenHeight - yMouse;
                }
                break;
            default: break;
        }
        glutPostRedisplay();                  //����ִ�����»��Ʋ���
	}
}

void ProcessMenu(int value)//����˵���Ӧ
{
    iMode = value;
    glutPostRedisplay();
}

void onMidPointEllispe(int a,int b)//������Բ(��a,b���̰���)���е�Bresenham�㷨ɨ��ת��
{
	int x,y;
    float d1,d2;
	glBegin(GL_POINTS);
    x=0;y=b;
    d1=b*b+a*a*(-b+0.25);
    glVertex2i(x,y);
    glVertex2i(-x,-y);
    glVertex2i(-x,y);
    glVertex2i(x,-y);
    while(b*b*(x+1)<a*a*(y-0.5))
    {
        if(d1<=0)
        {
            d1+=b*b*(2*x+3);
            x++;
        }
        else
        {
            d1+=b*b*(2*x+3)+a*a*(-2*y+2);
            x++; y--;
        }
        glVertex2f(x,y);
        glVertex2f(-x,-y);
        glVertex2f(-x,y);
        glVertex2f(x,-y);
    }
    d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
    while(y>0)
    {
        if(d2<=0)
        {
            d2+=b*b*(2*x+2)+a*a*(-2*y+3);
            x++; y--;
        }
        else
        {
            d2+=a*a*(-2*y+3);
            y--;
        }
        glVertex2f(x,y);
        glVertex2f(-x,-y);
        glVertex2f(-x,y);
        glVertex2f(x,-y);
    }
	glEnd();
    glFlush();
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //�õ�ǰ����ɫ��䴰��
    glColor3f(1.0f, 0.0f, 0.0f); //���þ�����ɫΪ��ɫ

    switch(iMode)
    {
        case 1://��Բ�˵�
        case 2://��Բ��������(��shift��)����ʵ�ֵĲ˵�
            if(iPointNum == 1)           //���ƾ���
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                //����GL_FRONT_AND_BACK����ʾ��ʾģʽ������������������棻
                //����GL_LINE����ʾ��ʾ�߶Σ��������������ʾ
                glRectf(x_1,y_1,x_2,y_2);
            }
            glColor3f(0.0f, 1.0f, 0.0f); //������Բ��ɫΪ��ɫ
            glTranslated((x_1+x_2)/2, (y_1+y_2)/2, 0); //����������ԭ��ƽ�Ƶ���������
            onMidPointEllispe(abs((x_2-x_1)/2),  abs((y_2-y_1)/2)); //������Բ�����볤����
            glTranslated(-(x_1+x_2)/2,  -(y_1+y_2)/2,  0); //��ƽ��
            break;
        default: break;
    }
	glutSwapBuffers(); //����������
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //ʹ�á�˫���桱�Լ�RGBģ��
	glutInitWindowSize(600,400);
	glutInitWindowPosition(200,200);
	glutCreateWindow("20002462");

    //�����˵�������˵��ص�����
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Ellispe", 1);
    glutAddMenuEntry("Ellispe+Circle", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON); //�����˵�������Ҽ�����

	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);                //ָ�����������λص�����
	glutMouseFunc(MousePlot);                  //ָ�������Ӧ����
	glutPassiveMotionFunc(PassiveMouseMove);    //ָ������ƶ���Ӧ����

	Initial();
	glutMainLoop();
	return 0;
}

