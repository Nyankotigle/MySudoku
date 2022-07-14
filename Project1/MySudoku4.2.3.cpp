#include <stdio.h>
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#define INIT_WIN(X,Y,X_,Y_) initgraph(X, Y);\
HWND hwnd = GetHWnd();\
SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE));\
MoveWindow(hwnd, 340, 10, X_, Y_, TRUE);\
COLOR_1 cleardevice();
//用含参宏定义初始化窗口的语句，X,Y,X_,Y_分别为初始化操作窗口的宽、高，调整后所显示的窗口的宽、高
//"\"+回车将上面多行语句组合为一个逻辑行
//去掉窗口的标题栏只需在SetWindowLong()的最后一个参数后添加"- WS_CAPTION"

#define COLOR_1 setfillcolor(WHITE);setbkcolor(WHITE);settextcolor(BLACK);//
#define COLOR_11 setfillcolor(RGB(250, 80, 0));setbkcolor(RGB(250, 80, 0));settextcolor(BLACK);
#define COLOR_12 setfillcolor(BLACK);setbkcolor(BLACK);settextcolor(RGB(250, 80, 0));
#define COLOR_2 setfillcolor(RGB(250, 250, 30));setbkcolor(RGB(250, 250, 30));settextcolor(BLACK);//黄填充黄背景黑字
#define COLOR_3 setfillcolor(RGB(100, 250, 100));setbkcolor(RGB(100, 250, 100));settextcolor(BLACK);//选择界面按钮按下颜色
#define COLOR_4 setfillcolor(RGB(10, 150, 50));setbkcolor(RGB(10, 150, 50));settextcolor(WHITE);//数字菜单栏
#define COLOR_5 setfillcolor(RGB(10, 150, 50));setbkcolor(RGB(10, 150, 50));settextcolor(BLACK);//点击时数字菜单栏
#define COLOR_7 setfillcolor(RGB(200, 250, 200));setbkcolor(RGB(200, 250, 200));settextcolor(BLACK);//初始数
#define COLOR_8 setfillcolor(RGB(250, 100, 20));setbkcolor(RGB(250, 100, 20));settextcolor(BLACK);//菜单红  
#define COLOR_9 setfillcolor(RGB(0, 250, 250)); setbkcolor(RGB(0, 250, 250));settextcolor(BLACK);//相同数字高亮
#define COLOR_10 setfillcolor(RGB(0, 250, 150)); setbkcolor(RGB(0, 250, 150));settextcolor(BLACK);//检查区域高亮
#define TEXT_STYLE_1 settextstyle(50, 30, _T("微软雅黑"), 0, 0, FW_DONTCARE, false, false, false);
#define TEXT_STYLE_2 settextstyle(50, 20, _T("华文中宋"), 0, 0, FW_DONTCARE, false, false, false);
#define TEXT_STYLE_3 settextstyle(50, 20, _T("华文中宋"), 2700, 0, FW_DONTCARE, false, false, false);
#define TEXT_STYLE_4 settextstyle(60, 25, _T("华文中宋"), 2700, 0, FW_DONTCARE, false, false, false);
#define SOLIDRECTANGLE_1(X,Y) solidrectangle(Y * 67 + 5, X * 67 + 6, Y * 67 + 57, X * 67 + 57);
#define SOLIDRECTANGLE_2(X,Y) solidrectangle((X / 67) * 67 + 5, (Y / 67) * 67 + 6, (X / 67) * 67 + 57, (Y / 67) * 67 + 57);

int init();
void init_sudoku();
void show();
int solve_win();
int select_win();
void select_from_lib();
char* Int_to_str(int b ,char a[]);
int create_sudoku(int);
int rand_number(int);
void show_time(clock_t,int);
void Show_this_num(int);
void Show_check_area(int,int);
int set_number(int sudoku[9][9], int row, int col);
int check_number(int[9][9], int, int, int);
void print_sudoku(int sudoku[9][9]);
int find_empty(int sudoku[9][9], int startrow, int *row, int *col);

int SUDOKU_ARR[9][9] = { 0 };
int Row, Col;
int SUDOKU_COPY[9][9] = { 0 };
IMAGE img1, img2, img3;
//将IMAGE初始化为局部变量有时会出现图像未保存上的情况，而初始化为全局变量则不会出现这种情况
//推测其原因为：全局变量是静态存储的，存储空间在程序运行之前已经分配好，而局部变量的存储空间是动态划分的
//而IMAGE类型需要的存储空间较大，动态分配可能会出现问题

int main()
{
	int i;
	while (1) {
		init_sudoku();
		i=init();
		if (i == 1) {
			if (solve_win() == 2)print_sudoku(SUDOKU_ARR);
		}
		else if (i == 2) {
			if (create_sudoku(select_win()) == 1)print_sudoku(SUDOKU_ARR);
		}
	}
	_getch();
	return 0;
}

