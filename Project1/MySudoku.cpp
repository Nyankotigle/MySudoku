#include <stdio.h>
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <math.h>
void init();
void show();
void solve_win();
void select_win();
void create_sudoku(int);
int rand_number(int);
char* transfer_time(int sec, char*);
void Show_this_num(int);
int set_number(int sudoku[9][9], int row, int col);
int check_number(int[9][9], int, int, int);
void print_sudoku(int sudoku[9][9]);
int find_empty(int sudoku[9][9], int startrow, int *row, int *col);

int SUDOKU_ARR[9][9] = { 0 };
int Row, Col;
int SUDOKU_COPY[9][9];
int SOLVE_COPY[9][9];

int main()
{
	init();
	
	_getch();
	return 0;
}

void init() {//初始界面
	initgraph(600, 675);
	HWND hwnd = GetHWnd();
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	MoveWindow(hwnd, 340, 0, 600, 675, TRUE);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(200, 40, _T("微软雅黑"));
	settextcolor(RGB(250, 100, 50));
	outtextxy(50, 60, "MY");
	settextcolor(BLACK);
	outtextxy(190, 60, "SUDOKU");
	setfillcolor(YELLOW);
	solidrectangle(200, 300, 400, 400);
	solidrectangle(200, 450, 400, 550);
	setbkcolor(WHITE);
	settextstyle(20, 6, _T("华文中宋"));
	outtextxy(205, 610, "Alt+Space+M+方向键 移动窗口位置");
	outtextxy(130, 630, "版权所有：1204219458@qq.com |版本:4.0 |2020.02.26 ");
	setbkcolor(YELLOW); 
	settextstyle(50, 20, _T("华文中宋"));
	outtextxy(258, 325, "求解");
	outtextxy(258, 475, "挑战");
	MOUSEMSG m;		// 定义鼠标消息
	while (true)
	{// 获取一条鼠标消息
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {//左键按下消息
			if (m.x >= 200 && m.x <= 400 && m.y >= 300 && m.y <= 400) {
				setfillcolor(RGB(150, 250, 150));
				solidrectangle(200, 300, 400, 400);
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 450 && m.y <= 550) {
				setfillcolor(RGB(150, 250, 150));
				solidrectangle(200, 450, 400, 550);
			}
		}
		if (m.uMsg == WM_LBUTTONUP) {//左键弹起消息
			if (m.x >= 200 && m.x <= 400 && m.y >= 300 && m.y <= 400) {
				closegraph();
				solve_win();
				return;
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 450 && m.y <= 550) {
				select_win();
				return;
			}
		}
	}
}

void show() {//宫格基础界面
	initgraph(600, 675);
	HWND hwnd = GetHWnd();
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	MoveWindow(hwnd, 340, 0, 600, 675, TRUE);
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 5, NULL, 0);
	line(0, 1, 600, 1);
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(0, 600, 600, 600);
	line(0, 673, 600, 673);
	line(1, 0, 1, 670);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
	line(598, 0, 598, 670);
	setlinestyle(PS_SOLID, 2, NULL, 0);
	for (int i = 67; i < 600; i += 67) {
		line(0, i, 600, i);
		line(i, 0, i, 600);
	}
	return;
}
void solve_win() {//求解
	show();
	setbkcolor(YELLOW);
	setfillcolor(YELLOW);
	settextcolor(BLACK);
	solidrectangle(5, 605, 595, 670);
	settextstyle(60, 25, _T("华文中宋"));
	outtextxy(200, 605, "确定提交");
	settextstyle(50, 30, _T("微软雅黑"));
	int ch;
	MOUSEMSG m;		// 定义鼠标消息
	while (true)
	{// 获取一条鼠标消息
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {//左键按下消息
			if (m.y > 600) {//确认提交
				find_empty(SUDOKU_ARR, 0, &Row, &Col);
				if (set_number(SUDOKU_ARR, Row, Col) == 0) {//如果无解
					//提示输入无解
					setbkcolor(RGB(250, 100, 50)); setfillcolor(RGB(250, 100, 50)); settextstyle(60, 25, _T("华文中宋"));
					solidrectangle(5, 605, 595, 670);
					outtextxy(200, 605, "输入无解");
					Sleep(1000);
					for (int v = 0; v < 9; v++) {//清空当前输入
						for (int w = 0; w < 9; w++) {SUDOKU_ARR[v][w] = 0;}
					}
					closegraph();
					init();
					return;
				}
				print_sudoku(SUDOKU_ARR);
				return;
			}
			else
			{	//当前点击方格高亮
				solidrectangle((m.x / 67) * 67 + 5, (m.y / 67) * 67 + 6, (m.x / 67) * 67 + 57, (m.y / 67) * 67 + 57);
				while (1) {
					if (_kbhit()) {
						ch = _getch();
						//fflush(stdin);//清空缓冲区（貌似不起作用）
						break;
					}
				}
				if (check_number(SUDOKU_ARR, ch - 48, m.y / 67, m.x / 67)) {
					SUDOKU_ARR[m.y / 67][m.x / 67] = ch - 48;//将ch的ASCII码值转换为相应的整数
					outtextxy((m.x / 67) * 67 + 10, (m.y / 67) * 67 + 6, ch);
				}
				else {
					setfillcolor(WHITE);//取消当前点击方格高亮
					solidrectangle((m.x / 67) * 67 + 5, (m.y / 67) * 67 + 6, (m.x / 67) * 67 + 57, (m.y / 67) * 67 + 57);
					//提示输入有误
					setbkcolor(RGB(250,100,50));setfillcolor(RGB(250, 100, 50)); settextstyle(60, 25, _T("华文中宋"));
					solidrectangle(5, 605, 595, 670);
					outtextxy(200, 605, "输入有误");
					Sleep(500);
					//恢复确认提交
					setbkcolor(YELLOW); setfillcolor(YELLOW); settextstyle(60, 25, _T("华文中宋"));
					solidrectangle(5, 605, 595, 670);
					outtextxy(200, 605, "确定提交");
					settextstyle(50, 30, _T("微软雅黑"));
				}
			}
		}
	}
}

