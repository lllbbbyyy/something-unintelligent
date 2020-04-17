#include<graphics.h>
#include<iostream>
#include<conio.h>
#include<time.h>
#include<thread>
#include"innerDefinition.h"
#include"UIDefinition.h"
//��������״̬
void input(array& grid)
{
	std::cout << "input:" << std::endl;
	grid.step = 0;
	for (int i = 1; i < int(grid.arr.size()); i++)
	{
		for (int j = 1; j < int(grid.arr[0].size()); j++)
		{
			std::cin >> grid.arr[i][j];
		}
	}
}
//���Դ�ӡ����
void print(nodeState& tem)
{
	std::cout << "nowstep:" << tem.state.step << std::endl;
	for (int i = 1; i < int(tem.state.arr.size()); i++)
	{
		for (int j = 1; j < int(tem.state.arr[0].size()); j++)
		{
			std::cout << tem.state.arr[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	system("pause");
}
void print(foundState& tem)
{
	std::cout << "-------" << std::endl;
	for (int i = 1; i < int(tem.arr.size()); i++)
	{
		for (int j = 1; j < int(tem.arr[0].size()); j++)
		{
			std::cout << tem.arr[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	system("pause");
}

//�ж����λ���Ƿ��ھ�����
bool inRect(int x, int y, int left, int top, int width, int height)
{
	return (x >= left && x <= left + width && y >= top && y <= top + height);
}

//���߳��ڲ�������¼�
void getMouseStatus(bool &done, volatile bool &isPause)
{
	MOUSEMSG m;
	while(!done)
	{
		m = GetMouseMsg();
		if(m.uMsg == WM_LBUTTONDOWN)
		{
			if(inRect(m.x, m.y, xButtonContinue, yButton, widthButton, heightButton))
				isPause = false;
			if(inRect(m.x, m.y, xButtonPause, yButton, widthButton, heightButton))
				isPause = true;
		}
	}
}

int main()
{
	//ע�ⲻ��std::array���洢�˲�������ȣ���Ϣ
	array gridBegin;
	array gridEnd;

	int isEnd = 0;

	while(!isEnd)
	{
		//ѡ������ģʽ������ʾģʽ
		const wchar_t* patterns[] = { PLAY, DISPLAY };
		int pattern = select_initial(2, patterns);
		int function = 0;
		if(pattern == 1) {
			//ѡ������ʽ����
			const wchar_t* functions[] = { FUNCTION1, FUNCTION2, FUNCTION3 };
			function = select_initial(3, functions);
		}

		//ѡ��������ֻ��ֶ�����
		const wchar_t* initials[] = { RANDOM, PERSONAL };
		int choice = select_initial(2, initials);
		//1.������� 2.�ֶ�����
		if(choice == RANDOM_INITIAL)
			random_initial(gridBegin, gridEnd);
		else if(choice == PERSONAL_INITIAL)
		{
			int ans = personal_initial(gridBegin, gridEnd, PATH);
			//todo:����״̬����ʾ
			if(ans == NO_INPUT_FOUND || ans == NO_SOLUTION)
				return 0;
		}

		//��ʾģʽ
		if(pattern == 1) {
			//ѡ���Զ���ʾ���ֶ���ʾ
			const wchar_t* dispModeText[] = { AUTO_PLAY, MANUAL_PLAY };
			//0.�Զ���ʾ 1.�ֶ���ʾ
			int dispMode = select_initial(2, dispModeText);
			//���ȶ��У�����������Ϊ�ؼ��ʵ�С���ѣ�ͬʱ�洢�˾���
			priQueue qu;
			//����Ѿ��������Ľڵ㣬�൱�ڼ�֦��ע�ⲻͬ��std::map
			map foundMap;
			//�ڵ��ŵ�ǰ��Ϣ
			nodeState gridCurr = { calculateValue(gridBegin, gridEnd, function + 1), gridBegin };
			//��¼�Ѿ������Ľڵ�����
			int numFoundNode = 0;
			//���ڼ�ʱ
			clock_t clockStart, clockEnd;
			double milSec;
			//��ʼ��ʱ
			clockStart = clock();
			//�����վ��治��ͬʱ
			while(!isEqual(gridCurr.state, gridEnd))
			{
				//Ѱ����һ��ڵ�
				nextState(gridCurr.state, gridEnd, qu, foundMap, function + 1);
				gridCurr = qu.top();
				qu.pop();
				numFoundNode++;
				//	print(gridCurr);
			}
			//������ʱ
			clockEnd = clock();
			milSec = ((double)clockEnd - (double)clockStart) * 1000 / CLOCKS_PER_SEC;
			//Ѱ��·��
			std::deque<foundState> route;
			findRoute(gridBegin, gridEnd, foundMap, route);
			//��������Ϣ������չ�ڵ㣬δ��չ�ڵ�
			std::cout << route.size() - 1 << std::endl << numFoundNode << std::endl << qu.size() << std::endl;

			//��ʼ��ͼ
			int stepCnt = 0;
			bool mDone = false;
			volatile bool isPause = false;
			init(dispMode, function, milSec, int(route.size() - 1), numFoundNode, (int)qu.size());
			std::thread thr(getMouseStatus, std::ref(mDone), std::ref(isPause));
			drawFinalStatus(foundState(gridEnd));
			for(auto it : route)
			{
				paintingDraw(it);
				updateStatus(stepCnt++);
				if(dispMode == 0) Sleep(1000);
				else if(dispMode == 1) _getch();
				while(dispMode == 0 && isPause);
			}
			mDone = true;
			thr.detach();
		//	thr.join();
		}
		//����ģʽ
		else if(pattern == 0) {
			init_play(gridBegin, gridEnd);
			array gridCurrent = gridBegin;
			while(!isEqual(gridCurrent, gridEnd)) {
				click_to_next(gridCurrent);
				paintingDraw(gridCurrent);
			}
		}

		const wchar_t* endHints[] = { RESTAER_PROG, END_PROG };
		isEnd = select_initial(2, endHints);
	}

	end();
	return 0;
}
/*
8 6 7
0 5 1
4 3 2
1 2 3
4 5 6
7 8 0
*/