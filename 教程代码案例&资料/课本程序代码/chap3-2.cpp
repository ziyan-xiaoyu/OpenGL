#include <gl/glut.h>

int iPointNum = 0;                     //��ȷ�������Ŀ
int x1=0,x2=0,y1=0,y2=0;               //ȷ���ĵ�����
int winWidth = 400, winHeight = 300;     //���ڵĿ�Ⱥ͸߶�

void Initial(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);         
}

void ChangeSize(int w, int h)
{
	winWidth = w;	winHeight = h;
	glViewport(0, 0, w, h);                 //ָ��������ʾ����
	glMatrixMode(GL_PROJECTION);      //����ͶӰ����
	glLoadIdentity();
	gluOrtho2D(0.0,winWidth,0.0,winHeight);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f); 
	if(iPointNum >= 1)	{
		glBegin(GL_LINES);              //����ֱ�߶�
			glVertex2i(x1,y1);
			glVertex2i(x2,y2);
		glEnd();
	}
	glutSwapBuffers();                    //����������
}

void PassiveMouseMove (GLint xMouse, GLint yMouse)
{
	if(iPointNum == 1)	{
		x2 = xMouse;
		y2 = winHeight - yMouse;	
		glutPostRedisplay();
	}	
}


void Key(unsigned char key, int x, int y)
{
	switch(key){
		case 'p':
			if(iPointNum == 0 || iPointNum == 2)	{
				iPointNum = 1;
				x1 = x;	y1 = winHeight - y;
			}
			else	{
				iPointNum = 2;
				x2 = x;	y2 = winHeight - y;
				glutPostRedisplay();
			}
			break;
		default: break;
	}	
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //ʹ��˫���漰RGBģ��
	glutInitWindowSize(400,300); 
	glutInitWindowPosition(100,100);
	glutCreateWindow("��Ƥ���"); 
	glutDisplayFunc(Display); 
	glutReshapeFunc(ChangeSize);                //ָ�����������λص�����
	glutKeyboardFunc(Key);        //ָ��������Ӧ����
	glutPassiveMotionFunc(PassiveMouseMove);    //ָ������ƶ���Ӧ����
	Initial();                                    
	glutMainLoop();                               
	return 0;
}
