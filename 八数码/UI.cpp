#include"UIDefinition.h"
#include<iostream>
#include<graphics.h>
//ͼ�ν���ĳ�ʼ��
void init(const double searchTime, const int totalStep, const int visNum, const int unvisNum)
{
	initgraph(widthWindow, heightWindow);
	//��ɫ����ɫ
	setbkcolor(LIGHTGRAY);
	cleardevice();
	//���󷽿�
	setfillcolor(RED);
	fillrectangle(xFrame, yFrame, xFrame + lengthFrame, yFrame + lengthFrame);
	//TODO:�����ֿ�
	//����������ʽ
	settextcolor(BLACK);
	settextstyle(fontSize, 0, _T("����"));
	//��ʾȫ����Ϣ
	int xText = xTextBegin, yText = yTextTop;
	TCHAR s[1024];
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
//ͼ�ν����ͷ�
void end()
{
	closegraph();
}
//��һ�����֣�������Ժ�����ͼƬ�ȴ���
void digitDraw(int num,int reLeft,int reTop,int reRight,int reBottom)
{
	RECT r = { reLeft,reTop,reRight,reBottom };
	char numc[2];
	numc[0] = num + '0';
	numc[1] = 0;
	WCHAR numC[10];
	swprintf(numC, 100, L"%S", numc);
	setbkmode(TRANSPARENT);
	settextstyle(lengthRectan, 0, _T("����"));
	drawtext(numC, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_EDITCONTROL);
}
//����һ��״̬����
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
			//����������
			fillrectangle(reLeft, reTop, reRight, reBottom);
			//������
			digitDraw(paint.arr[i][j], reLeft, reTop, reRight, reBottom);
		}
	}
}


//���µ�ǰ���ݣ�Ŀǰֻ�е�ǰ����
void updateStatus(const int step)
{
	TCHAR s[1024];
	settextstyle(fontSize, 0, _T("����"));
	clearrectangle(xTextBegin, yTextMid, xTextBegin + 120, yTextMid + fontSize);
	_stprintf_s(s, _T("%Ts%d"), CURRENT_STEP, step);
	outtextxy(xTextBegin, yTextMid, s);
}