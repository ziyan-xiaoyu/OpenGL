#include <iostream>
#include <vector>
using namespace std;
#include "lineClipping.h"

int screenWidth = 600, screenHeight = 400;

int iKeyPointNum = 0;               //����'p'ȷ��ֱ�߶ζ˵����Ŀ��0-�ޡ�1-��ʼ�㡢2-��ֹ��
int iMousePointNum= 0;              //��굥��ȷ���ü����ڵ����Ŀ��0-�ޡ�1-��ʼ�㡢2-��ֹ��
int xw1=0,yw1=0;                    //�ü����ڵ���ʼ����ֵ
int xw2=0,yw2=0;	                 //���Ʋü�����ʱ����������ƶ�ʱ������ֵ

rect winObj;                        //��׼���βü����ڶ���
point p[10];                        //��point���͵����� ��¼��׼���߶ζ˵�
point p_sub[10];                    //��point���͵����� ��¼ÿһ�βü����ĵ�
int i=0;                            //��¼���߶ζ˵����
int k=0;                            //��¼�ü�����Ķ˵�ĸ���
vector<point> points;               //�ü�ʱ���ض˵������

//����ΪLiang_Barsky�ü��㷨����
/***********************************************
*���p����<0�����㡢����umax����֤umax�����uֵ
*���p����>0�����㡢����umin����֤umin����Сuֵ
*���umax>umin������0�����򷵻�1
***********************************************/
int Clip_Top(float p,float q,float &umax,float &umin)
{
	float r=0.0;
    if(p<0.0)	//�߶δӲü������ⲿ���쵽�ڲ���ȡ���ֵr������umax
	{
		r=q/p;
		if (r>umin) return 0;	//umax>umin���������֮
		else if (r>umax)  umax=r;
	}
	else if(p>0.0)      //�߶δӲü������ڲ����쵽�ⲿ,ȡ��Сֵr������umin
		{
			r=q/p;
			if (r<umax) return 0;	//umax>umin���������֮
			else if(r<umin)  umin=r;
		}
	   else 		//p=0ʱ���߶�ƽ���ڲü�����
	      if(q<0.0) return 0;
	 return 1;
}
/*************************************************************
*��֪winRect�����ζ��󣬴�ű�׼�ü�����4������Ϣ
*    points����Ķ�̬���飬���ֱ��2���˵���Ϣ
*���ݲü����ڵ����ұ߽磬��umax��
*���ݲü����ڵ��¡��ϱ߽磬��umin
*���umax>umin���ü����ں�ֱ���޽��㣬������ü���ֱ���¶˵�
***************************************************************/
void Line_Clipping(vector<point> &Points,rect & winRect)
{
	//�Ƚ����ұ߽磬�������umax
	point &p_1=Points[0],&p_2=Points[1];
	float dx=p_2.x-p_1.x,dy=p_2.y-p_1.y,umax=0.0,umin=1.0;
	point p=p_1;
	if (Clip_Top(-dx,p_1.x- winRect.w_xmin,umax,umin))  //��߽�
		if (Clip_Top(dx,winRect.w_xmax-p_1.x, umax,umin)) //�ұ߽�
			//�Ƚ��¡��ϱ߽磬�����С��umin
			if (Clip_Top(-dy,p_1.y- winRect.w_ymin, umax,umin)) //�±߽�
				if (Clip_Top(dy,winRect.w_ymax-p_1.y, umax,umin)) //�ϱ߽�
				{//��ü���ֱ���¶˵㣨ѡ��ֱ�ӽ��������ȫ�ֱ�����
					p_sub[k].x=(int)(p.x+umax*dx);
					p_sub[k].y=(int)(p.y+umax*dy);
					p_sub[k+1].x=(int)(p.x+umin*dx);
					p_sub[k+1].y=(int)(p.y+umin*dy);
					k = k+2;
					cout<<k<<endl;
				}
}

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