void select_win() {//选择难度
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(BLACK);
	setfillcolor(YELLOW);
	solidrectangle(200, 150, 400, 250);
	solidrectangle(200, 300, 400, 400);
	solidrectangle(200, 450, 400, 550);
	setbkcolor(YELLOW);
	settextstyle(50, 20, _T("华文中宋"));
	outtextxy(258, 175, "菜鸟");
	outtextxy(258, 325, "专家");
	outtextxy(258, 475, "大师");
	setbkcolor(RGB(150, 250, 150));
	setfillcolor(RGB(150, 250, 150));
	MOUSEMSG m;		// 定义鼠标消息
	while (true)
	{// 获取一条鼠标消息
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {//左键按下消息
			if (m.x >= 200 && m.x <= 400 && m.y >= 150 && m.y <= 250) {
				solidrectangle(200, 150, 400, 250);
				outtextxy(258, 175, "稍等");
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 300 && m.y <= 400) {
				solidrectangle(200, 300, 400, 400);
				outtextxy(258, 325, "稍等");
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 450 && m.y <= 550) {
				solidrectangle(200, 450, 400, 550);
				outtextxy(258, 475, "稍等");
			}
		}
		if (m.uMsg == WM_LBUTTONUP) {//左键弹起消息
			if (m.x >= 200 && m.x <= 400 && m.y >= 150 && m.y <= 250) {
				closegraph();
				create_sudoku(40);
				return;
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 300 && m.y <= 400) {
				closegraph();
				create_sudoku(30);
				return;
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 450 && m.y <= 550) {
				closegraph();
				create_sudoku(20);
				return;
			}
		}
	}
}
	


