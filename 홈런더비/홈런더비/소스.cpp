#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int lo = 0;		//비거리
int ma = 0;		//최고 기록
int sc = 0;		//총합점수
int y = 3;		//공 위치
int ch = 10;		//기회
int bs;			//구속
int s;		//시작 변수
int le;		//난이도

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

//배경색 변경
void color(short b)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 + (b << 4));
}

//삭제 함수
void erase(int y)
{
	int a;		//반복 변수

	xy(60, y);
	printf("  ");
}

//문장 삭제 함수
void clear()
{
	int a;		//반복 변수

	for (a = 0; a < 3; a++)
	{
		xy(90, 15 + a);
		printf("                 ");		//문장 공백으로 삭제
	}
	xy(57, 25);
	printf("                 ");		//구속 삭제
	xy(80, 3);
	printf("                 ");		//투구 상황 삭제
}

//선택함수
int option()
{
	int ke;

	xy(58,4);
	printf("난이도 설정");
	xy(57,6);
	printf("1:하     2:상");
	while (1)
	{
		ke = getch();
		if(ke=='1'||ke=='2')
		{
			break;
		}
	}
	system("cls");

	return ke-'1';
}

//타격 타이밍
void timing()
{
	int a, t = 1;		//반복 변수

	for (a = 0; a < 3; a++)
	{
		xy(59, 21 + a);
		color(12 + t * 2);
		printf(" ");
		t = !t;
	}
	color(0);
}

//타격 결과
void bat(int y)
{
	int ba, r = 0;		//타격 변수

	xy(90, 15);
	ba = rand() % 25;		//타격결과 확률
	if (y == 22)		//정확히 타격
	{
		if (ba < 6)
		{
			r = 1;
		}
		else if (ba < 12)
		{
			r = 2;
		}
		else if (ba < 18)
		{
			r = 3;
		}
		else
		{
			printf("홈런!");
			r = 4;
			ch++;
		}
	}
	else if (y == 21 || y == 23)		//타이밍 좀 놓친 타격
	{
		if (ba < 5)
		{
			printf("파울");
			r = 0;
		}
		else if (ba < 11)
		{
			r = 1;
		}
		else if (ba < 18)
		{
			r = 2;
		}
		else
		{
			r = 3;
		}
	}
	else
	{
		printf("헛스윙");
	}
	if (r == 1)			lo = rand() % 20 + 40;			//1루타 비거리
	else if (r == 2)	lo = rand() % 40 + 60;		//2루타 비거리
	else if (r == 3)	lo = rand() % 20 + 100;		//3루타 비거리
	else if (r == 4)	lo = rand() % 30 + 120;		//홈런 비거리
	else				lo = 0;
	if (lo != 0)		//안타일 경우 비거리 출력
	{
		xy(90, 16);
		printf("비거리 %d m", lo);
	}
	if (lo > ma)		//최고 기록을 경신했을때
	{
		ma = lo;		//최고 기록 초기화
		xy(90, 17);
		printf("최고 기록 경신!");
	}
	sc += lo;
}

//투구
void pitch()
{
	int sl;		//대기 시간

	if (s == 0)
	{
		xy(80,4);		
		printf("아무키나 누르면 시작합니다.");
		getch();
		xy(80,4);
		printf("                           ");
		s=!s;
	}
	bs = rand() % 50 + 80+20*le;		//구속
	sl = rand() % 500 + 1000;		//대기 시간
	xy(80, 3);
	printf("투구 대기중");
	Sleep(sl);
	clear();
}

//구속 출력
void bpr(int bs)
{
	y = 2;
	ch--;
	xy(57, 25);
	printf("%d KM/h", bs);		//구속 출력
}

//공 출력
void ball()
{
	clock_t st, et;		//시간 변수
	int ke = 0;		//키 입력 변수

	st = clock();		//시간 초기화
	while (ch>0)		//기회가 없어질때까지
	{
		xy(20, 1);
		printf("최고 기록:%3d", ma);
		xy(50, 1);
		printf("총합 점수:%4d", sc);
		xy(80, 1);
		printf("남은 공:%2d", ch);
		xy(60, y);		//공 위치
		printf("○");
		if (y == 3)
		{
			pitch();		//투구 대기
		}
		et = clock();		//현재 시간 초기화
		if (kbhit())		//키보드 눌릴 경우
		{
			ke = getch();		//눌린 키 대입
			if (ke == '\r')		//눌린 키가 엔터일경우
			{
				bat(y);		//타격 결과 출력
				erase(y);		//전에 출력한 공 공백으로 삭제
				st = clock();		//시간 초기화
				bpr(bs);
			}
		}
		if (et - st > 6000 / bs)		//일정 시간 지날 경우
		{
			erase(y);		//전에 출력한 공 공백으로 삭제
			st = clock();		//시간 초기화
			if (y == 29)		//공이 맨 밑까지 내려갔을 때
			{
				xy(90, 15);
				printf("스트라이크");
				ke = '\r';
				bpr(bs);
			}
			y++;		//공 위치 값 증가
		}
	}
	for (y = 0; y < 80; y++)
	{
		xy(20 + y, 1);
		printf(" ");
	}
}

//결과 출력
int result()
{
	int ke;

	xy(30, 15);
	printf("최고 기록:%d", ma);
	xy(70, 15);
	printf("총합 점수:%d", sc);
	xy(50, 18);
	printf("종료:ESC");
	ke = getch();
	if (ke == 27)
	{
		return 0;
	}
	else
	{
		ma = 0;
		sc = 0;
		y = 3;
		ch = 10;
		s = 0;
		system("cls");

		return 1;
	}
}

int main()
{
	int a = 1;

	srand(time(NULL));
	view(0);		//커서 숨김

	while (a)
	{
		le = option();		//난이도 선택
		timing();		//타격 타이밍 출력
		ball();			//공출력
		a = result();		//결과 출력
	}
	return 0;
}