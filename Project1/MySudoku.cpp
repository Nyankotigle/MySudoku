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

void init() {//��ʼ����
	initgraph(600, 675);
	HWND hwnd = GetHWnd();
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	MoveWindow(hwnd, 340, 0, 600, 675, TRUE);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(200, 40, _T("΢���ź�"));
	settextcolor(RGB(250, 100, 50));
	outtextxy(50, 60, "MY");
	settextcolor(BLACK);
	outtextxy(190, 60, "SUDOKU");
	setfillcolor(YELLOW);
	solidrectangle(200, 300, 400, 400);
	solidrectangle(200, 450, 400, 550);
	setbkcolor(WHITE);
	settextstyle(20, 6, _T("��������"));
	outtextxy(205, 610, "Alt+Space+M+����� �ƶ�����λ��");
	outtextxy(130, 630, "��Ȩ���У�1204219458@qq.com |�汾:4.0 |2020.02.26 ");
	setbkcolor(YELLOW); 
	settextstyle(50, 20, _T("��������"));
	outtextxy(258, 325, "���");
	outtextxy(258, 475, "��ս");
	MOUSEMSG m;		// ���������Ϣ
	while (true)
	{// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {//���������Ϣ
			if (m.x >= 200 && m.x <= 400 && m.y >= 300 && m.y <= 400) {
				setfillcolor(RGB(150, 250, 150));
				solidrectangle(200, 300, 400, 400);
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 450 && m.y <= 550) {
				setfillcolor(RGB(150, 250, 150));
				solidrectangle(200, 450, 400, 550);
			}
		}
		if (m.uMsg == WM_LBUTTONUP) {//���������Ϣ
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

void show() {//�����������
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
void solve_win() {//���
	show();
	setbkcolor(YELLOW);
	setfillcolor(YELLOW);
	settextcolor(BLACK);
	solidrectangle(5, 605, 595, 670);
	settextstyle(60, 25, _T("��������"));
	outtextxy(200, 605, "ȷ���ύ");
	settextstyle(50, 30, _T("΢���ź�"));
	int ch;
	MOUSEMSG m;		// ���������Ϣ
	while (true)
	{// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {//���������Ϣ
			if (m.y > 600) {//ȷ���ύ
				find_empty(SUDOKU_ARR, 0, &Row, &Col);
				if (set_number(SUDOKU_ARR, Row, Col) == 0) {//����޽�
					//��ʾ�����޽�
					setbkcolor(RGB(250, 100, 50)); setfillcolor(RGB(250, 100, 50)); settextstyle(60, 25, _T("��������"));
					solidrectangle(5, 605, 595, 670);
					outtextxy(200, 605, "�����޽�");
					Sleep(1000);
					for (int v = 0; v < 9; v++) {//��յ�ǰ����
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
			{	//��ǰ����������
				solidrectangle((m.x / 67) * 67 + 5, (m.y / 67) * 67 + 6, (m.x / 67) * 67 + 57, (m.y / 67) * 67 + 57);
				while (1) {
					if (_kbhit()) {
						ch = _getch();
						//fflush(stdin);//��ջ�������ò�Ʋ������ã�
						break;
					}
				}
				if (check_number(SUDOKU_ARR, ch - 48, m.y / 67, m.x / 67)) {
					SUDOKU_ARR[m.y / 67][m.x / 67] = ch - 48;//��ch��ASCII��ֵת��Ϊ��Ӧ������
					outtextxy((m.x / 67) * 67 + 10, (m.y / 67) * 67 + 6, ch);
				}
				else {
					setfillcolor(WHITE);//ȡ����ǰ����������
					solidrectangle((m.x / 67) * 67 + 5, (m.y / 67) * 67 + 6, (m.x / 67) * 67 + 57, (m.y / 67) * 67 + 57);
					//��ʾ��������
					setbkcolor(RGB(250,100,50));setfillcolor(RGB(250, 100, 50)); settextstyle(60, 25, _T("��������"));
					solidrectangle(5, 605, 595, 670);
					outtextxy(200, 605, "��������");
					Sleep(500);
					//�ָ�ȷ���ύ
					setbkcolor(YELLOW); setfillcolor(YELLOW); settextstyle(60, 25, _T("��������"));
					solidrectangle(5, 605, 595, 670);
					outtextxy(200, 605, "ȷ���ύ");
					settextstyle(50, 30, _T("΢���ź�"));
				}
			}
		}
	}
}

void select_win() {//ѡ���Ѷ�
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(BLACK);
	setfillcolor(YELLOW);
	solidrectangle(200, 150, 400, 250);
	solidrectangle(200, 300, 400, 400);
	solidrectangle(200, 450, 400, 550);
	setbkcolor(YELLOW);
	settextstyle(50, 20, _T("��������"));
	outtextxy(258, 175, "����");
	outtextxy(258, 325, "ר��");
	outtextxy(258, 475, "��ʦ");
	setbkcolor(RGB(150, 250, 150));
	setfillcolor(RGB(150, 250, 150));
	MOUSEMSG m;		// ���������Ϣ
	while (true)
	{// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {//���������Ϣ
			if (m.x >= 200 && m.x <= 400 && m.y >= 150 && m.y <= 250) {
				solidrectangle(200, 150, 400, 250);
				outtextxy(258, 175, "�Ե�");
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 300 && m.y <= 400) {
				solidrectangle(200, 300, 400, 400);
				outtextxy(258, 325, "�Ե�");
			}
			if (m.x >= 200 && m.x <= 400 && m.y >= 450 && m.y <= 550) {
				solidrectangle(200, 450, 400, 550);
				outtextxy(258, 475, "�Ե�");
			}
		}
		if (m.uMsg == WM_LBUTTONUP) {//���������Ϣ
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
	if(set_number(SUDOKU_ARR, Row, Col) == 0) {//����޽�
		for (int v = 0; v < 9; v++) {//��յ�ǰ����
			for (int w = 0; w < 9; w++) { SUDOKU_ARR[v][w] = 0; }
		}
		goto createsudoku;//��������
	}
	else //����н�
	{
		for (int v = 0; v < 9; v++) {//���ݽ�
			for (int w = 0; w < 9; w++) { SOLVE_COPY[v][w] = SUDOKU_ARR[v][w]; }
		}
		for (int i, j, k, count = 0; count < 81-rank;) {//��������17��������Ψһ��
			i = rand_number(1); //Sleep(1);
			j = rand_number(2); //Sleep(3);
			k = rand_number(3); //Sleep(5);
			if (SUDOKU_ARR[i][j] != 0 ) {
				SUDOKU_ARR[i][j] = 0;
				count++;
			}
		}
	}
	for (int v = 0; v < 9; v++) {//�������ɵĳ�ʼ����
		for (int w = 0; w < 9; w++) { SUDOKU_COPY[v][w] = SUDOKU_ARR[v][w]; }
	}
	
CLEAN_INPUT://������в��������¿�ʼ
	show();			
	settextcolor(BLACK);
	setbkcolor(RGB(200, 250, 200));
	setfillcolor(RGB(200,250,200));
	settextstyle(50, 30, _T("΢���ź�"));
	for (int v = 0; v < 9; v++) {//��ʾ���ɵĳ�ʼ����
		for (int w = 0; w < 9; w++) {
			if (SUDOKU_COPY[v][w] != 0) {
				solidrectangle(w * 67 + 5, v * 67 + 6, w * 67 + 57, v * 67 + 57);//��ʼ����Ϊ��ɫ
				outtextxy(w * 67 + 10, v * 67 + 6, SUDOKU_COPY[v][w] + 48); //������ת��Ϊ��Ӧ��ASCII��ֵ
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
	settextstyle(50, 20, _T("��������"));
	outtextxy(20, 610, "����");
	outtextxy(140, 610, "�ָ�");
	outtextxy(380, 610, "���");
	outtextxy(500, 610, "����");
	settextstyle(50, 30, _T("΢���ź�"));
	clock_t  start, now;
	start = clock();
	char time_str[9] = { 0 };//�洢ʱ���ַ���
	int count = 0;//��¼��������
	int count_max = 0;//��¼��ǰ����������
	int Track[81][3] = { 0 };//��¼����켣
	int ch;
	MOUSEMSG m;		// ���������Ϣ
	while (true)
	{
		now = clock();//������ʾʱ��
		settextstyle(40, 12, _T("΢���ź�")); setbkcolor(YELLOW);
		outtextxy(250, 615, transfer_time((int)((now - start) / CLK_TCK), time_str));
		settextstyle(50, 30, _T("΢���ź�"));

		FlushMouseMsgBuffer();//�����껺����
		m = GetMouseMsg();// ��ȡһ�������Ϣ
		if (m.uMsg == WM_LBUTTONDOWN) {//���������Ϣ
			if (m.y > 600 && m.x > 0 && m.x < 120) {//����
				setfillcolor(WHITE);
				if (count > 0) {
					count--;
					SUDOKU_ARR[Track[count][0]][Track[count][1]] = 0;//
					solidrectangle(Track[count][1] * 67 + 5, Track[count][0] * 67 + 6, Track[count][1] * 67 + 57, Track[count][0] * 67 + 57);
				}
			}
			if (m.y > 600 && m.x > 120 && m.x < 240) {//�ָ�
				if (count < count_max) {
					SUDOKU_ARR[Track[count][0]][Track[count][1]] = Track[count][2];//
					settextcolor(BLACK);
					setfillcolor(YELLOW); setbkcolor(YELLOW);
					solidrectangle(Track[count][1] * 67 + 5, Track[count][0] * 67 + 6, Track[count][1] * 67 + 57, Track[count][0] * 67 + 57);
					outtextxy(Track[count][1] * 67 + 10, Track[count][0] * 67 + 6, Track[count][2]);
					count++;
				}
			}
			if (m.y > 600 && m.x > 240 && m.x < 360) {//��ʾ��
				for (int v = 0; v < 9; v++) {
					for (int w = 0; w < 9; w++) {
						setfillcolor(YELLOW); setbkcolor(YELLOW);
						solidrectangle(w * 67 + 5, v * 67 + 6, w * 67 + 57, v * 67 + 57);
						outtextxy(w * 67 + 10, v * 67 + 6, SOLVE_COPY[v][w] + 48); 
					}
				}
				setbkcolor(RGB(250, 100, 50)); setfillcolor(RGB(250, 100, 50)); settextstyle(60, 25, _T("��������"));
				solidrectangle(5, 602, 595, 670);
				outtextxy(200, 605, "��������");
				while (true)//����ص���ʼ����
				{
					m = GetMouseMsg();
					if (m.uMsg == WM_LBUTTONDOWN) {
						init(); return;
					}
				}
			}
			
			if (m.y < 600 )//������񲿷�
			{	
				if (SUDOKU_COPY[m.y / 67][m.x / 67] != 0) {//������ǳ�ʼֵ
					Show_this_num(SUDOKU_ARR[m.y / 67][m.x / 67]);
				}
				if (SUDOKU_COPY[m.y / 67][m.x / 67] == 0) {//����Ĳ��ǳ�ʼֵ
					if (SUDOKU_ARR[m.y / 67][m.x / 67] != 0) {//����Ĳ��ǿո�
						Show_this_num(SUDOKU_ARR[m.y / 67][m.x / 67]);
					}
					//��ǰ��������������������
					setfillcolor(YELLOW);
					solidrectangle((m.x / 67) * 67 + 5, (m.y / 67) * 67 + 6, (m.x / 67) * 67 + 57, (m.y / 67) * 67 + 57);
					SUDOKU_ARR[m.y / 67][m.x / 67] = 0;
					while (1) {//��ȡ��������
						if (_kbhit()) {//������ô������뻺�滹δ�⣬����һ����������ʱ����һ��ֱ�Ӵӻ��������������ǵȴ���������
							ch = _getch();
							break;
						}
					}
					if (ch==27) {//���Esc����ȡ����ǰ��������
						if (SUDOKU_ARR[m.y / 67][m.x / 67] == 0) {//֮ǰ������ǿո�
							setfillcolor(WHITE);
							solidrectangle((m.x / 67) * 67 + 5, (m.y / 67) * 67 + 6, (m.x / 67) * 67 + 57, (m.y / 67) * 67 + 57);
							setfillcolor(YELLOW);
						}//���»ָ��ո�
						if (SUDOKU_ARR[m.y / 67][m.x / 67] != 0 && SUDOKU_COPY[m.y / 67][m.x / 67] == 0) {//֮ǰ�����Ϊ�ǳ�ʼ��
							setbkcolor(YELLOW);
							outtextxy((m.x / 67) * 67 + 10, (m.y / 67) * 67 + 6, SUDOKU_ARR[m.y / 67][m.x / 67] + 48);
						}//���»ָ�����
					}
					else if (check_number(SUDOKU_ARR, ch - 48, m.y / 67, m.x / 67)) {//�����������
						SUDOKU_ARR[m.y / 67][m.x / 67] = ch - 48;//��ch��ASCII��ֵת��Ϊ��Ӧ��������������
						setbkcolor(YELLOW);
						outtextxy((m.x / 67) * 67 + 10, (m.y / 67) * 67 + 6, ch);
						Track[count][0] = m.y / 67;
						Track[count][1] = m.x / 67;
						Track[count][2] = ch;
						count++;
						count_max = count;//����count_max
						if ((count + rank) == 81) {//����+��ʼ=81�������ϣ���ʾ�ɹ�
							setbkcolor(RGB(250, 100, 50)); setfillcolor(RGB(250, 100, 50)); settextstyle(60, 25, _T("��������"));
							solidrectangle(5, 602, 595, 670);
							outtextxy(200, 605, "��ս�ɹ�");
							while (true)//����ص���ʼ����
							{
								m = GetMouseMsg();
								if (m.uMsg == WM_LBUTTONDOWN) {
									init(); return;
								}
							}
						}
					}
					else {//��˸��ʾ��������
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

			if (m.y > 600 && m.x > 360 && m.x < 480) {//���
				setbkcolor(RGB(250, 100, 50)); setfillcolor(RGB(250, 100, 50)); settextstyle(50, 20, _T("��������"));
				solidrectangle(365, 605, 475, 670); outtextxy(380, 610, "���");
				while (true)
				{
					m = GetMouseMsg();// ��ȡһ�������Ϣ
					if (m.uMsg == WM_LBUTTONDOWN) {//���������Ϣ
						if (m.y < 600 && SUDOKU_ARR[m.y / 67][m.x / 67] == 0) {
							solidrectangle((m.x / 67) * 67 + 5, (m.y / 67) * 67 + 6, (m.x / 67) * 67 + 57, (m.y / 67) * 67 + 57);
							settextstyle(50, 12, _T("��������"));
							outtextxy(370, 610, "�س�����");
							while (1) {
								if (_kbhit()) {
									ch = _getch();
									if (ch >= 49 && ch <= 57) {
										settextstyle(18, 10, _T("΢���ź�"));
										outtextxy((m.x / 67) * 67 + ((ch - 49) % 3) * 15 + 10, (m.y / 67) * 67 + ((ch - 49) / 3) * 15+10, ch);

									}
									if (ch == 13) {//�س���
										setbkcolor(YELLOW); setfillcolor(YELLOW); settextstyle(50, 20, _T("��������"));
										solidrectangle(365, 605, 475, 670); outtextxy(380, 610, "���");
										settextstyle(50, 30, _T("΢���ź�"));
										break;
									}
								}
							}
							break;
						}
					}
				}
			}
			if (m.y > 600 && m.x > 480 && m.x < 600) {//����
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

char* transfer_time(int sec,char* time_str) {//��������ת��Ϊʱ���ַ���
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

void Show_this_num(int num) {//������ʾ������ͬ����
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (SUDOKU_ARR[i][j] == num ) {
				setfillcolor(RGB(0, 150, 250)); setbkcolor(RGB(0, 150, 250));
				solidrectangle(j * 67 + 5, i * 67 + 6, j * 67 + 57, i * 67 + 57);
				outtextxy(j * 67 + 10, i * 67 + 8, num+48);//����λ�������ƶ�2���γɶ�̬Ч��
			}
		}
	}
	Sleep(1000);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (SUDOKU_ARR[i][j] == num && SUDOKU_COPY[i][j] != 0) {//��ʼ��
				setfillcolor(RGB(200, 250, 200)); setbkcolor(RGB(200, 250, 200));
				solidrectangle(j * 67 + 5, i * 67 + 6, j * 67 + 57, i * 67 + 57);
				outtextxy(j * 67 + 10, i * 67 + 6, num + 48);
			}
			if (SUDOKU_ARR[i][j] == num && SUDOKU_COPY[i][j] == 0) {//�ǳ�ʼ��
				setfillcolor(YELLOW); setbkcolor(YELLOW);
				solidrectangle(j * 67 + 5, i * 67 + 6, j * 67 + 57, i * 67 + 57);
				outtextxy(j * 67 + 10, i * 67 + 6, num + 48);
			}
		}
	}
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

void print_sudoku(int sudoku[9][9]) {//�����
	int v, w;
	closegraph();
	show();
	settextcolor(BLACK);
	settextstyle(50, 30, _T("΢���ź�"));
	for (v = 0; v < 9; v++) {
		for (w = 0; w < 9; w++) {
			outtextxy(w * 67 + 10, v * 67 + 5, sudoku[v][w] + 48); //������ת��Ϊ��Ӧ��ASCII��ֵ
			sudoku[v][w] = 0;//����󼴳�ʼ��Ϊ��һ����׼��
		}
	}
	setbkcolor(YELLOW); setfillcolor(YELLOW); settextstyle(60, 25, _T("��������"));
	solidrectangle(5, 605, 595, 670);
	setlinestyle(PS_SOLID, 5, NULL, 0);
	line(300, 600, 300, 670);
	outtextxy(100, 605, "���");
	outtextxy(400, 605, "��ս");
	settextstyle(50, 30, _T("΢���ź�"));
	MOUSEMSG m;		// ���������Ϣ
	while (true)
	{// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {//���������Ϣ
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

