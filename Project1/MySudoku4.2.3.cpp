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
//�ú��κ궨���ʼ�����ڵ���䣬X,Y,X_,Y_�ֱ�Ϊ��ʼ���������ڵĿ��ߣ�����������ʾ�Ĵ��ڵĿ���
//"\"+�س����������������Ϊһ���߼���
//ȥ�����ڵı�����ֻ����SetWindowLong()�����һ�����������"- WS_CAPTION"

#define COLOR_1 setfillcolor(WHITE);setbkcolor(WHITE);settextcolor(BLACK);//
#define COLOR_11 setfillcolor(RGB(250, 80, 0));setbkcolor(RGB(250, 80, 0));settextcolor(BLACK);
#define COLOR_12 setfillcolor(BLACK);setbkcolor(BLACK);settextcolor(RGB(250, 80, 0));
#define COLOR_2 setfillcolor(RGB(250, 250, 30));setbkcolor(RGB(250, 250, 30));settextcolor(BLACK);//�����Ʊ�������
#define COLOR_3 setfillcolor(RGB(100, 250, 100));setbkcolor(RGB(100, 250, 100));settextcolor(BLACK);//ѡ����水ť������ɫ
#define COLOR_4 setfillcolor(RGB(10, 150, 50));setbkcolor(RGB(10, 150, 50));settextcolor(WHITE);//���ֲ˵���
#define COLOR_5 setfillcolor(RGB(10, 150, 50));setbkcolor(RGB(10, 150, 50));settextcolor(BLACK);//���ʱ���ֲ˵���
#define COLOR_7 setfillcolor(RGB(200, 250, 200));setbkcolor(RGB(200, 250, 200));settextcolor(BLACK);//��ʼ��
#define COLOR_8 setfillcolor(RGB(250, 100, 20));setbkcolor(RGB(250, 100, 20));settextcolor(BLACK);//�˵���  
#define COLOR_9 setfillcolor(RGB(0, 250, 250)); setbkcolor(RGB(0, 250, 250));settextcolor(BLACK);//��ͬ���ָ���
#define COLOR_10 setfillcolor(RGB(0, 250, 150)); setbkcolor(RGB(0, 250, 150));settextcolor(BLACK);//����������
#define TEXT_STYLE_1 settextstyle(50, 30, _T("΢���ź�"), 0, 0, FW_DONTCARE, false, false, false);
#define TEXT_STYLE_2 settextstyle(50, 20, _T("��������"), 0, 0, FW_DONTCARE, false, false, false);
#define TEXT_STYLE_3 settextstyle(50, 20, _T("��������"), 2700, 0, FW_DONTCARE, false, false, false);
#define TEXT_STYLE_4 settextstyle(60, 25, _T("��������"), 2700, 0, FW_DONTCARE, false, false, false);
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
//��IMAGE��ʼ��Ϊ�ֲ�������ʱ�����ͼ��δ�����ϵ����������ʼ��Ϊȫ�ֱ����򲻻�����������
//�Ʋ���ԭ��Ϊ��ȫ�ֱ����Ǿ�̬�洢�ģ��洢�ռ��ڳ�������֮ǰ�Ѿ�����ã����ֲ������Ĵ洢�ռ��Ƕ�̬���ֵ�
//��IMAGE������Ҫ�Ĵ洢�ռ�ϴ󣬶�̬������ܻ��������

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

