#include<graphics.h>
#include<iostream>
#include<conio.h>
#include<time.h>
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

int main()
{
	//注意不是std::array，存储了步长（深度）信息
	array gridBegin;
	array gridEnd;

	//选择手玩模式或者演示模式
	const wchar_t* patterns[] = { PLAY,DISPLAY };
	int pattern = select_initial(2,patterns);
	int function = 0;
	if (pattern == 1) {
		//选择启发式函数
		const wchar_t* functions[] = { FUNCTION1,FUNCTION2 };
		function = select_initial(2,functions);
	}

	//选择随机开局或手动开局
	const wchar_t* initials[] = { RANDOM,PERSONAL };
	int choice = select_initial(2,initials);
	//1.随机开局 2.手动开局
	if (choice == RANDOM_INITIAL)
		random_initial(gridBegin, gridEnd);
	else if (choice == PERSONAL_INITIAL)
	{
		int ans = personal_initial(gridBegin, gridEnd, PATH);
		//todo:错误状态无提示
		if (ans == NO_INPUT_FOUND || ans == NO_SOLUTION)
			return 0;
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
		nodeState gridCurr = { calculateValue(gridBegin,gridEnd,function+1),gridBegin };
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
			nextState(gridCurr.state, gridEnd, qu, foundMap);
			gridCurr = qu.top();
			qu.pop();
			numFoundNode++;
			//	print(gridCurr);
		}
		//结束计时
		clockEnd = clock();
		milSec = (double)(clockEnd - clockStart) * 1000 / CLOCKS_PER_SEC;
		//输出深度信息，已扩展节点，未扩展节点
		std::cout << gridCurr.value << std::endl << numFoundNode << std::endl << qu.size() << std::endl;
		std::deque<foundState> route;
		findRoute(gridBegin, gridEnd, foundMap, route);
		//开始画图
		int stepCnt = 0;
		init(dispMode, function, milSec, gridCurr.value, numFoundNode, (int)qu.size());
		drawFinalStatus(foundState(gridEnd));
		for (auto it : route)
		{
			paintingDraw(it);
			updateStatus(stepCnt++);
			if (dispMode == 0) Sleep(1000);
			else if (dispMode == 1) _getch();
		}
		system("pause");
		end();
		return 0;
	}
	//手玩模式
	else if(pattern == 0) {
		init_play(gridBegin,gridEnd);
		array gridCurrent = gridBegin;
		while (!isEqual(gridCurrent, gridEnd)) {
			click_to_next(gridCurrent);
			paintingDraw(gridCurrent);
		}
		return 0;
	}	
}
/*
8 6 7
0 5 1
4 3 2
1 2 3
4 5 6
7 8 0
*/