#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define GA 12		//가로 길이
#define SE 23		//세로 길이
#define HE 29-SE		//높이
#define AP SE+HE-1		//공격줄 출력 세로 좌표
#define KE 300		//키 보정 값
#define KY 2		//키 정보 출력 높이
#define opt 6		//옵션 개수

clock_t st, et;		//시간 변수
clock_t lpt, lvt, cpt;		//출력 시간(줄, 레벨, 컴퓨터 행동)
int p;		//게임 진행
int op = 0;		//선택 변수
int nt, svt;		//블록 생성 변수
int col, cc;		//블록 색 변수
int x, y, xs, ys, cx, cy, cxs, cys;		//위치 변수
int dx, dr;		//목표 행동 변수
int yy;		//낙하 예측 지점의 세로 좌표
int po, lv, ca;		//점수,레벨,컴퓨터 행동속도
int tb;		//사용한 블록 개수
int co;		//콤보
int h;		//홀드변수
int l, al, dl;		//줄 변수
int de;		//삭제 여부 판별
int bp;		//블록 출력 위치 조정
int vb;		//빈공간의 개수
int mc[3], ba[3];		//기록
int sc[GA][SE + 1], cs[GA][SE + 1];		//화면 배열 값
int ub[4][2], nb[4][2], cb[4][2];		//블록 배열
int li[21], cl[21];		//라인 배열
int ra[7];		//이산 확률 배열
int kee[7];		//키 변수

//커서 숨기기
void view(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

//커서 이동
void xy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//문자색 변경
void color(short t, short b)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), t + (b << 4));
}

//삭제 함수
void erase()
{
	int a;		//반복 변수

	for (a = 0; a < 4; a++)
	{
		xy(2 * (ub[a][0] + xs) + bp, ub[a][1] + ys + HE);
		printf("  ");
		xy(2 * (ub[a][0] + xs) + bp, ub[a][1] + yy + HE);
		printf("  ");
	}
}

//처음 화면
void title()
{
	int c=1;		//색깔 변수
	int t = 1;		//출력/삭제
	int ke;		//입력 변수

	st = et - 300;		//처음엔 무조건 들어감
	while (1)
	{
		et = clock();
		if (et - st > 300)		//일정 시간 마다 변경
		{
			st = clock();
			xy(10, 10);	 printf("■■■■■  ■■■■■  ■■■■■  ■■■■■  ■■■■■  ■■■■■  ■■■■■");
			color(c % 15 + 1, 0);
			c = rand() % 15 + 1;
			xy(10, 11);	 printf("    ■      ■              ■      ■          ■      ■      ■     ■");
			color(c % 15 + 1, 0);
			c = rand() % 15 + 1;
			xy(10, 12);	 printf("    ■      ■■■■■      ■      ■■■■■  ■■■■■      ■      ■■■■■");
			color(c % 15 + 1, 0);
			c = rand() % 15 + 1;
			xy(10, 13);	 printf("    ■      ■              ■      ■          ■   ■         ■               ■");
			color(c % 15 + 1, 0);
			c = rand() % 15 + 1;
			xy(10, 14);	 printf("    ■      ■■■■■      ■      ■■■■■  ■      ■  ■■■■■  ■■■■■");
			color(c % 15 + 1, 0);
			c = rand() % 15 + 1;
			xy(40, 20);
			if (t)		printf("PRESS ANY KEY TO START");
			else		printf("                      ");
			t = !t;		//출력/삭제가 번갈아가면서 실행됨(0과 1이 서로 바뀜)
			c = rand() % 15 + 1;		//16가지 색상 중에서 검은색은 제외(0은 제외)하고 선택
		}
		if (kbhit())		break;		//아무키나 눌릴경우 게임 시작
	}
	ke = getch();
	color(7, 0);
}

//선택 창
void option()
{
	int ke;		//입력 변수

	xy(25, 10);		printf("일반 모드");
	xy(65, 10);		printf("연습 모드");
	xy(25, 15);		printf("삭제 모드");
	xy(65, 15);		printf("대전 모드");
	xy(25, 20);		printf("키   변경");
	xy(65, 20);		printf("통산 기록");

	do
	{
		xy(29 + 40 * (op % 2), 9 + 5 * (op / 2));	printf("↓");		//선택한 모드 표시
		ke = getch();		//입력 받음
		xy(29 + 40 * (op % 2), 9 + 5 * (op / 2));	printf("  ");		//이전에 선택한 모드 삭제
		if (ke == 224)
		{
			ke = getch();
			if (ke == 72)		op -= 2;
			if (ke == 75)		op--;
			if (ke == 77)		op++;
			if (ke == 80)		op += 2;
		}
		if (op < 0)		op += opt;	//음수 방지
		op %= opt;		//선택지는 5가지
	} while (ke != '\r');
	system("cls");
	p = 1;		//게임 진행
}

//출력이 제대로 안되는 키 임의로 출력되게 함
void keyprint(int ke)
{
	if (ke == 8)				printf("Backspace");
	else if (ke == 9)			printf("TAB");
	else if (ke == '\r')		printf("ENTER    ");
	else if (ke == ' ')			printf("Space Bar");
	if (ke > 200)
	{
		ke -= KE;		//키값 재보정
		if (ke == 27)							printf("ESC      ");
		else if (ke >= 59 && ke <= 68)			printf("F%2d     ", ke - 58);
		else if (ke == 71)						printf("Home     ");
		else if (ke == 72)						printf("↑       ");
		else if (ke == 73)						printf("Page UP  ");
		else if (ke == 75)						printf("←       ");
		else if (ke == 77)						printf("→       ");
		else if (ke == 79)						printf("END      ");
		else if (ke == 80)						printf("↓       ");
		else if (ke == 81)						printf("Page Down");
		else if (ke == 82)						printf("Insert   ");
		else if (ke == 83)						printf("Delete   ");
		else if (ke == 133 || ke == 134)		printf("F%2d     ", ke - 122);
		ke += KE;		//키값	보정
	}
}

