#include"UIDefinition.h"
#include<iostream>
//ͼ�ν���ĳ�ʼ��
void init()
{
	initgraph(widthWindow, heightWindow);
	//��ɫ����ɫ
	setbkcolor(LIGHTGRAY);
	cleardevice();
	//���󷽿�
	setfillcolor(RED);
	fillrectangle(xFrame, yFrame, xFrame + lengthFrame, yFrame + lengthFrame);
}
//ͼ�ν����ͷ�
void end()
{
	closegraph();
}
//��һ�����֣�������Ժ�����ͼƬ�ȴ���
void digitDraw(int x,int y,int num)
{

}
//����һ��״̬����
void paintingDraw(foundState& paint)
{
	setfillcolor(BLUE);
	for (int i = 1; i < (int)paint.arr.size(); i++)
	{
		for (int j = 1; j < paint.arr[0].size(); j++)
		{
			fillrectangle(xFrame + (2 * j - 1) * gap + (j - 1) * lengthRectan, yFrame + (2 * i - 1) * gap + (i - 1) * lengthRectan,
				xFrame + (2 * j - 1) * gap + j * lengthRectan, yFrame + (2 * i - 1) * gap + i * lengthRectan);
			RECT r = { xFrame + (2 * j - 1) * gap + (j - 1) * lengthRectan ,yFrame + (2 * i - 1) * gap + (i - 1) * lengthRectan ,
			xFrame + (2 * j - 1) * gap + j * lengthRectan, yFrame + (2 * i - 1) * gap + i * lengthRectan };
			char numc[2];
			numc[0] = paint.arr[i][j] + '0';
			numc[1] = 0;
			WCHAR numC[10];
			swprintf(numC, 100,L"%S", numc);
			setbkmode(TRANSPARENT);
			settextstyle(lengthRectan, 0, _T("����"));
			drawtext(numC, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE| DT_EDITCONTROL);
		}
	}
}