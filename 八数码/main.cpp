//#include<graphics.h>
#include<iostream>
#include<array>
#include<conio.h>
#include<queue>
#include<map>
#include<stack>
#include"definition.h"
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
//�ж�����״̬�Ƿ����
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
//ͼ�ν���ĳ�ʼ��
//void init()
//{
//	initgraph(640, 480);
//}
//ͼ�ν����ͷ�
//void end()
//{
//	closegraph();
//}
//����������Ŀǰmode=1Ϊ����ͬ������������mode=2Ϊ�����پ��������µ�����
int calculateValue(array& curState, array& endState, int mode = 2)
{
	int value = 0;
	for (int i = 1; i < int(endState.arr.size()); i++)
	{
		for (int j = 1; j < int(endState.arr[0].size()); j++)
		{
			//����ͬ����������
			if (mode == 1) {
				if (curState.arr[i][j] != endState.arr[i][j])
				{
					value++;
				}
			}
			//�����پ�������
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
	//�ĸ��ƶ�����
	const int rowMove[] = { -1,0,1,0 };
	const int colMove[] = { 0,-1,0,1 };
	bool flag = false;
	int blankRow, blankCol;
	//Ѱ�ҿհ׿�
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
	//�ĸ�������
	foundState parent(curState);
	for (int i = 0; i < 4; i++)
	{
		newRow = blankRow + rowMove[i];
		newCol = blankCol + colMove[i];
		//�ڱ߽緶Χ��
		if (newRow >= 1 && newRow < int(curState.arr.size()) && newCol >= 1 && newCol < int(curState.arr[0].size()))
		{
			std::swap(curState.arr[blankRow][blankCol], curState.arr[newRow][newCol]);
			curState.step++;
			if (foundMap.empty() || !foundMap.count(foundState(curState))) {
				//����Ѿ��������ı�Ϊ�ջ��ߵ�ǰ��״̬û�б�Ѱ�ҹ������
				qu.push({ calculateValue(curState,endState),curState });
				foundMap[foundState(curState)] = parent;
			}
			//����
			std::swap(curState.arr[blankRow][blankCol], curState.arr[newRow][newCol]);
			curState.step--;
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
//���ش洢��·��,��ֹ���캯������̫��ʱ�����ʹ�����ô���
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
	//ע�ⲻ��std::array���洢�˲�������ȣ���Ϣ
	array gridBegin;
	array gridEnd;
	//�����ʼ����״̬
	input(gridBegin);
	input(gridEnd);
	//	init();
	//���ȶ��У�����������Ϊ�ؼ��ʵ�С���ѣ�ͬʱ�洢�˾���
	priQueue qu;
	//����Ѿ��������Ľڵ㣬�൱�ڼ�֦��ע�ⲻͬ��std::map
	map foundMap;
	//�ڵ��ŵ�ǰ��Ϣ
	nodeState gridCurr = { calculateValue(gridBegin,gridEnd),gridBegin };
	//��¼�Ѿ������Ľڵ�����
	int numFoundNode = 0;
	//�����վ��治��ͬʱ
	while (!isEqual(gridCurr.state, gridEnd))
	{
		//Ѱ����һ��ڵ�
		nextState(gridCurr.state, gridEnd, qu, foundMap);
		gridCurr = qu.top();
		qu.pop();
		numFoundNode++;
		//	print(gridCurr);
	}
	//��������Ϣ������չ�ڵ㣬δ��չ�ڵ�
	std::cout << gridCurr.value << std::endl << numFoundNode << std::endl << qu.size() << std::endl;
	std::deque<foundState> route;
	findRoute(gridBegin, gridEnd, foundMap, route);
	for (auto it : route)
	{
		print(it);
		//draw()������ʾ
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