//정보 출력
void info()
{
	int a = KY;		//초기 출력 위치

	color(7, 0);
	if (op != 4)		//키 변경이 아닐때
	{
		xy(29 + bp, 20);		printf("다음 블록");
		xy(-15 + bp, 20);		printf("홀드 블록");
	}
	if (op != 3)		//대전 모드가 아닐때
	{
		xy(30 - bp / 2, a += 2);		printf("떨어뜨리기   : %c        ", kee[0]);
		xy(30 - bp / 2, a += 2);		printf("왼쪽   이동  : %c        ", kee[1]);
		xy(30 - bp / 2, a += 2);		printf("오른쪽 이동  : %c        ", kee[2]);
		xy(30 - bp / 2, a += 2);		printf("아래쪽 이동  : %c        ", kee[3]);
		xy(30 - bp / 2, a += 2);		printf("회       전  : %c        ", kee[4]);
		xy(30 - bp / 2, a += 2);		printf("홀       드  : %c        ", kee[5]);
		xy(30 - bp / 2, a += 2);		printf("일시정지/해제: %c        ", kee[6]);
		for (a = 0; a < 7; a++)
		{
			xy(45 - bp / 2, 4 + 2 * a);
			keyprint(kee[a]);		//키 출력
		}
	}
	else
	{
		xy(9, AP);		printf("공격 →");
		xy(87, AP);		printf("← 공격");
		xy(29, 5);		printf("player");
		xy(68, 5);		printf("computer");
	}
}

//초기화
void reset()
{
	int a, b;

	system("cls");
	for (a = 1; a < GA - 1; a++)
	{
		for (b = 0; b < SE; b++)
		{
			sc[a][b] = 0;		//게임 진행 공간 배열값 초기화
			cs[a][b] = 0;		//컴퓨터 진행 공간 배열값 초기화
		}
	}
	for (a = 0; a < 21; a++)
	{
		li[a] = 0;		//라인 배열 값 초기화
		cl[a] = 0;		//컴퓨터 라인 배열 값 초기화
	}
	for (a = 0; a < 7; a++)		ra[a] = 0;		//이산 확률 배열 초기화

	//각종 정보 값 초기화
	lv = 1;	po = 0;		//레벨 점수
	tb = 0;	de = 0;		//블록개수 삭제여부
	al = 0;	dl = 0;		//공격할줄  방어할줄
	svt = 8;
}

//화면&초기 값 설정
void screen()
{
	int a, b;		//반복 변수

	bp = 40;
	for (a = 0; a < 2; a++)		//양 옆 경계 출력
	{
		for (b = 0; b < SE; b++)		//세로 크기 -1 만큼 반복
		{
			if (b < 3)		color(0, 12);		//맨 위에 3칸은 빨간색
			else			color(0, 7);		//나머지 칸은 흰색
			xy(41 + a * 21, b + HE);
			printf(" ");
			sc[0 + 11 * a][b] = 1;		//양 옆 경계 배열 값 초기화
		}
	}
	xy(40, b + HE);
	for (a = 0; a < GA; a++)				//맨 밑 경계 출력
	{
		printf("  ");
		sc[a][b] = 1;		//맨 밑 경계 배열 값 초기화
	}
}

//화면 두개(대전 모드 용)
void twoscreen()
{
	int a, b;		//반복 변수

	bp = 20;
	//유저 화면
	for (a = 0; a < 2; a++)		//양 옆 경계 출력
	{
		for (b = 0; b < SE; b++)		//세로 크기 -1 만큼 반복
		{
			if (b < 3)		color(0, 12);		//맨 위에 3칸은 빨간색
			else			color(0, 7);		//나머지 칸은 흰색
			xy((a + 1) * 21, b + HE);
			printf(" ");
			sc[0 + 11 * a][b] = 1;		//양 옆 경계 배열 값 초기화
		}
	}
	xy(20, b + HE);
	for (a = 0; a < GA; a++)				//맨 밑 경계 출력
	{
		printf("  ");
		sc[a][b] = 1;		//맨 밑 경계 배열 값 초기화
	}

	//컴퓨터 화면
	for (a = 0; a < 2; a++)		//양 옆 경계 출력
	{
		for (b = 0; b < SE; b++)		//세로 크기 -1 만큼 반복
		{
			if (b < 3)		color(0, 12);		//맨 위에 3칸은 빨간색
			else			color(0, 7);		//나머지 칸은 흰색
			xy((a + 1) * 21 + 40, b + HE);
			printf(" ");
			cs[0 + 11 * a][b] = 1;		//양 옆 경계 배열 값 초기화
		}
	}
	xy(60, b + HE);
	for (a = 0; a < GA; a++)				//맨 밑 경계 출력
	{
		printf("  ");
		cs[a][b] = 1;		//맨 밑 경계 배열 값 초기화
	}
}

//키값 보정
int keychange(int ke)
{
	if (ke == 224 || ke == 0 || ke == 27)		//입력한키가 출력이 안되는 키일 경우
	{
		if (ke == 224 || ke == 0)		ke = getch();		//한번 더 입력 받은 후
		ke += KE;		//다른 키와 겹치지 않게 키 값 보정
	}

	return ke;
}

