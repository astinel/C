#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int x[4];		//위치
int p;		//플레이어 변수

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

//글자색 변경
void color(short t, short b)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), t + (b << 4));
}

//플레이어 위치
void player(int p)
{
	int a, b;

	a = 2 * (x[p] % 10);		//가로 좌표
	b = x[p] / 10;		//세로 좌표
	xy(a,b);		//커서 이동
	if (p == 0)
	{
		color(8,0);		//회색
		printf("☆");
	}
	else if (p == 1)
	{
		color(9, 0);		//파란색
		printf("◇");
	}
	else if (p == 2)
	{
		color(10, 0);		//초록색
		printf("♤");
	}
	else if (p == 3)
	{
		color(11, 0);		//하늘색
		printf("♡");
	}
	color(7, 0);		//흰색
}

//보드판 출력
void board()
{
	int a, b;

	xy(0,0);
	for (a=0;a<10;a++)
	{
		for (b = 0; b < 10; b++)
		{
			printf("□");
		}
		printf("\n");
	}
	for (a = 0; a <p ; a++)
	{
		player(a);		//플레이어 위치 출력
	}
}

//주사위 값 받음
int dice()
{
	int d;

	d = rand()%6+1;

	return d;
}

//위치  출력
void place()
{
	int a;		//반복 변수

	for (a = 0; a < p; a++)
	{
		xy(25, a+3);
		printf("%d P 위치:%3d",a+1, x[a] + 1);
	}
}

//게임 진행
int play()
{
	int d = 0;		//주사위 변수
	int r = 1;		//반복 변수
	int t = 0;		//플레이어 턴

	printf("참여할 인원을 입력해주세요(최대 4명):");
	scanf("%d",&p);		//인원 입력 받음
	system("cls");

	while (r)
	{
		board();		//보드 출력
		xy(25, 1);
		printf("%d P가 주사위를 굴립니다.", t + 1);
		getch();
		d = dice();		//주사위 값 받음
		x[t] += d;		//주사위 값만큼 이동
		if (x[t] >= 99)		//마지막 칸
		{
			x[t] = 99;		//99가 넘을경우 99로 초기화
			r = 0;		//반복문 탈출
		}
		xy(25, 2);
		printf("나온 주사위 값:%d", d);
		place();
		if (x[t] != 99)
		{
			t++;		//턴 바뀜
		}
		if (t == p)
		{
			t = 0;
		}
	}
	board();		//보드 출력
	xy(25, 8);
	printf("%d P 도착!", t + 1);

	return r;
}

int main()
{
	int r;		//재시작 변수

	view(0);		//커서 숨김
	srand(time(NULL));
	
	do
	{
		r = play();
	} while (r);
	
	getch();
	return 0;
}