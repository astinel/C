#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#define N 6		//���� ����
#define ML 5		//���� �ִ� ����
#define MAX 45		//�ִ�
#define MIN 1		//�ּڰ�
#define Red 12		//��������
#define White 15	//�Ͼ����
#define lineY 20	//�� ��ġ
#define C 9

char ans[N + 1];		//���� ��ȣ(�⺻ ���� + ���ʽ� ���� �Ѱ�)
char n;			//�Է� ��ȣ
char lot;		//���� ���� ����
char inp;		//�Էµ� ���� ����

//�Էµ� ��ȣ ����ü
struct number
{
	char num[N];		//�Էµ� ��ȣ
	unsigned char sum;		//�Էµ� ��ȣ�� ��
	int mul;		//�Էµ� ��ȣ�� ��
};
number num[ML];

//Ŀ�� �̵�
void xy(short x, short y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//Ŀ�� �����
void cursor() {
	CONSOLE_CURSOR_INFO cur = { 0, };
	cur.dwSize = 1;
	cur.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}

//�� ����
void clear(char y) {
	xy(0, y);
	for (char a = 0; a < 80; a++)		printf(" ");
}

//���� �Լ�
void color(char col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}

//����
void sort(char* arr) {
	char sma;
	char sub;		//���� ����

	for (char a = 0; a < N - 1; a++) {
		sma = a;
		for (char b = a + 1; b < N; b++)
			if (arr[sma] > arr[b])		sma = b;
		if (a != sma) {
			sub = arr[a];
			arr[a] = arr[sma];
			arr[sma] = sub;
		}
	}
}

//���� ���� �Լ�
void random(char* arr,char n) {
	char num[MAX];
	char i;
	
	for (char a = 0; a < MAX; a++)		num[a] = a + MIN;		//�ּڰ����� �ִ񰪱��� �迭�� �ʱ�ȭ
	for (char a = 0; a < n;) {		//������ ���� ��ŭ ���� ����
		i = rand() % (MAX - a);		//������ ���� ���ڿ��� ���� ����
		arr[a++] = num[i];
		num[i] = num[MAX - a];		//������ ���� �ε��� �������� ����
	}
	sort(arr);
}

//�迭 �� �Լ�
char equal(char* p) {
	char ar1[N];
	char ar2[N];
	char n = N;		//�迭�� �����ִ� ��ȣ ����
	char c = 0;		//�Ȱ��� ��ȣ ����

	//���� �迭 �ʱ�ȭ
	for (char a = 0; a < N; a++) {
		ar1[a] = ans[a];
		ar2[a] = *(p + a);
	}

	//���� ���� �ʿ�
	for (char a = 0; a < n; a++) {
		for (char b = 0; b < n; b++) {
			if (ar1[a] == ar2[b]) {		//�迭�� �ִ� �� ��ȣ�� ���� ���
				c++;	n--;
				//�迭�� �ش� ��ȣ ����
				ar1[a] = ar1[n];
				ar2[b] = ar2[n];
				a--;		//���� ����
				break;
			}
		}
	}

	return c;
}

//���� ���� �Լ�
void rank() {
	char cou;		//ī��Ʈ ����
	char ran[ML] = {0};		//����

	for (char a = 0; a < lot; a++) {
		cou = equal(num[a].num);		//�Էµ� ��ȣ���� ����� ���� ��ȣ ���� ����

		if (cou == 6)		ran[a] = 1;		//�� ���߸� 1��
		else if (cou >= 3) {		//3���̻� ���� ���
			ran[a] = 8 - cou;		//���� ������ ���� ���� ����
			if (ran[a] == 3)		//3���ϰ�� �� ����
				for (char b = 0; b < N; b++)		//���ʽ� ���� ��
					if (ans[N] == num[a].num[b])		ran[a] = 2;		//���ʽ� ���ڿ� ��ġ�ϸ� 2��
		}
		//���� ���� ���
		xy(31, 5 + 2 * a);
		if (ran[a])			printf("%d ��", ran[a]);		
		else			printf("X");
	}
}

//��輱 ���
void line() {
	const char L = 80;		//�ܼ��� ���� ����

	xy(0, lineY);		//���� ����� ��ġ
	for (char a = 0; a < L; a++)		printf("-");		//�� ���

	xy(1, lineY + 3);
	printf("����Ű: ��ȣ ����  SPACE BAR: ���� ��ȣ �Է�  ENTER: ���� ����");
	xy(1, lineY + 4);
	printf("1: ���� �Ϸ�  ");
	printf("2: ��ȣ �ʱ�ȭ  ");
	printf("3: ���� ���� ����  ");
	printf("4: ����  ");
}

//�˸� �� ���
void notice(char n) {
	char x, y;		//��� �� ��ġ

	x = 1;	y = lineY + 1;
	clear(y);		//�ش� �� ����
	xy(x, y);
	
	if (n == 0)				printf("�ٽ� �����Ͻ÷��� �ƹ�Ű�� �����ּ���");
	else if (n == 1) {
		if (inp < N)		printf("%d���� ���ڸ� �Է��� �ּ���", N - inp);
		else				printf("�Էµ� ���ڸ� Ȯ���� �ּ���");
	}
	else if (n == 2)		printf("�� �̻� �Է¹��� �� �����ϴ�.");
	else if (n == 3)		printf("�ߺ��� ���ڰ� �Է���ϴ�.");
	else if (n == 4)		printf("�ߺ��� ���� ������ �̹� �ֽ��ϴ�.");
	else if (n == 5)		printf("�Է��� �Ϸ��� �ּ���");
}

//��ȣ�� ��� �Լ�
void print(char n) {
	char x = 40, y = 1;		//���� ��� ��ġ

	xy(x, y);
	for (char a = 0; a < N; a++) {
		printf("%4d", num[lot].num[a]);		//���� �Է� ��ȣ
	}
	xy(x, y+=3);		//��ȣ ���
	for (char a = MIN; a <= MAX; a++) {
		if (n == a)		color(Red);		//���� ���� ��ȣ�� ������
		else			color(White);		//�������� ���
		printf("%2d ", a);		//��ȣ ���
		if (a % C == 0)		xy(x, ++y);		//���� ���� ���� �� �� ���
	}
	color(White);
}


//�Էµ� ���� ���
void lotto() {
	char x = 5, y = 3;		//�ʱ� ��� ��ġ

	xy(x, y);	printf("�Էµ� ��ȣ");
	y += 2;
	xy(x - 2, y + 2 * lot);
	printf("%d: ", lot + 1);
	sort(num[lot].num);		//ũ�� ������ ����
	for (char a = 0; a < N; a++)		printf("%3d", num[lot].num[a]);		//�Էµ� ��ȣ ���
}

//�Էµ� ��ȣ �ʱ�ȭ
void resetNum(char lot) {
	for (char c = 0; c < N; c++){
		num[lot].num[c] = 0;		//�Էµ� ��ȣ �ʱ�ȭ
		num[lot].sum = 0;
		num[lot].mul = 1;
	}
	inp = 0;
}

//�ߺ� Ȯ��
char check() {
	num[lot].mul = 1;		//�Էµ� ��ȣ�� ��
	num[lot].sum = 0;		//�Էµ� ��ȣ�� ��
	
	for (char a = 0; a < N; a++) {
		num[lot].mul *= num[lot].num[a];
		num[lot].sum += num[lot].num[a];
	}
	if (lot) {		//�Էµ� ��ȣ ������ ���� ���
		for (char a = 0; a < lot; a++) {		//���� ���� ��ŭ �ݺ�
			if (num[lot].mul == num[a].mul)		//�Էµ� ��ȣ�� �� ��
				if (num[lot].sum == num[a].sum) {		//�Էµ� ��ȣ�� �� ��
					resetNum(lot);		//�Էµ� ��ȣ �ʱ�ȭ
					notice(4);		//�ߺ� ���� ����
					return 1;
				}
		}
	}
	return 0;
}

//�Է� ��ȣ �ߺ� Ȯ��
char numCheck() {
	for (char a = 0; a < inp; a++)
		if (num[lot].num[a] == n)		return 1;

	return 0;
}

//���� ����
void answer() {
	xy(0, 15);

	printf("����: ");
	for (char a = 0; a < N; a++)		printf("%3d", ans[a]);		//���� ��ȣ ����
	printf(" + %d", ans[N]);
}

//�ʱ�ȭ
void reset() {
	system("cls");		//ȭ�� ����
	system("mode con cols=80 lines=25");		//�ܼ�â ũ�� ����
	cursor();		//Ŀ�� �����
	color(White);
	line();		//��輱 ���
	random(ans, N + 1);		//�ߺ� ���� ���� ����
	for (char a = 0; a < N; a++)		resetNum(a);		//�Էµ� ��ȣ�� �ʱ�ȭ
	n = 1;
	lot = inp = 0;
}

//Ű �Է� �Լ�
char key() {
	char k;		//�Է� ���� Ű ����
	char no = 1;

	k = _getch();		//�Է� ���� Ű
	if (k == -32) {		//�Է� ���� Ű�� ����Ű�� ���
		k = _getch();		//�߰� �Է� ����
		if (k == 72)			n -= C;		//��
		else if (k == 75)		n--;		//��
		else if (k == 77)		n++;		//��
		else if (k == 80)		n += C;		//��

		if (n <= 0)			n += MAX;		//��ȣ�� 0������ ��� �ִ��� ����
		else if (n > MAX)	n -= MAX;		//��ȣ�� �ִ� ���� Ŭ ��� �ִ��� ��
	}
	else if (k == ' ') {		//�����̽��ٸ� �Է� ���� ���
		if (numCheck())		no = 3;
		else if (inp == N)		no = 2;		//�� �̻� �Է� ������ ���� ���
		else 			num[lot].num[inp++] = n;		//��ȣ �Է� ����
	}
	else if (k == '\r') {		//���͸� �Է� ���� ���
		no = 5;
		if (inp == N) {		//�Է��� �� �� ���
			if (!check())		//�ߺ� Ȯ��
			{
				lotto();		//�Էµ� ��ȣ ���
				lot++;		//���� ���� ����
				no = 1;
			}
			else	no = 4;
			if (lot == ML)		return 0;		//������ �ִ� ������ �Ȱ����� ���� ����
			inp = 0;		//�Էµ� ��ȣ ���� �ʱ�ȭ
		}
	}
	else if (k == '1') {		//1�� �Է� ���� ��� 
		return 0;		//���� ����
	}
	else if (k == '2') {		//2�� �Է� ���� ���
		resetNum(lot);		//�ʱ�ȭ
	}
	else if (k == '3') {		//3�� �Է� ���� ���
		random(num[lot].num,N);
		inp = N;
	}
	else if (k == '4') {
		exit(0);
	}
	else if (k == '0') {		//0�� �Է� ���� ���
		answer();		//���� ����
	}

	notice(no);

	return 1;
}

//���� ��÷
void start() {
	while(1){
		reset();		//�ʱ�ȭ
		notice(1);
		do {
			print(n);		//��ȣ ���
		} while (key());		//Ű �Է� ����

		notice(0);
		rank();		//���� ���
		answer();

		_getch();
	}
}

//Ÿ��Ʋ ���
void title() {
	char x = 12;
	char y = 5;

	system("mode con cols=80 lines=25");

	xy(x, y++);		printf("��      ��              ��      ��           ��      ��");
	xy(x, y++);		printf("������  ������  ��  ������   ������  ��");
	xy(x, y++);		printf("��      ��          ��  ��      ��           ��      ��");
	xy(x, y++);		printf("������              ��    ��  ��       ��  ��  ���");
	xy(x, y++);		printf("    ��      ������  ��  ��      ��   ��      ��  ��");
	xy(x, y++);		printf("������      ��      ��                           ��");
	xy(x, y++);		printf("            ��  ��  ����  ������     ������");
	xy(x, y++);		printf("������  ��          ��      ��         ��      ��");
	xy(x, y++);		printf("        ��  ������  ��      ��         ������");
	xy(2*x, y+=2);	printf("    21628001 �����");
	xy(2*x, y+=2);	printf("PRESS ANY KEY TO START");

	_getch();
}

int main() {
	srand(time(NULL));
	//title();
	start();		//���� ����

	return 0;
}