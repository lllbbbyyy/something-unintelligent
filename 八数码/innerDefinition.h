#pragma once
#include<array>
#include<map>
#include<queue>
#include<time.h>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<iostream>
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
	double value;
	array state;
	bool operator < (const nodeState& a) const
	{
		return value > a.value;
	}
};
typedef std::priority_queue<nodeState> priQueue;
typedef std::map<foundState, foundState> map;

//initial flags,���ִ���������ҵڼ�����ť[0,1]
const int RANDOM_INITIAL = 0;
const int PERSONAL_INITIAL = 1;

//personal initial��ȡ�ļ�λ��
const std::string PATH = ".\\input.txt";
//personal initial flags
const int NO_INPUT_FOUND = -1;
const int NO_SOLUTION = -2;


//inner����

//�ж�����״̬�Ƿ����
bool isEqual(array& grid1, array& grid2);
//����������Ŀǰmode=1Ϊ����ͬ������������mode=2Ϊ�����پ��������µ�������mode=3Ϊŷ����þ�������
//ȡ��Ĭ�ϲ�������ֹ�������ĵ���
double calculateValue(array& curState, array& endState, int mode);
//Ѱ����һ��״̬
//���Ӳ���mode����֤��������������ʱ�򲻻�һֱʹ��Ĭ�ϵĲ���
void nextState(array& curState, array& endState, priQueue& qu, map& foundMap,int mode);
//���ش洢��·��,��ֹ���캯������̫��ʱ�����ʹ�����ô���
void findRoute(array& beginState, array& endState, map& foundMap, std::deque<foundState>& route);
//�ж϶�Ӧ���ֺ��վ��Ƿ��н�
bool has_solution(array gridBegin, array gridEnd);
//�����ʼ�����ֺ��վ�
void random_initial(array& gridBegin,array& gridEnd);
int personal_initial(array& gridBegin,array& gridEnd,const std::string path);