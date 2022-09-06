#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

clock_t st, et, pt;		//시간 변수
int xs = 59, fs[3], gs[2];		//저장 변수
int gk = 0, gx = 0, gy = 28, ga = 0;		//게이지
int d;		//거리
int x=59;		//위치 변수
int ch = 5;		//기회
int ke;		//입력 변수
int po = 0;		//현재 점수
int ad;		//추가 점수
int f;		//물고기 변수

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

//삭제 함수
void erase(int x,int y)
{
	xy(x, y);
	printf(" ");
}

//처음 화면
void title()
{
	int t = 0;		//문장 출력 유무
	int co = 1;		//문자 색깔
	int ke;		//입력 변수
	int a,b;		//반복 변수

	for (a = 0; a < 2; a++)
	{
		for (b = 0; b < 58; b++)
		{
			printf("─");
		}
		xy(0,29);
		printf("└");
	}
	
	xy(0,0);
	printf("┌-");
	for (a = 0; a < 2; a++)
	{
		for (b = 0; b < 28; b++)
		{
			xy(0+117*a,b+1);
			printf("│");
		}
	}
	xy(116, 0);
	printf("-┐");
	xy(117, 29);
	printf("┘");
	xy(50, 1);
	printf("-------낚시-------");

	while (1)		//무한 루프
	{
		color(co,0);		//글자 색깔 바꿈
		if (clock() - st >= 500)		//0.5초가 지날경우
		{
			st = clock();		//시간 다시 초기화
			xy(50, 20);
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
	color(7,0);		//글자 색깔 바꿈
	system("cls");
}

//갑판 출력
void deck()
{
	int a;

	xy(0,24);
	for (a = 0; a < 120; a++)		//한줄 출력
	{
		printf("-");
	}
}

//낚싯대 출력
void fishingpole(int x)
{
	int a;

	for (a = 0; a < 10; a++)		//이전에 출력한 낚싯대 삭제
	{
		erase(xs,20+a);
	}
	xy(xs,24);
	printf("-");
	for (a = 0; a < 10; a++)
	{
		xy(x, 20 + a);
		printf("│");
	}
	xs = x;		//이전 위치 저장
}

//물고기 그래픽 출력
void fish()
{
	int x, y;		//물고기 위치

	x = rand() % 101 + 10;		//물고기 가로 위치 선정
	y = rand() % 15 + 5;		//물고기 세로 위치 선정

	xy(x, y);
	printf("o");		//물고기 출력
	fs[0] = x;		//물고기 가로 위치 저장
	fs[1] = y;		//물고기 세로 위치 저장
}

//입질 대기
void wait()
{
	int t=0;		//시간 변수

	f = 3;		//물고기 변수 초기화
	t = rand()%1000+1000;		//입질 대기 시간
	st = clock();		//시간 초기화
	while (1)
	{
		et = clock();
		if (kbhit())		//키가 눌릴경우
		{
			ke = getch();		//키 입력 받음
			if (ke == '\r')		//엔터를 누를 경우
			{
				if (t != 0)		f = 0;
				else			break;		//반복문 탈출
			}
			if (ke == 224)
			{
				f = 0;		//낚시 취소(반복문 탈출)
			}
		}
		if (t != 0 && et >= st + t)		//입질 대기시간이 지난후
		{
			t = 0;		//입질중
			st = clock();		//시간 초기화
			xy(gs[0] + 3, gs[1]);
			printf("!");		//입질 알림 출력
		}
		if (t == 0 && et - st > 400)		//0.4초 지날경우
		{
			f--;		//물고기 변수 값 증가
			st = clock();		//시간 초기화
		}
		if (f == 0)		//입질이 시작한후 1.2초가 지난경우 또는 입질 전에 움직인 경우
		{
			break;		//반복문 탈출
		}
	}
	erase(gs[0] + 3, gs[1]);		//입질 알림 삭제
	erase(gs[0], gs[1]);		//낚시 지점 삭제
}

//게이지 함수
void gage()
{
	gk = 1;		//게이지 입력됨
	color(0, 12);		//게이지바 색깔은 빨간색
	xy(gx, gy);	printf(" ");		//게이지 출력
	gx++;		//게이지 증가
	ga++;		//게이지 값 증가
	if (gx == 10)
	{
		gx = 0;		//맨 왼쪽
		gy--;		//바로위에 게이지 출력
		if (gy == 25)		//3줄만 출력
		{
			gy++;		//게이지가 위로 올라가지 않음
		}
	}
	if (ga == 31)
	{
		ga--;		//게이지 최대치는 30
	}
	color(7, 0);		//색깔 원래대로 초기화
	st = clock();		//시간 초기화
}

//낚싯대 던짐 함수
int throw_pole()
{
	int si,po=0;		//물고기 크기

	ga = 19 - ga / 2;		//게이지 보정
	gs[0] = x;		//낚싯대 가로 위치 저장
	gs[1] = ga;		//낚싯대 세로 위치 저장
	d = fs[0] + fs[1] - x - ga;		//물고기와 낚싯대 거리
	for (; gy <= 28; gy++)		//출력한 게이지 삭제
	{
		xy(0, gy);	printf("          ");
	}
	erase(fs[0], fs[1]);		//전에 출력한 물고기 삭제
	xy(x, ga);	 printf("*");		//낚시 지점 출력
	if (d <= 2 && d >= -2)		si = rand() % 5 + 5;	//물고기 주위에 낚싯대를 던질경우
	else		si = rand() % 4 + 1;		//물고기에게서 떨어진 곳에서 낚싯대를 던질경우
	wait();		//입질 대기
	if (f == 0)		ch--;		//낚시 실패할 경우 기회 감소
	else			po = si + f;		//최종 점수
	xy(60, 2);	printf("%d CM", si);		//물고기 크기 출력
	fish();		//새로운 물고기 생성
	pt = clock();		//출력한 문자 삭제 시간 기준
	gk = 0;		//게이지 입력 초기화
	gx = 0;		//게이지량 초기화
	gy = 28;	//게이지높이 초기화
	ga = 0;		//게이지 값 초기화

	return po;
}

//낚시 함수
void fishing()
{
	fishingpole(x);		//낚싯대 출력
	fish();		//첫 물고기 생성

	while (ch > 0)
	{
		et = clock();
		if (kbhit())
		{
			ke = getch();
			if (ke == 224)		//방향키가 입력 됬을경우
			{
				ke = getch();
				if (ke == 75 && x != 10)			x--;		//오른쪽 방향키를 눌렀을때 오른쪽 이동
				else if (ke == 77 && x != 110)		x++;		//왼쪽 방향키를 눌렀을때 왼쪽 이동
			}
			else if (ke == ' ' )		gage();		//힘조절(스페이스바 입력시)
			fishingpole(x);		//낚싯대 출력
		}
		else if (gk == 1 && et - st > 300)		//낚싯대 던짐(키보드 미입력이 0.3초가 될경우)
		{
			ad = throw_pole();
			po += ad;
		}
		else if (et - st > 2000)		//마지막 낚시 이후로 2초가 지날경우
		{
			st = clock();		//시간 초기화
			erase(fs[0], fs[1]);		//전에 출력한 물고기 삭제
			fish();		//새 물고기 생성
		}
		if (et - pt > 400)		//문자 출력후 일정시간 후에 공백으로 삭제
		{
			xy(60, 2);	printf("             ");
		}
		xy(35, 1);	printf("현재 점수:%d", po);
		xy(75, 1);	printf("남은 기회:%d", ch);
	}
	xy(50, 15);	printf("종료!  최종 점수:%d\n", po);
}

//결과 변수
int result()
{
	int re=0;

	xy(50,16);	printf("0번을 누르시면 재시작 합니다.");
	re = getch();
	if (re == '0')		re = 1;
	else				re = 0;

	system("cls");

	return re;
}

int main()
{
	int ke;		//입력 변수
	int re;		//반복 변수

	srand(time(NULL));
	view(0);		//커서 감춤
	title();		//타이틀 출력

	do
	{
		deck();				//갑판 출력
		fishing();			//낚시
		re = result();		//결과 출력
	} while (re);

	return 0;
}