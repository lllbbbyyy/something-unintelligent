#include<graphics.h>
#include<iostream>
#include<conio.h>
#include<time.h>
#include<thread>
#include"innerDefinition.h"
#include"UIDefinition.h"
//负责输入状态
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
//调试打印函数
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

//子线程内捕获鼠标事件
void getMouseStatus(bool& done, volatile bool& isPause,int dispMode)
{
	MOUSEMSG m;
	while (!done&&dispMode==0)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (inRect(m.x, m.y, xButtonContinue, yButton, widthButton, heightButton))
				isPause = false;
			if (inRect(m.x, m.y, xButtonPause, yButton, widthButton, heightButton))
				isPause = true;
		}
	}
}

int main()
{
	//注意不是std::array，存储了步长（深度）信息
	array gridBegin;
	array gridEnd;
	tree search_tree;
	int isEnd = 0;

	while (!isEnd)
	{
		//选择手玩模式或者演示模式或者退出
		const wchar_t* patterns[] = { PLAY, DISPLAY,END_PROG };
		int pattern = select_initial(3, patterns);
		//直接退出
		if (pattern == 2)
		{
			break;
		}
		int function = 0;
		if (pattern == 1) {
			//选择启发式函数
			const wchar_t* functions[] = { FUNCTION1, FUNCTION2, FUNCTION3 };
			function = select_initial(3, functions);
		}

		//选择随机开局或手动开局
		const wchar_t* initials[] = { RANDOM, PERSONAL };
		int choice = select_initial(2, initials);
		//1.随机开局 2.手动开局
		if (choice == RANDOM_INITIAL)
			random_initial(gridBegin, gridEnd);
		else if (choice == PERSONAL_INITIAL)
		{
			int ans = personal_initial(gridBegin, gridEnd, PATH);
			//todo:错误状态无提示
			if (ans == NO_INPUT_FOUND || ans == NO_SOLUTION)
				continue;
		}

		//演示模式
		if (pattern == 1) {
			//选择自动演示或手动演示
			const wchar_t* dispModeText[] = { AUTO_PLAY, MANUAL_PLAY };
			//0.自动演示 1.手动演示
			int dispMode = select_initial(2, dispModeText);
			//优先队列，以评估代价为关键词的小根堆，同时存储了局面
			priQueue qu;
			//存放已经遍历过的节点，相当于剪枝，注意不同于std::map
			map foundMap;
			//节点存放当前信息
			nodeState gridCurr = { calculateValue(gridBegin, gridEnd, function + 1), gridBegin };
			//记录已经遍历的节点数量
			int numFoundNode = 0;
			//用于计时
			clock_t clockStart, clockEnd;
			double milSec;
			//开始计时
			clockStart = clock();
			//与最终局面不相同时
			while (!isEqual(gridCurr.state, gridEnd))
			{
				//寻找下一层节点
				nextState(gridCurr.state, gridEnd, qu, foundMap, function + 1,search_tree);
				gridCurr = qu.top();
				qu.pop();
				numFoundNode++;
				//	print(gridCurr);
			}
			//结束计时
			clockEnd = clock();
			milSec = ((double)clockEnd - (double)clockStart) * 1000 / CLOCKS_PER_SEC;
			//寻找路径
			std::deque<foundState> route;
			findRoute(gridBegin, gridEnd, foundMap, route);
			//输出深度信息，已扩展节点，未扩展节点
	//		std::cout << route.size() - 1 << std::endl << numFoundNode << std::endl << qu.size() << std::endl;
			//绘制搜索树
			draw_tree(search_tree,route,function+1);
			//开始画图
			int stepCnt = 0;
			bool mDone = false;
			volatile bool isPause = false;
			init(dispMode, function, milSec, int(route.size() - 1), numFoundNode, (int)qu.size());
			std::thread thr(getMouseStatus, std::ref(mDone), std::ref(isPause),dispMode);
			drawFinalStatus(foundState(gridEnd));
			for (auto it : route)
			{
				paintingDraw(it);
				updateStatus(stepCnt++);
				if (dispMode == 0) Sleep(1000);
				else if (dispMode == 1)
				{
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
								break;
						}
					}
				}
				while (dispMode == 0 && isPause);
			}
			mDone = true;
			//thr.detach();
			draw_promote();
			thr.join();
			isEnd = endButton();
		}
		//手玩模式
		else if (pattern == 0) {
			init_play(gridBegin, gridEnd);
			draw_play_promote();
			array gridCurrent = gridBegin;
			int opt = 1;
			while (!isEqual(gridCurrent, gridEnd)) {
				opt=click_to_next(gridCurrent);
				if (opt == 0)
				{
					isEnd = 0;
					break;
				}
				else if (opt == -1)
				{
					isEnd = 1;
					break;
				}
				paintingDraw(gridCurrent);
			}
			if (opt != 1)
			{
				continue;
			}
			isEnd = endButton();
		}

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