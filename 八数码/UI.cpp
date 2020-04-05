#include"UIDefinition.h"
#include<iostream>
#include<graphics.h>
//图形界面的初始化
void init(const double searchTime, const int totalStep, const int visNum, const int unvisNum)
{
	initgraph(widthWindow, heightWindow);
	//灰色背景色
	setbkcolor(LIGHTGRAY);
	cleardevice();
	//设置字体
	settextcolor(BLACK);
	settextstyle(fontSize, 0, _T("宋体"));
	TCHAR s[1024];
	//画左右框架
	setfillcolor(RED);
	fillrectangle(xFrameLeft, yFrameLeft, xFrameLeft + lengthFrame, yFrameLeft + lengthFrame);
	fillrectangle(xFrameRight, yFrameRight, xFrameRight + lengthFrame, yFrameRight + lengthFrame);
	_stprintf_s(s, _T("%Ts"),CURRENT_STATUS);
	outtextxy(xFrameLeft, yFrameLeft - fontSize, s);
	_stprintf_s(s, _T("%Ts"), FINAL_STATUS);
	outtextxy(xFrameRight, yFrameRight - fontSize, s);
	//画文字框
	setfillcolor(WHITE);
	fillrectangle(xFrameStatus, yFrameStatus, xFrameStatus + widthFrameStatus, yFrameStatus + heightFrameStatus);
	//显示全局信息
	setbkcolor(WHITE);
	int xText = xTextBegin, yText = yTextTop;
	_stprintf_s(s, _T("%Ts%.2f%Ts"), SEARCH_TIME, searchTime, MILLISECOND);
	outtextxy(xText, yText, s);
	yText += fontSize;
	_stprintf_s(s, _T("%Ts%d"), SOLUTION_STEP, totalStep);
	outtextxy(xText, yText, s);
	yText += fontSize;
	_stprintf_s(s, _T("%Ts%d"), VISITED_NUMBER, visNum);
	outtextxy(xText, yText, s);
	yText += fontSize;
	_stprintf_s(s, _T("%Ts%d"), UNVISITED_NUMBER, unvisNum);
	outtextxy(xText, yText, s);
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
	settextstyle(lengthBlock, 0, _T("宋体"));
	drawtext(numC, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_EDITCONTROL);
}
//绘制目标状态
void drawFinalStatus(const foundState& paint)
{
	setfillcolor(BLUE);
	for(int i = 1; i < (int)paint.arr.size(); i++)
	{
		for(int j = 1; j < paint.arr[0].size(); j++)
		{
			int reLeft = xFrameRight + (2 * j - 1) * gapBlock + (j - 1) * lengthBlock;
			int reTop = yFrameRight + (2 * i - 1) * gapBlock + (i - 1) * lengthBlock;
			int reRight = xFrameRight + (2 * j - 1) * gapBlock + j * lengthBlock;
			int reBottom = yFrameRight + (2 * i - 1) * gapBlock + i * lengthBlock;
			//画背景方框
			fillrectangle(reLeft, reTop, reRight, reBottom);
			//画数字
			digitDraw(paint.arr[i][j], reLeft, reTop, reRight, reBottom);
		}
	}
}
//绘制一次状态画面
void paintingDraw(foundState& paint)
{
	setfillcolor(BLUE);
	for (int i = 1; i < (int)paint.arr.size(); i++)
	{
		for (int j = 1; j < paint.arr[0].size(); j++)
		{
			int reLeft = xFrameLeft + (2 * j - 1) * gapBlock + (j - 1) * lengthBlock;
			int reTop = yFrameLeft + (2 * i - 1) * gapBlock + (i - 1) * lengthBlock;
			int reRight = xFrameLeft + (2 * j - 1) * gapBlock + j * lengthBlock;
			int reBottom = yFrameLeft + (2 * i - 1) * gapBlock + i * lengthBlock;
			//画背景方框
			fillrectangle(reLeft, reTop, reRight, reBottom);
			//画数字
			digitDraw(paint.arr[i][j], reLeft, reTop, reRight, reBottom);
		}
	}
}
//更新当前数据，目前只有当前步长
void updateStatus(const int step)
{
	TCHAR s[1024];
	settextstyle(fontSize, 0, _T("宋体"));
	clearrectangle(xTextBegin, yTextMid, xTextBegin + 120, yTextMid + fontSize);
	_stprintf_s(s, _T("%Ts%d"), CURRENT_STEP, step);
	outtextxy(xTextBegin, yTextMid, s);
}