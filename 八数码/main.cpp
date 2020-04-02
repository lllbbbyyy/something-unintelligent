//#include<graphics.h>
#include<iostream>
#include<array>
#include<conio.h>
#include<queue>
#include<map>
#include<stack>
#include"definition.h"
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
//判断两个状态是否相等
bool isEqual(array& grid1, array& grid2)
{
	for (int i = 1; i < int(grid1.arr.size()); i++)
	{
		for (int j = 1; j < int(grid1.arr[0].size()); j++)
		{
			if (grid1.arr[i][j] != grid2.arr[i][j])
			{
				return false;
			}
		}
	}
	return true;
}
//图形界面的初始化
//void init()
//{
//	initgraph(640, 480);
//}
//图形界面释放
//void end()
//{
//	closegraph();
//}
//评估函数，目前mode=1为不相同个数的评估，mode=2为曼哈顿距离意义下的评估
int calculateValue(array& curState, array& endState, int mode = 2)
{
	int value = 0;
	for (int i = 1; i < int(endState.arr.size()); i++)
	{
		for (int j = 1; j < int(endState.arr[0].size()); j++)
		{
			//不相同个数的评估
			if (mode == 1) {
				if (curState.arr[i][j] != endState.arr[i][j])
				{
					value++;
				}
			}
			//曼哈顿距离评估
			else if (mode == 2) {
				int flag = 0;
				for (int m = 1; m < int(endState.arr.size()); m++)
				{
					for (int n = 1; n < int(endState.arr[0].size()); n++)
					{
						if (curState.arr[i][j] == endState.arr[m][n])
						{
							if (i < m)
								value += m - i;
							else
								value += i - m;
							if (j < n)
								value += n - j;
							else
								value += j - n;
							flag = 1;
							break;
						}
					}
					if (flag)
					{
						break;
					}
				}
			}

		}
	}
	//g+h
	return curState.step + value;
}
void nextState(array& curState, array& endState, priQueue& qu, map& foundMap)
{
	//四个移动方向
	const int rowMove[] = { -1,0,1,0 };
	const int colMove[] = { 0,-1,0,1 };
	bool flag = false;
	int blankRow, blankCol;
	//寻找空白块
	for (blankRow = 1; blankRow < int(curState.arr.size()); blankRow++)
	{
		for (blankCol = 1; blankCol < int(curState.arr[0].size()); blankCol++)
		{
			if (curState.arr[blankRow][blankCol] == 0)
			{
				flag = true;
				break;
			}
		}
		if (flag)
		{
			break;
		}
	}
	int newRow, newCol;
	//四个方向尝试
	foundState parent(curState);
	for (int i = 0; i < 4; i++)
	{
		newRow = blankRow + rowMove[i];
		newCol = blankCol + colMove[i];
		//在边界范围内
		if (newRow >= 1 && newRow < int(curState.arr.size()) && newCol >= 1 && newCol < int(curState.arr[0].size()))
		{
			std::swap(curState.arr[blankRow][blankCol], curState.arr[newRow][newCol]);
			curState.step++;
			if (foundMap.empty() || !foundMap.count(foundState(curState))) {
				//如果已经遍历过的表为空或者当前的状态没有被寻找过，入队
				qu.push({ calculateValue(curState,endState),curState });
				foundMap[foundState(curState)] = parent;
			}
			//回溯
			std::swap(curState.arr[blankRow][blankCol], curState.arr[newRow][newCol]);
			curState.step--;
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
//返回存储的路径,防止构造函数花费太多时间因此使用引用传递
void findRoute(array& beginState, array& endState, map& foundMap, std::deque<foundState>& route)
{
	foundState tem(endState);
	route.push_front(tem);
	while (foundMap[tem] != beginState)
	{
		tem = foundMap[tem];
		route.push_front(tem);
	}
	route.push_front(foundState(beginState));
}
int main()
{
	//注意不是std::array，存储了步长（深度）信息
	array gridBegin;
	array gridEnd;
	//输入初始结束状态
	input(gridBegin);
	input(gridEnd);
	//	init();
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
	for (auto it : route)
	{
		print(it);
		//draw()动画演示
	}
	//	end();
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