#include"innerDefinition.h"
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
//评估函数，目前mode=1为不相同个数的评估，mode=2为曼哈顿距离意义下的评估
int calculateValue(array& curState, array& endState, int mode)
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