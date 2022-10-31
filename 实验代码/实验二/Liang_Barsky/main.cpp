#include <iostream>
#include <vector>
using namespace std;
#include "lineClipping.h"

int screenWidth = 600, screenHeight = 400;

int iKeyPointNum = 0;               //键盘'p'确定直线段端点的数目：0-无、1-起始点、2-终止点
int iMousePointNum= 0;              //鼠标单击确定裁剪窗口点的数目：0-无、1-起始点、2-终止点
int xw1=0,yw1=0;                    //绘制裁剪窗口的起始坐标值
int xw2=0,yw2=0;	                 //绘制裁剪窗口时，保留鼠标移动时的坐标值

rect winObj;                        //标准矩形裁剪窗口对象
point p1,p2;                        //标准直线段端点
vector<point> points;

//以下为Liang_Barsky裁剪算法代码
/***********************************************
*如果p参数<0，计算、更新umax，保证umax是最大u值
*如果p参数>0，计算、更新umin，保证umin是最小u值
*如果umax>umin，返回0，否则返回1
***********************************************/
int Clip_Top(float p,float q,float &umax,float &umin)
{
	float r=0.0;
    if(p<0.0)	//线段从裁剪窗口外部延伸到内部，取最大值r并更新umax
	{
		r=q/p;
		if (r>umin) return 0;	//umax>umin的情况，弃之
		else if (r>umax)  umax=r;
	}
	else if(p>0.0)      //线段从裁剪窗口内部延伸到外部,取最小值r并更新umin
		{
			r=q/p;
			if (r<umax) return 0;	//umax>umin的情况，弃之
			else if(r<umin)  umin=r;
		}
	   else 		//p=0时，线段平行于裁剪窗口
	      if(q<0.0) return 0;
	 return 1;
}
/*************************************************************
*已知winRect：矩形对象，存放标准裁剪窗口4条边信息
*    points：点的动态数组，存放直线2个端点信息
*根据裁剪窗口的左、右边界，求umax；
*根据裁剪窗口的下、上边界，求umin
*如果umax>umin，裁剪窗口和直线无交点，否则求裁剪后直线新端点
***************************************************************/
void Line_Clipping(vector<point> &Points,rect & winRect)//特点在于运用了引用类型
{
	//比较左、右边界，获得最大的umax
	point &p_1=Points[0],&p_2=Points[1];
	float dx=p_2.x-p_1.x,dy=p_2.y-p_1.y,umax=0.0,umin=1.0;
	point p=p_1;
	if (Clip_Top(-dx,p_1.x- winRect.w_xmin,umax,umin))  //左边界
		if (Clip_Top(dx,winRect.w_xmax-p_1.x, umax,umin)) //右边界
			//比较下、上边界，获得最小的umin
			if (Clip_Top(-dy,p_1.y- winRect.w_ymin, umax,umin)) //下边界
				if (Clip_Top(dy,winRect.w_ymax-p_1.y, umax,umin)) //上边界
				{//求裁剪后直线新端点
					p1.x=(int)(p.x+umax*dx);
					p1.y=(int)(p.y+umax*dy);
					p2.x=(int)(p.x+umin*dx);
					p2.y=(int)(p.y+umin*dy);
				}
}

void Initial(void)//初始化窗口
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //设置窗口背景颜色为白色
}

void ChangeSize(int w, int h)
{
	screenWidth = w;
	screenHeight = h;
	glViewport(0, 0, w, h);                 //指定窗口显示区域
	glMatrixMode(GL_PROJECTION);            //设置投影参数
	glLoadIdentity();
	gluOrtho2D(0.0,screenWidth,0.0,screenHeight);
}

void Key(unsigned char key, int xMouse, int yMouse)   //指定键盘响应函数
{
	switch(key)
	{
		case 'p':   //绘制直线段
			if(iKeyPointNum == 0 || iKeyPointNum == 2)
            {
                iKeyPointNum = 1;
                p1.x = xMouse;
                p1.y = screenHeight - yMouse;
            }
            else
            {
                iKeyPointNum = 2;
                p2.x = xMouse;
                p2.y = screenHeight - yMouse;
                glutPostRedisplay();                  //窗口执行重新绘制操作
            }
			break;
        case 'c':   //进行直线裁剪
            {
                points.push_back(p1);   //将直线两端点放入容器中
                points.push_back(p2);
                Line_Clipping(points, winObj);//调用Liang-Barsky直线裁剪函数
                points.pop_back();
                points.pop_back();      //将直线两端点从容器中释放
                break;
            }

		default: break;
	}
}

void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
    if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)//鼠标左击，绘制裁剪窗口
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
            //判断一下裁剪窗口边界值的大小，给rect结构体中的元素赋值
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
            glutPostRedisplay();                  //窗口执行重新绘制操作
        }
    }

	if(button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)//右击清除
	{
		iKeyPointNum = 0;
		iMousePointNum = 0;
		glutPostRedisplay();                      //窗口执行重新绘制操作
	}
}

void PassiveMouseMove (GLint xMouse, GLint yMouse)//鼠标移动过程中
{
	if(iKeyPointNum == 1)//正在绘制直线段
    {
        p2.x = xMouse;
        p2.y = screenHeight - yMouse;
	}
	if(iMousePointNum == 1)//正在绘制裁剪窗口
    {
        xw2 = xMouse;
        yw2 = screenHeight - yMouse;
	}
	glutPostRedisplay();   //窗口执行重新绘制操作
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //用当前背景色填充窗口

    glColor3f(1.0f, 0.0f, 0.0f); //设置矩形颜色为红色
    if(iMousePointNum >= 1)           //绘制矩形
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //参数GL_FRONT_AND_BACK：表示显示模式将适用于物体的所有面；
        //参数GL_LINE：表示显示线段，多边形用轮廓显示
        glRectf(xw1,yw1,xw2,yw2);
    }

    glColor3f(0.0f, 0.0f, 0.0f); //设置直线段颜色为黑色
    if(iKeyPointNum >= 1)           //绘制直线段
    {
        glBegin(GL_LINES);
        glVertex2i(p1.x,p1.y);
        glVertex2i(p2.x,p2.y);
        glEnd();
    }
	glutSwapBuffers(); //交换缓冲区
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //使用“双缓存”以及RGB模型
	glutInitWindowSize(600,400);
	glutInitWindowPosition(200,200);
	glutCreateWindow("20002462");

	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);                //指定窗口在整形回调函数
	glutMouseFunc(MousePlot);                  //指定鼠标响应函数
	glutPassiveMotionFunc(PassiveMouseMove);    //指定鼠标移动响应函数
	glutKeyboardFunc(Key);                      //指定键盘响应函数

	Initial();
	glutMainLoop();
	return 0;
}
