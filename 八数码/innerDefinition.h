#pragma once
#include<array>
#include<map>
#include<queue>
#include<time.h>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<iostream>
//n数码问题的行列
const int row = 3;
const int col = 3;
//存放格子信息和当前状态的深度
struct array
{
	std::array<std::array<int, col + 1>, row + 1> arr;
	int step;
};
//主要用于配合map存放已经寻找过的局面信息，主要是为了重载小于号，便于判断两个局面是否相同
struct foundState
{
	std::array<std::array<int, col + 1>, row + 1> arr;
	foundState()
	{
		for (int i = 0; i < int(arr.size()); i++)
		{
			for (int j = 0; j < int(arr[0].size()); j++)
			{
				arr[i][j] = 0;
			}
		}
	}
	foundState(array& a)
	{
		for (int i = 0; i < int(arr.size()); i++)
		{
			for (int j = 0; j < int(arr[0].size()); j++)
			{
				arr[i][j] = a.arr[i][j];
			}
		}
	}
	bool operator < (const foundState& a)const
	{
		for (int i = 1; i < int(arr.size()); i++)
		{
			for (int j = 1; j < int(arr[0].size()); j++)
			{
				if (arr[i][j] < a.arr[i][j])
				{
					return true;
				}
				else if (arr[i][j] > a.arr[i][j])
				{
					return false;
				}
			}
		}
		return false;
	}
	bool operator != (const foundState& a)const
	{
		for (int i = 1; i < int(arr.size()); i++)
		{
			for (int j = 1; j < int(arr[0].size()); j++)
			{
				if (arr[i][j] != a.arr[i][j])
				{
					return true;
				}
			}
		}
		return false;
	}
	bool operator = (const foundState& a)
	{
		for (int i = 1; i < int(arr.size()); i++)
		{
			for (int j = 1; j < int(arr[0].size()); j++)
			{
				arr[i][j] = a.arr[i][j];

			}
		}
		return false;
	}
};
//配合优先队列，重载小于号将评估值作为比较对象，小根堆
struct nodeState
{
	double value;
	array state;
	bool operator < (const nodeState& a) const
	{
		return value > a.value;
	}
};
typedef std::priority_queue<nodeState> priQueue;
typedef std::map<foundState, foundState> map;

//initial flags,数字代表从左至右第几个按钮[0,1]
const int RANDOM_INITIAL = 0;
const int PERSONAL_INITIAL = 1;

//personal initial读取文件位置
const std::string PATH = ".\\input.txt";
//personal initial flags
const int NO_INPUT_FOUND = -1;
const int NO_SOLUTION = -2;


//inner函数

//判断两个状态是否相等
bool isEqual(array& grid1, array& grid2);
//评估函数，目前mode=1为不相同个数的评估，mode=2为曼哈顿距离意义下的评估，mode=3为欧几里得距离评估
//取消默认参数，防止不正常的调用
double calculateValue(array& curState, array& endState, int mode);
//寻找下一个状态
//增加参数mode，保证调用评估函数的时候不会一直使用默认的参数
void nextState(array& curState, array& endState, priQueue& qu, map& foundMap,int mode);
//返回存储的路径,防止构造函数花费太多时间因此使用引用传递
void findRoute(array& beginState, array& endState, map& foundMap, std::deque<foundState>& route);
//判断对应开局和终局是否有解
bool has_solution(array gridBegin, array gridEnd);
//随机初始化开局和终局
void random_initial(array& gridBegin,array& gridEnd);
int personal_initial(array& gridBegin,array& gridEnd,const std::string path);