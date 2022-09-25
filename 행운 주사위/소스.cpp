#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<stdlib.h>
#define W 100		//�ܼ� ���� ũ��
#define H 30		//�ܼ� ���� ũ��
#define P 2			//�÷��̾� ��
#define MDI 15		//�ֻ��� �ִ� ����
#define MSH 6		//���� �ִ� ����
#define MHP 10		//����� �ִ� ��
#define GAP H - 3		//�� ��� ��ġ ����
#define White 15		//����
#define Blue 9		//�Ķ���
#define Yellow 14		//�����
#define Green 10		//���λ�
#define BGC	16		//���� ��
#define PX W / 3		//���� ��� ĭ
#define PY H / 2		//���� ���
#define DPX W / 2 - MDI		//�ֻ��� ��� ĭ
#define DPY 3		//�ֻ��� ��� ��
#define DK 4		//�ֻ��� ����
#define MTD 5		//�ִ�� ������ �ִ� �ֻ��� ����
#define Sec 1000		//��� �ð�

char remD[] = { "���� �ֻ���: �� X %2d" };
char t;		//��
char dx;		//�ֻ��� ���� ���� ��ǥ

struct data
{
	char dice;
	char shi;
	char hp;
}pla[P];

struct die {
	char y;
	char k;
}di[MTD];