int init() {//初始界面
	INIT_WIN(600,600,615,640) //调用宏
	settextstyle(200, 40, _T("微软雅黑"), 0, 0, FW_HEAVY, false, false, false);//加粗
	settextcolor(RGB(250, 80, 0));
	outtextxy(58, 20, "MY");
	COLOR_1
	outtextxy(190, 20, "SUDOKU");
	//开始动画
	getimage(&img1, 65, 40, 125, 150);//MY
	getimage(&img2, 190, 40, 350, 150);//SUDOKU
	for (int m = 600,n=0; m >50; m-=12, n += 4) {
		COLOR_2
		cleardevice();
		putimage(n, 40, &img2, SRCAND);
		putimage(m, 40, &img1, SRCAND);
		Sleep(5);
	}
	COLOR_11
	solidrectangle(60, 180, 70, 600); 
	Sleep(50);
	solidrectangle(114, 180, 126, 584); solidrectangle(114, 570, 600, 584);
	settextstyle(14, 6, _T("华文中宋"), 0, 0, FW_DONTCARE, false, false, false);//文字笔画粗细置为默认
	outtextxy(180, 570, "版权所有：1204219458@qq.com |版本:4.2.3 |2020.03.01 "); 
	Sleep(50);
	solidrectangle(153, 180, 165, 310); solidrectangle(153, 303, 300, 317);
	solidroundrect(200, 260, 400, 360, 100, 100); TEXT_STYLE_2 outtextxy(258, 285, "求解");
	Sleep(50);
	COLOR_12
	solidrectangle(510, 0, 522, 65);solidrectangle(474, 0, 486, 65); 
	Sleep(50); 
	solidrectangle(269, 0, 281, 65);solidrectangle(233, 0, 245, 65);
	Sleep(50);
	solidrectangle(421, 0, 433, 460); solidrectangle(300, 453, 433, 467);
	solidroundrect(200, 410, 400, 510, 100, 100); TEXT_STYLE_2 outtextxy(258, 435, "挑战");

	MOUSEMSG m;		// 定义鼠标消息
	while (true)
	{// 获取一条鼠标消息
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {//左键按下消息
			if (m.x >= 200 && m.x <= 400 && m.y >= 260 && m.y <= 360) {
				COLOR_11
				solidroundrect(200, 260, 400, 360, 100, 100);
				outtextxy(258, 285, "稍等");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();
					if (m_0.uMsg == WM_LBUTTONUP) {//左键弹起消息
						closegraph();
						return 1;
					}
				}
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 410 && m.y <= 510) {
				COLOR_12
				solidroundrect(200, 410, 400, 510, 100, 100);
				outtextxy(258, 435, "稍等");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();
					if (m_0.uMsg == WM_LBUTTONUP) {//左键弹起消息
						//closegraph();//select_win()要继续使用窗口
						return 2;
					}
				}
			}
		}
	}
}

void init_sudoku() {
	for (int v = 0; v < 9; v++) {
		for (int w = 0; w < 9; w++) {
			SUDOKU_ARR[v][w] = 0;
			SUDOKU_COPY[v][w] = 0;
		}
	}
	return;
}

void show() {//宫格基础界面
	INIT_WIN(740, 600, 755, 643)
	COLOR_4//右边数字栏
	solidrectangle(600, 0, 667, 600);
	TEXT_STYLE_1
	for (int j = 0; j < 9; j++) {
		outtextxy(9 * 67 + 10, j * 67 + 6, j + 49);
	}
	COLOR_2 solidrectangle(667, 0, 740, 600);
	setlinecolor(BLACK);setlinestyle(PS_SOLID, 5, NULL, 0);
	line(0, 2, 740, 2);    //横线
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(0, 600, 740, 600);
	line(1, 0, 1, 600);    //竖线
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
	line(600, 0, 600, 600);
	line(737, 0, 737, 600);
	line(667, 0, 667, 600);
	setlinestyle(PS_SOLID, 2, NULL, 0);//细格线
	for (int i = 67; i < 600; i += 67) {
		line(0, i, 667, i);
		line(i, 0, i, 600);
	}
	return;
}

