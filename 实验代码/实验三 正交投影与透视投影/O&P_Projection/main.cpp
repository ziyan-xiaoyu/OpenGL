#include<iostream>
#include<vector>
#include<windows.h>
#include<gl/glut.h>
using namespace std;
#include "setLookAt.h"       //������ά�����point3D�Ķ���ͽ����ӽ��Ӿ�Ч������setLookAt()
#include "getAxis.h"         //�����᳤��������ά������ͼ�Σ�x��Ϊ��ɫ��y��Ϊ��ɫ��z��Ϊ��ɫ
#include "getTetrahedron.h"  //����4����ά�����ABCD������������ͼ��

static GLsizei iMode = 1;   //����ͼ�˵���
float axisLength = 20.0;    //��ά�����᳤

GLuint objectID,axisID;          //���������ID��������ID��
int winWidth = 400, winHeight = 200;    //���ڵĿ�Ⱥ͸߶�
static float angle = 45.0;		 //�����������ת��
static point3D s_eye(5.0,5.0,5.0);      //�۲��λ��
static point3D s_at(0.0,0.0,0.0);       //�ӵ�����
static point3D A(2.0f,0.0f,0.0),B(2.0f,1.0f,0.0),C(0.0f,1.0f,0.0),D(1.0f,1.0f,1.0);//�������ĵ�����

void initial(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //���ô��ڱ�����ɫΪ��ɫ
}

void ChangeSize(GLsizei w, GLsizei h)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�����ģʽΪ�߿�
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);                 //ָ��������ʾ����
	glMatrixMode(GL_PROJECTION);            //����ͶӰ����
	glLoadIdentity();
}

void triangle(GLsizei mode)     //������ͼ�Ļ��ƣ�mode����ѡ��orѡ��
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�����ģʽΪ�߿�
    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT ,vp); //������������½����ꡢ��Ⱥ͸߶���Ϣ
    int w = vp[2], h = vp[3];
    float aspect;
    if(w < h){
        aspect = (float)w/(float)h;
    }
    else{
        aspect = (float)h/(float)w;
    }
	glMatrixMode(GL_MODELVIEW);            //ָ����ǰ����ģ����ͼ�����ջ
	glLoadIdentity();                      //�ָ���ʼ����ϵ������ǰ���ƶ�����Ļ����

	if(mode==1)//������
    {
        setLookAt(iMode, s_eye, s_at);//���ݲ˵�iModeѡ������ͼ�������ӽ��Ӿ�Ч��
    	glMatrixMode(GL_PROJECTION);            //����ͶӰ����
        glLoadIdentity();
        glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, -5.0);//��������������ά�����۲�����壬����һ������ͶӰ����
    }
    else//������
    {
        setLookAt(iMode, angle, s_eye, s_at);//���ݲ˵�iModeѡ�������ͼ����������ԭ��Χ��ĳ��������תangle�������ӽ��Ӿ�Ч��
    	glMatrixMode(GL_PROJECTION);            //����ͶӰ����
        glLoadIdentity();
        gluPerspective(45.0f, aspect, 0.0f, 10.0f);//��������������ά͸�ӹ۲������
    }
    glCallList(objectID);                   //ִ����ʾ�б����洢�ĺ���
    glCallList(axisID);
}

void SpecialKeys(int key, int x, int y)
{
    if(key == GLUT_KEY_UP)
    {
        angle = angle + 1;
    }
    else if(key == GLUT_KEY_DOWN)
    {
        angle = angle - 1;
    }
    glutPostRedisplay();//ˢ��

}

void ProcessMenu(int value)//����˵���Ӧ
{
    iMode = value;
    glutPostRedisplay();
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    axisID = getAxis(axisLength);             //�����᳤axisLength����XYZ��ά����ϵ
    objectID = getTetrahedron( A, B, C, D);     //4��ABCD����������ͼԪ

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�����ģʽΪ�߿�
    //������
    glViewport(0, 0, 200, 200);//ָ����0��0��ʼ�������Ϊ200������
    triangle(1);
    //������
    glViewport(200, 0, 200, 200);//ָ����200��0��ʼ�������Ϊ200������
    triangle(2);
    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE  | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("20002462");//������
    //�����˵�������˵��ص�����
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("To__XOZ(V)",1);
    glutAddMenuEntry("To__XOY(H)",2);
    glutAddMenuEntry("To__YOZ(W)",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);//���˵�������Ҽ�����
    initial();
    glutDisplayFunc(Display);		//ָ�������ػ���Ӧ����
    glutReshapeFunc(ChangeSize);    //ָ�����ڴ�С�ı���Ӧ����
    glutSpecialFunc(SpecialKeys);   //ָ�����ܼ���Ӧ����
    glutMainLoop();
    return 0;
}
