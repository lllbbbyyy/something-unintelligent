#pragma once
#include<graphics.h>
#include"innerDefinition.h"
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

//函数声明

//图形界面的初始化
void init();
//图形界面释放
void end();
//绘制一次状态画面
void paintingDraw(foundState& paint);
//画一个数字，这个可以后面用图片等代替
void digitDraw(int x, int y, int num);