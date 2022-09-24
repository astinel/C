#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#define Garo 70 
#define Size sizeof(long long) * 8
#define PX Garo - Size
#define PY 2
#define Z '0'
#define D 4

long long num;
char bin[Size];
char sig = 1;
char type = 1;

//Ŀ�� �̵�
void xy(short X, short Y) {
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

//�� ����
void deleteL(char y) {
	xy(0, y);
	for (char a = 0; a < Garo; a++)		printf(" ");
}

//���
void name() {
	xy(20, 0);		printf("���� ��ȯ - 21628001 �����");
}

//�Է� ���� ���
void enterType() {
	deleteL(PY - 1);
	xy(0, PY - 1);		printf("�Է¸��: ");
	if (type == 0)			printf("%2d", 16);
	else if (type == 1)		printf("%2d", 10);
	else if (type == 2)		printf("%2d", 8);
	else if (type == 3)		printf("%2d", 2);
}

//�ʱ�ȭ
void reset() {
	system("mode con cols=70 lines=20");		//â ũ�� ����
	name();		//���� �̸� ���
	cursor();		//Ŀ�� �����
	enterType();
}

//������ ��ȯ
void binary() {
	unsigned long long un = num * sig;		//���� ����� ���� �ڷ��� �ٲ�
	char n = 0;		//�ڸ���

	for (char a = 0; a < Size; a++)		bin[a] = '0';

	do {
		for (char a = 0; a < D; a++) {		//2������ �ٲ�
			bin[D * n + a] += un % 2;
			un /= 2;
		}
		n++;		//�ڸ��� ����
	} while (un);

	for (char a = n * D - 1; a >= 0; a--) {		//�ڸ��� ��ŭ ������ ���
		printf("%c", bin[a]);		//�� ��Ʈ�� ���
		if (a % 4 == 0)		printf(" ");		//4�ڸ��� ���� ���
	}
}

//���� �Է� ���� ���
void number() {
	long long n = num * sig;
	char a = 0;

	deleteL(PY);		//���� �Է� �ߴ� ���� ����

	xy(PX, PY);

	if (type == 0) {
		printf("%I64x", num);
	}
	else if (type == 1) {
		if (sig == 1 || n)		printf("%64lld", n);		//-0�� �ƴҰ��
		else if (sig == -1)		printf("%64s", "-0");		//-0 �� ���
	}
	else if (type == 2) {
		printf("%I64o", n);
	}
	else if (type == 3) {
		for (char a = Size - 1,b = 1; a > 0; a--) {
			if (b) {
				if (bin[a] == '0')		printf(" ");
				else			b = 0, a++;
			}
			else		printf("%c", bin[a]);
		}
		printf("%c", bin[0]);
	}
}

//��� ǥ��
void result() {
	char x = 1, y = 5;		//����� ��ġ
	long long n = num * sig;

	for (char a = 1; a <= 5; a++)		deleteL(y + a);		//�� ����
	xy(x, y);
	printf("\n%2d����: %I64X", 16, n);			//16���� ���
	printf("\n%2d����: %lld", 10, n);		//long long �� 10���� ���
	printf("\n%2d����: %I64o", 8, n);			//8���� ���
	printf("\n%2d����: ", 2);		binary();		//2���� ���
}

//���� �ʱ�ȭ
void clear() {
	num = 0;		//���� 0���� �ʱ�ȭ
	sig = 1;		//��ȣ ���
}

//���� ���� Ȯ��
void check(char c) {
	if (type == 0) {		//16����
		if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) {
			num *= 16;
			if (c >= '0' && c <= '9')			num += (c - '0');
			else if (c >= 'a' && c <= 'f')		num += (c - 'a' + 10);
			else								num += (c - 'A' + 10);
		}
	}
	else if (type == 1) {		//10����
		if (c >= '0' && c <= '9') {
			num *= 10;
			num += (c - '0');
		}
	}
	else if (type == 2) {		//8����
		if (c >= '0' && c <= '7') {
			num *= 8;
			num += (c - '0');
		}
	}
	else if (type == 3) {		//2����
		if (c == '0' || c == '1') {
			num *= 2;
			num += (c - Z);
		}
	}
}

//Ű �Է�
void key() {
	const char N = 10;
	char ch;

	ch = _getch();

	if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F')) {
		check(ch);
	}
	else if (ch == 8) {
		if (!num)		sig = 1;
		if (type == 0)		num /= 16;
		else if (type == 1)	num /= 10;
		else if (type == 2)	num /= 8;
		else if (type == 3)	num /= 2;
	}
	else if (ch == '-') {
		if (!num)
			sig = -1;
	}
	else if (ch == 27) {
		clear();
	}
	else if (ch == '\r') {
		clear();
		type++;
		if (type == 4)		type = 0;
		enterType();
	}
}

int main() {
	reset();

	while (1) {
		result();
		number();
		key();
	}

	return 0;
}