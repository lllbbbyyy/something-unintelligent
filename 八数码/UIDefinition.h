#pragma once
#include<graphics.h>
#include"innerDefinition.h"
#include<stdio.h>
//定义
//窗口大小
const int widthWindow = 640;
const int heightWindow = 480;
//红色框左上位置和正方形长度
const int yFrame = 70;
const int xFrame = 100;
const int lengthFrame = 300;
//间隔和每一个块的长度
const int gap = 10;
const int lengthRectan = 80;
//文字字体参数
const int fontSize = 20;
//文字起始位置
const int xTextBegin = 420;
const int yTextTop = 70;
const int yTextMid = 220;
//文字字符串常量
const wchar_t SEARCH_TIME[] = L"搜索时间：";
const wchar_t MILLISECOND[] = L"毫秒";
const wchar_t SOLUTION_STEP[] = L"解步长：";
const wchar_t VISITED_NUMBER[] = L"已扩展节点：";
const wchar_t UNVISITED_NUMBER[] = L"未扩展节点：";
const wchar_t CURRENT_STEP[] = L"当前步长：";

//函数声明

//图形界面的初始化
void init(const double searchTime, const int totalStep, const int visNum, const int unvisNum);
//图形界面释放
void end();
//绘制一次状态画面
void paintingDraw(foundState& paint);
//画一个数字，这个可以后面用图片等代替
void digitDraw(int num, int reLeft, int reTop, int reRight, int reBottom);
//更新当前数据，目前只有当前步长
void updateStatus(const int step);