void create_sudoku(int rank) {
createsudoku://随机生成数独
		for (int i, j, k, count = 0; count < 17;) {//数独至少17个数才有唯一解
			//srand((unsigned int)time(NULL));//秒级随机数，不适合连续生成
			i = rand_number(1); //Sleep(1);
			j = rand_number(2); //Sleep(3);
			k = rand_number(3); //Sleep(5);
			if (SUDOKU_ARR[i][j] == 0 && check_number(SUDOKU_ARR, k + 1, i, j)) {
				SUDOKU_ARR[i][j] = k + 1;
				count++;
			}
		}
	find_empty(SUDOKU_ARR, 0, &Row, &Col);
	if(set_number(SUDOKU_ARR, Row, Col) == 0) {//如果无解
		for (int v = 0; v < 9; v++) {//清空当前输入
			for (int w = 0; w < 9; w++) { SUDOKU_ARR[v][w] = 0; }
		}
		goto createsudoku;//重新生成
	}
	else //如果有解
	{
		for (int v = 0; v < 9; v++) {//备份解
			for (int w = 0; w < 9; w++) { SOLVE_COPY[v][w] = SUDOKU_ARR[v][w]; }
		}
		for (int i, j, k, count = 0; count < 81-rank;) {//数独至少17个数才有唯一解
			i = rand_number(1); //Sleep(1);
			j = rand_number(2); //Sleep(3);
			k = rand_number(3); //Sleep(5);
			if (SUDOKU_ARR[i][j] != 0 ) {
				SUDOKU_ARR[i][j] = 0;
				count++;
			}
		}
	}
	for (int v = 0; v < 9; v++) {//备份生成的初始数独
		for (int w = 0; w < 9; w++) { SUDOKU_COPY[v][w] = SUDOKU_ARR[v][w]; }
	}
	
CLEAN_INPUT://清空所有操作，重新开始
	show();			
	settextcolor(BLACK);
	setbkcolor(RGB(200, 250, 200));
	setfillcolor(RGB(200,250,200));
	settextstyle(50, 30, _T("微软雅黑"));
	for (int v = 0; v < 9; v++) {//显示生成的初始数独
		for (int w = 0; w < 9; w++) {
			if (SUDOKU_COPY[v][w] != 0) {
				solidrectangle(w * 67 + 5, v * 67 + 6, w * 67 + 57, v * 67 + 57);//初始数标为绿色
				outtextxy(w * 67 + 10, v * 67 + 6, SUDOKU_COPY[v][w] + 48); //将整数转换为相应的ASCII码值
			}
		}
	}
	setbkcolor(YELLOW);
	setfillcolor(YELLOW);
	settextcolor(BLACK);
	solidrectangle(5, 605, 595, 670);
	setlinestyle(PS_SOLID, 5, NULL, 0);
	line(120, 600, 120, 670);
	line(240, 600, 240, 670);
	line(360, 600, 360, 670);
	line(480, 600, 480, 670);
	settextstyle(50, 20, _T("华文中宋"));
	outtextxy(20, 610, "撤销");
	outtextxy(140, 610, "恢复");
	outtextxy(380, 610, "标记");
	outtextxy(500, 610, "重置");
	settextstyle(50, 30, _T("微软雅黑"));
	clock_t  start, now;
	start = clock();
	char time_str[9] = { 0 };//存储时间字符串
	int count = 0;//记录填数个数
	int count_max = 0;//记录当前已填最大个数
	int Track[81][3] = { 0 };//记录填入轨迹
	int ch;
	MOUSEMSG m;		// 定义鼠标消息
	while (true)
	{
		now = clock();//更新显示时间
		settextstyle(40, 12, _T("微软雅黑")); setbkcolor(YELLOW);
		outtextxy(250, 615, transfer_time((int)((now - start) / CLK_TCK), time_str));
		settextstyle(50, 30, _T("微软雅黑"));

		FlushMouseMsgBuffer();//清空鼠标缓冲区
		m = GetMouseMsg();// 获取一条鼠标消息
		if (m.uMsg == WM_LBUTTONDOWN) {//左键按下消息
			if (m.y > 600 && m.x > 0 && m.x < 120) {//撤销
				setfillcolor(WHITE);
				if (count > 0) {
					count--;
					SUDOKU_ARR[Track[count][0]][Track[count][1]] = 0;//
					solidrectangle(Track[count][1] * 67 + 5, Track[count][0] * 67 + 6, Track[count][1] * 67 + 57, Track[count][0] * 67 + 57);
				}
			}
			if (m.y > 600 && m.x > 120 && m.x < 240) {//恢复
				if (count < count_max) {
					SUDOKU_ARR[Track[count][0]][Track[count][1]] = Track[count][2];//
					settextcolor(BLACK);
					setfillcolor(YELLOW); setbkcolor(YELLOW);
					solidrectangle(Track[count][1] * 67 + 5, Track[count][0] * 67 + 6, Track[count][1] * 67 + 57, Track[count][0] * 67 + 57);
					outtextxy(Track[count][1] * 67 + 10, Track[count][0] * 67 + 6, Track[count][2]);
					count++;
				}
			}
			if (m.y > 600 && m.x > 240 && m.x < 360) {//显示答案
				for (int v = 0; v < 9; v++) {
					for (int w = 0; w < 9; w++) {
						setfillcolor(YELLOW); setbkcolor(YELLOW);
						solidrectangle(w * 67 + 5, v * 67 + 6, w * 67 + 57, v * 67 + 57);
						outtextxy(w * 67 + 10, v * 67 + 6, SOLVE_COPY[v][w] + 48); 
					}
				}
				setbkcolor(RGB(250, 100, 50)); setfillcolor(RGB(250, 100, 50)); settextstyle(60, 25, _T("华文中宋"));
				solidrectangle(5, 602, 595, 670);
				outtextxy(200, 605, "您已认输");
				while (true)//点击回到初始界面
				{
					m = GetMouseMsg();
					if (m.uMsg == WM_LBUTTONDOWN) {
						init(); return;
					}
				}
			}
			
			if (m.y < 600 )//点击宫格部分
			{	
				if (SUDOKU_COPY[m.y / 67][m.x / 67] != 0) {//点击的是初始值
					Show_this_num(SUDOKU_ARR[m.y / 67][m.x / 67]);
				}
				if (SUDOKU_COPY[m.y / 67][m.x / 67] == 0) {//点击的不是初始值
					if (SUDOKU_ARR[m.y / 67][m.x / 67] != 0) {//点击的不是空格
						Show_this_num(SUDOKU_ARR[m.y / 67][m.x / 67]);
					}
					//当前点击方格高亮，并且清零
					setfillcolor(YELLOW);
					solidrectangle((m.x / 67) * 67 + 5, (m.y / 67) * 67 + 6, (m.x / 67) * 67 + 57, (m.y / 67) * 67 + 57);
					SUDOKU_ARR[m.y / 67][m.x / 67] = 0;
					while (1) {//获取键盘输入
						if (_kbhit()) {//这里怎么清除输入缓存还未解，导致一次输入多个数时，下一次直接从缓冲区读数而不是等待键盘输入
							ch = _getch();
							break;
						}
					}
					if (ch==27) {//点击Esc，即取消当前输入锁定
						if (SUDOKU_ARR[m.y / 67][m.x / 67] == 0) {//之前点击的是空格
							setfillcolor(WHITE);
							solidrectangle((m.x / 67) * 67 + 5, (m.y / 67) * 67 + 6, (m.x / 67) * 67 + 57, (m.y / 67) * 67 + 57);
							setfillcolor(YELLOW);
						}//重新恢复空格
						if (SUDOKU_ARR[m.y / 67][m.x / 67] != 0 && SUDOKU_COPY[m.y / 67][m.x / 67] == 0) {//之前点击的为非初始数
							setbkcolor(YELLOW);
							outtextxy((m.x / 67) * 67 + 10, (m.y / 67) * 67 + 6, SUDOKU_ARR[m.y / 67][m.x / 67] + 48);
						}//重新恢复数字
					}
					else if (check_number(SUDOKU_ARR, ch - 48, m.y / 67, m.x / 67)) {//如果可以填入
						SUDOKU_ARR[m.y / 67][m.x / 67] = ch - 48;//将ch的ASCII码值转换为相应的整数填入数组
						setbkcolor(YELLOW);
						outtextxy((m.x / 67) * 67 + 10, (m.y / 67) * 67 + 6, ch);
						Track[count][0] = m.y / 67;
						Track[count][1] = m.x / 67;
						Track[count][2] = ch;
						count++;
						count_max = count;//更新count_max
						if ((count + rank) == 81) {//已填+初始=81，填充完毕，显示成功
							setbkcolor(RGB(250, 100, 50)); setfillcolor(RGB(250, 100, 50)); settextstyle(60, 25, _T("华文中宋"));
							solidrectangle(5, 602, 595, 670);
							outtextxy(200, 605, "挑战成功");
							while (true)//点击回到初始界面
							{
								m = GetMouseMsg();
								if (m.uMsg == WM_LBUTTONDOWN) {
									init(); return;
								}
							}
						}
					}
					else {//闪烁提示不可填入
						setfillcolor(RGB(250, 100, 50));
						solidrectangle((m.x / 67) * 67 + 5, (m.y / 67) * 67 + 6, (m.x / 67) * 67 + 57, (m.y / 67) * 67 + 57);
						Sleep(100);
						setfillcolor(WHITE);
						solidrectangle((m.x / 67) * 67 + 5, (m.y / 67) * 67 + 6, (m.x / 67) * 67 + 57, (m.y / 67) * 67 + 57);
						Sleep(100);
						setfillcolor(RGB(250, 100, 50));
						solidrectangle((m.x / 67) * 67 + 5, (m.y / 67) * 67 + 6, (m.x / 67) * 67 + 57, (m.y / 67) * 67 + 57);
						Sleep(100);
						setfillcolor(WHITE);
						solidrectangle((m.x / 67) * 67 + 5, (m.y / 67) * 67 + 6, (m.x / 67) * 67 + 57, (m.y / 67) * 67 + 57);
						setbkcolor(YELLOW); setfillcolor(YELLOW);
					}
				}
			}

			if (m.y > 600 && m.x > 360 && m.x < 480) {//标记
				setbkcolor(RGB(250, 100, 50)); setfillcolor(RGB(250, 100, 50)); settextstyle(50, 20, _T("华文中宋"));
				solidrectangle(365, 605, 475, 670); outtextxy(380, 610, "标记");
				while (true)
				{
					m = GetMouseMsg();// 获取一条鼠标消息
					if (m.uMsg == WM_LBUTTONDOWN) {//左键按下消息
						if (m.y < 600 && SUDOKU_ARR[m.y / 67][m.x / 67] == 0) {
							solidrectangle((m.x / 67) * 67 + 5, (m.y / 67) * 67 + 6, (m.x / 67) * 67 + 57, (m.y / 67) * 67 + 57);
							settextstyle(50, 12, _T("华文中宋"));
							outtextxy(370, 610, "回车结束");
							while (1) {
								if (_kbhit()) {
									ch = _getch();
									if (ch >= 49 && ch <= 57) {
										settextstyle(18, 10, _T("微软雅黑"));
										outtextxy((m.x / 67) * 67 + ((ch - 49) % 3) * 15 + 10, (m.y / 67) * 67 + ((ch - 49) / 3) * 15+10, ch);

									}
									if (ch == 13) {//回车键
										setbkcolor(YELLOW); setfillcolor(YELLOW); settextstyle(50, 20, _T("华文中宋"));
										solidrectangle(365, 605, 475, 670); outtextxy(380, 610, "标记");
										settextstyle(50, 30, _T("微软雅黑"));
										break;
									}
								}
							}
							break;
						}
					}
				}
			}
			if (m.y > 600 && m.x > 480 && m.x < 600) {//重置
				for (int v = 0; v < 9; v++) {
					for (int w = 0; w < 9; w++) { SUDOKU_ARR[v][w] = SUDOKU_COPY[v][w]; }
				}
				closegraph();
				goto CLEAN_INPUT;
			}
		}
	}
	return;
}

