#include"innerDefinition.h"
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
//����������Ŀǰmode=1Ϊ����ͬ������������mode=2Ϊ�����پ��������µ�����
int calculateValue(array& curState, array& endState, int mode)
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