//블록 생성 함수
void block(int p, int r)
{
	int a, b;		//반복 변수
	int bl[4][2];

	//왼쪽은 초기 가로 좌표 오른쪽은 초기 세로좌표
	if (r == 0)		//J 블록
	{
		bl[0][0] = 0;	bl[0][1] = 1;
		bl[1][0] = 0;	bl[1][1] = 2;
		bl[2][0] = 1;	bl[2][1] = 2;
		bl[3][0] = 2;	bl[3][1] = 2;
	}
	else if (r == 1)		//S 블록
	{
		bl[0][0] = 1;	bl[0][1] = 2;
		bl[1][0] = 2;	bl[1][1] = 2;
		bl[2][0] = 2;	bl[2][1] = 1;
		bl[3][0] = 3;	bl[3][1] = 1;
	}
	else if (r == 2)		//I 블록
	{
		bl[0][0] = 0;	bl[0][1] = 2;
		bl[1][0] = 1;	bl[1][1] = 2;
		bl[2][0] = 2;	bl[2][1] = 2;
		bl[3][0] = 3;	bl[3][1] = 2;
	}
	else if (r == 3)		//T 블록
	{
		bl[0][0] = 1;	bl[0][1] = 1;
		bl[1][0] = 0;	bl[1][1] = 2;
		bl[2][0] = 1;	bl[2][1] = 2;
		bl[3][0] = 2;	bl[3][1] = 2;
	}
	else if (r == 4)		//Z 블록
	{
		bl[0][0] = 0;	bl[0][1] = 1;
		bl[1][0] = 1;	bl[1][1] = 1;
		bl[2][0] = 1;	bl[2][1] = 2;
		bl[3][0] = 2;	bl[3][1] = 2;
	}
	else if (r == 5)		//ㅁ 블록
	{
		bl[0][0] = 1;	bl[0][1] = 1;
		bl[1][0] = 2;	bl[1][1] = 1;
		bl[2][0] = 1;	bl[2][1] = 2;
		bl[3][0] = 2;	bl[3][1] = 2;
	}
	else if (r == 6)		//L 블록
	{
		bl[0][0] = 1;	bl[0][1] = 2;
		bl[1][0] = 2;	bl[1][1] = 2;
		bl[2][0] = 3;	bl[2][1] = 2;
		bl[3][0] = 3;	bl[3][1] = 1;
	}
	if (!p)		//다음 블록 생성
	{
		for (a = 0; a < 4; a++)		//생성된 블록을 현재 블록으로 바꿈
		{
			for (b = 0; b < 2; b++)		ub[a][b] = bl[a][b];
		}
		col = r + 9;		//현재 블록 색깔
	}
	else if (p == 1)
	{
		for (a = 0; a < 4; a++)		//생성된 블록을 다음 블록으로 바꿈
		{
			for (b = 0; b < 2; b++)		nb[a][b] = bl[a][b];
		}
		nt = r;		//다음 블록값
	}
	else if (p == 2)
	{
		for (a = 0; a < 4; a++)		//생성된 블록을 컴퓨터 블록으로 바꿈
		{
			for (b = 0; b < 2; b++)		cb[a][b] = bl[a][b];
		}
		cc += 9;		//컴퓨터 블록값
	}
	else if (p == 3)		//홀드 블록 생성
	{
		for (a = 0; a < 4; a++)		//생성된 블록을 컴퓨터 블록으로 바꿈
		{
			for (b = 0; b < 2; b++)		cb[a][b] = bl[a][b];
		}
		cc += 9;		//컴퓨터 블록값
	}
}

//블록 결정 함수
int blockselect()
{
	int a, b;		//반복 변수
	int r;		//랜덤 변수

	r = rand() % 7;		//다음 블록 결정
	if (tb % 10 == 9)		//10번째 블록 마다 블록 확률 보정
	{
		for (a = 0; a < 6; a++)		//제일 안나온 블록을 판별
		{
			if (ra[a] > ra[a + 1])		b = a + 1;		//각 배열의 최솟값을 구함
		}
		r = a;		//블록 보정
	}
	ra[r]++;		//해당 블록 값 증가

	return r;
}

//블록 바꿈
void blockchange()
{
	int a;		//반복 변수
	int	b;		//블록 변수

	b = blockselect();		//블록 결정
	block(0, nt);		//유저 현재 테트리미노 결정
	block(1, b);		//유저 다음 테트리미노 결정
	for (a = 0; a < 4; a++)		//전에 출력한 다음 블록삭제 
	{
		xy(2 * ub[a][0] + 30 + bp, ub[a][1] + 22);
		printf("  ");
	}
	color(b + 9, 0);
	for (a = 0; a < 4; a++)		//다음 블록 출력
	{
		xy(2 * nb[a][0] + 30 + bp, nb[a][1] + 22);
		printf("□");
	}
}

//충돌 판별 함수
int crash()
{
	int a;		//반복 변수
	int c;		//대입 변수

	for (a = 0; a < 4; a++)
	{
		if (sc[ub[a][0] + x][ub[a][1] + y])		//충돌 시
		{
			if (x != xs)
			{
				x = xs;
				a--;
				continue;
			}
			if (y != ys)		//세로만 다를때
			{
				y--;
				if (y < 0)		y = 0;
				return 1;
			}
			else				//회전시
			{
				return 1;
			}
			break;
		}
	}
	return 0;
}

//블록 출력 함수
void blockprint()
{
	int a, b;		//반복 변수
	int c;		//대입 변수

	xs = x;	ys = y;		//출력한 테트리미노 좌표 저장

	for (c = y; !crash(); y++);		//바로 밑에 블록과 충돌할때 까지 블록 하강 시킴
	yy = y;
	y = c;

	for (a = 0; a < 2; a++)
	{
		if (!a)
		{
			color(8, 0);		//회색
			c = yy;		//낙하 예측 지점
		}
		else
		{
			color(col, 0);		//블록 마다 색깔 다름
			c = y;		//현재 블록 위치
		}
		for (b = 0; b < 4; b++)		//블록 출력
		{
			xy(2 * (ub[b][0] + x) + bp, ub[b][1] + c + HE);
			printf("□");
		}
	}
	color(7, 0);
}

//줄 함수 
void line(int l)
{
	int a, b;		//반복 변수

	for (a = l; a > 0; a--)		//삭제된 줄부터 처음까지 배열 값 초기화
	{
		if (a > 2)		li[a - 2] = li[a - 3];
		xy(2 + bp, a + HE);
		for (b = 1; b <= 10; b++)
		{
			sc[b][a] = sc[b][a - 1];
			color(sc[b][a], 0);
			if (sc[b][a])		printf("□");
			else				printf("  ");
		}
	}
	b = 0;
	for (a = 1; a <= 10; a++)		//3번째줄 라인 값 구함
	{
		if (sc[a][2])		b++;		//블록이 있을경우 값 증가
	}
	li[0] = b;		//마지막 라인 배열 초기화
	color(7, 0);		//흰색
}