int rand_number(int rand_rank) {//生成0到8随机数
	LARGE_INTEGER seed;
	QueryPerformanceFrequency(&seed);
	QueryPerformanceCounter(&seed);
	srand(seed.QuadPart);//初始化一个以微秒为单位的时间种子
	for (int i = 0; i < rand_rank; i++) {//
		srand(seed.QuadPart + rand() % 17);
		srand(seed.QuadPart + rand() % 29);
		srand(seed.QuadPart + rand() % 37);
		srand(seed.QuadPart + rand() % 43);
		srand(seed.QuadPart + rand() % 55);
		srand(seed.QuadPart + rand() % 61);
		srand(seed.QuadPart + rand() % 79);
		srand(seed.QuadPart + rand() % 83);
	}
	return rand() % 9;
}

char* transfer_time(int sec,char* time_str) {//将整数秒转换为时间字符串
	time_str[0] = (sec / 3600) / 10 + 48;
	time_str[1] = (sec / 3600) % 10 + 48;
	time_str[2] = ':';
	time_str[3] = ((sec % 3600) / 60) / 10 + 48;
	time_str[4] = ((sec % 3600) / 60) % 10 + 48;
	time_str[5] = ':';
	time_str[6] = ((sec % 3600) % 60) / 10 + 48;
	time_str[7] = ((sec % 3600) % 60) % 10 + 48;
	return time_str;
}

