#include <iostream>
#include <vector>
#include <windows.h>
#include <GL/glut.h>
#include <cstdio>
#include "graphicType.h"
using namespace std;
int winWidth = 600, winHeight = 400;
int iMode = 0;

vector <point> pointVertex;        //�������߶�������
bool isEnd=false;			        //��ʶ�����Ƿ�������
const GLint ControlN = 4;           //��4�����Ƶ㶨������bezier���߶�
color redColor(1,0,0),blackColor(0,0,0);//��ɫ����ɫ
int iMousePointNum = 0;              //��굥��ȷ�����߶������

//���ݵ�������������points����������
void drawPolygonalLine(vector<point> &points,color &c )
{
	glColor3f(c.r, c.g, c.b);
	glBegin(GL_LINE_STRIP);
    for(int i=0;i<iMousePointNum;i++)
    {
        glVertex2i(points[i].x, points[i].y);
    }
	glEnd();
}

//ͨ����m��3+1�����Ƶ㣬����m��n-1��Bezier���߶�
void drawBezierCurve(vector<Point> &points,int n,color &c)
{
    for(int i=0;i<n-1;i++)
    {
        int j = 3*i;
        GLfloat ControlP[4][3];
        for(int k=0;k<4;k++)
        {
            ControlP[k][0] = points[j].x;
            ControlP[k][1] = points[j].y;
            ControlP[k][2] = 0.0;
            j++;
        }
        glColor3f(c.r, c.g, c.b);
        glPointSize(2);
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, *ControlP);
        glEnable(GL_MAP1_VERTEX_3);
        glMapGrid1f(100, 0.0, 1.0);    //���ɾ��ȷֲ���һά�������ֵ
        glEvalMesh1(GL_LINE, 0, 100);  //����Bezier����
        if(j>=iMousePointNum)break;
    }
}

void Initial(void)//��ʼ������
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //���ô��ڱ�����ɫΪ��ɫ
}
void ChangeSize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);                 //ָ��������ʾ����
	glMatrixMode(GL_PROJECTION);            //����ͶӰ����
	glLoadIdentity();
	gluOrtho2D(0.0,winWidth,0.0,winHeight);
}
void ProcessMenu(int value)                //����˵���Ӧ
{
    iMode = value;
    glutPostRedisplay();
}

void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
    Point p0;
    if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && iMode==5)//�����������������ϵĵ�
    {
        p0.x = xMouse;
        p0.y = winHeight - yMouse;
        pointVertex.push_back(p0);
        iMousePointNum++;
    }
    else if(button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN && iMode==5)//����һ���������������
    {
        isEnd = TRUE;//����
    }
}
void PassiveMouseMove (GLint xMouse, GLint yMouse)//����ƶ�������
{
	if(iMousePointNum>=1 && !isEnd)//���ڻ�������
    {
        Point p0;
        p0.x = xMouse;
        p0.y = winHeight - yMouse;
        pointVertex.push_back(p0);
        glutPostRedisplay();       //����ִ�����»��Ʋ���
        pointVertex.pop_back();
	}
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //�õ�ǰ����ɫ��䴰��
    switch(iMode)
    {
        case 5:
            glColor3f(0.0f, 0.0f, 0.0f); //����������ɫΪ��ɫ
            glLineStipple(1, 0x00FF);    //������������Ϊ����
            glEnable(GL_LINE_STIPPLE);
            if(iMousePointNum >= 1)      //��������
            {
                drawPolygonalLine(pointVertex, blackColor);
                if(!isEnd)
                {
                    glBegin(GL_LINES);
                    glVertex2i(pointVertex[iMousePointNum-1].x, pointVertex[iMousePointNum-1].y);
                    glVertex2i(pointVertex[iMousePointNum].x, pointVertex[iMousePointNum].y);
                    glEnd();
                }
            }
            glDisable(GL_LINE_STIPPLE);
            if(isEnd)           //����Bezier���ߣ�m*3+1�����Ӧm��
            {
                drawBezierCurve(pointVertex, 4, redColor);
            }
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
	glutCreateWindow("ʵ��4_by_20002462");

    //�����˵�������˵��ص�����
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Ellispe", 1);
    glutAddMenuEntry("LineClipping", 2);
    glutAddMenuEntry("Graphic", 3);
    glutAddMenuEntry("Bezier", 4);
    glutAddMenuEntry("Bezier_Extend", 5);//ѡ��˵�5
    glutAttachMenu(GLUT_MIDDLE_BUTTON); //�����˵���������ļ�����

	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);                 //ָ�����������λص�����
	glutMouseFunc(MousePlot);                    //ָ�������Ӧ����
	glutPassiveMotionFunc(PassiveMouseMove);     //ָ������ƶ���Ӧ����
	Initial();
	glutMainLoop();
	return 0;
}