//테트리미노 함수
void tet()
{
	int a;		//반복 변수
	int c = 0;		//지운 줄수

	tb++;		//사용한 블록 수 증가
	if (op == 0&&tb >= 100)		//무제한 모드이고 사용한 블록 100개가 될 때마다
	{
		tb -= 100;		//사용한 블록 수 감소
		lv++;		//레벨 증가
		xy(80, 9);		printf("레벨 업!");
		lvt = et + 500;
	}
	for (a = 0; a < 4; a++)
	{
		sc[ub[a][0] + x][ub[a][1] + y] = col;		//블록 쌓음
		li[ub[a][1] + y - 2]++;		//해당 라인 배열 값 증가
	}
	for (a = 1; a < 21; a++)		//첫줄 부터 끝까지 확인
	{
		if (li[a] == 10)		//라인 꽉참
		{
			c++;		//지운 줄수 증가
			l--;		//줄 수 감소
			line(a + 2);		//줄 삭제
			if (op == 2 && a == 20)		de = 1;		//삭제 유
		}
	}
	if (c)			//지운 줄이 존재할경우
	{
		if (op == 3)		//대전 모드 일경우
		{
			al += c - 1;		//유저 공격 줄수
			if (al > 4)		al = 4;		//최대 공격 가능 줄수는 4줄
			color(8, 0);
			for (a = 0; a < al; a++)
			{
				xy(84, AP - a);
				printf("■");
			}
			color(7, 0);
		}
		xy(30 + bp, 12);
		for (a = 1; a <= c; a++)		po += a;		//한꺼번에 많이 지울때마다 증가 점수가 커짐
		po += co;		//콤보 보너스
		if (c == 2)				printf("더블     ");
		else if (c == 3)		printf("트리플   ");
		else if (c == 4)		printf("테트리스!");
		lpt = et + 500;
		if (op != 3)		//대전 모드가 아닐때
		{
			co++;		//콤보 증가
			if (co > 1)		//2연속 부터
			{
				xy(70, 14);		printf("콤보 X %d", co - 1);		//콤보 출력
			}
		}
	}
	else if (co)		//지운 줄이 없고 콤보가 있었을 경우
	{
		xy(70, 14);		printf("        ");
		co = 0;		//콤보 초기화
	}
}

//회전 함수
void rotate()
{
	int a, b = 0;		//반복 변수
	int c;		//대입 변수

	for (a = 0; a < 4; a++)		//90도 회전
	{
		c = ub[a][1];		//덮어쓰기 방지
		ub[a][1] = ub[a][0];
		ub[a][0] = 3 - c;
	}
	if (crash())		//충돌시
	{
		a = xs;
		while (b < 2)		//좌표 보정후 재판정
		{
			c = 1;
			if (col == 11)		c = 2;
			for (; c > 0; c--)
			{
				if (b == 0)			x--;		//오른쪽 벽에 붙어 회전안되는 현상 보정
				else if (b == 1)	x++;		//왼쪽 벽에 붙어 회전안되는 현상 보정
				xs = x;		//제대로된 충돌판정을 위해 이전 가로 좌표값 초기화
				if (!crash())		break;		//충돌안할시 탈출
			}
			if (!crash())		break;		//충돌안할시 탈출
			b++;
			x = a;
		}
		if (b == 2)
		{
			for (a = 0; a < 4; a++)		//-90도 회전
			{
				c = ub[a][0];		//덮어쓰기 방지
				ub[a][0] = ub[a][1];
				ub[a][1] = 3 - c;
			}
		}
	}
}

//블록 홀드 함수
void hold()
{
	int a, b;		//반복 변수
	int d;		//매개 변수

	x = 4;	y = 0;		//좌표 초기화

	for (a = 0; a < 4; a++)		//이전에 저장한 블록 삭제
	{
		for (b = 0; b < 4; b++)
		{
			xy(2 * a - 15 + bp, b + 22);
			printf("  ");
		}
	}
	col -= 9; block(0, col); color(col, 0);		//현재 블록 초기화
	for (a = 0; a < 4; a++)		//저장할 블록 출력
	{
		xy(2 * ub[a][0] - 15 + bp, ub[a][1] + 22);
		printf("□");
	}
	d = col - 9;		//현재 블록 임시 저장
	block(0, svt);		//현재 블록을 저장된 블록으로 바꿈
	if (svt == 8)		blockchange();		//첫 홀드였을경우
	svt = d;

	color(7, 0);
}

//정보 보여주기
void print()
{
	int rt;		//남은 시간

	if (op != 3)		//대전 모드 제외
	{
		xy(70, 9);		printf("레벨:%d", lv);
		xy(70, 10);		printf("점수:%d", po);
		if (lvt < et)		//레벨, 점수 변화 출력
		{
			xy(80, 9);		printf("         ");
			xy(80, 10);		printf("                 ");
		}
	}
	else		//대전 모드일때
	{
		color(7, 0);
		xy(29, 5);		printf("player");
		xy(68, 5);		printf("computer");
	}
	if (op == 1)		//연습 모드일 경우
	{
		if (l < 0)		l = 0;		//음수일경우 0으로 만듬
		xy(70, 16);		 printf("남은 줄:%d ", l);
	}
	else if (op == 2)		//삭제 모드일경우
	{
		rt = (cpt - et + 60000) / 1000;
		if (rt > 0)
		{
			xy(50, 4);		printf("%d ", rt);
		}
	}
	if (lpt < et)		//삭제 상황 출력
	{
		xy(30 + bp, 12);
		printf("         ");
	}
}

//일시 정지 함수
int pause()
{
	int ke;		//입력 변수
	int t = 0;

	st = clock();		//시간 초기화
	color(7, 0);		//흰색
	xy(30 + bp, 7);		printf("일시 정지");
	xy(5, 18);		printf("종료: %c", kee[5]);
	xy(11, 18);		keyprint(kee[5]);

	do
	{
		et = clock();		//현재 시간 초기화
		if (kbhit())		//입력 받음
		{
			ke = getch();
			ke = keychange(ke);		//키값 보정
			if (ke == kee[6] || ke == kee[5])		break;		//일시정지 해제
		}
		else if (et - st > 500)
		{
			xy(30 + bp, 7);
			if (t)		printf("일시 정지");
			else		printf("         ");
			t = !t;
			st = clock();		//시간 초기화
		}
	} while (1);
	xy(30 + bp, 7);		printf("         ");		//일시 정지 문구 삭제
	xy(5, 18);		printf("               ");		//키 문구 삭제
	if (ke == kee[6])		return 1;		//게임 계속 진행
	else					return 0;		//게임 진행하지 않음
}