void Show_this_num(int num) {//高亮显示所有相同数字
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (SUDOKU_ARR[i][j] == num ) {
				setfillcolor(RGB(0, 150, 250)); setbkcolor(RGB(0, 150, 250));
				solidrectangle(j * 67 + 5, i * 67 + 6, j * 67 + 57, i * 67 + 57);
				outtextxy(j * 67 + 10, i * 67 + 8, num+48);//数字位置向下移动2，形成动态效果
			}
		}
	}
	Sleep(1000);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (SUDOKU_ARR[i][j] == num && SUDOKU_COPY[i][j] != 0) {//初始数
				setfillcolor(RGB(200, 250, 200)); setbkcolor(RGB(200, 250, 200));
				solidrectangle(j * 67 + 5, i * 67 + 6, j * 67 + 57, i * 67 + 57);
				outtextxy(j * 67 + 10, i * 67 + 6, num + 48);
			}
			if (SUDOKU_ARR[i][j] == num && SUDOKU_COPY[i][j] == 0) {//非初始数
				setfillcolor(YELLOW); setbkcolor(YELLOW);
				solidrectangle(j * 67 + 5, i * 67 + 6, j * 67 + 57, i * 67 + 57);
				outtextxy(j * 67 + 10, i * 67 + 6, num + 48);
			}
		}
	}
}

