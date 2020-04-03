#include<graphics.h>
#include<iostream>
#include<conio.h>
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
	//输入初始结束状态
	input(gridBegin);
	input(gridEnd);
	//优先队列，以评估代价为关键词的小根堆，同时存储了局面
	priQueue qu;
	//存放已经遍历过的节点，相当于剪枝，注意不同于std::map
	map foundMap;
	//节点存放当前信息
	nodeState gridCurr = { calculateValue(gridBegin,gridEnd),gridBegin };
	//记录已经遍历的节点数量
	int numFoundNode = 0;
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
	//输出深度信息，已扩展节点，未扩展节点
	std::cout << gridCurr.value << std::endl << numFoundNode << std::endl << qu.size() << std::endl;
	std::deque<foundState> route;
	findRoute(gridBegin, gridEnd, foundMap, route);
	//开始画图
	init();

	for (auto it : route)
	{
		paintingDraw(it);
		//draw()动画演示
		system("pause");
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