//줄 생성 함수
void linemake()
{
	int a, b, c;		//반복 변수
	int r, l;		//랜덤 변수

	for (a = 0; a < 4; a++)		//이전에 저장한 블록 삭제
	{
		for (b = 0; b < 4; b++)
		{
			xy(2 * a - 15 + bp, b + 22);
			printf("  ");
		}
	}
	block(0, 2); color(col, 0);		//현재 블록 초기화
	for (a = 0; a < 4; a++)		//일자 블록 출력
	{
		xy(2 * ub[a][0] - 15 + bp, ub[a][1] + 22);
		printf("□");
	}
	svt = 2;
	for (a = 0; a < 6; a++)		//1 ~ 6라인 초기화
	{
		for (c = 1; c <= 10; c++)		sc[c][a + 2] = 0;
	}
	while (a)
	{
		r = rand() % 10 + 1;		//구멍 위치 랜덤 생성
		l = rand() % 4 + 1;		//최대 4줄
		for (b = 0; b < l; b++)
		{
			li[a] = 9;		//한 칸 빔(구멍 생성)
			for (c = 1; c <= 10; c++)		sc[c][a + 2] = 7;		//회색 블록
			sc[r][a + 2] = 0;		//블록 없음
			a++;
			if (a == 21)
			{
				a = 0;		//함수 종료
				break;
			}
		}
	}
	color(7, 0);		//흰색
	for (a = 22; a > 2; a--)		//삭제된 줄부터 처음까지 배열 값 초기화
	{
		xy(42, a + HE);
		for (b = 1; b <= 10; b++)
		{
			if (sc[b][a])		printf("□");
			else				printf("  ");
		}
	}
	color(7, 0);
}

//대기 함수
void wait()
{
	int c = 0;		//색깔
	int t = 0;		//횟수

	color(7, 0);
	xy(49, 10);		printf("READY !");
	Sleep(1000);
	st = clock();
	while (t != 10)
	{
		if (clock() - st > 100)
		{
			t++;
			c = rand() % 7 + 8;
			color(c, 0);
			xy(49, 10);		printf("START !");
			st = clock();
		}
		if (kbhit())		c = getch();		//입력한키 버퍼에서 삭제
	}
	xy(49, 10);		printf("        ");
}

//컴퓨터 이동 제어
int control(int x, int y)
{
	int a;		//반복 변수

	for (a = 0; a < 4; a++)		//각 블록 4개 충돌 유무 판별
	{
		if (cs[cb[a][0] + x][cb[a][1] + y])			return 0;		//충돌함
	}

	return 1;		//충돌 하지 않음
}

//컴퓨터 회전
void comrotate()
{
	int a, b;
	for (a = 0; a < 4; a++)		//90도 회전
	{
		b = cb[a][1];		//덮어쓰기 방지
		cb[a][1] = cb[a][0];
		cb[a][0] = 3 - b;
	}
}

//블록 높이의 합
int blockheight(int y)
{
	int he = 0;		//블록 높이
	int a;		//반복 변수

	for (a = 0; a < 4; a++)		he += cb[a][1];
	he += lv*y;

	return he;
}

//완성된 줄의 개수
int linefinish(int x, int y)
{
	int l = 0;		//완성된 줄의 갯수
	int a;		//반복 변수

	for (a = 0; a < 4; a++)		cl[cb[a][1] + y - 2]++;		//해당 라인 배열 값 증가
	for (a = 1; a < 21; a++)	if (cl[a] == 10)		l++;		//완성된줄의 개수 증가

	return 10 * l;
}

//전체 빈공간 개수 카운트
int blockcount()
{
	int bc = 0;		//블록 카운트
	int a, b;		//반복 변수

	for (a = 1; a <= 10; a++)		//세로 10줄 확인
	{
		for (b = 3; b < 23; b++)		//가로 20줄 확인
		{
			if(!cs[a][b])		bc++;		//블록 카운트
		}
	}

	return bc;
}

//유효 빈공간 확인
int voidspace(int x,int y)
{
	int vs = 0;
	int a, b;		//반복 변수

	for (a = 0; a < 4; a++)		cs[cb[a][0] + x][cb[a][1] + y] = 1;		//블록 쌓음
	for (a = 1; a <= 10; a++)		//10줄 빈 공간 확인
	{
		for (b = 3; !cs[a][b]; b++)		vs++;		//유효 빈공간 카운트
	}

	return 2 * lv * vs + 1;
}

//주변 블록 개수 확인
int narrowblock(int x,int y)
{
	int a;		//반복 블록
	int c = 0;		//카운트 변수

	for (a = 0; a < 4; a++)		//4블록 확인
	{
		if (cs[cb[a][0] + x - 1][cb[a][1] + y])		c++;
		if (cs[cb[a][0] + x + 1][cb[a][1] + y])		c++;
		if (cs[cb[a][0] + x][cb[a][1] + y - 1])		c++;
		if (cs[cb[a][0] + x][cb[a][1] + y + 1])		c++;
	}

	return 4 * c;
}

//블록 상태 되돌림
void blockreturn(int x, int y)
{
	int a;		//반복 변수

	if (lv != 2)		for (a = 0; a < 4; a++)		cl[cb[a][1] + y - 2]--;		//해당 라인 배열 값 감소
	for (a = 0; a < 4; a++)		cs[cb[a][0] + x][cb[a][1] + y] = 0;		//블록 쌓음
}

//컴퓨터 인공지능
void computer()
{
	int x, y, r;		//블록 상태
	int sc;		//최종 점수
	int he;		//블록높이의 합
	int	l = 0;		//완성된 줄의개수
	int nb = 0;		//주변 블록 개수
	int vs = 0, vb;		//빈공간
	int cp = -200;		//비교 변수
	int a;		//반복 변수

	vb = blockcount();		//전체 빈공간 계산
	for (r = 0; r < 4; r++)		//회전 방향은 4가지
	{
		x = 1;
		while (control(--x, 0));		//블록 왼쪽 반복이동
		while (control(++x, 0))		//블록 오른쪽 반복 이동
		{
			y = 0;		//좌표값 초기화
			while (control(x, ++y));		//컴퓨터 블록 아래 반복 이동
			y--;		//세로 좌표 보정
			he = blockheight(y);		//블록 높이의 합 계산
			vs = voidspace(x, y);		//유효 빈공간 계산
			vs = vb - vs;		//블록 사이의 빈공간 계산
			if (lv >= 3)		l = linefinish(x, y);		//완성된 줄의 개수 계산
			if (lv == 4)		nb = narrowblock(x, y);		//주위의 블록 개수 계산
			sc = he - vs + l + nb;		//최종 점수 계산
			if (sc > cp)		//최종 점수가 이전 점수보다 더 클경우
			{
				dx = x;	cp = sc; dr = r;		//블록 정보 초기화
			}
			blockreturn(x, y);		//계산 과정에서 변화한 값 초기화
		}
		comrotate();		//컴퓨터 회전
	}
}

