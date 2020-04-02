#pragma once
//n数码问题的行列
const int row = 3;
const int col = 3;
//存放格子信息和当前状态的深度
struct array
{
	std::array<std::array<int, col + 1>, row + 1> arr;
	int step;
};
//主要用于配合set存放已经寻找过的局面信息，主要是为了重载小于号，便于判断两个局面是否相同
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
	int value;
	array state;
	bool operator < (const nodeState& a) const
	{
		return value > a.value;
	}
};
typedef std::priority_queue<nodeState> priQueue;
typedef std::map<foundState, foundState> map;
