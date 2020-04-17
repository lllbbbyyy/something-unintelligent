#include"UIDefinition.h"
#include<iostream>
#include<graphics.h>
//图形界面的初始化
void init(const int dispMode, const int selFun, const double searchTime, const int totalStep, const int visNum, const int unvisNum)
{
	initgraph(widthWindow, heightWindow);
	//灰色背景色
	setbkcolor(LIGHTGRAY);
	cleardevice();
	//设置字体
	settextstyle(fontSize, 0, _T("宋体"));
	TCHAR s[1024];

	IMAGE background;
	loadimage(&background, L"./images/background.JPG", widthWindow, heightWindow);
	putimage(0, 0, &background);

	//画左右框架
	setfillcolor(BLACK);
	fillrectangle(xFrameLeft, yFrameLeft, xFrameLeft + lengthFrame, yFrameLeft + lengthFrame);
	fillrectangle(xFrameRight, yFrameRight, xFrameRight + lengthFrame, yFrameRight + lengthFrame);
	settextcolor(WHITE);
	_stprintf_s(s, _T("%Ts"), CURRENT_STATUS);
	outtextxy(xFrameLeft, yFrameLeft - fontSize, s);
	_stprintf_s(s, _T("%Ts"), FINAL_STATUS);
	outtextxy(xFrameRight, yFrameRight - fontSize, s);
	//画文字框
	setfillcolor(BLACK);
	fillrectangle(xFrameStatus, yFrameStatus, xFrameStatus + widthFrameStatus, yFrameStatus + heightFrameStatus);
	//显示全局信息
	setbkcolor(BLACK);
	int xText = xTextBegin, yText = yTextTop;
	_stprintf_s(s, _T("%Ts"), dispMode ? MANUAL_PLAY : AUTO_PLAY);
	outtextxy(xText, yText, s);
	yText += fontSize;
	if (selFun == 0)
	{
		_stprintf_s(s, _T("%Ts%Ts"), SELECTED_FUNCTION, FUNCTION1);
	}
	else if (selFun == 1)
	{
		_stprintf_s(s, _T("%Ts%Ts"), SELECTED_FUNCTION, FUNCTION2);
	}
	else if (selFun == 2)
	{
		_stprintf_s(s, _T("%Ts%Ts"), SELECTED_FUNCTION, FUNCTION3);
	}

	outtextxy(xText, yText, s);
	yText += fontSize;
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

	//加载控制按钮图片
	IMAGE button;
	loadimage(&button, L"./images/button.jpg", widthButton, heightButton, true);
	putimage(xButtonContinue, yButton, &button);
	if (dispMode == 0) 
	{
		putimage(xButtonPause, yButton, &button);
	}

	RECT rContinue = { xButtonContinue, yButton,xButtonContinue + widthButton, yButton + heightButton };
	RECT rPause = { xButtonPause, yButton,xButtonPause + widthButton, yButton + heightButton };
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);

	if (dispMode == 0)
		_stprintf_s(s, _T("%Ts"), CONTINUE);
	else if (dispMode == 1)
		_stprintf_s(s, _T("%Ts"), GO_ON);

	drawtext(s, &rContinue, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_EDITCONTROL);

	setbkmode(TRANSPARENT);

	if (dispMode == 0) 
	{
		_stprintf_s(s, _T("%Ts"), PAUSE);

		drawtext(s, &rPause, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_EDITCONTROL);
	}
}
//图形界面释放
void end()
{
	closegraph();
}
//画一个数字
void digitDraw(int num, int reLeft, int reTop, int reRight, int reBottom)
{
	RECT r = { reLeft,reTop,reRight,reBottom };
	char numc[2];
	numc[0] = num + '0';
	numc[1] = 0;
	WCHAR numC[10];
	swprintf(numC, 100, L"%S", numc);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(lengthBlock, 0, _T("宋体"));
	if (numC[0] != '0')
		drawtext(numC, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_EDITCONTROL);
}
//绘制目标状态
void drawFinalStatus(const foundState& paint)
{
	//setfillcolor(0x434343);
	//setfillcolor(BLACK);
	//setfillcolor(0x271a1c);
	//setfillcolor(0x392c43);
	setfillcolor(RGB(31, 31, 31));
	//setfillcolor(0x3c3229);
	for (int i = 1; i < (int)paint.arr.size(); i++)
	{
		for (int j = 1; j < (int)paint.arr[0].size(); j++)
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
	//setfillcolor(0x3c3229);
	setfillcolor(0x3c3229);
	//setfillcolor(RGB(31, 31, 31));
	for (int i = 1; i < (int)paint.arr.size(); i++)
	{
		for (int j = 1; j < (int)paint.arr[0].size(); j++)
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
void paintingDraw(array& paint) {
	setfillcolor(0x3c3229);
	//setfillcolor(RGB(31, 31, 31));
	for (int i = 1; i < (int)paint.arr.size(); i++)
	{
		for (int j = 1; j < (int)paint.arr[0].size(); j++)
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
	settextcolor(WHITE);
	setbkcolor(BLACK);
	settextstyle(fontSize, 0, _T("宋体"));
	clearrectangle(xTextBegin, yTextMid, xTextBegin + 120, yTextMid + fontSize);
	_stprintf_s(s, _T("%Ts%d"), CURRENT_STEP, step);
	outtextxy(xTextBegin, yTextMid, s);
}

/*
int select_function() {
	//画大框
	initgraph(widthWindow, heightWindow);
	//灰色背景色
	setbkcolor(LIGHTGRAY);
	//光标恢复到(0,0),颜色为背景色
	cleardevice();
	//设置字体
	setbkcolor(BLACK);
	settextcolor(WHITE);
	settextstyle(fontSize, 0, _T("宋体"));
	//画三个选择框
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

	//+1避免文本框遮挡边框线
	TCHAR s[1024];
	_stprintf_s(s, _T("%Ts"), FUNCTION1);
	outtextxy(button_x[0]+1, button_y[0]+1, s);
	_stprintf_s(s, _T("%Ts"), FUNCTION2);
	outtextxy(button_x[1]+1, button_y[1]+1, s);
	_stprintf_s(s, _T("%Ts"), FUNCTION3);
	outtextxy(button_x[2]+1, button_y[2]+1, s);
	//判断鼠标点击事件
	MOUSEMSG m;
	FlushMouseMsgBuffer();
	while (1)
	{
		m = GetMouseMsg();
		if(m.uMsg==WM_LBUTTONDOWN)
		{
			for (int i = 0; i < 3; i++) {
				//to do:可加选择效果
				if (m.x > button_x[i] && m.x<button_x[i] + button_width && m.y>button_y[i] && m.y < button_y[i] + button_height)
					return i;
			}
		}
	}
}
*/

int select_initial(int button_count, const wchar_t** text) {
	//画大框
	initgraph(widthWindow, heightWindow);
	//灰色背景色
	setbkcolor(LIGHTGRAY);
	//光标恢复到(0,0),颜色为背景色
	cleardevice();
	//设置字体
	setbkcolor(BLACK);
	settextcolor(WHITE);
	settextstyle(fontSize, 0, _T("宋体"));
	IMAGE background;
	loadimage(&background, L"./images/background.JPG", widthWindow, heightWindow);
	putimage(0, 0, &background);
	//画两个选择框
	int num = button_count;
	int* button_x = new int[num];
	int* button_y = new int[num];
	const int button_width = widthWindow / (2 * num + 1);
	const int button_height = heightWindow / 8;
	setfillcolor(BLACK);
	for (int i = 0; i < num; i++) {
		button_x[i] = widthWindow * (2 * i + 1) / (2 * num + 1);
		button_y[i] = heightWindow * 2 / 3;
		IMAGE button;
		loadimage(&button, L"./images/button.jpg", button_width, button_height, true);
		putimage(button_x[i], button_y[i], &button);
		//fillrectangle(button_x[i], button_y[i], button_x[i] + button_width, button_y[i] + button_height);
	}

	//+1避免文本框遮挡边框线
	TCHAR s[1024];
	for (int i = 0; i < num; i++)
	{
		RECT r = { button_x[i],button_y[i],button_x[i] + button_width,button_y[i] + button_height };
		setbkmode(TRANSPARENT);
		_stprintf_s(s, _T("%Ts"), text[i]);

		//outtextxy(button_x[i] + button_width/2, button_y[i] + button_height/2, s);
		drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_EDITCONTROL);
	}
	//判断鼠标点击事件
	MOUSEMSG m;
	FlushMouseMsgBuffer();
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			for (int i = 0; i < num; i++) {
				//to do:可加选择效果
				if (m.x > button_x[i] && m.x<button_x[i] + button_width && m.y>button_y[i] && m.y < button_y[i] + button_height)
					return i;
			}
		}
	}
}

void init_play(array gridBegin, array gridEnd) {
	initgraph(widthWindow, heightWindow);
	//灰色背景色
	setbkcolor(LIGHTGRAY);
	cleardevice();
	//设置字体
	settextcolor(WHITE);
	settextstyle(fontSize, 0, _T("宋体"));

	IMAGE background;
	loadimage(&background, L"./images/background.JPG", widthWindow, heightWindow);
	putimage(0, 0, &background);

	TCHAR s[1024];
	//画左右框架
	setfillcolor(BLACK);
	fillrectangle(xFrameLeft, yFrameLeft, xFrameLeft + lengthFrame, yFrameLeft + lengthFrame);
	fillrectangle(xFrameRight, yFrameRight, xFrameRight + lengthFrame, yFrameRight + lengthFrame);
	_stprintf_s(s, _T("%Ts"), CURRENT_STATUS);
	outtextxy(xFrameLeft, yFrameLeft - fontSize, s);
	_stprintf_s(s, _T("%Ts"), FINAL_STATUS);
	outtextxy(xFrameRight, yFrameRight - fontSize, s);

	settextstyle(fontSize, 0, _T("宋体"));
	//加载控制按钮图片
	IMAGE button;
	loadimage(&button, L"./images/button.jpg", widthButton, heightButton, true);
	putimage(xButtonContinue, yButton, &button);
	putimage(xButtonPause, yButton, &button);

	RECT restartProc = { xButtonContinue, yButton,xButtonContinue + widthButton, yButton + heightButton };
	RECT endProc = { xButtonPause, yButton,xButtonPause + widthButton, yButton + heightButton };
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	_stprintf_s(s, _T("%Ts"), RESTAER_PROG);
	drawtext(s, &restartProc, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_EDITCONTROL);

	setbkmode(TRANSPARENT);
	_stprintf_s(s, _T("%Ts"), END_PROG);
	drawtext(s, &endProc, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_EDITCONTROL);

	paintingDraw(gridBegin);
	drawFinalStatus(gridEnd);
}

//坐标转换为行列数
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

//判断该格是否可移动
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
			//邻居有空格
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
//返回1表示正常进行了下一步点击，返回0表示返回主界面，返回-1表示直接退出程序
int click_to_next(array& current) {
	//判断鼠标点击事件
	int x, y = 0;
	MOUSEMSG m;
	FlushMouseMsgBuffer();
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (inRect(m.x, m.y, xButtonContinue, yButton, widthButton, heightButton))
				return 0;
			if (inRect(m.x, m.y, xButtonPause, yButton, widthButton, heightButton))
				return -1;
			x = m.x;
			y = m.y;

			int col = 0, line = 0;
			//x,y匹配为行列
			bool valid = match(current, x, y, col, line);
			if (!valid)
				continue;

			bool ok = move(current, col, line);
			if (ok)
				return 1;
			else
				continue;
		}
	}
}
//判断鼠标位置是否在矩形内
bool inRect(int x, int y, int left, int top, int width, int height)
{
	return (x >= left && x <= left + width && y >= top && y <= top + height);
}
//检测结束时的按钮，0为重新开始，1为退出
bool endButton()
{
	settextstyle(fontSize, 0, _T("宋体"));
	TCHAR s[1024];
	//加载控制按钮图片
	IMAGE button;
	loadimage(&button, L"./images/button.jpg", widthButton, heightButton, true);
	putimage(xButtonContinue, yButton, &button);
	putimage(xButtonPause, yButton, &button);

	RECT restartProc = { xButtonContinue, yButton,xButtonContinue + widthButton, yButton + heightButton };
	RECT endProc = { xButtonPause, yButton,xButtonPause + widthButton, yButton + heightButton };
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	_stprintf_s(s, _T("%Ts"), RESTAER_PROG);
	drawtext(s, &restartProc, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_EDITCONTROL);

	setbkmode(TRANSPARENT);
	_stprintf_s(s, _T("%Ts"), END_PROG);
	drawtext(s, &endProc, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_EDITCONTROL);

	MOUSEMSG m;
	FlushMouseMsgBuffer();
	while (1)
	{
		//	return 0;
		m = GetMouseMsg();
		//	return 0;
		//	std::cout << 1;
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (inRect(m.x, m.y, xButtonContinue, yButton, widthButton, heightButton))
				return 0;
			if (inRect(m.x, m.y, xButtonPause, yButton, widthButton, heightButton))
				return 1;
		}
	}
	return 0;
}
//提示移动鼠标
void draw_promote()
{
	TCHAR s[1024];
	settextcolor(WHITE);
	setbkcolor(BLACK);
	settextstyle(fontSize, 0, _T("宋体"));
	_stprintf_s(s, _T("%Ts"), PROMOTE);
	outtextxy(10, 10, s);
}
//提示手玩模式如何使用
void draw_play_promote()
{
	TCHAR s[1024];
	settextcolor(WHITE);
	setbkcolor(BLACK);
	settextstyle(fontSize, 0, _T("宋体"));
	_stprintf_s(s, _T("%Ts"), PLAY_PROMOTE);
	outtextxy(10, 10, s);
}