//공격 함수
void attack(int p)
{
	int a, b;		//반복 변수
	int r;		//랜덤 변수

	if (p == 1)		//유저 공격
	{
		r = rand() % 10 + 1;		//구멍 위치
		for (a = 2; a <= 22 - al; a++)		//처음부터 일정한 줄까지 배열 값 초기화
		{
			cl[a - 2] = cl[a - 2 + al];		//라인 배열값 시프트
			xy(2 + 3 * bp, a + HE);
			for (b = 1; b <= 10; b++)		//화면 배열값 시프트 후 재출력
			{
				cs[b][a] = cs[b][a + al];
				color(cs[b][a], 0);
				if (cs[b][a])		printf("□");
				else				printf("  ");
			}
		}
		for (a = 22; al > 0; al--, a--)		//밑에서 블록 올라옴
		{
			cl[a - 2] = 9;		//한 칸 빔(구멍 생성)
			for (b = 1; b <= 10; b++)		cs[b][a] = 7;		//흰색 블록
			cs[r][a] = 0;		//블록 없음
			xy(2 + 3 * bp, a + HE);
			for (b = 1; b <= 10; b++)		//화면 배열값 초기화 후 재출력
			{
				color(7, 0);
				if (cs[b][a])		printf("□");
				else				printf("  ");
			}
		}
		for (a = 0; a < 4; a++)
		{
			xy(84, AP - a);
			printf("  ");
		}
	}
	else if (p == 2)		//컴퓨터 공격
	{
		r = rand() % 10 + 1;		//구멍 위치
		for (a = 2; a <= 22 - dl; a++)		//처음부터 일정한 줄까지 배열 값 초기화
		{
			li[a - 2] = li[a - 2 + dl];		//라인 배열값 시프트
			xy(2 + bp, a + HE);
			for (b = 1; b <= 10; b++)		//화면 배열값 시프트 후 재출력
			{
				sc[b][a] = sc[b][a + dl];
				color(sc[b][a], 0);
				if (sc[b][a])		printf("□");
				else				printf("  ");
			}
		}
		for (a = 22; dl > 0; dl--, a--)		//밑에서 블록 올라옴
		{
			li[a - 2] = 9;		//한 칸 빔(구멍 생성)
			for (b = 1; b <= 10; b++)		sc[b][a] = 7;		//흰색 블록
			sc[r][a] = 0;		//블록 없음
			xy(2 + bp, a + HE);
			for (b = 1; b <= 10; b++)		//화면 배열값 초기화 후 재출력
			{
				color(7, 0);
				if (sc[b][a])		printf("□");
				else				printf("  ");
			}
		}
		for (a = 0; a < 4; a++)
		{
			xy(18, AP - a);
			printf("  ");
		}
	}
}

//컴퓨터 행동
int AI()		//회전 상태만 입력 받음
{
	int a, b, c;		//반복 변수
	int lc = 0;		//줄수 카운트

	cpt = clock();
	color(cc, 0);		//컴퓨터 블록색 조정
	if (de == 0)		//현재 블록이 없을때
	{
		de = 1;		//현재 블록 있음
		cx = 4; cy = 0;
		cc = rand() % 7;
		//왼쪽은 초기 가로 좌표 오른쪽은 초기 세로좌표
		block(2, cc);
		color(cc, 0);		//컴퓨터 블록 색깔
		for (a = 0; a < 4; a++)
		{
			xy(2 * (cb[a][0] + cx) + 3 * bp, cb[a][1] + cy + HE);	printf("□");		//블록 출력
		}
		cys = cy;	cxs = cx;		//컴퓨터 블록 위치 초기화	
		computer();		//컴퓨터 행동 결정

		return 1;
	}
	if (dr)		//컴퓨터 블록 회전
	{
		for (a = 0; a < 4; a++)
		{
			xy(2 * (cb[a][0] + cxs) + 3 * bp, cb[a][1] + cys + HE);			printf("  ");		//블록 지움
		}
		dr--;
		for (a = 0; a < 4; a++)		//90도 회전
		{
			c = cb[a][1];		//덮어쓰기 방지
			cb[a][1] = cb[a][0];
			cb[a][0] = 3 - c;
		}
		for (a = 0; a < 4; a++)		//충돌 판별
		{
			if (cs[cb[a][0] + cx][cb[a][1] + cy])		//충돌 시
			{
				for (a = 0; a < 4; a++)		//-90도 회전
				{
					c = cb[a][0];		//덮어쓰기 방지
					cb[a][0] = cb[a][1];
					cb[a][1] = 3 - c;
				}
				dr = 0;		//더 이상 회전 하지 않음
			}
		}
		for (a = 0; a < 4; a++)
		{
			xy(2 * (cb[a][0] + cx) + 3 * bp, cb[a][1] + cy + HE);			printf("□");		//블록 출력
		}
	}
	else if (cx == dx)		//목표 가로지점에 도착하거나 평평할경우
	{
		cy++;		//컴퓨터 블록 하강
	}
	else		//컴퓨터 블록 가로 이동
	{
		if (cx > dx)		cx--;
		if (cx < dx)		cx++;
	}
	if (0)		//컴퓨터 홀드(미구현)
	{
		//h++;		//홀드 값 증가로 연속 홀드 방지
		erase();		//전에 출력한 블록 삭제
		hold();		//블록 저장
		blockprint();		//바뀐 블록 출력
		st = clock();		//시간 초기화
							//continue;		//바뀐 블록으로 계속 진행
	}
	for (a = 0; a < 4; a++)		//충돌 판별
	{
		if (cs[cb[a][0] + cx][cb[a][1] + cy])		//충돌 시
		{
			if (cx != cxs)
			{
				dx = cx = cxs;		//더이상 가로로 움직이지 않음
				a--;
				continue;		//재판정
			}
			if (cy != cys)		//세로만 다를때
			{
				de = 0;		//블록 없음
				cy--;
				for (a = 0; a < 4; a++)
				{
					cs[cb[a][0] + cx][cb[a][1] + cy] = cc;		//블록 쌓음
					cl[cb[a][1] + cy - 2]++;		//해당 라인 배열 값 증가
				}
				for (a = 1; a < 21; a++)		//첫줄 부터 끝까지 확인
				{
					if (cl[a] == 10)		//라인 꽉참
					{
						lc++;
						for (b = a + 2; b > 0; b--)		//삭제된 줄부터 처음까지 배열 값 초기화
						{
							if (b > 2)		cl[b - 2] = cl[b - 3];
							xy(2 + 3 * bp, b + HE);
							for (c = 1; c <= 10; c++)
							{
								cs[c][b] = cs[c][b - 1];
								color(cs[c][b], 0);
								if (cs[c][b])		printf("□");
								else				printf("  ");
							}
						}
						b = 0;
						for (c = 1; c <= 10; c++)		//3번째줄 라인 값 구함
						{
							if (cs[c][2])		b++;		//블록이 있을경우 값 증가
						}
						cl[0] = b;		//마지막 라인 배열 초기화
					}
				}
				if (lc >= 2)		//삭제한 줄의 수가 2줄이상일때
				{
					dl += lc - 1;
					if (dl > 4)		dl = 4;		//방어할 최대 줄의 수는 4줄
					color(8, 0);
					for (a = 0; a < dl; a++)
					{
						xy(18, AP - a);
						printf("■");
					}
					color(cc, 0);
				}
				if (al)		attack(1);		//공격할 줄이 있을때 유저 공격
				if (cl[0])		//블록이 20줄 넘게 쌓였을때
				{
					return 0;		//종료
				}
			}
		}
	}
	if (cx + cy != cxs + cys)		//블록이 움직였을경우
	{
		for (a = 0; a < 4; a++)
		{
			xy(2 * (cb[a][0] + cxs) + 3 * bp, cb[a][1] + cys + HE);			printf("  ");		//이전 출력한 블록 지움

		}
		for (a = 0; a < 4; a++)
		{
			xy(2 * (cb[a][0] + cx) + 3 * bp, cb[a][1] + cy + HE);			printf("□");		//블록 출력
		}
		cys = cy;	cxs = cx;		//컴퓨터 블록 위치 초기화
	}

	return  1;		//계속 진행
}