int init() {//��ʼ����
	INIT_WIN(600,600,615,640) //���ú�
	settextstyle(200, 40, _T("΢���ź�"), 0, 0, FW_HEAVY, false, false, false);//�Ӵ�
	settextcolor(RGB(250, 80, 0));
	outtextxy(58, 20, "MY");
	COLOR_1
	outtextxy(190, 20, "SUDOKU");
	//��ʼ����
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
	settextstyle(14, 6, _T("��������"), 0, 0, FW_DONTCARE, false, false, false);//���ֱʻ���ϸ��ΪĬ��
	outtextxy(180, 570, "��Ȩ���У�1204219458@qq.com |�汾:4.2.3 |2020.03.01 "); 
	Sleep(50);
	solidrectangle(153, 180, 165, 310); solidrectangle(153, 303, 300, 317);
	solidroundrect(200, 260, 400, 360, 100, 100); TEXT_STYLE_2 outtextxy(258, 285, "���");
	Sleep(50);
	COLOR_12
	solidrectangle(510, 0, 522, 65);solidrectangle(474, 0, 486, 65); 
	Sleep(50); 
	solidrectangle(269, 0, 281, 65);solidrectangle(233, 0, 245, 65);
	Sleep(50);
	solidrectangle(421, 0, 433, 460); solidrectangle(300, 453, 433, 467);
	solidroundrect(200, 410, 400, 510, 100, 100); TEXT_STYLE_2 outtextxy(258, 435, "��ս");

	MOUSEMSG m;		// ���������Ϣ
	while (true)
	{// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {//���������Ϣ
			if (m.x >= 200 && m.x <= 400 && m.y >= 260 && m.y <= 360) {
				COLOR_11
				solidroundrect(200, 260, 400, 360, 100, 100);
				outtextxy(258, 285, "�Ե�");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();
					if (m_0.uMsg == WM_LBUTTONUP) {//���������Ϣ
						closegraph();
						return 1;
					}
				}
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 410 && m.y <= 510) {
				COLOR_12
				solidroundrect(200, 410, 400, 510, 100, 100);
				outtextxy(258, 435, "�Ե�");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();
					if (m_0.uMsg == WM_LBUTTONUP) {//���������Ϣ
						//closegraph();//select_win()Ҫ����ʹ�ô���
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

void show() {//�����������
	INIT_WIN(740, 600, 755, 643)
	COLOR_4//�ұ�������
	solidrectangle(600, 0, 667, 600);
	TEXT_STYLE_1
	for (int j = 0; j < 9; j++) {
		outtextxy(9 * 67 + 10, j * 67 + 6, j + 49);
	}
	COLOR_2 solidrectangle(667, 0, 740, 600);
	setlinecolor(BLACK);setlinestyle(PS_SOLID, 5, NULL, 0);
	line(0, 2, 740, 2);    //����
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(0, 600, 740, 600);
	line(1, 0, 1, 600);    //����
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
	line(600, 0, 600, 600);
	line(737, 0, 737, 600);
	line(667, 0, 667, 600);
	setlinestyle(PS_SOLID, 2, NULL, 0);//ϸ����
	for (int i = 67; i < 600; i += 67) {
		line(0, i, 667, i);
		line(i, 0, i, 600);
	}
	return;
}

int solve_win() {//���
	show();
	COLOR_2
	TEXT_STYLE_4
	outtextxy(702, 143, "�ύ���");
	TEXT_STYLE_1
	int ch;
	MOUSEMSG m;		// ���������Ϣ
	while (true)
	{// ��ȡһ�������Ϣ
		FlushMouseMsgBuffer();//�����껺����
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {//���������Ϣ
			if (m.x > 667) {//ȷ���ύ
				memmove(SUDOKU_COPY, SUDOKU_ARR, 81 * sizeof(int));//��������
				find_empty(SUDOKU_ARR, 0, &Row, &Col);
				if (set_number(SUDOKU_ARR, Row, Col) == 0) {//����޽�
					//��ʾ�����޽�
					COLOR_8
					TEXT_STYLE_4
					solidrectangle(670, 5, 734, 597);
					outtextxy(702, 143, "�����޽�");
					TEXT_STYLE_1
					Sleep(1000);
					init_sudoku();//��յ�ǰ����
					closegraph();
					return 1;
				}
				//�����н�
				closegraph();
				return 2;
			}
			else if(m.x<600)
			{	//��ǰ����������
				COLOR_2
				SOLIDRECTANGLE_2(m.x,m.y)
				while (1) {
					MOUSEMSG m_1;//�����������������
					m_1 = GetMouseMsg();
					if (m_1.uMsg == WM_LBUTTONDOWN) {//���������Ϣ
						if (m_1.x < 667 && m_1.x >600) {//�������������Ӧ�����ɰױ�ڣ����������ƶ�4����굯���ָ�
							COLOR_5 outtextxy(9 * 67 + 10, (m_1.y / 67) * 67 + 10, m_1.y / 67 + 49);
							while (1) {
								MOUSEMSG m_0 = GetMouseMsg();// ��ȡһ�������Ϣ
								if (m_0.uMsg == WM_LBUTTONUP) {//�������
									COLOR_4 outtextxy(9 * 67 + 10, (m_1.y / 67) * 67 + 6, m_1.y / 67 + 49);
									break;
								}
							}
							SUDOKU_ARR[m.y / 67][m.x / 67] = 0;//���µ��������룬��մ˸�
							ch = m_1.y / 67 + 49;
							break;
						}//������ǵ�������������ٴε���˸�
						if (((m_1.x / 67) == (m.x / 67)) && ((m_1.y / 67) == (m.y / 67))) {
							ch = 27;
							break;
						}
					}
				}
				if (ch == 27) {//�ٴε���˸�ȡ����ǰ�����������ָ����֮ǰ�Ŀո��������
					if (SUDOKU_ARR[m.y / 67][m.x / 67] == 0) {//֮ǰ����ĸ���û������
						COLOR_1
						SOLIDRECTANGLE_2(m.x, m.y)
					}//���»ָ��ո�
					if (SUDOKU_ARR[m.y / 67][m.x / 67] != 0) {//֮ǰ����ĸ����Ѿ�����
						COLOR_2
						outtextxy((m.x / 67) * 67 + 10, (m.y / 67) * 67 + 6, SUDOKU_ARR[m.y / 67][m.x / 67] + 48);
					}//���»ָ�����
				}
				else if (check_number(SUDOKU_ARR, ch - 48, m.y / 67, m.x / 67)) //���������벢�ҿ�������
				{
					SUDOKU_ARR[m.y / 67][m.x / 67] = ch - 48;//��ch��ASCII��ֵת��Ϊ��Ӧ������
					COLOR_2 outtextxy((m.x / 67) * 67 + 10, (m.y / 67) * 67 + 6, ch);
				}
				else {//��˸��ʾ��������
					COLOR_8  SOLIDRECTANGLE_2(m.x, m.y) Sleep(100);
					COLOR_1  SOLIDRECTANGLE_2(m.x, m.y) Sleep(100);
					COLOR_8  SOLIDRECTANGLE_2(m.x, m.y) Sleep(100);
					COLOR_1  SOLIDRECTANGLE_2(m.x, m.y)
				}
			}
		}
	}
}

int select_win() {//ѡ���Ѷ�
	COLOR_2
	cleardevice();
	TEXT_STYLE_2
	COLOR_11
	solidrectangle(150, 0, 160, 120); solidrectangle(150, 115, 300, 125);
	solidroundrect(200, 80, 400, 160, 100, 100); outtextxy(258, 95, "����");
	Sleep(50);
	solidrectangle(100, 0, 110, 240); solidrectangle(100, 235, 300, 245);
	solidroundrect(200, 200, 400, 280, 100, 100); outtextxy(258, 215, "ר��");
	Sleep(50);
	solidrectangle(50, 0, 60, 360); solidrectangle(50, 355, 300, 365);
	solidroundrect(200, 320, 400, 400, 100, 100); outtextxy(258, 335, "��ʦ");
	Sleep(50);
	COLOR_12
	solidrectangle(500, 0, 510, 480); solidrectangle(300, 475, 510, 485);
	solidroundrect(200, 440, 400, 520, 100, 100); outtextxy(240, 455, "������");
	MOUSEMSG m;		// ���������Ϣ
	while (true)
	{// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {//���������Ϣ
			if (m.x >= 200 && m.x <= 400 && m.y >= 80 && m.y <=160) {
				COLOR_11 solidroundrect(200, 80, 400, 160, 100, 100);
				outtextxy(258, 95, "�Ե�");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();
					if (m_0.uMsg == WM_LBUTTONUP)return 40;
				}
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 200 && m.y <= 280) {
				COLOR_11 solidroundrect(200, 200, 400, 280, 100, 100);
				outtextxy(258, 215, "�Ե�");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();
					if (m_0.uMsg == WM_LBUTTONUP)return 30;
				}
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 320 && m.y <= 400) {
				COLOR_11 solidroundrect(200, 320, 400, 400, 100, 100);
				outtextxy(258, 335, "�Ե�");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();
					if (m_0.uMsg == WM_LBUTTONUP)return 20;
				}
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 440 && m.y <= 520) {
				COLOR_12 solidroundrect(200, 440, 400, 520, 100, 100);
				outtextxy(258, 455, "�Ե�");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();
					if (m_0.uMsg == WM_LBUTTONUP) { select_from_lib(); return 0; }
				}
			}
		}
	}
}

