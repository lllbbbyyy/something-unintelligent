#pragma once
#include<array>
#include<map>
#include<queue>
//n�������������
const int row = 3;
const int col = 3;
//��Ÿ�����Ϣ�͵�ǰ״̬�����
struct array
{
	std::array<std::array<int, col + 1>, row + 1> arr;
	int step;
};
//��Ҫ�������map����Ѿ�Ѱ�ҹ��ľ�����Ϣ����Ҫ��Ϊ������С�ںţ������ж����������Ƿ���ͬ
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
//������ȶ��У�����С�ںŽ�����ֵ��Ϊ�Ƚ϶���С����
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

//inner����

//�ж�����״̬�Ƿ����
bool isEqual(array& grid1, array& grid2);
//����������Ŀǰmode=1Ϊ����ͬ������������mode=2Ϊ�����پ��������µ�����
int calculateValue(array& curState, array& endState, int mode = 2);
//Ѱ����һ��״̬
void nextState(array& curState, array& endState, priQueue& qu, map& foundMap);
//���ش洢��·��,��ֹ���캯������̫��ʱ�����ʹ�����ô���
void findRoute(array& beginState, array& endState, map& foundMap, std::deque<foundState>& route);