//키보드 초기화
void keyreset()
{
	int a;		//반복 변수

	kee[0] = 72; kee[1] = 75; kee[2] = 77; kee[3] = 80;		//방향키 초기화(위,왼쪽,오른쪽,아래)
	kee[4] = 'a';	kee[5] = '\r';	kee[6] = ' ';	//특수키 초기화(회전, 홀드, 일시정지)
	for (a = 0; a < 4; a++)		kee[a] += KE;		//키값 보정
}

//키 변경 함수
void key()
{
	int ke;		//입력 변수
	int a, b = 0, c;		//이동 변수
	int dc = 0;		//화살표 색깔
	int sk[7];		//키 매개 변수

	bp = 0;

	for (a = 0; a < 7; a++)		sk[a] = kee[a];		//키 임시 저장
	system("cls");
	while (1)
	{
		a = KY + 14;
		color(7 + dc * 5, 0);		//화살표 색깔 변경
		xy(27, KY + 2 + 2 * b);		printf("→");
		color(7, 0);
		info();		//키 정보 출력
		xy(30, a += 2);		printf("초기값   ");
		xy(30, a += 2);		printf("취소     ");
		xy(30, a += 2);		printf("적용     ");
		ke = getch();
		xy(27, KY + 2 + 2 * b);		printf("  ");		//이전 화살표 삭제
		if (dc == 1)		//키 변경중
		{
			dc = 0;
			if (b < 7)
			{
				ke = keychange(ke);		//키값 보정
				kee[b] = ke;		//키 변경
			}
		}
		else if (ke == 224)		//방향키 제어
		{
			ke = getch();
			if (ke == 72)		b--;		//위로
			if (ke == 80)		b++;		//아래로
			if (b < 0)		b += 10;		//음수 값 보정
			b %= 10;		//옵션은 10가지
		}
		else if (ke == '\r')		//엔터 입력시 키 변경 모드 변환
		{
			if (b > 6)
			{
				if (b == 7)		//초기값
				{
					system("cls");
					keyreset();		//키 초기값 불러옴
				}
				else if (b == 8)		//취소
				{
					for (a = 0; a < 7; a++)		kee[a] = sk[a];		//키 초기화
					break;		//키값 적용
				}
				else if (b == 9)		//적용
				{
					for (a = 0; a < 6; a++)		//중복 검사
					{
						for (c = a + 1; c < 7; c++)
						{
							if (kee[a] == kee[c])		//중복키가 있을경우
							{
								a = c = 7;		//두개의 반복문 탈출 조건
								xy(40, 22);		printf("중복키 존재");
								getch();
								xy(40, 22);		printf("           ");
							}
						}
					}
					if (a != 8)		break;		//키값 적용
				}
			}
			else
			{
				dc = 1;
			}
		}
	}
}

//키보드 제어
int keyboard(int ke)
{
	int sat[2];		//시간 저장 변수

	ke = keychange(ke);		//키값 보정
	if (ke == kee[0])		//블록 하강
	{
		for (; !crash(); y++);		//바로 밑에 블록과 충돌할때 까지 블록 하강 시킴
		erase();
		blockprint();
		y++;		//충돌 판정을 위해 블록 하강
		st = clock();		//시간 초기화
	}
	else if (ke == kee[1])		//왼쪽 이동
	{
		x--;
	}
	else if (ke == kee[2])		//오른쪽 이동
	{
		x++;
	}
	else if (ke == kee[3])		//아래 이동
	{
		y++;
		st = clock();		//입력 시간 초기화
	}
	if (ke == kee[4])		//회전
	{
		erase();		//전에 출력한 블록 삭제
		rotate();
		blockprint();		//블록 출력
	}
	else if (!h&&ke == kee[5])		//홀드(한 블록당 한번만 가능)
	{
		h++;		//홀드 값 증가로 연속 홀드 방지
		erase();		//전에 출력한 블록 삭제
		hold();		//블록 저장
		blockprint();		//바뀐 블록 출력
		st = clock();		//시간 초기화
		return 1;		//컨티뉴
	}
	else if (ke == kee[6])			//일시정지	
	{
		sat[0] = et - st;		//남은 시간 저장
		sat[1] = et - cpt;		//남은 컴퓨터 시간 저장
		ke = pause();		//일시 정지
		st = et - sat[0];		//남은 시간 진행
		cpt = et - sat[1];		//남은 컴퓨터 시간 진행
		if (!ke)		return 2;		//ESC를 누른경우 게임 종료
	}
	return 0;
}