void select_from_lib() {//ѡ���������д洢������
	COLOR_2
	cleardevice();
	char sudoku_num_str[5];
	int sudoku_sum, num;
	FILE * SUDOKU_LIB;
	errno_t err;
	err = fopen_s(&SUDOKU_LIB, "MySudoku������.txt", "a+"); 
	//���������ֻ��ģʽ"r"���ļ������ļ�������ʱ����������дģʽ"a"���ļ�������Ա����ļ�������ʱ�������޷�������ȡ�ļ�
	//ֻ���ø���ģʽ"a+"���������ļ�βд�����Զ������ļ����ļ�������ʱ���Դ������ļ�
	if (err == 0) {//�ļ��򿪳ɹ�
		fseek(SUDOKU_LIB, 0L, SEEK_END);//���ҵ��ļ�β
		long byte_number = ftell(SUDOKU_LIB);//������ļ�ͷ���ļ�β���ж��ٸ��ֽ�
		sudoku_sum = byte_number / 83;//�ѱ���������ܸ�����ÿ������ռ��83���ֽ�
		num = sudoku_sum;//num��ʼΪ������
	}
	else {outtextxy(200, 250, "��ʧ��"); Sleep(1000); return;}
	if (num == 0) {outtextxy(200, 250, "�ļ�Ϊ��"); fclose(SUDOKU_LIB); Sleep(1000); return;}
	TEXT_STYLE_4 outtextxy(560, 193, "ȷ ��");
	COLOR_12 solidcircle(0, 300, 450);
	COLOR_11 solidcircle(0, 300, 300);
	COLOR_12 solidcircle(50,300,50);
	POINT pts1[] = { {73, 255}, {73, 345}, {280, 300} }; solidpolygon(pts1, 3);//��ɫ���Ǽ�ͷ
	COLOR_2 solidcircle(50, 300, 5);
	while (1)
	{
		COLOR_12 TEXT_STYLE_2
		outtextxy(328, 275, Int_to_str(num , sudoku_num_str));//���м��ѡ�е��������
		settextcolor(RGB(250, 250, 30));//���¸���ʾ5����С���������
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
		if (m_4.uMsg == WM_MOUSEWHEEL) {//���ֹ�����Ϣ
			if (m_4.wheel > 0 && num < sudoku_sum)num++;//���Ϲ�������
			if (m_4.wheel < 0 && num > 1)num--;//���¹�����ż�С
		}
		if (m_4.uMsg == WM_LBUTTONDOWN) {//����ѡ��
			fseek(SUDOKU_LIB, long((num-1)*83) , SEEK_SET);//���ҵ�Ҫ��ȡ�����������ֽ�λ��
			for (int i = 0; i < 81; i++) {//��Ҫ��ȡ����������������
				SUDOKU_ARR[i/9][i%9] = getc(SUDOKU_LIB) - 48;
			}
			fclose(SUDOKU_LIB);//�ر��ļ�
			break;
		}
	}
	return;
}