int solve_win() {//求解
	show();
	COLOR_2
	TEXT_STYLE_4
	outtextxy(702, 143, "提交求解");
	TEXT_STYLE_1
	int ch;
	MOUSEMSG m;		// 定义鼠标消息
	while (true)
	{// 获取一条鼠标消息
		FlushMouseMsgBuffer();//清空鼠标缓冲区
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {//左键按下消息
			if (m.x > 667) {//确认提交
				memmove(SUDOKU_COPY, SUDOKU_ARR, 81 * sizeof(int));//备份输入
				find_empty(SUDOKU_ARR, 0, &Row, &Col);
				if (set_number(SUDOKU_ARR, Row, Col) == 0) {//如果无解
					//提示输入无解
					COLOR_8
					TEXT_STYLE_4
					solidrectangle(670, 5, 734, 597);
					outtextxy(702, 143, "输入无解");
					TEXT_STYLE_1
					Sleep(1000);
					init_sudoku();//清空当前输入
					closegraph();
					return 1;
				}
				//输入有解
				closegraph();
				return 2;
			}
			else if(m.x<600)
			{	//当前点击方格高亮
				COLOR_2
				SOLIDRECTANGLE_2(m.x,m.y)
				while (1) {
					MOUSEMSG m_1;//点击数字栏输入数字
					m_1 = GetMouseMsg();
					if (m_1.uMsg == WM_LBUTTONDOWN) {//左键按下消息
						if (m_1.x < 667 && m_1.x >600) {//点击数字栏，相应数字由白变黑，并且向下移动4，鼠标弹起后恢复
							COLOR_5 outtextxy(9 * 67 + 10, (m_1.y / 67) * 67 + 10, m_1.y / 67 + 49);
							while (1) {
								MOUSEMSG m_0 = GetMouseMsg();// 获取一条鼠标消息
								if (m_0.uMsg == WM_LBUTTONUP) {//左键弹起
									COLOR_4 outtextxy(9 * 67 + 10, (m_1.y / 67) * 67 + 6, m_1.y / 67 + 49);
									break;
								}
							}
							SUDOKU_ARR[m.y / 67][m.x / 67] = 0;//有新的数字输入，清空此格
							ch = m_1.y / 67 + 49;
							break;
						}//如果不是点击数字栏而是再次点击此格
						if (((m_1.x / 67) == (m.x / 67)) && ((m_1.y / 67) == (m.y / 67))) {
							ch = 27;
							break;
						}
					}
				}
				if (ch == 27) {//再次点击此格即取消当前输入锁定，恢复点击之前的空格或者数字
					if (SUDOKU_ARR[m.y / 67][m.x / 67] == 0) {//之前点击的格子没有填数
						COLOR_1
						SOLIDRECTANGLE_2(m.x, m.y)
					}//重新恢复空格
					if (SUDOKU_ARR[m.y / 67][m.x / 67] != 0) {//之前点击的格子已经填数
						COLOR_2
						outtextxy((m.x / 67) * 67 + 10, (m.y / 67) * 67 + 6, SUDOKU_ARR[m.y / 67][m.x / 67] + 48);
					}//重新恢复数字
				}
				else if (check_number(SUDOKU_ARR, ch - 48, m.y / 67, m.x / 67)) //有数字输入并且可以填入
				{
					SUDOKU_ARR[m.y / 67][m.x / 67] = ch - 48;//将ch的ASCII码值转换为相应的整数
					COLOR_2 outtextxy((m.x / 67) * 67 + 10, (m.y / 67) * 67 + 6, ch);
				}
				else {//闪烁提示不可填入
					COLOR_8  SOLIDRECTANGLE_2(m.x, m.y) Sleep(100);
					COLOR_1  SOLIDRECTANGLE_2(m.x, m.y) Sleep(100);
					COLOR_8  SOLIDRECTANGLE_2(m.x, m.y) Sleep(100);
					COLOR_1  SOLIDRECTANGLE_2(m.x, m.y)
				}
			}
		}
	}
}

int select_win() {//选择难度
	COLOR_2
	cleardevice();
	TEXT_STYLE_2
	COLOR_11
	solidrectangle(150, 0, 160, 120); solidrectangle(150, 115, 300, 125);
	solidroundrect(200, 80, 400, 160, 100, 100); outtextxy(258, 95, "菜鸟");
	Sleep(50);
	solidrectangle(100, 0, 110, 240); solidrectangle(100, 235, 300, 245);
	solidroundrect(200, 200, 400, 280, 100, 100); outtextxy(258, 215, "专家");
	Sleep(50);
	solidrectangle(50, 0, 60, 360); solidrectangle(50, 355, 300, 365);
	solidroundrect(200, 320, 400, 400, 100, 100); outtextxy(258, 335, "大师");
	Sleep(50);
	COLOR_12
	solidrectangle(500, 0, 510, 480); solidrectangle(300, 475, 510, 485);
	solidroundrect(200, 440, 400, 520, 100, 100); outtextxy(240, 455, "数独库");
	MOUSEMSG m;		// 定义鼠标消息
	while (true)
	{// 获取一条鼠标消息
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {//左键按下消息
			if (m.x >= 200 && m.x <= 400 && m.y >= 80 && m.y <=160) {
				COLOR_11 solidroundrect(200, 80, 400, 160, 100, 100);
				outtextxy(258, 95, "稍等");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();
					if (m_0.uMsg == WM_LBUTTONUP)return 40;
				}
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 200 && m.y <= 280) {
				COLOR_11 solidroundrect(200, 200, 400, 280, 100, 100);
				outtextxy(258, 215, "稍等");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();
					if (m_0.uMsg == WM_LBUTTONUP)return 30;
				}
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 320 && m.y <= 400) {
				COLOR_11 solidroundrect(200, 320, 400, 400, 100, 100);
				outtextxy(258, 335, "稍等");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();
					if (m_0.uMsg == WM_LBUTTONUP)return 20;
				}
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 440 && m.y <= 520) {
				COLOR_12 solidroundrect(200, 440, 400, 520, 100, 100);
				outtextxy(258, 455, "稍等");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();
					if (m_0.uMsg == WM_LBUTTONUP) { select_from_lib(); return 0; }
				}
			}
		}
	}
}

