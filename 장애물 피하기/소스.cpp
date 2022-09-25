#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define L 10		//�� ��
#define W 2*L		//�ܼ� �ʺ�
#define H 21		//����
#define PSX L / 2		//���� ��ǥ
#define sec 200		//
#define MIS 1		//��ֹ� ���� ���� �ӵ�
#define Range 3		//��ֹ� �ӵ� ����
#define White 15
#define Red 12

int ms;		//�ð� ����
char sha[][3] = { "��","��" };		//����
char x, y;		//�÷��̾� ��ǥ

struct object {
	char state;
	char y;			//��ֹ� ��ǥ
	char speed;		//���� �ӵ�
	int t;
}obj[L];

//�ܼ� ũ�� ����(����,����)
void console(char w, char h) {
	char sys[] = "mode con cols=    lines=   ";
	char col = 14;		//�ܼ� ���� ũ�� �Է� ��ġ
	char lin = 24;		//�ܼ� ���� ũ�� �Է� ��ġ
	short n;

	for (n = 10; w / n; n *= 10);
	for (n /= 10; n > 0; w %= n, n /= 10)
		sys[col++] = w / n + '0';
	for (n = 10; h / n; n *= 10);
	for (n /= 10; n > 0; h %= n, n /= 10)		sys[lin++] = h / n + '0';

	system(sys);		//�ܼ� ũ�� ����
}

//Ŀ�� �����
void cursor(char a) {
	CONSOLE_CURSOR_INFO cur = { 0, };
	cur.dwSize = 2;
	cur.bVisible = a;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}

//Ŀ�� �̵�
void xy(char x, char y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//���� �Լ�
void color(unsigned char col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}

//���� �Լ�
void clear(char x, char y) {
	xy(2 * x, y);		printf("  ");
}

//���
void print() {
	color(White);
	xy(L, 0);		printf("%3d", (clock() - ms) / 1000);
	for (char a = 0; a < L; a++) {
		xy(2 * a, obj[a].y);
		printf(sha[1]);
	}
}

//��ֹ� ����
void obstacle(char i) {
	unsigned char r = rand();

	obj[i] = { 0, 1,r % Range + MIS,clock() };
}

//�÷��̾� ǥ��
void player() {
	color(Red);
	xy(2 * x, y);
	printf(sha[0]);
}

//Ű �Է�
void key() {
	char k = _getch();

	if (k == -32) {
		k = _getch();
		clear(x, y);
		if (k == 75) {
			if (x)			x--;		//��
		}
		else if (k == 77) {
			if (x < L - 1)	x++;		//��
		}
		player();
	}
}

//Ȯ��
void check(int t) {
	for (char a = 0; a < L; a++) {
		if (t - obj[a].t > sec / obj[a].speed) {
			clear(a, obj[a].y++);
			obj[a].t = clock();
			if (obj[a].y == H)	obstacle(a);
		}
	}
}

//�ʱ�ȭ
void reset() {
	console(W, H);		//�ܼ� ũ�� ����
	cursor(0);		//Ŀ�� ����
	srand(time(NULL));
	x = PSX, y = H - 1;		//�÷��̾� ��ġ �ʱ�ȭ
	player();		//�÷��̾� ��ġ ǥ��
	for (char a = 0; a < L; a++) obstacle(a);
	ms = clock();
	color(White);
	xy(L- 5, 0);	printf("����:");
}

//Ÿ��Ʋ ���
void title() {
	int tim = clock();
	char name[] = { "21628001 �����" };
	char start[] = { "PRESS ANY KEY TO START" };
	char vis = 1;
	char x, y;
	const char w = 100;

	console(w, H);
	x = y = 1;
	xy(x, y++);	printf("������ ��                  ��  ��  �������              ��             ��              ��");
	xy(x, y++);	printf("    ��     ��      �����    ��  ��  ��        ��   ������ ��     ��      ��   ������ ��");
	xy(x, y++);	printf("  ��  ��   ���  ��        ��  ��  ��  ��        ��     ��  ��   �� ������  ��           �� ��");
	xy(x, y++);	printf(" ��    ��  ��    ��        ��  ����  �������     ��  ��   ��             ��          ��  ��");
	xy(x, y++);	printf("��      �� ��    ��        ��  ��  ��                 ������ ��  �����   ����     ��   ��");
	xy(x, y++);	printf("                   �����    ��  �� ��������             �� ��      ��  ��        ��    ��");
	xy(x, y++);	printf("  ������                   ��  ��       ��                       �����   ��       ��     ��");
	xy(x, y++);	printf("��          ��                          ������                              ��              ��");
	xy(x, y++);	printf("��          ��                                  ��                              ��");
	xy(x, y++);	printf("  ������                            ������");
	xy(x, y++);	printf("                                        ��");
	xy(x, y++);	printf("                                        ������");
	cursor(0);

	x = (w - sizeof(name)) / 2;	y += 2;
	xy(x, y);	printf("%s", name);

	x = (w - sizeof(start)) / 2;	y += 2;

	while (1) {
		if (clock() - tim >= 500) {
			vis = !vis;
			tim = clock();
			xy(x, y);
			if (vis)		printf("%s", start);
			else		printf("                      ");
		}
		if (_kbhit()) {
			_getch();
			break;
		}
	}
}

//����
char death() {
	char k;

	color(White);
	xy(W / 3, H / 2);	printf("�����? Y/N");
	while (1) {
		k = _getch();
		if (k == 'y' || k == 'Y')			return 1;
		else if (k == 'n' || k == 'N')		return 0;
	}
}

//����
void game() {
	char dl = H - 1;

	while (1) {
		if (_kbhit())		key();
		check(clock());
		if (obj[x].y == dl) {
			if (death())	break;
			else			exit(0);
		}
		print();
	}
}

int main() {
	title();
	while (1) {
		reset();
		game();
	}
}