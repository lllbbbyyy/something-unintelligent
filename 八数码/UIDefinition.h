#pragma once
#include<graphics.h>
#include"innerDefinition.h"
#include<stdio.h>
//定义
//窗口大小
const int widthWindow		= 1024;
const int heightWindow		= 576;
//框长度
const int lengthFrame		= 300;
//框间间隔
const int gapFrame			= 30;
//左框左上位置
const int yFrameLeft		= (heightWindow - lengthFrame) / 2;
const int xFrameLeft		= 30;
//右框左上位置
const int yFrameRight		= yFrameLeft;
const int xFrameRight		= lengthFrame + 2 * gapFrame;
//块间间隔和块长度
const int gapBlock			= 10;
const int lengthBlock		= 80;
//状态框宽高
const int widthFrameStatus	= 300;
const int heightFrameStatus = 300;
//状态框左上位置
const int yFrameStatus		= (heightWindow - heightFrameStatus) / 2;
const int xFrameStatus		= 2 * lengthFrame + 3 * gapFrame;
//文字字体参数
const int fontSize			= 20;
//文字起始位置
const int xTextBegin		= xFrameStatus + 20;
const int yTextTop			= yFrameLeft + 20 + 2;
const int yTextMid			= heightWindow / 2;
//按钮宽高
const int widthButton		= 120;
const int heightButton		= 60;
//控制按钮左上位置
const int xButtonContinue	= xFrameStatus + 20;
const int xButtonPause		= xFrameStatus + widthButton + 40;
const int yButton			= yFrameStatus + heightFrameStatus - heightButton - 20;
//文字字符串常量
const wchar_t SEARCH_TIME[] = L"搜索时间：";
const wchar_t MILLISECOND[] = L"毫秒";
const wchar_t SOLUTION_STEP[] = L"解步长：";
const wchar_t VISITED_NUMBER[] = L"已扩展节点：";
const wchar_t UNVISITED_NUMBER[] = L"未扩展节点：";
const wchar_t CURRENT_STEP[] = L"当前步长：";
const wchar_t CURRENT_STATUS[] = L"当前局面";
const wchar_t FINAL_STATUS[] = L"目标局面";
const wchar_t SELECTED_FUNCTION[] = L"估价函数：";

const wchar_t FUNCTION1[] = L"不在位棋子数";
const wchar_t FUNCTION2[] = L"曼哈顿距离";
const wchar_t FUNCTION3[] = L"欧几里得距离";

const wchar_t PLAY[] = L"手玩模式";
const wchar_t DISPLAY[] = L"演示模式";

const wchar_t RANDOM[] = L"随机开局";
const wchar_t PERSONAL[] = L"手动开局";

const wchar_t AUTO_PLAY[] = L"自动演示";
const wchar_t MANUAL_PLAY[] = L"手动演示";

const wchar_t CONTINUE[] = L"继续";
const wchar_t PAUSE[] = L"暂停";

const wchar_t DISPLAY_END[] = L"操作/演示结束";
const wchar_t RESTAER_PROG[] = L"返回开始界面";
const wchar_t END_PROG[] = L"结束";
const wchar_t PROMOTE[] = L"移动鼠标继续";

const wchar_t GO_ON[] = L"下一步";

const wchar_t PLAY_PROMOTE[] = L"点击空格周围的格子进行移动";

//函数声明

//图形界面的初始化
void init(const int dispMode, const int selFun, const double searchTime, const int totalStep, const int visNum, const int unvisNum);
//图形界面释放
void end();
//绘制目标状态
void drawFinalStatus(const foundState& paint);
//绘制一次状态画面
void paintingDraw(foundState& paint);
void paintingDraw(array& paint);
//画一个数字，这个可以后面用图片等代替
void digitDraw(int num, int reLeft, int reTop, int reRight, int reBottom);
//更新当前数据，目前只有当前步长
void updateStatus(const int step);

//int select_function();
int select_initial(int button_count, const wchar_t** text);
//手玩模式的图形界面显示
void init_play(array gridBegin,array gridEnd);
int click_to_next(array& current);
bool match(array& paint, int x, int y, int& col, int& line);
bool move(array& current, int col, int line);
//判断鼠标位置是否在矩形内
bool inRect(int x, int y, int left, int top, int width, int height);
//检测结束时的按钮，0为重新开始，1为退出
bool endButton();
//提示移动鼠标
void draw_promote();
//提示手玩模式如何使用
void draw_play_promote();
//绘制搜索树
void draw_tree(tree& search_tree, std::deque<foundState> route,int mode);