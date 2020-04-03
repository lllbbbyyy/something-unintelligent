#include<graphics.h>
#include<iostream>
#include<conio.h>
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

int main()
{
	//ע�ⲻ��std::array���洢�˲�������ȣ���Ϣ
	array gridBegin;
	array gridEnd;
	//�����ʼ����״̬
	input(gridBegin);
	input(gridEnd);
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
	//��ʼ��ͼ
	init();

	for (auto it : route)
	{
		paintingDraw(it);
		//draw()������ʾ
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