void select_from_lib() {//选择数独库中存储的数独
	COLOR_2
	cleardevice();
	char sudoku_num_str[5];
	int sudoku_sum, num;
	FILE * SUDOKU_LIB;
	errno_t err;
	err = fopen_s(&SUDOKU_LIB, "MySudoku数独库.txt", "a+"); 
	//这里如果用只读模式"r"打开文件，则文件不存在时会出错；如果用写模式"a"打开文件，则可以避免文件不存在时出错，但无法正常读取文件
	//只能用更新模式"a+"，可以在文件尾写，可以读整个文件，文件不存在时可以创建新文件
	if (err == 0) {//文件打开成功
		fseek(SUDOKU_LIB, 0L, SEEK_END);//查找到文件尾
		long byte_number = ftell(SUDOKU_LIB);//计算从文件头到文件尾共有多少个字节
		sudoku_sum = byte_number / 83;//已保存的数独总个数，每个数独占用83个字节
		num = sudoku_sum;//num初始为最大序号
	}
	else {outtextxy(200, 250, "打开失败"); Sleep(1000); return;}
	if (num == 0) {outtextxy(200, 250, "文件为空"); fclose(SUDOKU_LIB); Sleep(1000); return;}
	TEXT_STYLE_4 outtextxy(560, 193, "确 定");
	COLOR_12 solidcircle(0, 300, 450);
	COLOR_11 solidcircle(0, 300, 300);
	COLOR_12 solidcircle(50,300,50);
	POINT pts1[] = { {73, 255}, {73, 345}, {280, 300} }; solidpolygon(pts1, 3);//黑色三角箭头
	COLOR_2 solidcircle(50, 300, 5);
	while (1)
	{
		COLOR_12 TEXT_STYLE_2
		outtextxy(328, 275, Int_to_str(num , sudoku_num_str));//最中间待选中的数独序号
		settextcolor(RGB(250, 250, 30));//上下各显示5个大小连续的序号
		if (num > 5)outtextxy(225, 25, Int_to_str(num - 5, sudoku_num_str));
		else solidrectangle(225, 25, 325, 75);
		if (num > 4)outtextxy(265, 75, Int_to_str(num - 4, sudoku_num_str));
		else solidrectangle(265, 75, 365, 125);
		if (num > 3)outtextxy(295, 125, Int_to_str(num - 3, sudoku_num_str));
		else solidrectangle(295, 125, 395, 175);
		if (num > 2)outtextxy(313, 175, Int_to_str(num - 2, sudoku_num_str));
		else solidrectangle(313, 175, 413, 225);
		if (num > 1)outtextxy(325, 225, Int_to_str(num - 1, sudoku_num_str));
		else solidrectangle(325, 225, 425, 275);
		if (num < (sudoku_sum))outtextxy(325, 325, Int_to_str(num + 1, sudoku_num_str));
		else solidrectangle(325, 325, 425, 375);
		if (num < (sudoku_sum-1))outtextxy(313, 375, Int_to_str(num + 2, sudoku_num_str));
		else solidrectangle(313, 375, 413, 425);
		if (num < (sudoku_sum-2))outtextxy(295, 425, Int_to_str(num + 3, sudoku_num_str));
		else solidrectangle(295, 425, 395, 475);
		if (num < (sudoku_sum-3))outtextxy(265, 475, Int_to_str(num + 4, sudoku_num_str));
		else solidrectangle(265, 475, 365, 525);
		if (num < (sudoku_sum - 4))outtextxy(225, 525, Int_to_str(num + 5, sudoku_num_str));
		else solidrectangle(225, 525, 325, 575);
		MOUSEMSG m_4 = GetMouseMsg();
		if (m_4.uMsg == WM_MOUSEWHEEL) {//滚轮滚动消息
			if (m_4.wheel > 0 && num < sudoku_sum)num++;//向上滚动增大
			if (m_4.wheel < 0 && num > 1)num--;//向下滚动序号减小
		}
		if (m_4.uMsg == WM_LBUTTONDOWN) {//单击选中
			fseek(SUDOKU_LIB, long((num-1)*83) , SEEK_SET);//查找到要读取的数独的首字节位置
			for (int i = 0; i < 81; i++) {//将要读取的数独读入数组中
				SUDOKU_ARR[i/9][i%9] = getc(SUDOKU_LIB) - 48;
			}
			fclose(SUDOKU_LIB);//关闭文件
			break;
		}
	}
	return;
}

char* Int_to_str(int b, char a[]) {//将整数转换为字符串，只显示四位数
	a[0] = (b / 1000) % 10 + 48;
	a[1] = (b / 100) % 10 + 48;
	a[2] = (b / 10) % 10 + 48;
	a[3] =  b % 10 + 48;
	a[4] = '\0';
	return a;
}