int find_empty(int sudoku[9][9], int startrow, int *row, int *col) {//传递地址以便修改操作位置
	int i, j;
	for (i = startrow; i < 9; i++)//从当前行开始检查未填数的位置
		for (j = 0; j < 9; j++)
			if (sudoku[i][j] == 0) {//将遇到的第一个未填充位置置为当前操作位置
				*row = i;
				*col = j;
				return 1;
			}
	return 0;//没有未填充的位置了
}

int set_number(int sudoku[9][9], int row, int col) {//深度优先递归填充数独
	int m, next_row, next_col;
	for (m = 1; m <= 9; m++) {
		if (check_number(sudoku, m, row, col) == 1) {//如果可填

			sudoku[row][col] = m;//填入
			//寻找下一个未填充位置
			if (find_empty(sudoku, row, &next_row, &next_col) == 0) return 1;//全部填充完毕逐层返回
			//否则递归填充下一个位置（利用递归返回实现深度优先搜索的回溯）
			if (set_number(sudoku, next_row, next_col) == 0) {//下一个位置填充失败则返回到当前位置
				sudoku[row][col] = 0;//将当前位置填充的数清零
				continue;//继续for循环 在之前填充的数之后寻找其他可填充数
			}
			else return 1;//下一个位置填充成功
		}
	}
	return 0;//没有可填充的数，填充失败
}

int check_number(int sudoku[9][9], int m, int row, int col) {//检查是否重复
	int i, j;
	for (i = 0; i < 9; i++) {//同行检查
		if (sudoku[row][i] == m) return 0;
	}
	for (i = 0; i < 9; i++) {//同列检查
		if (sudoku[i][col] == m) return 0;
	}
	//同宫检查
	int x = (row / 3) * 3;
	int y = (col / 3) * 3;//x,y为当前位置所在小九宫格左上角坐标
	for (i = x; i < x + 3; i++) {
		for (j = y; j < y + 3; j++) {
			if (sudoku[i][j] == m) return 0;
		}
	}
	return 1;//返回可填信号
}

void print_sudoku(int sudoku[9][9]) {//输出解
	int v, w;
	closegraph();
	show();
	settextcolor(BLACK);
	settextstyle(50, 30, _T("微软雅黑"));
	for (v = 0; v < 9; v++) {
		for (w = 0; w < 9; w++) {
			outtextxy(w * 67 + 10, v * 67 + 5, sudoku[v][w] + 48); //将整数转换为相应的ASCII码值
			sudoku[v][w] = 0;//输出后即初始化为下一轮做准备
		}
	}
	setbkcolor(YELLOW); setfillcolor(YELLOW); settextstyle(60, 25, _T("华文中宋"));
	solidrectangle(5, 605, 595, 670);
	setlinestyle(PS_SOLID, 5, NULL, 0);
	line(300, 600, 300, 670);
	outtextxy(100, 605, "求解");
	outtextxy(400, 605, "挑战");
	settextstyle(50, 30, _T("微软雅黑"));
	MOUSEMSG m;		// 定义鼠标消息
	while (true)
	{// 获取一条鼠标消息
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {//左键按下消息
			if (m.y > 600 && m.x > 0 && m.x < 300) {
				closegraph();
				solve_win();
				return;
			}
			if (m.y > 600 && m.x > 300 && m.x < 600) {
				select_win();
				return;
			}
		}
	}
}

