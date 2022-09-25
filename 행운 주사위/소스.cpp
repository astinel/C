#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<stdlib.h>
#define W 100		//콘솔 가로 크기
#define H 30		//콘솔 세로 크기
#define P 2			//플레이어 수
#define MDI 15		//주사위 최대 개수
#define MSH 6		//방패 최대 개수
#define MHP 10		//생명력 최대 값
#define GAP H - 3		//줄 출력 위치 차이
#define White 15		//햐양색
#define Blue 9		//파란색
#define Yellow 14		//노란색
#define Green 10		//연두색
#define BGC	16		//배경색 값
#define PX W / 3		//정보 출력 칸
#define PY H / 2		//정보 출력
#define DPX W / 2 - MDI		//주사위 출력 칸
#define DPY 3		//주사위 출력 줄
#define DK 4		//주사위 종류
#define MTD 5		//최대로 던질수 있는 주사위 개수
#define Sec 1000		//대기 시간

char remD[] = { "남은 주사위: ■ X %2d" };
char t;		//턴
char dx;		//주사위 가로 시작 좌표

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

//커서 이동
void xy(char X, char Y) {
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

//색깔 함수
void color(unsigned char col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}

//줄 삭제
void clear(char y) {
	xy(0, y);
	for (char a = 0; a < W; a++)		printf(" ");
}

//타이틀 출력
void title() {
	int tim = clock();
	char vis = 1;
	char x = 5, y = 8;
	char name[] = { "21628001 강경운" };
	char start[] = { "PRESS ANY KEY TO START" };

	system("mode con cols=100 lines=30");
	cursor();
	xy(x, y++);		printf("■       ■      ■   ■■■■ ■   ■ ■      ■   ■■■    ■■■   ■■■■ ■■■■■");
	xy(x, y++);		printf("■       ■      ■  ■        ■  ■  ■      ■   ■   ■     ■    ■        ■");
	xy(x, y++);		printf("■       ■      ■ ■         ■ ■    ■    ■    ■    ■    ■   ■         ■");
	xy(x, y++);		printf("■       ■      ■ ■         ■■      ■  ■     ■     ■   ■   ■         ■■■■■");
	xy(x, y++);		printf("■       ■      ■ ■         ■■       ■■      ■     ■   ■   ■         ■");
	xy(x, y++);		printf("■       ■      ■ ■         ■ ■       ■       ■    ■    ■   ■         ■");
	xy(x, y++);		printf("■        ■    ■   ■        ■  ■      ■       ■   ■     ■    ■        ■");
	xy(x, y++);		printf("■■■■   ■■■     ■■■■ ■   ■     ■       ■■■    ■■■   ■■■■ ■■■■■");

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

//주사위 개수 출력
void dice() {
	char x = W - (sizeof(remD));		//글자 크기 만큼 뒤에서 출력
	char y = H - 1;		//콘솔 맨 밑에 출력
	char a = 0;

	if (t)		xy(0, 0);
	else		xy(x, y);

	printf(remD, pla[t].dice);		//해당 플레이어의 주사위 정보 출력

	x = DPX;
	if (t)		y = DPY;
	else		y = H - 4;

	xy(x, y);		color(Yellow);
	for (; a < pla[t].dice; a++)		printf("■");		//남아있는 주사위 출력
	for (; a < MDI; a++)		printf("  ");		//사용한 주사위 삭제
	color(White);
}

//방패 개수 출력
void shield() {
	char s;
	char x = W / 2 - MSH - 1;
	char y = 0;
	char gap = H - 2;

	if (t)		xy(x, y);
	else		xy(x, y + gap);

	for (s = 0; s < pla[t].shi; s++)		printf("●");		//가지고 있는 방패 개수 만큼 출력
	for (; s < MSH; s++)			printf("○");			//빈 방패 칸 개수 만큼 출력
}

//생명력 출력
void HP() {
	char c[] = { "    / 10  " };		//생명력 정보 표시 문자열
	char hp = pla[t].hp;
	char x = (W - sizeof(c)) / 2;
	char y = 1;
	char gap = H - 2;		//상대와 출력 줄 차이
	char i = sizeof(c) / 4;		//초기화할 문자열 인덱스 위치

	if (t)		xy(x, y);
	else		xy(x, y + gap);

	if (hp == 10) {		//생명력이 10일 경우 
		c[i - 1] = '1';
		c[i] = '0';
	}
	else		c[i] = hp + '0';		//현재 생명력으로 초기화

	color(White + Blue * BGC);
	for (i = 0; i < hp; i++)		printf("%c", c[i]);		//남은 생명력 표시
	color(White);
	for (; i <= MHP; i++)		printf("%c", c[i]);		//깍인 생명력 표시
}

//정보 출력
void print() {
	dice();		//주사위 출력
	shield();		//방패 출력
	HP();		//생명력 출력
}

//선공 선택
void turn() {
	t = rand() % P;		//선공 랜덤으로 선택

	xy(PX, PY);
	printf("당신은 ");
	if (t)		printf("후공입니다.");
	else		printf("선공입니다.");

	Sleep(2 * Sec);		//대기 시간
	clear(PY);
}

//문자 삭제 함수
void remove(char x,char y) {
	xy(x, y);
	printf("  ");
}

//주사위 던지기
void throwDice(char n) {
	const float frame = 10;		//프레임
	const char spd = 5;		//주사위 속도
	const char x = PX + 2 * pla[t].dice + 2;		//주사위 출력 시작 위치
	const char m = 3;		//주사위 최소 이동 거리
	short delay = Sec / (spd * frame);
	char y;		//주사위 세로 좌표
	char ran = H / 4;		//세로 좌표 범위
	float d[MTD];

	dice();		//주사위 개수 출력
	for (char a = 0; a < n; a++)			di[a].y = rand() % ran + m;
	dx = x;
	color(Yellow);		//주사위 던져지는 중에는 노랑색으로 출력
	if (t) {
		y = DPY + 1;
		for (char a = 0; a < frame; a++) {
			for (char b = 0; b < n; b++) {
				d[b] = y + (di[b].y / frame) * a;
				xy(x + 2 * b, d[b] );
				printf("■");
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
				printf("■");
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
		printf("■");
	}
	color(White);
	Sleep(Sec / 2);
}

//주사위 굴리기
void roll() {
	char d[DK] = { 0 };		//인덱스 - 0: 리롤, 1: 방패, 2: 해골, 3: 공격
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
				printf("리롤 X %d ", d[a]);
				pla[t].dice += d[a];
			}
			else if (a == 1) {
				printf("방패 X %d ", d[a]);
				pla[t].shi += d[a];
				if (pla[t].shi > MSH)		pla[t].shi = MSH;
			}
			else if (a == 2) {
				printf("해골 X %d ", d[a]);
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
				printf("공격 X %d ", d[a]);
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

//진행 여부 확인
char check() {
	char di = 0;
	char hp = 1;

	t = !t;		//턴 바꾸기
	print();		//정보 출력

	for (char a = 0; a < P; a++) {
		di += pla[a].dice;
		hp *= pla[a].hp;
	}
	if (!di)		return 0;
	if (!hp)		return 0;

	return 1;
}

//결과 출력
char result() {
	Sleep(Sec);
	print();	t = !t;		print();

	clear(PY);
	xy(PX, PY);

	if (pla[0].hp > pla[1].hp)			printf("이겼습니다.");
	else if (pla[0].hp < pla[1].hp)		printf("졌습니다.");
	else			printf("비겼습니다.");

	xy(PX, PY + 1);		printf("종료: ESC");
	if (_getch() == 27)		return 0;

	return 1;
}

//정보 출력
void notice() {
	xy(0, H - 5);
	for (char a = 0; a < 4; a++) {
		printf("\n");
		color(Green + a);
		printf("■:");
		if (a == 0)			printf("리롤");
		else if (a == 1)	printf("방패");
		else if (a == 2)	printf("해골");
		else if (a == 3)	printf("공격");
	}
	color(White);
}

//초기화
void reset() {
	system("cls");
	color(15);
	notice();

	for (t = 0; t < P; t++) {
		pla[t].dice = MDI;		//주사위 개수 초기화
		pla[t].shi = 0;		//방패 개수 초기화
		pla[t].hp = MHP;		//생명력 초기화
		print();
	}
	turn();		//선공 선택	
}

//게임
void game() {
	char x = W / 3;
	char y = PY;
	char p;
	char k;

	do {
		//완성하면 밑에 두 줄 삭제
		reset();		//초기화
		do {
			xy(x, y);
			if (pla[t].dice) {
				if (t) {
					printf("상대의 차례입니다.");
					Sleep(Sec);
				}
				else {
					printf("당신의 차례입니다. s: 그만하기");
					k = _getch();
					if (k == 's' || k == 'S')		exit(0);
				}
				roll();
			}
			else {
				printf("주사위가 없기 때문에 턴이 지나갑니다.");
				Sleep(Sec);
				clear(y);
				continue;
			}
		} while (check());		//게임 진행 여부 확인
	} while (result());		//결과 확인/재시작 여부 확인
}

int main() {
	srand(time(NULL));
	title();
	game();

	return 0;
}