int create_sudoku(int rank) {
	if (rank != 0) {//不使用数独库
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
		if (set_number(SUDOKU_ARR, Row, Col) == 0) {//如果无解
			for (int v = 0; v < 9; v++) {//清空
				for (int w = 0; w < 9; w++) { SUDOKU_ARR[v][w] = 0; }
			}
			goto createsudoku;//重新生成
		}
		else //如果有解
		{
			for (int i, j, k, count = 0; count < 81 - rank;) {//数独至少17个数才有唯一解
				i = rand_number(1); //Sleep(1);
				j = rand_number(2); //Sleep(3);
				k = rand_number(3); //Sleep(5);
				if (SUDOKU_ARR[i][j] != 0) {
					SUDOKU_ARR[i][j] = 0;
					count++;
				}
			}
		}
	}
	memmove(SUDOKU_COPY, SUDOKU_ARR, 81 * sizeof(int));//备份生成的初始数独
	closegraph();

CLEAN_INPUT://清空所有操作，重新开始
	show();			
	COLOR_7
	TEXT_STYLE_1
	for (int v = 0; v < 9; v++) {//显示生成的初始数独
		for (int w = 0; w < 9; w++) {
			if (SUDOKU_COPY[v][w] != 0) {
				SOLIDRECTANGLE_1(v,w)//初始数标为绿色
				outtextxy(w * 67 + 10, v * 67 + 6, SUDOKU_COPY[v][w] + 48); //将整数转换为相应的ASCII码值
			}
		}
	}
	COLOR_2
	setlinestyle(PS_SOLID, 5, NULL, 0);//右侧菜单栏格线
	line(667, 120, 740, 120);
	line(667, 240, 740, 240);
	line(667, 360, 740, 360);
	line(667, 480, 740, 480);
	TEXT_STYLE_3
	outtextxy(702, -25, "撤销");
	outtextxy(702, 95, "恢复");
	outtextxy(702, 335, "标记");
	outtextxy(702, 455, "重置");
	TEXT_STYLE_1
	clock_t  start = clock();//计时
	int count = 0;//记录填数个数
	int count_max = 0;//记录当前已填最大个数
	int Track[81][3] = { 0 };//记录填入轨迹
	int ch;
	MOUSEMSG m;		// 定义鼠标消息
	while (true)
	{
		COLOR_2 show_time(start, 243);
		FlushMouseMsgBuffer();//清空鼠标缓冲区
		m = GetMouseMsg();// 获取一条鼠标消息
		if (m.uMsg == WM_LBUTTONDOWN) {//左键按下消息
			if (m.x > 667 && m.y > 0 && m.y < 120) {//撤销
				COLOR_8
				TEXT_STYLE_3
				solidrectangle(670, 5, 734, 117);
				outtextxy(702, -25, "撤销");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();// 获取一条鼠标消息
					if (m_0.uMsg == WM_LBUTTONUP) {//左键弹起
						COLOR_2
						TEXT_STYLE_3
						solidrectangle(670, 5, 734, 117);
						outtextxy(702, -25, "撤销");
						TEXT_STYLE_1
						break;
					}//按下变红，弹起恢复
				}
				if (count > 0) {
					count--;
					SUDOKU_ARR[Track[count][0]][Track[count][1]] = 0;//
					COLOR_1
					SOLIDRECTANGLE_1(Track[count][0], Track[count][1])
				}
			}
			if (m.x > 667 && m.y > 120 && m.y < 240) {//恢复
				COLOR_8
				TEXT_STYLE_3
				solidrectangle(670, 123, 734, 237); outtextxy(702, 95, "恢复");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();// 获取一条鼠标消息
					if (m_0.uMsg == WM_LBUTTONUP) {//左键弹起
						COLOR_2
						TEXT_STYLE_3
						solidrectangle(670, 123, 734, 237); outtextxy(702, 95, "恢复");
						TEXT_STYLE_1
						break;
					}//按下变红，弹起恢复
				}
				if (count < count_max) {
					SUDOKU_ARR[Track[count][0]][Track[count][1]] = Track[count][2];//
					COLOR_2
					SOLIDRECTANGLE_1(Track[count][0], Track[count][1])
					outtextxy(Track[count][1] * 67 + 10, Track[count][0] * 67 + 6, Track[count][2]);
					count++;
				}
			}
			if (m.x > 667 && m.y > 240 && m.y < 360) {//点击时间栏
				getimage(&img3, 670, 5, 734, 597);//保存菜单栏方便返回
				COLOR_8
				TEXT_STYLE_4
				solidrectangle(670, 5, 734, 596);
				setlinestyle(PS_SOLID, 5, NULL, 0);
				line(667, 300, 740, 300);
				outtextxy(702, 0, "我要认输");
				outtextxy(702, 290, "继续挑战");
				TEXT_STYLE_1
				while (true)
				{
					MOUSEMSG m_0 = GetMouseMsg();
					if (m_0.uMsg == WM_LBUTTONDOWN) {
						if (m_0.x > 667 && m_0.y > 0 && m_0.y < 300) {//我要认输
							memmove(SUDOKU_ARR, SUDOKU_COPY, 81 * sizeof(int));//重置SUDOKU_ARR
							find_empty(SUDOKU_ARR, 0, &Row, &Col);
							set_number(SUDOKU_ARR, Row, Col);
							closegraph();
							return 1;
						}
						if (m_0.x > 667 && m_0.y > 300 && m_0.y < 600) {//继续挑战
							putimage(670, 5, &img3, SRCCOPY);
							break;
						}
					}
				}
			}
			
			if (m.x < 600 )//点击宫格部分
			{	
				if (SUDOKU_COPY[m.y / 67][m.x / 67] != 0) {//点击的是初始值
					Show_this_num(SUDOKU_ARR[m.y / 67][m.x / 67]);//高亮显示相同值
				}
				if (SUDOKU_COPY[m.y / 67][m.x / 67] == 0) {//点击的不是初始值
					if (SUDOKU_ARR[m.y / 67][m.x / 67] != 0) {//点击的不是空格
						Show_this_num(SUDOKU_ARR[m.y / 67][m.x / 67]);//高亮显示相同值
					}
					if (SUDOKU_ARR[m.y / 67][m.x / 67] == 0) {//点击的是空格
						Show_check_area(m.x,m.y);//高亮显示当前位置的所有冲突检查区域
					}
					//当前点击方格高亮
					COLOR_2
					SOLIDRECTANGLE_2(m.x, m.y)
					while (1) {
						MOUSEMSG m_1;//点击数字栏输入数字
						m_1 = GetMouseMsg();
						if (m_1.uMsg == WM_LBUTTONDOWN) {//左键按下消息
							if (m_1.x < 667 && m_1.x >600) {//点击数字栏，相应数字由白变黑，并且向下移动4，鼠标弹起后恢复
								COLOR_5 outtextxy(9 * 67 + 10, (m_1.y / 67) * 67 + 10, m_1.y / 67 + 49);
								while (1) {
									MOUSEMSG m_0 = GetMouseMsg();// 获取一条鼠标消息
									if (m_0.uMsg == WM_LBUTTONUP) {//左键弹起
										COLOR_4 outtextxy(9 * 67 + 10, (m_1.y / 67) * 67 + 6, m_1.y / 67 + 49);
										break;
									}
								}
								SUDOKU_ARR[m.y / 67][m.x / 67] = 0;//有新的数字输入，清空此格
								ch = m_1.y / 67 + 49;
								break;
							}
							if (((m_1.x /67)==(m.x/ 67)) && ((m_1.y / 67) == (m.y / 67))) {//再次点击此格
								ch = 27;
								break;
							}
							if (m_1.x > 667 && m_1.y > 360 && m_1.y < 480) {//如果点击标记
								SUDOKU_ARR[m.y / 67][m.x / 67] = 0;//清空此格
								ch = 13;
								break;
							}
						}
					}
					if (ch==27) {//再次点击此格（或者键盘模式单击Esc）即取消当前输入锁定
						if (SUDOKU_ARR[m.y / 67][m.x / 67] == 0) {//之前点击的格子没有填数
							COLOR_1
							SOLIDRECTANGLE_2(m.x, m.y)
						}//重新恢复空格
						if (SUDOKU_ARR[m.y / 67][m.x / 67] != 0 && SUDOKU_COPY[m.y / 67][m.x / 67] == 0) {//之前点击的为非初始数
							COLOR_2
							outtextxy((m.x / 67) * 67 + 10, (m.y / 67) * 67 + 6, SUDOKU_ARR[m.y / 67][m.x / 67] + 48);
						}//重新恢复数字
					}
					else if (ch==13) //标记
					{
						COLOR_8
						TEXT_STYLE_3
						solidrectangle(670, 363, 734, 477);
						outtextxy(702, 335, "标记");
						TEXT_STYLE_1
						
						if (SUDOKU_COPY[m.y / 67][m.x / 67] == 0) {//初始数无法标记
							SOLIDRECTANGLE_2(m.x, m.y)
							TEXT_STYLE_3
							solidrectangle(670, 363, 734, 477);
							outtextxy(702, 335, "右键");
							TEXT_STYLE_1
							while (1) {
								MOUSEMSG m_2;//点击数字栏输入数字
								m_2 = GetMouseMsg();
								if (m_2.uMsg == WM_LBUTTONDOWN) {//左键按下消息
									if (m_2.x < 667 && m_2.x >600) {//点击数字栏，相应数字由白变黑，并且向下移动4，鼠标弹起后恢复
										TEXT_STYLE_1
										COLOR_5 outtextxy(9 * 67 + 10, (m_2.y / 67) * 67 + 10, m_2.y / 67 + 49);
										while (1) {
											MOUSEMSG m_0 = GetMouseMsg();// 获取一条鼠标消息
											if (m_0.uMsg == WM_LBUTTONUP) {//左键弹起
												COLOR_4 outtextxy(9 * 67 + 10, (m_2.y / 67) * 67 + 6, m_2.y / 67 + 49);
												break;
											}
										}
										COLOR_8
										settextstyle(18, 10, _T("微软雅黑"));
										outtextxy((m.x / 67) * 67 + (m_2.y / 67 % 3) * 15 + 10, (m.y / 67) * 67 + (m_2.y / 67 / 3) * 15 + 10, m_2.y / 67 + 49);
									}
								}
								if (m_2.uMsg == WM_RBUTTONDOWN) {//单击右键完成标记
									COLOR_2 TEXT_STYLE_3
									solidrectangle(670, 363, 734, 477);
									outtextxy(702, 335, "标记");
									TEXT_STYLE_1
									break;
								}
							}
						}
					}
					else if (check_number(SUDOKU_ARR, ch - 48, m.y / 67, m.x / 67)) {//如果可以填入
						SUDOKU_ARR[m.y / 67][m.x / 67] = ch - 48;//将ch的ASCII码值转换为相应的整数填入数组
						COLOR_2
						outtextxy((m.x / 67) * 67 + 10, (m.y / 67) * 67 + 6, ch);
						Track[count][0] = m.y / 67;
						Track[count][1] = m.x / 67;
						Track[count][2] = ch;
						count++;
						count_max = count;//更新count_max
						if ((count + rank) == 81) {//已填+初始=81，填充完毕，显示成功
							COLOR_8
							TEXT_STYLE_4
							solidrectangle(670, 5, 734, 596);
							outtextxy(702, 8, "挑战成功");
							outtextxy(702, 273, "用时");
							TEXT_STYLE_1
							show_time(start, 428);
							while (true)//点击回到初始界面
							{
								m = GetMouseMsg();
								if (m.uMsg == WM_LBUTTONDOWN) {
									closegraph();
									return 0;
								}
							}
						}
					}
					else {//闪烁提示不可填入
						COLOR_8  SOLIDRECTANGLE_2(m.x, m.y) Sleep(100);
						COLOR_1  SOLIDRECTANGLE_2(m.x, m.y) Sleep(100);
						COLOR_8  SOLIDRECTANGLE_2(m.x, m.y) Sleep(100);
						COLOR_1  SOLIDRECTANGLE_2(m.x, m.y)
					}
				}
			}
			if (m.x > 667 && m.y > 480 && m.y < 600) {//重置
				COLOR_8
				TEXT_STYLE_3
				solidrectangle(670, 483, 734, 597); outtextxy(702, 455, "重置");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();// 获取一条鼠标消息
					if (m_0.uMsg == WM_LBUTTONUP) {//左键弹起
						COLOR_2
						TEXT_STYLE_3
						solidrectangle(670, 483, 734, 597); outtextxy(702, 455, "重置");
						TEXT_STYLE_1
						break;
					}//按下变红，弹起恢复
				}
				memmove(SUDOKU_ARR,SUDOKU_COPY,81*sizeof(int));//将SUDOKU_COPY拷贝给SUDOKU_ARR即初始化SUDOKU_ARR
				closegraph();
				goto CLEAN_INPUT;
			}
		}
	}
	return 0;
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

