#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#define W 80		//�ܼ� ���� ũ��
#define H 20		//�ܼ� ���� ũ��
#define M 5			//�ִ� ����
#define Red 12		//������
#define White 15		//�Ͼ��
#define XGap W / (M + 1)		//���� ��ġ ����
#define YGap H / (M + 1)		//���� ��ġ ����
#define LPY YGap * M		//��輱 ��� ��
#define L 7

char c[][L] = { "  ��  ", "  ��  " };
char x, y;

struct reservation
{
	char state = 0;
	char name[L] = "      ";
	char num;
}seat[M][M];

//Ŀ�� �̵�
void xy(char X, char Y) {
	COORD pos;
	pos.X = X;
	pos.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//Ŀ�� �����
void cursor(char a) {
	CONSOLE_CURSOR_INFO cur = { 0, };
	cur.dwSize = 2;
	cur.bVisible = a;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}

//���� �Լ�
void color(unsigned char col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}

//�ܼ� ũ�� ����(����,����)
void console(char w, char h) {
	char sys[] = "mode con cols=  lines=  ";		//�ܼ� ũ�� ����
	const char col = 14;		//�ܼ� ���� ũ�� �Է� ��ġ
	const char line = 22;		//�ܼ� ���� ũ�� �Է� ��ġ

	sys[col] = w / 10 + '0';	sys[col + 1] = w % 10 + '0';		//�ܼ� ���� ũ�� �Է�
	sys[line] = h / 10 + '0';	sys[line + 1] = h % 10 + '0';		//�ܼ� ���� ũ�� �Է�

	system(sys);		//�ܼ� ũ�� ����
}

//�� ����
void clear(char y) {
	xy(0, y);
	for (char a = 0; a < W; a++)		printf(" ");
}

//���ڿ�
void string(char* name, char* c) {
	for (char a = 0; a < L; a++)		name[a] = c[a];
}

//��� ����
void renew() {
	char x;
	char y = 1;
	const char fal = 1;

	for (char a = 0; a < M; a++) {
		for (char b = 0; b < M; b++) {
			if (seat[a][b].state == -1) {		//���� �����ϰ��
				if (a > 0) {		//���� �ڸ�
					seat[a - 1][b].state = fal;		//��� ���� ����
					string(seat[a - 1][b].name, c[fal]);
				}
				if (a + 1 < M) {
					seat[a + 1][b].state = fal;		//�Ʒ��� �ڸ� ���Ұ�
					string(seat[a + 1][b].name, c[fal]);
				}
				if (b > 0) {
					seat[a][b - 1].state = fal;		//���� �ڸ� ���Ұ�
					string(seat[a][b - 1].name, c[fal]);
				}
				if (b + 1 < M) {
					seat[a][b + 1].state = fal;		//������ �ڸ� ���Ұ�
					string(seat[a][b + 1].name, c[fal]);
				}
			}
		}
	}
	color(White);
	for (char a = 0; a < M; a++) {
		clear(y);
		x = 1;
		for (char b = 0; b < M; b++) {
			xy(x, y);
			printf("%s", seat[a][b].name);
			x += XGap;
		}
		y += YGap;
	}
}

//�ο���
void people(char b) {
	char gap = YGap;

	xy(x * XGap + 2, y * gap + 2);
	if (b)		printf("%3d", seat[y][x].num);
	else		printf("%7c", ' ');
}

//���
void cancel() {
	const char tru = 0;

	if (seat[y][x].state > -1) {
		renew();
		return;
	}
	seat[y][x].state = 0;
	string(seat[y][x].name, c[0]);
	if (y > 0) {		//���� �ڸ�
		seat[y - 1][x].state = tru;
		string(seat[y - 1][x].name, c[tru]);
	}
	if (y + 1 < M) {
		seat[y + 1][x].state = tru;	
		string(seat[y + 1][x].name, c[tru]);
	}
	if (x > 0) {
		seat[y][x - 1].state = tru;
		string(seat[y][x - 1].name, c[tru]);
	}
	if (x + 1 < M) {
		seat[y][x + 1].state = tru;
		string(seat[y][x + 1].name, c[tru]);
	}
	people(tru);
	renew();
}

//����
void reserve() {
	seat[y][x].state = -1;		//���� �ڸ� �����
	people(1);		//�ο��� ǥ��
	renew();		//���� ���
}

//�޴� ���
void menu() {
	char name[] = "21628001 �����";		//�й� �̸� ���ڿ�
	const char x = (W - sizeof(name)) / 2;		//�̸� ��� ��ġ�� �߰�
	char y = LPY;		//ù ��� ��

	xy(0, y);
	for (char a = 0; a < W; a++)		printf("-");		//��輱 ���
	xy(x, H - 1);		printf("%s", name);		//�̸� ���
	xy(1, H - 2);		
	printf("1: ���� ");
	printf("2: ��� ");
	printf("0: ���� ");
	printf(" �����̽���: ���� ");
	printf("����Ű: �̵�");
}

//�˸���
void notice(char n) {
	char x = 1;
	char y = LPY + 1;

	color(White);
	clear(y);
	xy(x, y);
	if (n == 0)			printf("�޴��� ������ �ּ���");
	else if (n == 1)	printf("������ �ڸ��� ������ �ּ���. ���� ���� �Ұ����� �ڸ��Դϴ�.");
	else if (n == 2)	printf("����� �ڸ��� �������ּ���");
	else if (n == 3)	printf("�̸��� �Է��� �ּ���");
	else if (n == 4)	printf("�ο��� �Է����ּ���");
	else if (n == 5)	printf("�ش��ڸ��� �����ϽǼ� �����ϴ�.");
}

//���� �Է� ����
void info(reservation* seat){
	char y = 1;
	char peo;

	notice(3);
	color(White);
	xy(XGap * M, y++);		//�̸� �Է� ���� ��ǥ
	cursor(1);		//Ŀ�� ǥ��
	string(seat->name, (char*)"      ");
	scanf("%s", seat->name);		//���ڿ� �Է� ����
	seat->name[L - 1] = 0;		//���ڿ� �ִ� ũ��� ¥��
	notice(4);
	xy(XGap * M, y);		//�ο� �Է� ���� ��ǥ
	do {
		peo = _getch() - '0';
	} while (peo > 4 || peo == 0);
	seat->num = peo;
	cursor(0);		//Ŀ�� �����
	clear(--y);
}

//�̵� �Լ�
void move(char col) {
	const char gap[2] = { XGap,YGap };		//������ ������ ��ȯ

	color(col);
	xy(x * gap[0] + 1, y * gap[1] + 1);
	printf("%s", seat[y][x].name);
}

//�̵�
void select(char b) {
	char k;

	b--;		//����: 0, ���: 1
	while (1) {
		move(Red);		//���� ��ġ ǥ��
		k = _getch();
		if (k == -32) {		//����Ű�� �Է� �ɽ�
			move(White);		//���� ��ġ ����
			k = _getch();		//���� ����
			if (k == 72) {
				if (y)		y--;		//��
			}
			else if (k == 75) {
				if (x)		x--;		//��
			}
			else if (k == 77) {
				if (x < M - 1)		x++;		//��
			}
			else if (k == 80) {
				if (y < M - 1)		y++;		//��
			}
			notice(1);
		}
		else if (k == ' ') {
			if (!b) {
				if (!seat[y][x].state) {
					info(&seat[y][x]);
					reserve();
				}
				else {
					notice(5);
					continue;
				}
			}
			else		cancel();
			break;
		}
		else if (k == '2') {
			move(White);
			break;
		}
		else if (k == '0')		exit(0);
	}
}

//Ű �Է�
void key() {
	char k;

	notice(0);
	k = _getch() - '0';
	notice(k);

	if (k == 1 || k == 2)		select(k);
	else if (k == 0)				exit(0);
}

//�ʱ�ȭ
void reset() {
	console(W, H);		//�ܼ� ũ�� ����
	cursor(0);			//Ŀ�� �����
	color(White);		//���ڻ��� ����
	menu();		//�й� �̸�, ��輱 ���
	for (char a = 0; a < M; a++)
		for (char b = 0; b < M; b++)
			string(seat[a][b].name, c[seat[a][b].state]);
	renew();		//��� ����
}

int main() {
	reset();		//�ʱ�ȭ

	while(1)	key();

	return 0;
}