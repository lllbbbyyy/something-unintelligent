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
void paintingDraw(array& paint) {
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

/*
int select_function() {
	//�����
	initgraph(widthWindow, heightWindow);
	//��ɫ����ɫ
	setbkcolor(LIGHTGRAY);
	//���ָ���(0,0),��ɫΪ����ɫ
	cleardevice();
	//��������
	setbkcolor(BLACK);
	settextcolor(WHITE);
	settextstyle(fontSize, 0, _T("����"));
	//������ѡ���
	int button_x[3];
	int button_y[3];
	const int button_width = widthWindow / 7;
	const int button_height = heightWindow / 8;
	setfillcolor(BLACK);
	for (int i = 0; i < 3; i++) {
		button_x[i] = widthWindow * (2 * i + 1) / 7;
		button_y[i] = heightWindow / 2;
		fillrectangle(button_x[i], button_y[i], button_x[i] + button_width, button_y[i] + button_height);
	}

	//+1�����ı����ڵ��߿���
	TCHAR s[1024];
	_stprintf_s(s, _T("%Ts"), FUNCTION1);
	outtextxy(button_x[0]+1, button_y[0]+1, s);
	_stprintf_s(s, _T("%Ts"), FUNCTION2);
	outtextxy(button_x[1]+1, button_y[1]+1, s);
	_stprintf_s(s, _T("%Ts"), FUNCTION3);
	outtextxy(button_x[2]+1, button_y[2]+1, s);
	//�ж�������¼�
	MOUSEMSG m;
	FlushMouseMsgBuffer();
	while (1)
	{
		m = GetMouseMsg();
		if(m.uMsg==WM_LBUTTONDOWN)
		{
			for (int i = 0; i < 3; i++) {
				//to do:�ɼ�ѡ��Ч��
				if (m.x > button_x[i] && m.x<button_x[i] + button_width && m.y>button_y[i] && m.y < button_y[i] + button_height)
					return i;
			}
		}
	}
}
*/

int select_initial(int button_count,const wchar_t** text) {
	//�����
	initgraph(widthWindow, heightWindow);
	//��ɫ����ɫ
	setbkcolor(LIGHTGRAY);
	//���ָ���(0,0),��ɫΪ����ɫ
	cleardevice();
	//��������
	setbkcolor(BLACK);
	settextcolor(WHITE);
	settextstyle(fontSize, 0, _T("����"));
	//������ѡ���
	int num = button_count;
	int* button_x = new int[num];
	int* button_y = new int[num];
	const int button_width = widthWindow / (2*num+1);
	const int button_height = heightWindow / 8;
	setfillcolor(BLACK);
	for (int i = 0; i < num; i++) {
		button_x[i] = widthWindow * (2 * i + 1) / (2*num+1);
		button_y[i] = heightWindow / 2;
		fillrectangle(button_x[i], button_y[i], button_x[i] + button_width, button_y[i] + button_height);
	}

	//+1�����ı����ڵ��߿���
	TCHAR s[1024];
	for (int i = 0; i < num; i++)
	{
		_stprintf_s(s, _T("%Ts"), text[i]);
		outtextxy(button_x[i] + 1, button_y[i] + 1, s);
	}
	//�ж�������¼�
	MOUSEMSG m;
	FlushMouseMsgBuffer();
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			for (int i = 0; i < num; i++) {
				//to do:�ɼ�ѡ��Ч��
				if (m.x > button_x[i] && m.x<button_x[i] + button_width && m.y>button_y[i] && m.y < button_y[i] + button_height)
					return i;
			}
		}
	}
}

void init_play(array gridBegin,array gridEnd) {
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
	_stprintf_s(s, _T("%Ts"), CURRENT_STATUS);
	outtextxy(xFrameLeft, yFrameLeft - fontSize, s);
	_stprintf_s(s, _T("%Ts"), FINAL_STATUS);
	outtextxy(xFrameRight, yFrameRight - fontSize, s);
	
	paintingDraw(gridBegin);
	drawFinalStatus(gridEnd);
}

//����ת��Ϊ������
bool match(array& paint, int x, int y, int& col, int& line) {
	int size1 = (int)paint.arr.size();
	int size2 = paint.arr[0].size();

	int k = 0;
	for (int i = 1; i < size1; i++)
	{
		for (int j = 1; j < size2; j++)
		{
			int reLeft = xFrameLeft + (2 * j - 1) * gapBlock + (j - 1) * lengthBlock;
			int reTop = yFrameLeft + (2 * i - 1) * gapBlock + (i - 1) * lengthBlock;
			int reRight = xFrameLeft + (2 * j - 1) * gapBlock + j * lengthBlock;
			int reBottom = yFrameLeft + (2 * i - 1) * gapBlock + i * lengthBlock;

			if (x > reLeft && x<reRight && y>reTop && y < reBottom)
			{
				col = j, line = i;
				return true;
			}
		}
	}
	return false;
}

//�жϸø��Ƿ���ƶ�
bool move(array& current, int col, int line) {

	int size1 = current.arr.size();
	int size2 = current.arr[0].size();

	int dirx[] = { -1,1,0,0 };//left,right,up,down
	int diry[] = { 0,0,-1,1 };//left,right,up,down

	for (int i = 0; i < 4; i++) {
		int nx = col + dirx[i];
		int ny = line + diry[i];
		if (nx >= 1 && nx < size2 && ny >= 1 && ny < size1)
		{
			//�ھ��пո�
			if (!current.arr[ny][nx])
			{
				int temp = current.arr[line][col];
				current.arr[line][col] = 0;
				current.arr[ny][nx] = temp;
				return true;
			}
		}
	}
	return false;

}

void click_to_next(array& current){
	//�ж�������¼�
	int x, y = 0;
	MOUSEMSG m;
	FlushMouseMsgBuffer();
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			x = m.x;
			y = m.y;

			int col = 0, line = 0;
			//x,yƥ��Ϊ����
			bool valid = match(current,x, y, col, line);
			if (!valid)
				continue;

			bool ok = move(current, col, line);
			if (ok)
				return;
			else
				continue;
		}
	}
}