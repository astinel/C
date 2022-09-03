#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int ho, min, sec, mil;		//시각 변수
int ts[15][4], re;		//시간 기록 변수(최대 15개까지 기록 가능)
int mo;				//모드 변수
int al;		//알람 변수

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
void clear(int y,int l)
{
	int a,b;		//반복 변수

	xy(0,y);
	for (a = 0; a < l; a++)
	{
		for (b = 0; b < 100; b++)
		{
			printf(" ");
		}
		printf("\n");
	}
}

//타이머 테두리 출력
void edge()
{
	xy(50, 8);		printf("┌──────┐");
	xy(50, 9);		printf("│            │");
	xy(50, 10);		printf("└──────┘");
}

//시간 출력 자리 조정
void timeprint()
{
	xy(52, 9);
	printf("%2d:", ho);		//시간 출력
	if (min<10)		//분이 1자리 수 일때
	{
		xy(55, 9);
		printf("0");		//자리수 공백을 0으로 채움
		xy(56, 9);
	}
	printf("%d:", min);		//분 출력
	if (sec < 10)		//초가 1자리 수 일때
	{
		xy(58, 9);
		printf("0");		//자리수 공백을 0으로 채움
		xy(59, 9);
	}
	printf("%d:", sec);		//초 출력
	if (mil < 10)		//밀리초가 1자리수일때
	{
		xy(61, 9);
		printf("0");		//자리수 공백을 0으로 채움
		xy(62, 9);
	}
	printf("%d │ ", mil);		//밀리초 출력
}

//시간 기록
void timerecord()
{
	int a,b;		//반복변수

	ts[0][0] = mil;		//밀리초 저장
	ts[0][1] = sec;		//초 저장
	ts[0][2] = min;		//분 저장
	ts[0][3] = ho;		//시간 저장
	xy(0, 5);
	for (a = re; a>=0; a--)		//기록한 시간 출력
	{
		printf("%2d번 기록: %2d시 %2d분 %2d초 %2d\n",re-a+1, ts[a][3], ts[a][2], ts[a][1], ts[a][0]);
	}
	if (re < 14)		//re는 증가하되 14를 넘길수 없음(최대가 14)
	{
		re++;		//re값 증가
	}
	for (a=re;a>0;a--)		//기록 시프트
	{
		for (b = 0; b < 4; b++)		//각 기록마다 4개의 데이터 시프트
		{
			ts[a][b] = ts[a - 1][b];
		}
	}
}

//시간 값 초기화
void reset()
{
	ho = 0;			//시간 초기화
	min = 0;		//분 초기화
	sec = 0;		//초 초기화
	mil = 0;		//밀리초 초기화
}

//타이머 함수
void timer()
{
	clock_t st=0, et=0;		//시간 변수
	int ke = 0, ks = 0;		//입력 변수

	system("cls");
	edge();		//테두리 출력
	xy(35, 12);
	printf("1:시작  2:일시정지  3:시간기록  4:초기화  0:모드변경");
	while (1)		//무한 루프
	{
		if (kbhit())		//키가 눌릴경우
		{
			ke = getch();		//키 입력 받음
			if (ke == '1')		//시작
			{
				if (ks != '1')		//전에 눌렀던 키가 시작이 아니여야함
				{
					st = clock();		//시작 시간
				}
			}
			else if (ke == '2')		//일시정지
			{
			}
			else if (ke == '3')		//시간기록
			{
				timerecord();		//시간 기록
				ke = ks;		//현 상태를 유지함
			}
			else if (ke == '4')
			{
				reset();		//초기화
				ke = ks;		//현 상태를 유지함
			}
			else if (ke == '0')		//알람 모드로 변경
			{
				mo = !mo;		//모드 변경
				break;		//반복문 탈출
			}
			else		//옵션 이외의 키가 눌릴경우
			{
				ke = ks;		//전에 눌럿던 키로 다시 초기화
			}
		}
		if (ke == '1')		//시작키를 누를경우 시간이 흐름
		{
			et = clock();		//현재 시간
			if (et - st >= 10)		//현재 시간이 시작 시간보다 0.01초 클때
			{
				st = clock();		//현재 시간을 다시 시작 시간으로 초기화
				mil++;		//밀리초 증가
			}
			if (mil >= 100)		//밀리초가 100 이상일대
			{
				sec++;		//초 증가
				mil -= 100;		//밀리초 100 감소
			}
			if (sec >= 60)		//초가 60 이상일때
			{
				min++;		//분 증가
				sec -= 60;		//초 60 감소
			}
			if (min >= 60)		//분이 60 이상일때
			{
				ho++;		//시간 증가
				min -= 60;		//분 60 감소
			}
		}
		ks = ke;		//키 입력 초기화
		timeprint();		//시간 출력 자리 조정
	}
}

//알람 함수
void alarm()
{
	clock_t st = 0, et = 0;		//시간 변수
	int ke;		//입력 변수
	int a;		//반복 변수

	system("cls");
	edge();
	reset();
	xy(40, 12);
	printf("1:알람 설정  2:기록 불러오기  3:알람 취소  0:모드 변경");
	while (1)
	{
		xy(52,9);		//테두리 안에 출력
		printf("%3d초 남음",al);
		if (kbhit())
		{
			ke = getch();
			if (ke == '1')		//알람 설정
			{
				view(1);		//커서 보임
				xy(40,15);
				printf("알람을 설정 합니다.");
				xy(40, 17);
				printf("설정할 초를 입력해주세요	");
				scanf("%d",&al);
				xy(40,19);
				printf("%d초 로 설정되었습니다.",al);
				getch();
				view(0);		//커서 안보임
				st = clock();		//시작 시간
				clear(15,5);		//15부터 5줄 삭제
			}
			else if (ke == '2')
			{
				xy(0, 0);
				if (re == 0)		continue;		//기록된게 없을때 다시 돌아감
				for (a = re-1; a >= 0; a--)		//기록한 시간 출력
				{
					printf("%2d번 기록: %2d시 %2d분 %2d초 %2d\n", re - a, ts[a][3], ts[a][2], ts[a][1], ts[a][0]);
				}	
			}
			else if (ke == '3')
			{
				al = 0;
			}
			else if (ke == '0')
			{
				mo = !mo;		//모드 변경
				break;		//반복문 탈출
			}
		}
		xy(40, 15);
		if (al != 0)
		{
			printf("알람 진행중");
			et = clock();
			if (et - st > 1000)
			{
				al--;
				st = clock();
			}
		}
		else
		{
			printf("알람 종료  ");
		}
	}
}

int main()
{
	view(0);		//커서 안보임
	while (1)
	{
		if(mo==0)	timer();		//타이머 작동
		else		alarm();		//알람 작동
	}
	getch();
	return 0;
}