//Ŀ�� �̵�
void xy(char X, char Y) {
	COORD pos;
	pos.X = X;
	pos.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//Ŀ�� �����
void cursor() {
	CONSOLE_CURSOR_INFO cur = { 0, };
	cur.dwSize = 1;
	cur.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}

//���� �Լ�
void color(unsigned char col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}

//�� ����
void clear(char y) {
	xy(0, y);
	for (char a = 0; a < W; a++)		printf(" ");
}

//Ÿ��Ʋ ���
void title() {
	int tim = clock();
	char vis = 1;
	char x = 5, y = 8;
	char name[] = { "21628001 �����" };
	char start[] = { "PRESS ANY KEY TO START" };

	system("mode con cols=100 lines=30");
	cursor();
	xy(x, y++);		printf("��       ��      ��   ����� ��   �� ��      ��   ����    ����   ����� ������");
	xy(x, y++);		printf("��       ��      ��  ��        ��  ��  ��      ��   ��   ��     ��    ��        ��");
	xy(x, y++);		printf("��       ��      �� ��         �� ��    ��    ��    ��    ��    ��   ��         ��");
	xy(x, y++);		printf("��       ��      �� ��         ���      ��  ��     ��     ��   ��   ��         ������");
	xy(x, y++);		printf("��       ��      �� ��         ���       ���      ��     ��   ��   ��         ��");
	xy(x, y++);		printf("��       ��      �� ��         �� ��       ��       ��    ��    ��   ��         ��");
	xy(x, y++);		printf("��        ��    ��   ��        ��  ��      ��       ��   ��     ��    ��        ��");
	xy(x, y++);		printf("�����   ����     ����� ��   ��     ��       ����    ����   ����� ������");

	x = (W - sizeof(name)) / 2;	y += 2;
	xy(x, y);	printf("%s", name);

	x = (W - sizeof(start)) / 2;	y += 2;
	
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

//�ֻ��� ���� ���
void dice() {
	char x = W - (sizeof(remD));		//���� ũ�� ��ŭ �ڿ��� ���
	char y = H - 1;		//�ܼ� �� �ؿ� ���
	char a = 0;

	if (t)		xy(0, 0);
	else		xy(x, y);

	printf(remD, pla[t].dice);		//�ش� �÷��̾��� �ֻ��� ���� ���

	x = DPX;
	if (t)		y = DPY;
	else		y = H - 4;

	xy(x, y);		color(Yellow);
	for (; a < pla[t].dice; a++)		printf("��");		//�����ִ� �ֻ��� ���
	for (; a < MDI; a++)		printf("  ");		//����� �ֻ��� ����
	color(White);
}

//���� ���� ���
void shield() {
	char s;
	char x = W / 2 - MSH - 1;
	char y = 0;
	char gap = H - 2;

	if (t)		xy(x, y);
	else		xy(x, y + gap);

	for (s = 0; s < pla[t].shi; s++)		printf("��");		//������ �ִ� ���� ���� ��ŭ ���
	for (; s < MSH; s++)			printf("��");			//�� ���� ĭ ���� ��ŭ ���
}

//����� ���
void HP() {
	char c[] = { "    / 10  " };		//����� ���� ǥ�� ���ڿ�
	char hp = pla[t].hp;
	char x = (W - sizeof(c)) / 2;
	char y = 1;
	char gap = H - 2;		//���� ��� �� ����
	char i = sizeof(c) / 4;		//�ʱ�ȭ�� ���ڿ� �ε��� ��ġ

	if (t)		xy(x, y);
	else		xy(x, y + gap);

	if (hp == 10) {		//������� 10�� ��� 
		c[i - 1] = '1';
		c[i] = '0';
	}
	else		c[i] = hp + '0';		//���� ��������� �ʱ�ȭ

	color(White + Blue * BGC);
	for (i = 0; i < hp; i++)		printf("%c", c[i]);		//���� ����� ǥ��
	color(White);
	for (; i <= MHP; i++)		printf("%c", c[i]);		//���� ����� ǥ��
}

//���� ���
void print() {
	dice();		//�ֻ��� ���
	shield();		//���� ���
	HP();		//����� ���
}

//���� ����
void turn() {
	t = rand() % P;		//���� �������� ����

	xy(PX, PY);
	printf("����� ");
	if (t)		printf("�İ��Դϴ�.");
	else		printf("�����Դϴ�.");

	Sleep(2 * Sec);		//��� �ð�
	clear(PY);
}

//���� ���� �Լ�
void remove(char x,char y) {
	xy(x, y);
	printf("  ");
}

//�ֻ��� ������
void throwDice(char n) {
	const float frame = 10;		//������
	const char spd = 5;		//�ֻ��� �ӵ�
	const char x = PX + 2 * pla[t].dice + 2;		//�ֻ��� ��� ���� ��ġ
	const char m = 3;		//�ֻ��� �ּ� �̵� �Ÿ�
	short delay = Sec / (spd * frame);
	char y;		//�ֻ��� ���� ��ǥ
	char ran = H / 4;		//���� ��ǥ ����
	float d[MTD];

	dice();		//�ֻ��� ���� ���
	for (char a = 0; a < n; a++)			di[a].y = rand() % ran + m;
	dx = x;
	color(Yellow);		//�ֻ��� �������� �߿��� ��������� ���
	if (t) {
		y = DPY + 1;
		for (char a = 0; a < frame; a++) {
			for (char b = 0; b < n; b++) {
				d[b] = y + (di[b].y / frame) * a;
				xy(x + 2 * b, d[b] );
				printf("��");
			}	
			Sleep(delay);
			for (char b = 0; b < n; b++)		remove(x + 2 * b, b[d]);
		}
	}
	else {
		y = H - 5;
		for (char a = 0; a < frame; a++) {
			for (char b = 0; b < n; b++) {
				d[b] = y - (di[b].y / frame) * a;
				xy(x + 2 * b, d[b]);
				printf("��");
			}
			Sleep(delay);
			for (char b = 0; b < n; b++)		remove(x + 2 * b, b[d]);
		}
	}
	for (char a = 0; a < n; a++) {
		if (t)		di[a].y = y + di[a].y;
		else		di[a].y = y - di[a].y;
		xy(x + 2 * a, di[a].y);
		color(Green + di[a].k);
		printf("��");
	}
	color(White);
	Sleep(Sec / 2);
}

//�ֻ��� ������
void roll() {
	char d[DK] = { 0 };		//�ε��� - 0: ����, 1: ����, 2: �ذ�, 3: ����
	char n;
	
	clear(PY);
	for (n = 0; n < MTD;) {
		di[n].k = rand() % DK;
		d[di[n].k]++;
		n++;
		if(!--pla[t].dice)		break;
	}
	throwDice(n);

	for (char a = 0; a < DK; a++) {
		xy(PX, PY);
		if (d[a]) {
			if (a == 0) {
				printf("���� X %d ", d[a]);
				pla[t].dice += d[a];
			}
			else if (a == 1) {
				printf("���� X %d ", d[a]);
				pla[t].shi += d[a];
				if (pla[t].shi > MSH)		pla[t].shi = MSH;
			}
			else if (a == 2) {
				printf("�ذ� X %d ", d[a]);
				for (char b = 0; b < d[a]; b++) {
					if (pla[t].shi)	pla[t].shi--;
					else			pla[t].hp--;
				}
				if (pla[t].hp <= 0) {
					pla[t].hp = 0;
					return;
				}
			}
			else if (a == 3) {
				printf("���� X %d ", d[a]);
				for (char b = 0; b < d[a]; b++) {
					if (pla[!t].shi)	pla[!t].shi--;
					else				pla[!t].hp--;
				}
				if (pla[!t].hp <= 0) {
					pla[!t].hp = 0;
					return;
				}
			}
			Sleep(Sec);
			for (char b = 0; b < n; b++)
				if (di[b].k == a)		remove(dx + 2 * b, di[b].y);
			print();
			//clear(PY);
		}
	}
	//for (char a = 0; a < n; a++)		remove(dx + 2 * a, di[a].y);
}

//���� ���� Ȯ��
char check() {
	char di = 0;
	char hp = 1;

	t = !t;		//�� �ٲٱ�
	print();		//���� ���

	for (char a = 0; a < P; a++) {
		di += pla[a].dice;
		hp *= pla[a].hp;
	}
	if (!di)		return 0;
	if (!hp)		return 0;

	return 1;
}

//��� ���
char result() {
	Sleep(Sec);
	print();	t = !t;		print();

	clear(PY);
	xy(PX, PY);

	if (pla[0].hp > pla[1].hp)			printf("�̰���ϴ�.");
	else if (pla[0].hp < pla[1].hp)		printf("�����ϴ�.");
	else			printf("�����ϴ�.");

	xy(PX, PY + 1);		printf("����: ESC");
	if (_getch() == 27)		return 0;

	return 1;
}

//���� ���
void notice() {
	xy(0, H - 5);
	for (char a = 0; a < 4; a++) {
		printf("\n");
		color(Green + a);
		printf("��:");
		if (a == 0)			printf("����");
		else if (a == 1)	printf("����");
		else if (a == 2)	printf("�ذ�");
		else if (a == 3)	printf("����");
	}
	color(White);
}

//�ʱ�ȭ
void reset() {
	system("cls");
	color(15);
	notice();

	for (t = 0; t < P; t++) {
		pla[t].dice = MDI;		//�ֻ��� ���� �ʱ�ȭ
		pla[t].shi = 0;		//���� ���� �ʱ�ȭ
		pla[t].hp = MHP;		//����� �ʱ�ȭ
		print();
	}
	turn();		//���� ����	
}

//����
void game() {
	char x = W / 3;
	char y = PY;
	char p;
	char k;

	do {
		//�ϼ��ϸ� �ؿ� �� �� ����
		reset();		//�ʱ�ȭ
		do {
			xy(x, y);
			if (pla[t].dice) {
				if (t) {
					printf("����� �����Դϴ�.");
					Sleep(Sec);
				}
				else {
					printf("����� �����Դϴ�. s: �׸��ϱ�");
					k = _getch();
					if (k == 's' || k == 'S')		exit(0);
				}
				roll();
			}
			else {
				printf("�ֻ����� ���� ������ ���� �������ϴ�.");
				Sleep(Sec);
				clear(y);
				continue;
			}
		} while (check());		//���� ���� ���� Ȯ��
	} while (result());		//��� Ȯ��/����� ���� Ȯ��
}

int main() {
	srand(time(NULL));
	title();
	game();

	return 0;
}