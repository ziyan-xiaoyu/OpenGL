#include <gl/glut.h>
void Initial(void)
{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);      //���ô��ڱ�����ɫΪ��ɫ
		glMatrixMode(GL_PROJECTION);     //����ͶӰ����
		gluOrtho2D(0.0,200.0,0.0,150.0);
}

void Display(void)
{
		glClear(GL_COLOR_BUFFER_BIT);   //�õ�ǰ����ɫ��䴰��
		glColor3f(1.0f, 0.0f, 0.0f);            //���õ�ǰ�Ļ�ͼ��ɫΪ��ɫ
		glRectf(50.0f, 100.0f, 150.0f, 50.0f);    //����һ������
glFlush();                         //�������е�OpenGL����
}

int main(int argc, char* argv[])
{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //��ʼ�����ڵ���ʾģʽ
		glutInitWindowSize(400,300);                  //���ô��ڵĳߴ�
		glutInitWindowPosition(100,120);               //���ô��ڵ�λ��
		glutCreateWindow("����");                    //����һ����Ϊ���εĴ���
		glutDisplayFunc(Display);                     //���õ�ǰ���ڵ���ʾ�ص�����
		Initial();                                    //��ɴ��ڳ�ʼ��
		glutMainLoop();                             //������GLUT�¼�����ѭ��
		return 0;
}
