#pragma once
#include<graphics.h>
#include"innerDefinition.h"
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

//��������

//ͼ�ν���ĳ�ʼ��
void init();
//ͼ�ν����ͷ�
void end();
//����һ��״̬����
void paintingDraw(foundState& paint);
//��һ�����֣�������Ժ�����ͼƬ�ȴ���
void digitDraw(int x, int y, int num);