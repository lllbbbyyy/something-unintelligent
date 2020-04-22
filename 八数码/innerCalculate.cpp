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
//����������Ŀǰmode=1Ϊ����ͬ������������mode=2Ϊ�����پ��������µ�������mode=3Ϊŷ����þ�������
//ȡ��Ĭ�ϲ�������ֹ�������ĵ���
double calculateValue(array& curState, array& endState, int mode)
{
	double value = 0;
	for (int i = 1; i < int(endState.arr.size()); i++)
	{
		for (int j = 1; j < int(endState.arr[0].size()); j++)
		{
			if (curState.arr[i][j] == 0)
			{
				continue;
			}
			//����ͬ����������
			if (mode == 1) {
				if (curState.arr[i][j] != endState.arr[i][j])
				{
					value++;
				}
			}
			//�����پ�������
			if (mode == 2 || mode == 3) {
				int flag = 0;
				for (int m = 1; m < int(endState.arr.size()); m++)
				{
					for (int n = 1; n < int(endState.arr[0].size()); n++)
					{
						if (curState.arr[i][j] == endState.arr[m][n])
						{
							if (mode == 2) {
								double tem = 0;
								if (i < m)
									tem += m - i;
								else
									tem += i - m;
								if (j < n)
									tem += n - j;
								else
									tem += j - n;
								flag = 1;
								value += tem;
								break;
							}
							else if (mode == 3)
							{
								value += sqrt((i - m) * (i - m) + (j - n) * (j - n));
							}
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
//���Ӳ���mode����֤��������������ʱ�򲻻�һֱʹ��Ĭ�ϵĲ���
void nextState(array& curState, array& endState, priQueue& qu, map& foundMap,int mode,tree& search_tree)
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

				double value_cur = calculateValue(curState, endState, mode);
				if (search_tree.count(parent))
				{
					search_tree[parent].push_back({ curState.arr,value_cur });
				}
				else
				{
					search_tree[parent] = std::vector<tree_node>{};
					search_tree[parent].push_back({ curState.arr,value_cur });
				}
				qu.push({value_cur ,curState });
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

bool has_solution(array gridBegin, array gridEnd) {
	int num = (gridBegin.arr.size() - 1) * (gridBegin.arr[0].size() - 1);
	int* B = new int[num];
	int* E = new int[num];
	int ansBegin = 0;
	int ansEnd = 0;
	for (int i = 0; i < num; i++) {
		B[i] = 0;
		E[i] = 0;
		for (int j = 0; j < i; j++) {
			if (gridBegin.arr[j / 3 + 1][j % 3 + 1] && gridBegin.arr[i / 3 + 1][i % 3 + 1] && gridBegin.arr[j / 3 + 1][j % 3 + 1] < gridBegin.arr[i / 3 + 1][i % 3 + 1])
				B[i]++;
			if (gridEnd.arr[j / 3 + 1][j % 3 + 1] && gridEnd.arr[i / 3 + 1][i % 3 + 1] && gridEnd.arr[j / 3 + 1][j % 3 + 1] < gridEnd.arr[i / 3 + 1][i % 3 + 1])
				E[i]++;
		}
		ansBegin += B[i];
		ansEnd += E[i];
	}
	delete[] B;
	delete[] E;

	if ((ansBegin + ansEnd) % 2 == 0)//ͬ��ͬż
		return true;
	else
		return false;
}

void random_initial(array& gridBegin, array& gridEnd) {

	gridBegin.step = 0;
	gridEnd.step = 0;

	int size1 = gridBegin.arr.size();
	int size2 = gridBegin.arr[0].size();

	//0-8���
	srand((unsigned)time(NULL));
	//num = 3*3
	int num = (size1 - 1) * (size2 - 1);
	int* shuffleBegin = new int[num];
	int* shuffleEnd = new int[num];
	for (int i = 0; i < num; i++) {
		shuffleBegin[i] = rand();
	}

	for (int i = 1; i < size1; i++)
	{
		for (int j = 1; j < size2; j++)
		{
			int max = 0;
			for (int k = 0; k < num; k++)
			{
				if (shuffleBegin[k] > shuffleBegin[max])
					max = k;
			}
			gridBegin.arr[i][j] = max;
			shuffleBegin[max] = -1;
		}
	}

	while (1) {

		for (int i = 0; i < num; i++) {
			shuffleEnd[i] = rand();
		}

		for (int i = 1; i < size1; i++)
		{
			for (int j = 1; j < size2; j++)
			{
				int max = 0;
				for (int k = 0; k < num; k++)
				{
					if (shuffleEnd[k] > shuffleEnd[max])
						max = k;
				}
				gridEnd.arr[i][j] = max;
				shuffleEnd[max] = -1;
			}
		}
		//����Ƿ���Կ���
		bool ok = true;
		ok = has_solution(gridBegin, gridEnd);
		if (ok)
		{
			delete[] shuffleBegin;
			delete[] shuffleEnd;
			return;
		}
		else
			continue;
	}

}

//�ļ������ȿ��ֺ��վ֣��ո���м������
int personal_initial(array& gridBegin, array& gridEnd, const std::string path)
{
	gridBegin.step = 0;
	gridEnd.step = 0;

	//����path���ļ�
	//todo ���ļ�����û����ͼ�ν�������ʾ
	std::fstream in;
	in.open(path, std::ios::in);
	if (!in.is_open())
	{
		std::cerr << "���ļ�����" << std::endl;
		return NO_INPUT_FOUND;
	}

	for (int i = 1; i < int(gridBegin.arr.size()); i++)
	{
		for (int j = 1; j < int(gridBegin.arr[0].size()); j++)
		{
			in >> gridBegin.arr[i][j];
		}
	}

	for (int i = 1; i < int(gridEnd.arr.size()); i++)
	{
		for (int j = 1; j < int(gridEnd.arr[0].size()); j++)
		{
			in >> gridEnd.arr[i][j];
		}
	}
	in.close();
	bool ok = has_solution(gridBegin, gridEnd);
	if (!ok)
		return NO_SOLUTION;
	else
		return 0;
}
