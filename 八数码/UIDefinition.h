#pragma once
#include<graphics.h>
#include"innerDefinition.h"
#include<stdio.h>
//����
//���ڴ�С
const int widthWindow		= 1024;
const int heightWindow		= 576;
//�򳤶�
const int lengthFrame		= 300;
//�����
const int gapFrame			= 30;
//�������λ��
const int yFrameLeft		= (heightWindow - lengthFrame) / 2;
const int xFrameLeft		= 30;
//�ҿ�����λ��
const int yFrameRight		= yFrameLeft;
const int xFrameRight		= lengthFrame + 2 * gapFrame;
//������Ϳ鳤��
const int gapBlock			= 10;
const int lengthBlock		= 80;
//״̬����
const int widthFrameStatus	= 300;
const int heightFrameStatus = 500;
//״̬������λ��
const int yFrameStatus		= (heightWindow - heightFrameStatus) / 2;
const int xFrameStatus		= 2 * lengthFrame + 3 * gapFrame;
//�����������
const int fontSize			= 20;
//������ʼλ��
const int xTextBegin		= xFrameStatus + 20;
const int yTextTop			= yFrameLeft;
const int yTextMid			= heightWindow / 2;
//��ť���
const int widthButton		= 120;
const int heightButton		= 60;
//���ư�ť����λ��
const int xButtonContinue	= xFrameStatus + 20;
const int xButtonPause		= xFrameStatus + widthButton + 40;
const int yButton			= yFrameStatus + heightFrameStatus - heightButton - 20;
//�����ַ�������
const wchar_t SEARCH_TIME[] = L"����ʱ�䣺";
const wchar_t MILLISECOND[] = L"����";
const wchar_t SOLUTION_STEP[] = L"�ⲽ����";
const wchar_t VISITED_NUMBER[] = L"����չ�ڵ㣺";
const wchar_t UNVISITED_NUMBER[] = L"δ��չ�ڵ㣺";
const wchar_t CURRENT_STEP[] = L"��ǰ������";
const wchar_t CURRENT_STATUS[] = L"��ǰ����";
const wchar_t FINAL_STATUS[] = L"Ŀ�����";
const wchar_t SELECTED_FUNCTION[] = L"���ۺ�����";

const wchar_t FUNCTION1[] = L"function1";
const wchar_t FUNCTION2[] = L"function2";

const wchar_t PLAY[] = L"����ģʽ";
const wchar_t DISPLAY[] = L"��ʾģʽ";

const wchar_t RANDOM[] = L"�������";
const wchar_t PERSONAL[] = L"�ֶ�����";

const wchar_t AUTO_PLAY[] = L"�Զ���ʾ";
const wchar_t MANUAL_PLAY[] = L"�ֶ���ʾ";

const wchar_t CONTINUE[] = L"����";
const wchar_t PAUSE[] = L"��ͣ";

//��������

//ͼ�ν���ĳ�ʼ��
void init(const int dispMode, const int selFun, const double searchTime, const int totalStep, const int visNum, const int unvisNum);
//ͼ�ν����ͷ�
void end();
//����Ŀ��״̬
void drawFinalStatus(const foundState& paint);
//����һ��״̬����
void paintingDraw(foundState& paint);
void paintingDraw(array& paint);
//��һ�����֣�������Ժ�����ͼƬ�ȴ���
void digitDraw(int num, int reLeft, int reTop, int reRight, int reBottom);
//���µ�ǰ���ݣ�Ŀǰֻ�е�ǰ����
void updateStatus(const int step);

//int select_function();
int select_initial(int button_count, const wchar_t** text);
//����ģʽ��ͼ�ν�����ʾ
void init_play(array gridBegin,array gridEnd);
void click_to_next(array& current);
bool match(array& paint, int x, int y, int& col, int& line);
bool move(array& current, int col, int line);