//게임 진행
int play()
{
	int a;
	int ke;		//입력 변수

	while (p)
	{
		x = 4; y = 0;		//초기 좌표 설정
		h = 0;		//홀드 값 초기화
		blockchange();		//새로운 블록 생성
		blockprint();		//블록 출력
		st = clock();		//입력 시간 초기화
		while (p)
		{
			et = clock();		//현재 시간 초기화
			if (op == 3 && cpt + ca < et)		p = AI();
			else		print();
			if (kbhit())
			{
				ke = getch();
				ke = keyboard(ke);
				if (ke == 1)
				{
					continue;		//바뀐 블록으로 계속 진행
				}
				else if (ke == 2)
				{
					li[0] = 1;		//게임 패배 조건
					p = 0;		//게임 종료
				}
			}
			if (et - st > 2000 / lv)		//마지막 키 입력 후 일정 시간이 지날경우
			{
				st = clock();		//입력 시간 초기화
				y++;		//블록 하강
			}
			if (crash())		//타 블록 위에 충돌시
			{
				tet();		//블록 쌓음
				if (op == 2 && de == 1)		//삭제 모드 일때
				{
					de = 0;		//삭제 여부 초기화
					po += lv*lv;		//보너스 점수
					xy(80, 9);		printf("레벨 업!");
					xy(80, 10);		printf("보너스 점수 %d", lv*lv);
					lvt = et + 500;
					lv++;		//레벨 증가
					linemake();		//줄 생성
					cpt = clock();		//시간 초기화
				}
				break;		//현 블록 이동 종료
			}
			if (x + y != xs + ys)		//블록이 움직였을경우
			{
				erase();		//전에 출력한 블록 삭제
				blockprint();		//블록 출력
			}
		}
		if (dl > 0)			attack(2);		//방어할줄이 생긴경우 컴퓨터 공격
		if (op == 2 && cpt + 60000 < et)		//삭제모드에서 시간이 지날 경우 밑에서 블록 올라옴
		{
			cpt = clock();
			dl = 1;			//방어할줄 1개 생성
			attack(2);		//블록 올라옴
		}
		if (li[0] || (op == 1 && l <= 0))		//게임 종료 기준을 달성했을때
		{
			p = 0;		//게임 종료
			break;
		}
	}
	system("cls");
	color(7, 0);
	xy(40, 15);
	if (op == 0)		printf("Game Over!  ");		//일반 모드 일때
	else if (op == 1)		//연습 모드 일때
	{
		if (l <= 0)		printf("Game Clear!  ");		//줄을 목표치 만큼 삭제해서 종료된경우
		else		printf("Game Over!  ");		//블록이 20줄이상 쌓여서 종료된경우
	}
	if (op != 3)
	{
		printf("최종점수:%d", po);
		if (po > mc[op])
		{
			xy(40, 17);		printf("최고 기록!");
			mc[op] = po;		//최고 기록 경신
		}
	}
	else
	{
		if (li[0])		printf("YOU LOSE!");
		else
		{
			lv -= 2;
			printf("YOU WIN!");
			ba[lv]++;
		}
	}
	FILE*fp = fopen("record.txt", "wt");
	for (a = 0; a < 3; a++)			fprintf(fp, "%d\n%d\n", mc[a], ba[a]);
	fclose(fp);
	xy(40, 20);		printf("re?    Y/N");
	do
	{
		ke = getch();
		if (ke == 'y' || ke == 'Y')				return 1;		//재시작
		else if (ke == 'n' || ke == 'N')		return 0;		//종료
	} while (1);
}

//최고 점수
void record()
{
	int a;

	a = 8;
	xy(30, a += 2);	printf("일반 모드 최고 : %d점", mc[0]);
	xy(30, a += 2);	printf("연습 모드 최고 : %d점", mc[1]);
	xy(30, a += 2);	printf("삭제 모드 최고 : %d점", mc[2]);
	xy(30, a += 2);	printf("대전 모드 하급 : %d승", ba[0]);
	xy(30, a += 2);	printf("대전 모드 중급 : %d승", ba[1]);
	xy(30, a += 2);	printf("대전 모드 상급 : %d승", ba[2]);
	getch();
}

//게임진행 함수
void game()
{
	system("cls");
	option();		//옵션 선택
	if (op >= 4)	//게임 진행이 아님
	{
		p = 0;		//진행 하지 않음
		if (op == 4)		key();		//키 변경
		else				record();		//최고 점수
	}
	while (p)		//게임 시작
	{
		reset();		//초기화
		if (op == 1)		//연습 모드 일때
		{
			view(1);		//커서 보임
			do
			{
				xy(10, 10);
				printf("난이도를 입력하세요(최소 1이상): ");
				scanf("%d", &lv);		//난이도 입력 받음
				system("cls");
			} while (lv <= 0);		//양의 정수일 경우 탈출
			do
			{
				xy(10, 10);
				printf("삭제할 목표치를 입력하세요: ");
				scanf("%d", &l);
				system("cls");
			} while (l <= 0);		//0줄 이상일 경우 탈출
			view(0);		//커서 다시 숨김
		}
		else if (op == 3)		//대전 모드 일때
		{
			do
			{
				xy(20, 10);
				printf("난이도를 선택하세요   1: 상  2: 중  3: 하  ");
				scanf("%d", &lv);
				system("cls");
			} while (lv < 1 || lv > 3);		//레벨 범위에 들때 탈출
			if (lv == 1)			ca = 17;
			else if (lv == 2)		ca = 134;
			else if (lv == 3)		ca = 286;
			lv = 5 - lv;		//레벨 조정
		}
		if (op != 3)		screen();		//화면 & 초기 값 생성
		else				twoscreen();		//2화면 출력
		info();
		blockchange();		//초기 블록 생성
		wait();		//대기
		if (op == 2)			linemake();		//줄 생성
		else if (op == 3)		AI();		//컴퓨터 행동
		cpt = clock();
		p = play();
		color(7, 0);		//흰색
	}
}

//파일열기
void file()
{
	int a;

	FILE*fp = fopen("record.txt", "rt");
	for (a = 0; a < 3; a++)		fscanf(fp, "%d %d", &mc[a], &ba[a]);
	fclose(fp);
}

int main()
{
	srand(time(NULL));
	view(0);
	title();		//타이틀 출력
	keyreset();		//키 초기화
	file();		//파일 열기
	while (1)		game();		//게임 시작

	return 0;
}