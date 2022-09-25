#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#define W 80		//콘솔 가로 크기
#define H 20		//콘솔 세로 크기
#define M 5			//최대 개수
#define Red 12		//빨강색
#define White 15		//하양색
#define XGap W / (M + 1)		//가로 위치 차이
#define YGap H / (M + 1)		//세로 위치 차이
#define LPY YGap * M		//경계선 출력 줄
#define L 7

char c[][L] = { "  ○  ", "  Ⅹ  " };
char x, y;

struct reservation
{
	char state = 0;
	char name[L] = "      ";
	char num;
}seat[M][M];

//커서 이동
void xy(char X, char Y) {
	COORD pos;
	pos.X = X;
	pos.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//커서 숨기기
void cursor(char a) {
	CONSOLE_CURSOR_INFO cur = { 0, };
	cur.dwSize = 2;
	cur.bVisible = a;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}

//색깔 함수
void color(unsigned char col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}

//콘솔 크기 조정(가로,세로)
void console(char w, char h) {
	char sys[] = "mode con cols=  lines=  ";		//콘솔 크기 조절
	const char col = 14;		//콘솔 가로 크기 입력 위치
	const char line = 22;		//콘솔 세로 크기 입력 위치

	sys[col] = w / 10 + '0';	sys[col + 1] = w % 10 + '0';		//콘솔 가로 크기 입력
	sys[line] = h / 10 + '0';	sys[line + 1] = h % 10 + '0';		//콘솔 세로 크기 입력

	system(sys);		//콘솔 크기 적용
}

//줄 삭제
void clear(char y) {
	xy(0, y);
	for (char a = 0; a < W; a++)		printf(" ");
}

//문자열
void string(char* name, char* c) {
	for (char a = 0; a < L; a++)		name[a] = c[a];
}

//출력 갱신
void renew() {
	char x;
	char y = 1;
	const char fal = 1;

	for (char a = 0; a < M; a++) {
		for (char b = 0; b < M; b++) {
			if (seat[a][b].state == -1) {		//예약 상태일경우
				if (a > 0) {		//위쪽 자리
					seat[a - 1][b].state = fal;		//사용 상태 변경
					string(seat[a - 1][b].name, c[fal]);
				}
				if (a + 1 < M) {
					seat[a + 1][b].state = fal;		//아래쪽 자리 사용불가
					string(seat[a + 1][b].name, c[fal]);
				}
				if (b > 0) {
					seat[a][b - 1].state = fal;		//왼쪽 자리 사용불가
					string(seat[a][b - 1].name, c[fal]);
				}
				if (b + 1 < M) {
					seat[a][b + 1].state = fal;		//오른쪽 자리 사용불가
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

//인원수
void people(char b) {
	char gap = YGap;

	xy(x * XGap + 2, y * gap + 2);
	if (b)		printf("%3d", seat[y][x].num);
	else		printf("%7c", ' ');
}

//취소
void cancel() {
	const char tru = 0;

	if (seat[y][x].state > -1) {
		renew();
		return;
	}
	seat[y][x].state = 0;
	string(seat[y][x].name, c[0]);
	if (y > 0) {		//위쪽 자리
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

//예약
void reserve() {
	seat[y][x].state = -1;		//현재 자리 사용중
	people(1);		//인원수 표시
	renew();		//새로 출력
}

//메뉴 출력
void menu() {
	char name[] = "21628001 강경운";		//학번 이름 문자열
	const char x = (W - sizeof(name)) / 2;		//이름 출력 위치는 중간
	char y = LPY;		//첫 출력 줄

	xy(0, y);
	for (char a = 0; a < W; a++)		printf("-");		//경계선 출력
	xy(x, H - 1);		printf("%s", name);		//이름 출력
	xy(1, H - 2);		
	printf("1: 예약 ");
	printf("2: 취소 ");
	printf("0: 종료 ");
	printf(" 스페이스바: 선택 ");
	printf("방향키: 이동");
}

//알림말
void notice(char n) {
	char x = 1;
	char y = LPY + 1;

	color(White);
	clear(y);
	xy(x, y);
	if (n == 0)			printf("메뉴를 선택해 주세요");
	else if (n == 1)	printf("예약할 자리를 선택해 주세요. Ⅹ는 선택 불가능한 자리입니다.");
	else if (n == 2)	printf("취소할 자리를 선택해주세요");
	else if (n == 3)	printf("이름을 입력해 주세요");
	else if (n == 4)	printf("인원을 입력해주세요");
	else if (n == 5)	printf("해당자리에 예약하실수 없습니다.");
}

//정보 입력 받음
void info(reservation* seat){
	char y = 1;
	char peo;

	notice(3);
	color(White);
	xy(XGap * M, y++);		//이름 입력 받을 좌표
	cursor(1);		//커서 표시
	string(seat->name, (char*)"      ");
	scanf("%s", seat->name);		//문자열 입력 받음
	seat->name[L - 1] = 0;		//문자열 최대 크기로 짜름
	notice(4);
	xy(XGap * M, y);		//인원 입력 받을 좌표
	do {
		peo = _getch() - '0';
	} while (peo > 4 || peo == 0);
	seat->num = peo;
	cursor(0);		//커서 숨기기
	clear(--y);
}

//이동 함수
void move(char col) {
	const char gap[2] = { XGap,YGap };		//정수형 값으로 변환

	color(col);
	xy(x * gap[0] + 1, y * gap[1] + 1);
	printf("%s", seat[y][x].name);
}

//이동
void select(char b) {
	char k;

	b--;		//예약: 0, 취소: 1
	while (1) {
		move(Red);		//현재 위치 표시
		k = _getch();
		if (k == -32) {		//방향키가 입력 될시
			move(White);		//이전 위치 삭제
			k = _getch();		//방향 구분
			if (k == 72) {
				if (y)		y--;		//상
			}
			else if (k == 75) {
				if (x)		x--;		//좌
			}
			else if (k == 77) {
				if (x < M - 1)		x++;		//우
			}
			else if (k == 80) {
				if (y < M - 1)		y++;		//하
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

//키 입력
void key() {
	char k;

	notice(0);
	k = _getch() - '0';
	notice(k);

	if (k == 1 || k == 2)		select(k);
	else if (k == 0)				exit(0);
}

//초기화
void reset() {
	console(W, H);		//콘솔 크기 조정
	cursor(0);			//커서 숨기기
	color(White);		//글자색은 햐양색
	menu();		//학번 이름, 경계선 출력
	for (char a = 0; a < M; a++)
		for (char b = 0; b < M; b++)
			string(seat[a][b].name, c[seat[a][b].state]);
	renew();		//출력 갱신
}

int main() {
	reset();		//초기화

	while(1)	key();

	return 0;
}