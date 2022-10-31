#include <gl/glut.h>
GLuint OlympicRings;

void Initial(void)
{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);    
		OlympicRings = glGenLists(1);
		glNewList(OlympicRings, GL_COMPILE);
			glColor3f(1.0, 1.0, 0.0);
			glTranslatef(-22.0, 0.0, 0.0);
			glutSolidTorus(0.5, 20.0, 15, 50);  //���ƻ�ɫ��
			glColor3f(0.0, 1.0, 0.0);
			glTranslatef(44.0, 0.0, 0.0);
			glutSolidTorus(0.5, 20.0, 15, 50);  //������ɫ��
			glColor3f(0.0, 0.0, 0.0);
			glTranslatef(-22.0, 30.0, 0.0);
			glutSolidTorus(0.5, 20.0, 15, 50);  //���ƺ�ɫ��
			glColor3f(0.0, 0.0, 1.0);
			glTranslatef(-42.0, 0.0, 0.0);
			glutSolidTorus(0.5, 20.0, 15, 50);  //������ɫ��
			glColor3f(1.0, 0.0, 0.0);
			glTranslatef(84.0, 0.0, 0.0);
			glutSolidTorus(0.5, 20.0, 15, 50);  //���ƺ�ɫ��
		glEndList();
}

void ChangeSize(int w, int h)
{
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D (-70.0f, 70.0f, -70.0f, 70.0f);
}

void Display(void)
{
		glClear(GL_COLOR_BUFFER_BIT); 
		glMatrixMode(GL_MODELVIEW);	
		glLoadIdentity();
		
		glCallList(OlympicRings);   //������ʾ�б�
		
		glFlush(); 
}

int main(int argc, char* argv[])
{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
		glutInitWindowSize(400,400);                  
		glutInitWindowPosition(100,100);              
		glutCreateWindow("OpenGLģ�ͻ��ƺ���ʾ��"); 
		glutDisplayFunc(Display);
		glutReshapeFunc(ChangeSize);
		Initial();                                    
		glutMainLoop();                               
		return 0;
}