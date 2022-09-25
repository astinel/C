#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define L 10		//줄 수
#define W 2*L		//콘솔 너비
#define H 21		//높이
#define PSX L / 2		//시작 좌표
#define sec 200		//
#define MIS 1		//장애물 최저 낙하 속도
#define Range 3		//장애물 속도 범위
#define White 15
#define Red 12

int ms;		//시간 변수
char sha[][3] = { "♥","■" };		//형태
char x, y;		//플레이어 좌표

struct object {
	char state;
	char y;			//장애물 좌표
	char speed;		//낙하 속도
	int t;
}obj[L];

//콘솔 크기 조정(가로,세로)
void console(char w, char h) {
	char sys[] = "mode con cols=    lines=   ";
	char col = 14;		//콘솔 가로 크기 입력 위치
	char lin = 24;		//콘솔 세로 크기 입력 위치
	short n;

	for (n = 10; w / n; n *= 10);
	for (n /= 10; n > 0; w %= n, n /= 10)
		sys[col++] = w / n + '0';
	for (n = 10; h / n; n *= 10);
	for (n /= 10; n > 0; h %= n, n /= 10)		sys[lin++] = h / n + '0';

	system(sys);		//콘솔 크기 적용
}

//커서 숨기기
void cursor(char a) {
	CONSOLE_CURSOR_INFO cur = { 0, };
	cur.dwSize = 2;
	cur.bVisible = a;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}

//커서 이동
void xy(char x, char y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//색깔 함수
void color(unsigned char col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}

//삭제 함수
void clear(char x, char y) {
	xy(2 * x, y);		printf("  ");
}

//출력
void print() {
	color(White);
	xy(L, 0);		printf("%3d", (clock() - ms) / 1000);
	for (char a = 0; a < L; a++) {
		xy(2 * a, obj[a].y);
		printf(sha[1]);
	}
}

//장애물 생성
void obstacle(char i) {
	unsigned char r = rand();

	obj[i] = { 0, 1,r % Range + MIS,clock() };
}

//플레이어 표시
void player() {
	color(Red);
	xy(2 * x, y);
	printf(sha[0]);
}

//키 입력
void key() {
	char k = _getch();

	if (k == -32) {
		k = _getch();
		clear(x, y);
		if (k == 75) {
			if (x)			x--;		//좌
		}
		else if (k == 77) {
			if (x < L - 1)	x++;		//우
		}
		player();
	}
}

//확인
void check(int t) {
	for (char a = 0; a < L; a++) {
		if (t - obj[a].t > sec / obj[a].speed) {
			clear(a, obj[a].y++);
			obj[a].t = clock();
			if (obj[a].y == H)	obstacle(a);
		}
	}
}

//초기화
void reset() {
	console(W, H);		//콘솔 크기 변경
	cursor(0);		//커서 숨김
	srand(time(NULL));
	x = PSX, y = H - 1;		//플레이어 위치 초기화
	player();		//플레이어 위치 표시
	for (char a = 0; a < L; a++) obstacle(a);
	ms = clock();
	color(White);
	xy(L- 5, 0);	printf("점수:");
}

//타이틀 출력
void title() {
	int tim = clock();
	char name[] = { "21628001 강경운" };
	char start[] = { "PRESS ANY KEY TO START" };
	char vis = 1;
	char x, y;
	const char w = 100;

	console(w, H);
	x = y = 1;
	xy(x, y++);	printf("■■■■■ ■                  ■  ■  ■■■■■■              ■             ■              ■");
	xy(x, y++);	printf("    ■     ■      ■■■■    ■  ■  ■        ■   ■■■■■ ■     ■      ■   ■■■■■ ■");
	xy(x, y++);	printf("  ■  ■   ■■  ■        ■  ■  ■  ■        ■     ■  ■   ■ ■■■■■  ■           ■ ■");
	xy(x, y++);	printf(" ■    ■  ■    ■        ■  ■■■  ■■■■■■     ■  ■   ■             ■          ■  ■");
	xy(x, y++);	printf("■      ■ ■    ■        ■  ■  ■                 ■■■■■ ■  ■■■■   ■■■     ■   ■");
	xy(x, y++);	printf("                   ■■■■    ■  ■ ■■■■■■■             ■ ■      ■  ■        ■    ■");
	xy(x, y++);	printf("  ■■■■■                   ■  ■       ■                       ■■■■   ■       ■     ■");
	xy(x, y++);	printf("■          ■                          ■■■■■                              ■              ■");
	xy(x, y++);	printf("■          ■                                  ■                              ■");
	xy(x, y++);	printf("  ■■■■■                            ■■■■■");
	xy(x, y++);	printf("                                        ■");
	xy(x, y++);	printf("                                        ■■■■■");
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

//죽음
char death() {
	char k;

	color(White);
	xy(W / 3, H / 2);	printf("재시작? Y/N");
	while (1) {
		k = _getch();
		if (k == 'y' || k == 'Y')			return 1;
		else if (k == 'n' || k == 'N')		return 0;
	}
}

//게임
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