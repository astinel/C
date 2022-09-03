#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>

int ke;		//입력 변수
int nu;		//사과 개수
int ap[100];		//사과 변수
int pa;		//독 사과 변수

//커서 숨기기
void CursorView(char show)
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
void erase(int x, int y)
{
	xy(x, y);
	printf(" ");		//출력한 사과를 공백으로 삭제
}

//처음 화면
void title()
{
	clock_t st, et;		//시간 변수
	int t = 0;		//문장 출력 유무
	int co = 1;		//문자 색깔

	st = clock();		//시간 초기화
	xy(40, 1);
	printf("-----사과나무게임-----");

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
				xy(0, 0);		//커서 이동하여 보이지 않게함
				co++;		//색깔 값 증가
				if (co > 15)		//표현할 수 있는 색깔까지 다 표현할경우
				{
					co = 1;		//1로 만듬
				}
			}
			else		//문장 출력 없을때
			{
				printf("                    ");		//공백으로 문장 삭제
				xy(0, 0);		//커서 이동하여 보이지 않게함
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
}

//사과 함수
void apple()
{
	int a;		//반복 변수
	int b;		//랜덤 변수
	int s=0;		//카운트 변수

	for (a=0;a<100;a++)
	{
		ap[a] = 0;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);		//글자 색 흰색으로 바꿈
	while (1)		//무한 루프
	{
		system("cls");		//화면 지움
		xy(40, 1);
		printf("사과개수를 입력해주세요(최소60,최대100개)\n");
		scanf("%d", &nu);		//사과 개수 입력 받음
		if (nu >= 60 && nu <= 100)		//사과 개수의 범위 안에 들때
		{
			break;		//반복문 탈출
		}
	}
	for (a=0;s!=nu;a++)		//사과 랜덤 배치
	{
		b = rand()%2;		//사과가 배치 될 확률
		if (b==0&&ap[a] == 0)
		{
			s++;		//사과가 배치된수 만큼 카운트
			ap[a] = 1;		//사과로 만듬
		}
		if (a==99)		//사과 배치가 덜끝났을경우
		{
			a = -1;		//처음부터
		}
	}
	for (a = 0;; a++)		//독 사과 랜덤 배치
	{
		b = rand() % nu;		//독 사과가 될 확룔
		if (b == 0&&ap[a]==1)
		{
			ap[a] = 2;		//독 사과로 만듬
			pa = a;		//독 사과 위치 저장
			break;		//독 사과가 만들어질 경우 탈출
		}
		if (a == 99)		//사과 배치가 덜끝났을경우
		{
			a = -1;		//처음부터
		}
	}
	system("cls");		//화면 지움	
}

//나뭇잎 출력
void leaf()
{
	int a,b=1,s;		//반복 변수
	int c=0;		//사과 개수 카운트 변수

	for (a=1;a<=10;a++,b+=2)
	{
		xy(40-a,a+3);
		for (s=1;s<=b;s++,c++)
		{
			if(ap[c]==2)			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);		//독 사과색은 자주색
			else if (ap[c] == 1)	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);		//사과색은 빨간색
			else					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);		//나뭇잎 색은 연두색
			printf("*");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);		//글자색 흰색으로 바꿈
}

//나무 기둥 출력
void wood()
{
	int a;		//반복 변수

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);		//글자색 흰색으로 바꿈
	for (a=1;a<=5;a++)
	{
		xy(38, a+13);
		printf("***");
	}
}

//추락 그래픽
void fall(int c)
{
	int a,b;		//반복 변수
	int xs[100],ys[100];		//좌표 저장

	for (a = 0; a < c; a++)		//떨어진 사과 개수 만큼 반복
	{
		xs[a] = rand() % 20 + 30;		//추락하는 가로위치 선정
		ys[a] = rand() % 6 + 15;		//추락하는 세로위치 선정
	}
	for (a = 0; a<2; a++)		//추락
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);		//사과색은 빨간색
		for (b = 0; b < c; b++)		//떨어진 사과 개수 만큼 반복
		{
			xy(xs[b], ys[b] + a);
			printf("*");		//추락하는 사과 출력
		}
		Sleep(500);		//0.5초 지연
		for (b = 0; b < c; b++)		//떨어지는 사과 삭제
		{
			erase(xs[b],ys[b]+a);		//출력한 사과 삭제
		}
		wood();		//가려질것을 대비해 나무 기둥 다시 출력
	}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);		//글자색 흰색으로 바꿈
}

//나무 함수
void tree()
{
	int ke;			//입력 변수
	int fa;			//사과가 떨어질 확률
	int a;			//반복 변수
	int c=0;		//카운트 변수
	int lo = 0, log[10] = {0},ks=0;		//로그변수

	wood();		//나무 기둥 출력
	while (1)		//무한루프
	{
		if (kbhit())		//키가 입력 됬을때
		{
			ke = getch();		//입력한 키를 저장
			if (ke == 224)		//방향키일 경우 처음에 224를 반환
			{
				ke = getch();		//두 번째로 다른 숫자를 입력받음
				if (ke == 72 || ke == 75 || ke == 77 || ke == 80)		//상하좌우의 두 번째 아스키 코드 값
				{
					xy(15, 25);
					printf("                                 ");		//공백으로 문장 삭제
					for (a=0;a<100;a++)
					{
						if (ap[a] == 0)		//이미 떨어진 사과일경우
						{
							continue;		//처음으로
						}
						fa = rand()% (nu / 5);		//사과가 떨어질 확룰(오류)
						if (fa == 0)
						{
							c++;		//떨어진 사과의 개수 카운트
							ap[a] = 0;		//사과 떨어짐
						}
					}
					nu -= log[0]=  c;		//떨어진 개수 만큼 사과 개수 감소,로그 기록
					xy(60, 10);
					printf("사과가 %d개 떨어졌습니다.", c);
					xy(60,14);
					printf("로그");
					for (a = 1; a <= lo; a++)		//로그 출력
					{
						xy(60, 15 + a);
						printf("%2d", log[a]);
					}
					for (a=9;a>=1;a--)		//로그 시프트
					{
						log[a] = log[a - 1];
					}
					if (lo < 9)
					{
						lo++;		//로그 기록 공간 늘림
					}
					if (nu < 0)		//남은 사과개수가 음수가 될경우
					{
						nu = 0;		//0으로 초기화
					}
					if (ap[pa] == 0||nu<4)		//독 사과 떨어짐
					{
						xy(60,12);
						ap[pa] = 0;		//사과나무 개수로 들어왔을 경우를 대비하여 초기화
						printf("독 사과가 떨어졌습니다.");
						leaf();		//독 사과 없는 나무 출력
					}
				}
			}
		}
		xy(40, 1);
		printf("남은 사과개수:%3d", nu);		//남은 사과 개수 출력
		leaf();		//나뭇잎 출력
		if (c!=0)		//사과가 떨어졌을때
		{
			fall(c);		//사과 추락 그래픽 출력
			c = 0;
		}
		if (ap[pa] == 0)	break;		//독 사과 떨어짐
	}
}

//선택 함수
void chose()
{
	Sleep(1000);		//1초 지연
	xy(15, 27);
	printf("다시하려면 0을 눌러주세요");
	ke = getch();
}

int main()
{
	CursorView(0);		//커서 숨기기
	title();
	srand(time(NULL));
	while (1)
	{
		apple();
		tree();
		chose();
		if (ke != '0')
		{
			break;
		}
	}
	return 0;
}