void show_time(clock_t start,int h) {//将整数秒转换为时间字符串
	clock_t  now = clock();
	int sec = (int)((now - start) / CLK_TCK);
	char time_str[9] = { 0 };//存储时间字符串
	time_str[0] = (sec / 3600) / 10 + 48;
	time_str[1] = (sec / 3600) % 10 + 48;
	time_str[2] = ':';
	time_str[3] = ((sec % 3600) / 60) / 10 + 48;
	time_str[4] = ((sec % 3600) / 60) % 10 + 48;
	time_str[5] = ':';
	time_str[6] = ((sec % 3600) % 60) / 10 + 48;
	time_str[7] = ((sec % 3600) % 60) % 10 + 48;
	settextstyle(35, 11, _T("华文中宋"));
	outtextxy(676, h, time_str[0]);
	outtextxy(692, h, time_str[1]);
	outtextxy(707, h, "时");
	outtextxy(676, h + 40, time_str[3]);
	outtextxy(692, h + 40, time_str[4]);
	outtextxy(707, h + 40, "分");
	outtextxy(676, h + 80, time_str[6]);
	outtextxy(692, h + 80, time_str[7]);
	outtextxy(707, h + 80, "秒");
	TEXT_STYLE_1
	return;
}

void Show_this_num(int num) {//高亮显示所有相同数字
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (SUDOKU_ARR[i][j] == num ) {
				COLOR_9  SOLIDRECTANGLE_1(i,j)
				outtextxy(j * 67 + 10, i * 67 + 8, num+48);//数字位置向下移动2，形成动态效果
			}
		}
	}
	while (1) {
		MOUSEMSG m_0 = GetMouseMsg();// 获取一条鼠标消息
		if (m_0.uMsg == WM_LBUTTONUP) {//左键弹起
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (SUDOKU_ARR[i][j] == num && SUDOKU_COPY[i][j] != 0) {//初始数
						COLOR_7  SOLIDRECTANGLE_1(i, j)
						outtextxy(j * 67 + 10, i * 67 + 6, num + 48);
					}
					if (SUDOKU_ARR[i][j] == num && SUDOKU_COPY[i][j] == 0) {//非初始数
						COLOR_2  SOLIDRECTANGLE_1(i, j)
						outtextxy(j * 67 + 10, i * 67 + 6, num + 48);
					}
				}
			}
			break;
		}
	}
	return;
}

