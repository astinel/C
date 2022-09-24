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

//커서 이동
void xy(short X, short Y) {
	COORD pos;
	pos.X = X;
	pos.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//커서 숨기기
void cursor() {
	CONSOLE_CURSOR_INFO cur = { 0, };
	cur.dwSize = 1;
	cur.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}

//줄 삭제
void deleteL(char y) {
	xy(0, y);
	for (char a = 0; a < Garo; a++)		printf(" ");
}

//출력
void name() {
	xy(20, 0);		printf("진수 변환 - 21628001 강경운");
}

//입력 형태 출력
void enterType() {
	deleteL(PY - 1);
	xy(0, PY - 1);		printf("입력모드: ");
	if (type == 0)			printf("%2d", 16);
	else if (type == 1)		printf("%2d", 10);
	else if (type == 2)		printf("%2d", 8);
	else if (type == 3)		printf("%2d", 2);
}

//초기화
void reset() {
	system("mode con cols=70 lines=20");		//창 크기 조절
	name();		//제목 이름 출력
	cursor();		//커서 숨기기
	enterType();
}

//이진수 변환
void binary() {
	unsigned long long un = num * sig;		//음수 계산을 위해 자료형 바꿈
	char n = 0;		//자리수

	for (char a = 0; a < Size; a++)		bin[a] = '0';

	do {
		for (char a = 0; a < D; a++) {		//2진수로 바꿈
			bin[D * n + a] += un % 2;
			un /= 2;
		}
		n++;		//자리수 증가
	} while (un);

	for (char a = n * D - 1; a >= 0; a--) {		//자릿수 만큼 이진수 출력
		printf("%c", bin[a]);		//한 비트씩 출력
		if (a % 4 == 0)		printf(" ");		//4자릿수 마다 띄움
	}
}

//현재 입력 숫자 출력
void number() {
	long long n = num * sig;
	char a = 0;

	deleteL(PY);		//전에 입력 했던 정보 삭제

	xy(PX, PY);

	if (type == 0) {
		printf("%I64x", num);
	}
	else if (type == 1) {
		if (sig == 1 || n)		printf("%64lld", n);		//-0이 아닐경우
		else if (sig == -1)		printf("%64s", "-0");		//-0 일 경우
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

//결과 표시
void result() {
	char x = 1, y = 5;		//출력할 위치
	long long n = num * sig;

	for (char a = 1; a <= 5; a++)		deleteL(y + a);		//줄 삭제
	xy(x, y);
	printf("\n%2d진수: %I64X", 16, n);			//16진수 출력
	printf("\n%2d진수: %lld", 10, n);		//long long 형 10진수 출력
	printf("\n%2d진수: %I64o", 8, n);			//8진수 출력
	printf("\n%2d진수: ", 2);		binary();		//2진수 출력
}

//숫자 초기화
void clear() {
	num = 0;		//숫자 0으로 초기화
	sig = 1;		//부호 양수
}

//숫자 범위 확인
void check(char c) {
	if (type == 0) {		//16진수
		if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) {
			num *= 16;
			if (c >= '0' && c <= '9')			num += (c - '0');
			else if (c >= 'a' && c <= 'f')		num += (c - 'a' + 10);
			else								num += (c - 'A' + 10);
		}
	}
	else if (type == 1) {		//10진수
		if (c >= '0' && c <= '9') {
			num *= 10;
			num += (c - '0');
		}
	}
	else if (type == 2) {		//8진수
		if (c >= '0' && c <= '7') {
			num *= 8;
			num += (c - '0');
		}
	}
	else if (type == 3) {		//2진수
		if (c == '0' || c == '1') {
			num *= 2;
			num += (c - Z);
		}
	}
}

//키 입력
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