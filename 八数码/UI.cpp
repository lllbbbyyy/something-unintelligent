#include"UIDefinition.h"
#include<iostream>
#include<graphics.h>
//图形界面的初始化
void init()
{
	initgraph(widthWindow, heightWindow);
	//灰色背景色
	setbkcolor(LIGHTGRAY);
	cleardevice();
	//画大方块
	setfillcolor(RED);
	fillrectangle(xFrame, yFrame, xFrame + lengthFrame, yFrame + lengthFrame);
}
//图形界面释放
void end()
{
	closegraph();
}
//画一个数字，这个可以后面用图片等代替
void digitDraw(int num,int reLeft,int reTop,int reRight,int reBottom)
{
	RECT r = { reLeft,reTop,reRight,reBottom };
	char numc[2];
	numc[0] = num + '0';
	numc[1] = 0;
	WCHAR numC[10];
	swprintf(numC, 100, L"%S", numc);
	setbkmode(TRANSPARENT);
	settextstyle(lengthRectan, 0, _T("宋体"));
	drawtext(numC, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_EDITCONTROL);
}
//绘制一次状态画面
void paintingDraw(foundState& paint)
{
	setfillcolor(BLUE);
	for (int i = 1; i < (int)paint.arr.size(); i++)
	{
		for (int j = 1; j < paint.arr[0].size(); j++)
		{
			int reLeft = xFrame + (2 * j - 1) * gap + (j - 1) * lengthRectan;
			int reTop = yFrame + (2 * i - 1) * gap + (i - 1) * lengthRectan;
			int reRight = xFrame + (2 * j - 1) * gap + j * lengthRectan;
			int reBottom = yFrame + (2 * i - 1) * gap + i * lengthRectan;
			//画背景方框
			fillrectangle(reLeft, reTop, reRight, reBottom);
			//画数字
			digitDraw(paint.arr[i][j], reLeft, reTop, reRight, reBottom);
		}
	}
}