void Show_check_area(int x, int y) {//显示所有检查区域的数字
	int row = y / 67, col = x / 67;
	int i, j;
	int x_ = (row / 3) * 3;
	int y_ = (col / 3) * 3;//x,y为当前位置所在小九宫格左上角坐标
	for (j = 0; j < 9; j++) {//同行高亮
		if (SUDOKU_ARR[row][j] != 0) {
			COLOR_10  SOLIDRECTANGLE_1(row, j)
				outtextxy(j * 67 + 10, row * 67 + 8, SUDOKU_ARR[row][j] + 48);
		}
	}
	for (i = 0; i < 9; i++) {//同列高亮
		if (SUDOKU_ARR[i][col] != 0) {
			COLOR_10  SOLIDRECTANGLE_1(i, col)
				outtextxy(col * 67 + 10, i * 67 + 8, SUDOKU_ARR[i][col] + 48);
		}
	}
	for (i = x_; i < x_ + 3; i++) {//同宫高亮
		for (j = y_; j < y_ + 3; j++) {
			if (SUDOKU_ARR[i][j] != 0) {
				COLOR_10  SOLIDRECTANGLE_1(i, j)
					outtextxy(j * 67 + 10, i * 67 + 8, SUDOKU_ARR[i][j] + 48);
			}
		}
	}
	while (1) {
		MOUSEMSG m_0 = GetMouseMsg();// 获取一条鼠标消息
		if (m_0.uMsg == WM_LBUTTONUP) {//左键弹起
			for (j = 0; j < 9; j++) {//同行恢复
				if (SUDOKU_COPY[row][j] != 0) {//初始数
					COLOR_7  SOLIDRECTANGLE_1(row, j)
					outtextxy(j * 67 + 10, row * 67 + 6, SUDOKU_ARR[row][j] + 48);
				}
				if (SUDOKU_ARR[row][j] != 0 && SUDOKU_COPY[row][j] == 0) {//非初始数
					COLOR_2  SOLIDRECTANGLE_1(row, j)
					outtextxy(j * 67 + 10, row * 67 + 6, SUDOKU_ARR[row][j] + 48);
				}
			}
			for (i = 0; i < 9; i++) {//同列恢复
				if (SUDOKU_COPY[i][col] != 0) {//初始数
					COLOR_7  SOLIDRECTANGLE_1(i, col)
					outtextxy(col * 67 + 10, i * 67 + 6, SUDOKU_ARR[i][col] + 48);
				}
				if (SUDOKU_ARR[i][col] != 0 && SUDOKU_COPY[i][col] == 0) {//非初始数
					COLOR_2  SOLIDRECTANGLE_1(i, col)
						outtextxy(col * 67 + 10, i * 67 + 6, SUDOKU_ARR[i][col] + 48);
				}
			}
			for (i = x_; i < x_ + 3; i++) {//同宫恢复
				for (j = y_; j < y_ + 3; j++) {
					if (SUDOKU_COPY[i][j] != 0) {//初始数
						COLOR_7  SOLIDRECTANGLE_1(i, j)
						outtextxy(j * 67 + 10, i * 67 + 6, SUDOKU_ARR[i][j] + 48);
					}
					if (SUDOKU_ARR[i][j] != 0 && SUDOKU_COPY[i][j] == 0) {//非初始数
						COLOR_2  SOLIDRECTANGLE_1(i, j)
							outtextxy(j * 67 + 10, i * 67 + 6, SUDOKU_ARR[i][j] + 48);
					}
				}
			}
			break;
		}
	}
	return;
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

void print_sudoku(int sudoku[9][9]) {//输出解int v, w;
	show();
	TEXT_STYLE_1
	for (int v = 0; v < 9; v++) {
		for (int w = 0; w < 9; w++) {
			COLOR_1
			if (SUDOKU_COPY[v][w] != 0) {
				COLOR_7  SOLIDRECTANGLE_1(v,w) //初始数标为绿色
			}
			outtextxy(w * 67 + 10, v * 67 + 5, sudoku[v][w] + 48); //将整数转换为相应的ASCII码值
		}
	}
	COLOR_2
	TEXT_STYLE_4
	setlinestyle(PS_SOLID, 5, NULL, 0);
	line(667, 300, 740, 300);
	outtextxy(702, 0, "返回菜单");
	outtextxy(702, 290, "存储数独");
	TEXT_STYLE_1
	while (true)
	{
		MOUSEMSG m_0 = GetMouseMsg();
		if (m_0.uMsg == WM_LBUTTONDOWN) {
			if (m_0.x > 667 && m_0.y > 0 && m_0.y < 300) {//继续开始
				closegraph();
				return;
			}
			if (m_0.x > 667 && m_0.y > 300 && m_0.y < 600) {//存储数独
				char sudoku_copy_str[83];
				for (int v = 0; v < 9; v++) {
					for (int w = 0; w < 9; w++) {
						sudoku_copy_str[v*9+w] = SUDOKU_COPY[v][w]+48;
					}
				}//将初始数独存放在字符数组里，并以回车结尾
				sudoku_copy_str[81] = '\n';
				sudoku_copy_str[82] = '\0';
				FILE * SUDOKU_LIB;
				errno_t err;
				err=fopen_s(&SUDOKU_LIB,"MySudoku数独库.txt", "a"); //在当前文件尾写
				COLOR_2 TEXT_STYLE_4 solidrectangle(670, 5, 734, 597);
				if (err == 0) {//文件打开成功
					fputs(sudoku_copy_str, SUDOKU_LIB);//将字符数组写入文件尾
					fseek(SUDOKU_LIB, 0L, SEEK_END);//查找到文件尾
					long byte_number = ftell(SUDOKU_LIB);//计算从文件头到文件尾共有多少个字节
					int sudoku_sum = byte_number / 83;//已保存的数独个数，每个数独占用83个字节
					char sudoku_sum_str[21]= "已保存为第0000项";
					sudoku_sum_str[13] = sudoku_sum % 10+48;
					sudoku_sum_str[12] = (sudoku_sum / 10) % 10 + 48;
					sudoku_sum_str[11] = (sudoku_sum / 100) % 10 + 48;
					sudoku_sum_str[10] = (sudoku_sum / 1000) % 10 + 48;
					outtextxy(702, 0, sudoku_sum_str);//显示数独个数
				}
				else outtextxy(702, 143, "保存失败");
				fclose(SUDOKU_LIB);//关闭文件
				while (1)//单击退出
				{
					MOUSEMSG m_4 = GetMouseMsg();
					if (m_4.uMsg == WM_LBUTTONDOWN) {
						closegraph();
						return;
					}
				}
			}
		}
	}
}

