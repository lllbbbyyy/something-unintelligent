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
	//��������
	settextcolor(BLACK);
	settextstyle(fontSize, 0, _T("����"));
	TCHAR s[1024];
	//�����ҿ��
	setfillcolor(RED);
	fillrectangle(xFrameLeft, yFrameLeft, xFrameLeft + lengthFrame, yFrameLeft + lengthFrame);
	fillrectangle(xFrameRight, yFrameRight, xFrameRight + lengthFrame, yFrameRight + lengthFrame);
	_stprintf_s(s, _T("%Ts"),CURRENT_STATUS);
	outtextxy(xFrameLeft, yFrameLeft - fontSize, s);
	_stprintf_s(s, _T("%Ts"), FINAL_STATUS);
	outtextxy(xFrameRight, yFrameRight - fontSize, s);
	//�����ֿ�
	setfillcolor(WHITE);
	fillrectangle(xFrameStatus, yFrameStatus, xFrameStatus + widthFrameStatus, yFrameStatus + heightFrameStatus);
	//��ʾȫ����Ϣ
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
	settextstyle(lengthBlock, 0, _T("����"));
	drawtext(numC, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_EDITCONTROL);
}
//����Ŀ��״̬
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
			//����������
			fillrectangle(reLeft, reTop, reRight, reBottom);
			//������
			digitDraw(paint.arr[i][j], reLeft, reTop, reRight, reBottom);
		}
	}
}
//����һ��״̬����
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