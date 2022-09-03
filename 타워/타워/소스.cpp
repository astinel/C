#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

clock_t st, et;		//시간 변수
int ke;		//입력 변수
int lv, po;		//레벨, 점수
int x = 1;		//이동 블록의 좌표
int y;		//하강 블록의 y 좌표
int px;		//전 블록의 x 좌표
int he;		//블록의 높이

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

//삭제 함수
void erase(int x)
{
	int a;		//반복 변수

	for (a = 3; a <= 4; a++)		//블록의 세로 크기가 2
	{
		xy(x, a);
		printf("     ");		//공백으로 삭제
	}
}

//레벨
void level()
{
	xy(32, 1);
	printf("레벨:%2d", lv);
}

//점수
void point()
{
	xy(48, 1);
	printf("점수:%d", po);
}

//높이
void height()
{
	xy(64,1);
	printf("높이:%d",he);
}

//블록 출력 함수
void block(int x,int y)
{
	xy(x, y);
	printf("┌─┐");
	xy(x, y+1);
	printf("└─┘");
}

//처음 화면
void title()
{
	int t = 0;		//문장 출력 유무
	int co = 1;		//문자 색깔

	st = clock();		//시간 초기화
	xy(40, 1);
	printf("------타워------");

	while (1)		//무한 루프
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), co);		//글자 색깔 바꿈
		if (clock() - st >= 500)		//0.5초가 지날경우
		{
			st = clock();		//시간 다시 초기화
			xy(40, 20);
			t = !t;		//문장 출력 유무 바꿈
			if (t == 1)		//문장 출력할때
			{
				printf("PRESS ENTER TO START");
				co++;		//색깔 값 증가
				if (co > 15)		//표현할 수 있는 색깔까지 다 표현할경우
				{
					co = 1;		//1로 만듬
				}
			}
			else		//문장 출력 없을때
			{
				printf("                    ");		//공백으로 문장 삭제
			}
			if (kbhit())		//키가 입력 됬을때
			{
				ke = getch();		//입력한 키를 저장
				if (ke == '\r')		//입력한 키가 엔터일경우
				{
					break;		//반복문 탈출
				}
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);		//글자 색깔 바꿈
}

//블록 하강 함수
int fall()
{
	int re = 0;		//결과 반환 값

	he++;
	y -= 1;		//전 블록보다 위에 출력
	xy(x, y);
	printf("┌─┐");
	xy(x, y + 1);
	if (x == px)		//전 블록 바로 위에 떨어졌을때
	{
		printf("├─┤");
		re = 2;
	}
	else if (x == px - 2)		//전 블록에서 왼쪽으로 비껴서 떨어졌을때
	{
		printf("└┬┴");
		re = 1;
	}
	else if (x == px + 2)		//전 블록에서 오른쪽으로 비껴서 떨어졌을때
	{
		xy(x - 1, y + 1);
		printf("┴┬┘");
		re = 1;
	}
	else if (x == px - 4)		//전 블록 바로 왼쪽에 떨어졌을때
	{
		printf("└─┼");
	}
	else if (x == px + 4)		//전 블록 바로 오른쪽에 떨어졌을때
	{
		xy(x - 1, y + 1);
		printf("┼─┘");
	}
	else		//전 블록에서 먼 곳에 떨어졌을때
	{
		printf("└─┘");
	}
	px = x;		//현재 블록의 좌표 저장

	return re;
}

//타워 함수
void tower()
{
	int t = 1;		//이동 방향 변수
	int re = 1;		//결과 값
	int r=0;		//이동 반복 여부

	y = 28;			//초기 블록 위치 초기화
	px = 49;		//이전 블록 위치 초기화
	lv = 1;			//레벨 초기화
	po = 0;			//점수 초기화
	he = 1;			//높이 초기화

	system("cls");		//화면 삭제
	xy(px, y);
	printf("┌─┐");
	xy(px, y + 1);
	printf("└─┘");		//처음 블록 위치
	st = clock();		//초기 시간

	while (1)
	{
		level();		//레벨 출력
		point();		//점수 출력
		height();		//높이 출력
		block(x,3);		//블록 출력
		et = clock();		//현재 시간
		if (kbhit())		//키보드 눌릴때
		{
			ke = getch();		//입력 받음
			if (ke == '\r')		//누른 키가 엔터일때
			{
				re = fall();		//블록 하강
				erase(x);		//전에 출력한 블록 삭제
				x = 3;		//블록 위치 초기화
				t = 1;		//이동 방향 초기화
				r = 0;		//이동 반복 여부 초기화
				st = clock();		//시간 초기화
				if (re != 0)
				{
					xy(80, 6);
					printf("%d점 획득", re);
					po += re;
				}
			}
		}
		if (et - st >= 250/lv)
		{
			erase(x);		//전에 출력한 블록 삭제
			x += 2 * t;		//블록 위치 이동
			st = clock();		//시간 초기화
			if (x == 1 || x == 99)		//블록 위치가 양쪽 끝에 도달할 때
			{
				t *= -1;		//방향 바꿈
				r++;
			}
		}
		if (re == 0||r==2)
		{
			xy(16, 6);
			printf("실패..  최종 점수:%d", po);
			break;
		}
		else if (y == 9)
		{
			system("cls");
			y = 28;
			block(px, y);		//마지막으로 쌓았던 블록 위치에서 시작
			xy(80, 6);
			printf("%d점 획득", re);		//시스템 함수로 삭제된거 다시 출력
			lv++;		//레벨 업
		}
	}
}

//선택 함수
int option()
{
	int ke;

	xy(10, 8);
	printf("ENTER를 누르면 다시 시작 합니다");
	ke = getch();
	if (ke == '\r')
	{
		ke = 1;		//반복
	}
	else
	{
		ke = 0;
	}

	return ke;
}

int main()
{
	int rp;		//재시작 여부

	view(0);		//커서 안보임
	title();		//타이틀 출력
	do
	{
		tower();		//타워 함수 실행
		rp = option();		//재시작 여부 선택
	} while (rp);

	return 0;
}