void Key(unsigned char key, int xMouse, int yMouse)   //ָ��������Ӧ����
{
	switch(key)
	{
		case 'p'://�������߶�
			if(iKeyPointNum == 0 || iKeyPointNum == 2)//0Ϊ��ʼ����1Ϊ���ڻ���2Ϊ������
            {
                if(iKeyPointNum == 2)
                {
                    i = 0;k = 0;
                }
                iKeyPointNum = 1;
                p[i].x = xMouse;
                p[i].y = screenHeight - yMouse;
                i++;
            }
            else
            {
                p[i].x = xMouse;
                p[i].y = screenHeight - yMouse;
                i++;
                glutPostRedisplay();                  //����ִ�����»��Ʋ���
            }
			break;
        case 'e'://ֹͣ�������߶�
            iKeyPointNum = 2;
            p[i].x = xMouse;
            p[i].y = screenHeight - yMouse;
            break;
        case 'c'://�������ߵĲü�
            {
                for(int j=0;j<i;j++)
                {
                    points.push_back(p[j]);
                    points.push_back(p[j+1]);
                    Line_Clipping(points, winObj);
                    points.pop_back();
                    points.pop_back();
                }
                break;
            }
		default: break;
	}
}

void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse)  //ָ�������Ӧ����
{
    if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)//������ ���Ʋü�����
    {
        if(iMousePointNum == 0 || iMousePointNum == 2)
        {
            iMousePointNum = 1;
            xw1 = xMouse;
            yw1 = screenHeight - yMouse;
        }
        else
        {
            iMousePointNum = 2;
            xw2 = xMouse;
            yw2 = screenHeight - yMouse;

            //�ж�һ�²ü����ڵı߽�ֵ��С����rectԪ�ظ�ֵ
            if(xw2 > xw1){
                winObj.w_xmin = xw1;
                winObj.w_xmax = xw2;
            }
            else{
                winObj.w_xmin = xw2;
                winObj.w_xmax = xw1;
            }
            if(yw2 > yw1){
                winObj.w_ymin = yw1;
                winObj.w_ymax = yw2;
            }
            else{
                winObj.w_ymin = yw2;
                winObj.w_ymax = yw1;
            }
            glutPostRedisplay();                  //����ִ�����»��Ʋ���
        }
    }

	if(button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)//�һ����
	{
		iKeyPointNum = 0;
		i = 0;k = 0;
		iMousePointNum = 0;
		glutPostRedisplay();                      //����ִ�����»��Ʋ���
	}
}

void PassiveMouseMove (GLint xMouse, GLint yMouse)//����ƶ�������
{
	if(iKeyPointNum == 1)  //���ڻ���ֱ�߶�
    {
        p[i].x = xMouse;
        p[i].y = screenHeight - yMouse;
	}
	if(iMousePointNum == 1)//���ڻ��Ʋü�����
    {
        xw2 = xMouse;
        yw2 = screenHeight - yMouse;
	}
	glutPostRedisplay();   //����ִ�����»��Ʋ���
}


void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //�õ�ǰ����ɫ��䴰��

    glColor3f(1.0f, 0.0f, 0.0f); //���òü����ڵ���ɫΪ��ɫ
    if(iMousePointNum >= 1)           //���Ʋü�����
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //����GL_FRONT_AND_BACK����ʾ��ʾģʽ������������������棻
        //����GL_LINE����ʾ��ʾ�߶Σ��������������ʾ
        glRectf(xw1,yw1,xw2,yw2);
    }

    glColor3f(0.0f, 0.0f, 0.0f); //����������ɫΪ��ɫ
    if(k == 2*i && k!=0)//�жϣ����ü����ʱ�����ü�������
    {
        for(int j=0;j<k;j=j+2)
        {
            if(iKeyPointNum >= 1)           //�������߶�
            {
                glBegin(GL_LINES);
                glVertex2i(p_sub[j].x,p_sub[j].y);
                glVertex2i(p_sub[j+1].x,p_sub[j+1].y);
                glEnd();
            }
        }
    }
    else if(i!=0)//����Ϊδ�ü���ϣ��ͻ�����������
    {
        for(int j=0;j<i;j++)
        {
            if(iKeyPointNum >= 1)           //�������߶�
            {
                glBegin(GL_LINES);
                glVertex2i(p[j].x,p[j].y);
                glVertex2i(p[j+1].x,p[j+1].y);
                glEnd();
            }
        }
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

	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);                //ָ�����������λص�����
	glutMouseFunc(MousePlot);                  //ָ�������Ӧ����
	glutPassiveMotionFunc(PassiveMouseMove);    //ָ������ƶ���Ӧ����
	glutKeyboardFunc(Key);                      //ָ��������Ӧ����

	Initial();
	glutMainLoop();
	return 0;
}