char* Int_to_str(int b, char a[]) {//������ת��Ϊ�ַ�����ֻ��ʾ��λ��
	a[0] = (b / 1000) % 10 + 48;
	a[1] = (b / 100) % 10 + 48;
	a[2] = (b / 10) % 10 + 48;
	a[3] =  b % 10 + 48;
	a[4] = '\0';
	return a;
}

int create_sudoku(int rank) {
	if (rank != 0) {//��ʹ��������
	createsudoku://�����������
		for (int i, j, k, count = 0; count < 17;) {//��������17��������Ψһ��
			//srand((unsigned int)time(NULL));//�뼶����������ʺ���������
			i = rand_number(1); //Sleep(1);
			j = rand_number(2); //Sleep(3);
			k = rand_number(3); //Sleep(5);
			if (SUDOKU_ARR[i][j] == 0 && check_number(SUDOKU_ARR, k + 1, i, j)) {
				SUDOKU_ARR[i][j] = k + 1;
				count++;
			}
		}
		find_empty(SUDOKU_ARR, 0, &Row, &Col);
		if (set_number(SUDOKU_ARR, Row, Col) == 0) {//����޽�
			for (int v = 0; v < 9; v++) {//���
				for (int w = 0; w < 9; w++) { SUDOKU_ARR[v][w] = 0; }
			}
			goto createsudoku;//��������
		}
		else //����н�
		{
			for (int i, j, k, count = 0; count < 81 - rank;) {//��������17��������Ψһ��
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
	memmove(SUDOKU_COPY, SUDOKU_ARR, 81 * sizeof(int));//�������ɵĳ�ʼ����
	closegraph();

CLEAN_INPUT://������в��������¿�ʼ
	show();			
	COLOR_7
	TEXT_STYLE_1
	for (int v = 0; v < 9; v++) {//��ʾ���ɵĳ�ʼ����
		for (int w = 0; w < 9; w++) {
			if (SUDOKU_COPY[v][w] != 0) {
				SOLIDRECTANGLE_1(v,w)//��ʼ����Ϊ��ɫ
				outtextxy(w * 67 + 10, v * 67 + 6, SUDOKU_COPY[v][w] + 48); //������ת��Ϊ��Ӧ��ASCII��ֵ
			}
		}
	}
	COLOR_2
	setlinestyle(PS_SOLID, 5, NULL, 0);//�Ҳ�˵�������
	line(667, 120, 740, 120);
	line(667, 240, 740, 240);
	line(667, 360, 740, 360);
	line(667, 480, 740, 480);
	TEXT_STYLE_3
	outtextxy(702, -25, "����");
	outtextxy(702, 95, "�ָ�");
	outtextxy(702, 335, "���");
	outtextxy(702, 455, "����");
	TEXT_STYLE_1
	clock_t  start = clock();//��ʱ
	int count = 0;//��¼��������
	int count_max = 0;//��¼��ǰ����������
	int Track[81][3] = { 0 };//��¼����켣
	int ch;
	MOUSEMSG m;		// ���������Ϣ
	while (true)
	{
		COLOR_2 show_time(start, 243);
		FlushMouseMsgBuffer();//�����껺����
		m = GetMouseMsg();// ��ȡһ�������Ϣ
		if (m.uMsg == WM_LBUTTONDOWN) {//���������Ϣ
			if (m.x > 667 && m.y > 0 && m.y < 120) {//����
				COLOR_8
				TEXT_STYLE_3
				solidrectangle(670, 5, 734, 117);
				outtextxy(702, -25, "����");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();// ��ȡһ�������Ϣ
					if (m_0.uMsg == WM_LBUTTONUP) {//�������
						COLOR_2
						TEXT_STYLE_3
						solidrectangle(670, 5, 734, 117);
						outtextxy(702, -25, "����");
						TEXT_STYLE_1
						break;
					}//���±�죬����ָ�
				}
				if (count > 0) {
					count--;
					SUDOKU_ARR[Track[count][0]][Track[count][1]] = 0;//
					COLOR_1
					SOLIDRECTANGLE_1(Track[count][0], Track[count][1])
				}
			}
			if (m.x > 667 && m.y > 120 && m.y < 240) {//�ָ�
				COLOR_8
				TEXT_STYLE_3
				solidrectangle(670, 123, 734, 237); outtextxy(702, 95, "�ָ�");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();// ��ȡһ�������Ϣ
					if (m_0.uMsg == WM_LBUTTONUP) {//�������
						COLOR_2
						TEXT_STYLE_3
						solidrectangle(670, 123, 734, 237); outtextxy(702, 95, "�ָ�");
						TEXT_STYLE_1
						break;
					}//���±�죬����ָ�
				}
				if (count < count_max) {
					SUDOKU_ARR[Track[count][0]][Track[count][1]] = Track[count][2];//
					COLOR_2
					SOLIDRECTANGLE_1(Track[count][0], Track[count][1])
					outtextxy(Track[count][1] * 67 + 10, Track[count][0] * 67 + 6, Track[count][2]);
					count++;
				}
			}
			if (m.x > 667 && m.y > 240 && m.y < 360) {//���ʱ����
				getimage(&img3, 670, 5, 734, 597);//����˵������㷵��
				COLOR_8
				TEXT_STYLE_4
				solidrectangle(670, 5, 734, 596);
				setlinestyle(PS_SOLID, 5, NULL, 0);
				line(667, 300, 740, 300);
				outtextxy(702, 0, "��Ҫ����");
				outtextxy(702, 290, "������ս");
				TEXT_STYLE_1
				while (true)
				{
					MOUSEMSG m_0 = GetMouseMsg();
					if (m_0.uMsg == WM_LBUTTONDOWN) {
						if (m_0.x > 667 && m_0.y > 0 && m_0.y < 300) {//��Ҫ����
							memmove(SUDOKU_ARR, SUDOKU_COPY, 81 * sizeof(int));//����SUDOKU_ARR
							find_empty(SUDOKU_ARR, 0, &Row, &Col);
							set_number(SUDOKU_ARR, Row, Col);
							closegraph();
							return 1;
						}
						if (m_0.x > 667 && m_0.y > 300 && m_0.y < 600) {//������ս
							putimage(670, 5, &img3, SRCCOPY);
							break;
						}
					}
				}
			}
			
			if (m.x < 600 )//������񲿷�
			{	
				if (SUDOKU_COPY[m.y / 67][m.x / 67] != 0) {//������ǳ�ʼֵ
					Show_this_num(SUDOKU_ARR[m.y / 67][m.x / 67]);//������ʾ��ֵͬ
				}
				if (SUDOKU_COPY[m.y / 67][m.x / 67] == 0) {//����Ĳ��ǳ�ʼֵ
					if (SUDOKU_ARR[m.y / 67][m.x / 67] != 0) {//����Ĳ��ǿո�
						Show_this_num(SUDOKU_ARR[m.y / 67][m.x / 67]);//������ʾ��ֵͬ
					}
					if (SUDOKU_ARR[m.y / 67][m.x / 67] == 0) {//������ǿո�
						Show_check_area(m.x,m.y);//������ʾ��ǰλ�õ����г�ͻ�������
					}
					//��ǰ����������
					COLOR_2
					SOLIDRECTANGLE_2(m.x, m.y)
					while (1) {
						MOUSEMSG m_1;//�����������������
						m_1 = GetMouseMsg();
						if (m_1.uMsg == WM_LBUTTONDOWN) {//���������Ϣ
							if (m_1.x < 667 && m_1.x >600) {//�������������Ӧ�����ɰױ�ڣ����������ƶ�4����굯���ָ�
								COLOR_5 outtextxy(9 * 67 + 10, (m_1.y / 67) * 67 + 10, m_1.y / 67 + 49);
								while (1) {
									MOUSEMSG m_0 = GetMouseMsg();// ��ȡһ�������Ϣ
									if (m_0.uMsg == WM_LBUTTONUP) {//�������
										COLOR_4 outtextxy(9 * 67 + 10, (m_1.y / 67) * 67 + 6, m_1.y / 67 + 49);
										break;
									}
								}
								SUDOKU_ARR[m.y / 67][m.x / 67] = 0;//���µ��������룬��մ˸�
								ch = m_1.y / 67 + 49;
								break;
							}
							if (((m_1.x /67)==(m.x/ 67)) && ((m_1.y / 67) == (m.y / 67))) {//�ٴε���˸�
								ch = 27;
								break;
							}
							if (m_1.x > 667 && m_1.y > 360 && m_1.y < 480) {//���������
								SUDOKU_ARR[m.y / 67][m.x / 67] = 0;//��մ˸�
								ch = 13;
								break;
							}
						}
					}
					if (ch==27) {//�ٴε���˸񣨻��߼���ģʽ����Esc����ȡ����ǰ��������
						if (SUDOKU_ARR[m.y / 67][m.x / 67] == 0) {//֮ǰ����ĸ���û������
							COLOR_1
							SOLIDRECTANGLE_2(m.x, m.y)
						}//���»ָ��ո�
						if (SUDOKU_ARR[m.y / 67][m.x / 67] != 0 && SUDOKU_COPY[m.y / 67][m.x / 67] == 0) {//֮ǰ�����Ϊ�ǳ�ʼ��
							COLOR_2
							outtextxy((m.x / 67) * 67 + 10, (m.y / 67) * 67 + 6, SUDOKU_ARR[m.y / 67][m.x / 67] + 48);
						}//���»ָ�����
					}
					else if (ch==13) //���
					{
						COLOR_8
						TEXT_STYLE_3
						solidrectangle(670, 363, 734, 477);
						outtextxy(702, 335, "���");
						TEXT_STYLE_1
						
						if (SUDOKU_COPY[m.y / 67][m.x / 67] == 0) {//��ʼ���޷����
							SOLIDRECTANGLE_2(m.x, m.y)
							TEXT_STYLE_3
							solidrectangle(670, 363, 734, 477);
							outtextxy(702, 335, "�Ҽ�");
							TEXT_STYLE_1
							while (1) {
								MOUSEMSG m_2;//�����������������
								m_2 = GetMouseMsg();
								if (m_2.uMsg == WM_LBUTTONDOWN) {//���������Ϣ
									if (m_2.x < 667 && m_2.x >600) {//�������������Ӧ�����ɰױ�ڣ����������ƶ�4����굯���ָ�
										TEXT_STYLE_1
										COLOR_5 outtextxy(9 * 67 + 10, (m_2.y / 67) * 67 + 10, m_2.y / 67 + 49);
										while (1) {
											MOUSEMSG m_0 = GetMouseMsg();// ��ȡһ�������Ϣ
											if (m_0.uMsg == WM_LBUTTONUP) {//�������
												COLOR_4 outtextxy(9 * 67 + 10, (m_2.y / 67) * 67 + 6, m_2.y / 67 + 49);
												break;
											}
										}
										COLOR_8
										settextstyle(18, 10, _T("΢���ź�"));
										outtextxy((m.x / 67) * 67 + (m_2.y / 67 % 3) * 15 + 10, (m.y / 67) * 67 + (m_2.y / 67 / 3) * 15 + 10, m_2.y / 67 + 49);
									}
								}
								if (m_2.uMsg == WM_RBUTTONDOWN) {//�����Ҽ���ɱ��
									COLOR_2 TEXT_STYLE_3
									solidrectangle(670, 363, 734, 477);
									outtextxy(702, 335, "���");
									TEXT_STYLE_1
									break;
								}
							}
						}
					}
					else if (check_number(SUDOKU_ARR, ch - 48, m.y / 67, m.x / 67)) {//�����������
						SUDOKU_ARR[m.y / 67][m.x / 67] = ch - 48;//��ch��ASCII��ֵת��Ϊ��Ӧ��������������
						COLOR_2
						outtextxy((m.x / 67) * 67 + 10, (m.y / 67) * 67 + 6, ch);
						Track[count][0] = m.y / 67;
						Track[count][1] = m.x / 67;
						Track[count][2] = ch;
						count++;
						count_max = count;//����count_max
						if ((count + rank) == 81) {//����+��ʼ=81�������ϣ���ʾ�ɹ�
							COLOR_8
							TEXT_STYLE_4
							solidrectangle(670, 5, 734, 596);
							outtextxy(702, 8, "��ս�ɹ�");
							outtextxy(702, 273, "��ʱ");
							TEXT_STYLE_1
							show_time(start, 428);
							while (true)//����ص���ʼ����
							{
								m = GetMouseMsg();
								if (m.uMsg == WM_LBUTTONDOWN) {
									closegraph();
									return 0;
								}
							}
						}
					}
					else {//��˸��ʾ��������
						COLOR_8  SOLIDRECTANGLE_2(m.x, m.y) Sleep(100);
						COLOR_1  SOLIDRECTANGLE_2(m.x, m.y) Sleep(100);
						COLOR_8  SOLIDRECTANGLE_2(m.x, m.y) Sleep(100);
						COLOR_1  SOLIDRECTANGLE_2(m.x, m.y)
					}
				}
			}
			if (m.x > 667 && m.y > 480 && m.y < 600) {//����
				COLOR_8
				TEXT_STYLE_3
				solidrectangle(670, 483, 734, 597); outtextxy(702, 455, "����");
				while (1) {
					MOUSEMSG m_0 = GetMouseMsg();// ��ȡһ�������Ϣ
					if (m_0.uMsg == WM_LBUTTONUP) {//�������
						COLOR_2
						TEXT_STYLE_3
						solidrectangle(670, 483, 734, 597); outtextxy(702, 455, "����");
						TEXT_STYLE_1
						break;
					}//���±�죬����ָ�
				}
				memmove(SUDOKU_ARR,SUDOKU_COPY,81*sizeof(int));//��SUDOKU_COPY������SUDOKU_ARR����ʼ��SUDOKU_ARR
				closegraph();
				goto CLEAN_INPUT;
			}
		}
	}
	return 0;
}

int rand_number(int rand_rank) {//����0��8�����
	LARGE_INTEGER seed;
	QueryPerformanceFrequency(&seed);
	QueryPerformanceCounter(&seed);
	srand(seed.QuadPart);//��ʼ��һ����΢��Ϊ��λ��ʱ������
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

void show_time(clock_t start,int h) {//��������ת��Ϊʱ���ַ���
	clock_t  now = clock();
	int sec = (int)((now - start) / CLK_TCK);
	char time_str[9] = { 0 };//�洢ʱ���ַ���
	time_str[0] = (sec / 3600) / 10 + 48;
	time_str[1] = (sec / 3600) % 10 + 48;
	time_str[2] = ':';
	time_str[3] = ((sec % 3600) / 60) / 10 + 48;
	time_str[4] = ((sec % 3600) / 60) % 10 + 48;
	time_str[5] = ':';
	time_str[6] = ((sec % 3600) % 60) / 10 + 48;
	time_str[7] = ((sec % 3600) % 60) % 10 + 48;
	settextstyle(35, 11, _T("��������"));
	outtextxy(676, h, time_str[0]);
	outtextxy(692, h, time_str[1]);
	outtextxy(707, h, "ʱ");
	outtextxy(676, h + 40, time_str[3]);
	outtextxy(692, h + 40, time_str[4]);
	outtextxy(707, h + 40, "��");
	outtextxy(676, h + 80, time_str[6]);
	outtextxy(692, h + 80, time_str[7]);
	outtextxy(707, h + 80, "��");
	TEXT_STYLE_1
	return;
}

void Show_this_num(int num) {//������ʾ������ͬ����
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (SUDOKU_ARR[i][j] == num ) {
				COLOR_9  SOLIDRECTANGLE_1(i,j)
				outtextxy(j * 67 + 10, i * 67 + 8, num+48);//����λ�������ƶ�2���γɶ�̬Ч��
			}
		}
	}
	while (1) {
		MOUSEMSG m_0 = GetMouseMsg();// ��ȡһ�������Ϣ
		if (m_0.uMsg == WM_LBUTTONUP) {//�������
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (SUDOKU_ARR[i][j] == num && SUDOKU_COPY[i][j] != 0) {//��ʼ��
						COLOR_7  SOLIDRECTANGLE_1(i, j)
						outtextxy(j * 67 + 10, i * 67 + 6, num + 48);
					}
					if (SUDOKU_ARR[i][j] == num && SUDOKU_COPY[i][j] == 0) {//�ǳ�ʼ��
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

void Show_check_area(int x, int y) {//��ʾ���м�����������
	int row = y / 67, col = x / 67;
	int i, j;
	int x_ = (row / 3) * 3;
	int y_ = (col / 3) * 3;//x,yΪ��ǰλ������С�Ź������Ͻ�����
	for (j = 0; j < 9; j++) {//ͬ�и���
		if (SUDOKU_ARR[row][j] != 0) {
			COLOR_10  SOLIDRECTANGLE_1(row, j)
				outtextxy(j * 67 + 10, row * 67 + 8, SUDOKU_ARR[row][j] + 48);
		}
	}
	for (i = 0; i < 9; i++) {//ͬ�и���
		if (SUDOKU_ARR[i][col] != 0) {
			COLOR_10  SOLIDRECTANGLE_1(i, col)
				outtextxy(col * 67 + 10, i * 67 + 8, SUDOKU_ARR[i][col] + 48);
		}
	}
	for (i = x_; i < x_ + 3; i++) {//ͬ������
		for (j = y_; j < y_ + 3; j++) {
			if (SUDOKU_ARR[i][j] != 0) {
				COLOR_10  SOLIDRECTANGLE_1(i, j)
					outtextxy(j * 67 + 10, i * 67 + 8, SUDOKU_ARR[i][j] + 48);
			}
		}
	}
	while (1) {
		MOUSEMSG m_0 = GetMouseMsg();// ��ȡһ�������Ϣ
		if (m_0.uMsg == WM_LBUTTONUP) {//�������
			for (j = 0; j < 9; j++) {//ͬ�лָ�
				if (SUDOKU_COPY[row][j] != 0) {//��ʼ��
					COLOR_7  SOLIDRECTANGLE_1(row, j)
					outtextxy(j * 67 + 10, row * 67 + 6, SUDOKU_ARR[row][j] + 48);
				}
				if (SUDOKU_ARR[row][j] != 0 && SUDOKU_COPY[row][j] == 0) {//�ǳ�ʼ��
					COLOR_2  SOLIDRECTANGLE_1(row, j)
					outtextxy(j * 67 + 10, row * 67 + 6, SUDOKU_ARR[row][j] + 48);
				}
			}
			for (i = 0; i < 9; i++) {//ͬ�лָ�
				if (SUDOKU_COPY[i][col] != 0) {//��ʼ��
					COLOR_7  SOLIDRECTANGLE_1(i, col)
					outtextxy(col * 67 + 10, i * 67 + 6, SUDOKU_ARR[i][col] + 48);
				}
				if (SUDOKU_ARR[i][col] != 0 && SUDOKU_COPY[i][col] == 0) {//�ǳ�ʼ��
					COLOR_2  SOLIDRECTANGLE_1(i, col)
						outtextxy(col * 67 + 10, i * 67 + 6, SUDOKU_ARR[i][col] + 48);
				}
			}
			for (i = x_; i < x_ + 3; i++) {//ͬ���ָ�
				for (j = y_; j < y_ + 3; j++) {
					if (SUDOKU_COPY[i][j] != 0) {//��ʼ��
						COLOR_7  SOLIDRECTANGLE_1(i, j)
						outtextxy(j * 67 + 10, i * 67 + 6, SUDOKU_ARR[i][j] + 48);
					}
					if (SUDOKU_ARR[i][j] != 0 && SUDOKU_COPY[i][j] == 0) {//�ǳ�ʼ��
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

int find_empty(int sudoku[9][9], int startrow, int *row, int *col) {//���ݵ�ַ�Ա��޸Ĳ���λ��
	int i, j;
	for (i = startrow; i < 9; i++)//�ӵ�ǰ�п�ʼ���δ������λ��
		for (j = 0; j < 9; j++)
			if (sudoku[i][j] == 0) {//�������ĵ�һ��δ���λ����Ϊ��ǰ����λ��
				*row = i;
				*col = j;
				return 1;
			}
	return 0;//û��δ����λ����
}

int set_number(int sudoku[9][9], int row, int col) {//������ȵݹ��������
	int m, next_row, next_col;
	for (m = 1; m <= 9; m++) {
		if (check_number(sudoku, m, row, col) == 1) {//�������

			sudoku[row][col] = m;//����
			//Ѱ����һ��δ���λ��
			if (find_empty(sudoku, row, &next_row, &next_col) == 0) return 1;//ȫ����������㷵��
			//����ݹ������һ��λ�ã����õݹ鷵��ʵ��������������Ļ��ݣ�
			if (set_number(sudoku, next_row, next_col) == 0) {//��һ��λ�����ʧ���򷵻ص���ǰλ��
				sudoku[row][col] = 0;//����ǰλ������������
				continue;//����forѭ�� ��֮ǰ������֮��Ѱ�������������
			}
			else return 1;//��һ��λ�����ɹ�
		}
	}
	return 0;//û�п������������ʧ��
}

int check_number(int sudoku[9][9], int m, int row, int col) {//����Ƿ��ظ�
	int i, j;
	for (i = 0; i < 9; i++) {//ͬ�м��
		if (sudoku[row][i] == m) return 0;
	}
	for (i = 0; i < 9; i++) {//ͬ�м��
		if (sudoku[i][col] == m) return 0;
	}
	//ͬ�����
	int x = (row / 3) * 3;
	int y = (col / 3) * 3;//x,yΪ��ǰλ������С�Ź������Ͻ�����
	for (i = x; i < x + 3; i++) {
		for (j = y; j < y + 3; j++) {
			if (sudoku[i][j] == m) return 0;
		}
	}
	return 1;//���ؿ����ź�
}

void print_sudoku(int sudoku[9][9]) {//�����int v, w;
	show();
	TEXT_STYLE_1
	for (int v = 0; v < 9; v++) {
		for (int w = 0; w < 9; w++) {
			COLOR_1
			if (SUDOKU_COPY[v][w] != 0) {
				COLOR_7  SOLIDRECTANGLE_1(v,w) //��ʼ����Ϊ��ɫ
			}
			outtextxy(w * 67 + 10, v * 67 + 5, sudoku[v][w] + 48); //������ת��Ϊ��Ӧ��ASCII��ֵ
		}
	}
	COLOR_2
	TEXT_STYLE_4
	setlinestyle(PS_SOLID, 5, NULL, 0);
	line(667, 300, 740, 300);
	outtextxy(702, 0, "���ز˵�");
	outtextxy(702, 290, "�洢����");
	TEXT_STYLE_1
	while (true)
	{
		MOUSEMSG m_0 = GetMouseMsg();
		if (m_0.uMsg == WM_LBUTTONDOWN) {
			if (m_0.x > 667 && m_0.y > 0 && m_0.y < 300) {//������ʼ
				closegraph();
				return;
			}
			if (m_0.x > 667 && m_0.y > 300 && m_0.y < 600) {//�洢����
				char sudoku_copy_str[83];
				for (int v = 0; v < 9; v++) {
					for (int w = 0; w < 9; w++) {
						sudoku_copy_str[v*9+w] = SUDOKU_COPY[v][w]+48;
					}
				}//����ʼ����������ַ���������Իس���β
				sudoku_copy_str[81] = '\n';
				sudoku_copy_str[82] = '\0';
				FILE * SUDOKU_LIB;
				errno_t err;
				err=fopen_s(&SUDOKU_LIB,"MySudoku������.txt", "a"); //�ڵ�ǰ�ļ�βд
				COLOR_2 TEXT_STYLE_4 solidrectangle(670, 5, 734, 597);
				if (err == 0) {//�ļ��򿪳ɹ�
					fputs(sudoku_copy_str, SUDOKU_LIB);//���ַ�����д���ļ�β
					fseek(SUDOKU_LIB, 0L, SEEK_END);//���ҵ��ļ�β
					long byte_number = ftell(SUDOKU_LIB);//������ļ�ͷ���ļ�β���ж��ٸ��ֽ�
					int sudoku_sum = byte_number / 83;//�ѱ��������������ÿ������ռ��83���ֽ�
					char sudoku_sum_str[21]= "�ѱ���Ϊ��0000��";
					sudoku_sum_str[13] = sudoku_sum % 10+48;
					sudoku_sum_str[12] = (sudoku_sum / 10) % 10 + 48;
					sudoku_sum_str[11] = (sudoku_sum / 100) % 10 + 48;
					sudoku_sum_str[10] = (sudoku_sum / 1000) % 10 + 48;
					outtextxy(702, 0, sudoku_sum_str);//��ʾ��������
				}
				else outtextxy(702, 143, "����ʧ��");
				fclose(SUDOKU_LIB);//�ر��ļ�
				while (1)//�����˳�
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

