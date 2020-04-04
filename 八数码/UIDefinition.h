#pragma once
#include<graphics.h>
#include"innerDefinition.h"
#include<stdio.h>
//����
//���ڴ�С
const int widthWindow = 640;
const int heightWindow = 480;
//��ɫ������λ�ú������γ���
const int yFrame = 70;
const int xFrame = 100;
const int lengthFrame = 300;
//�����ÿһ����ĳ���
const int gap = 10;
const int lengthRectan = 80;
//�����������
const int fontSize = 20;
//������ʼλ��
const int xTextBegin = 420;
const int yTextTop = 70;
const int yTextMid = 220;
//�����ַ�������
const wchar_t SEARCH_TIME[] = L"����ʱ�䣺";
const wchar_t MILLISECOND[] = L"����";
const wchar_t SOLUTION_STEP[] = L"�ⲽ����";
const wchar_t VISITED_NUMBER[] = L"����չ�ڵ㣺";
const wchar_t UNVISITED_NUMBER[] = L"δ��չ�ڵ㣺";
const wchar_t CURRENT_STEP[] = L"��ǰ������";

//��������

//ͼ�ν���ĳ�ʼ��
void init(const double searchTime, const int totalStep, const int visNum, const int unvisNum);
//ͼ�ν����ͷ�
void end();
//����һ��״̬����
void paintingDraw(foundState& paint);
//��һ�����֣�������Ժ�����ͼƬ�ȴ���
void digitDraw(int num, int reLeft, int reTop, int reRight, int reBottom);
//���µ�ǰ���ݣ�Ŀǰֻ�е�ǰ����
void updateStatus(const int step);