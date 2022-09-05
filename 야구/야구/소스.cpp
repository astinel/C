#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int sc[2];		//점수
int i;		//이닝
int s[2][10];		//이닝 별 득점
int hit[2];		//팀 안타수
int B[2];		//팀 볼넷수
int t;		//팀
int c;		//스킵 변수

//커서이동
void xy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//팀 판별
void team()
{
	if (t == 0)
	{
		printf("내 팀 ");
	}
	else
	{
		printf("상대 팀 ");
	}
}

//점수
void score()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	sc[t] += s[t][i];		//이번 이닝에 득점한 점수만큼 증가
	if (t == 0)
	{
		printf("%d회초", i);
	}
	else
	{
		printf("%d회말", i);
	}
	team();
	printf("%d득점\n\n", s[t][i]);
	t = !t;		//공수교대
	if (c == '2')
	{
		Sleep(500);		//0.5초 지연
	}
}

//투구
int pit()
{
	int p;

	p = rand() % 2;		//볼,스트라이크 구분
	if (p == 0)
	{
		return 0;		//볼
	}
	else
	{
		return 1;		//스트라이크
	}
}

//공격
int bat()
{
	int sw, ba, p, a = 0;
	int s = 0, b = 0;		//카운트 변수

	while (s != 3)
	{
		a++;		//투구수 추가
		p = pit();		//투구 결과 받음
		if (c == '4')
		{
			Sleep(250);		//0.3초 지연
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("%d구째 ", a);
		sw = rand() % (t + 4);		//스윙 할 확률
		if (sw <= 2)		//스윙
		{
			ba = rand() % 4;		//안타 칠 확률
			if (ba == 0)		//안타
			{
				a = rand() % 20;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				team();
				hit[t]++;		//안타 추가
				if (a < 10)
				{
					printf("타자 안타! ");
					return 1;
				}
				else if (a >= 10 && a < 15)
				{
					printf("타자 2루타! ");
					return 2;
				}
				else if (a >= 15 && a < 17)
				{
					printf("타자 3루타! ");
					return 3;
				}
				else
				{
					printf("타자 홈런! ");
					return 4;
				}
			}
			else if (ba == 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("파울 ");
				s++;		//스트라이크 추가
				if (s == 3)		//3스트라이크일 때
				{
					s--;		//아웃이 안되도록 스트라이크수 감소
				}
			}
			else if (ba == 2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("헛스윙 스트라이크 ");
				s++;		//스트라이크 추가
			}
			else if (ba == 3)		
			{
				printf("스윙 ");
				s = 3;		//아웃
			}
		}
		else             //스윙 하지 않을 경우
		{
			if (p == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("볼 ");
				b++;		//볼 추가
				if (b == 4)		//볼이 4개일 경우
				{
					team();
					printf(" 타자 볼넷");
					return 5;
				}
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("스트라이크  ");
				s++;		//스트라이크 추가
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	return 0;
}

//베이스
void base()
{
	int b[4] = { 0 };  //베이스
	int o = 0;  //아웃
	int re;  //결과
	int r = 0;  //득점
	while (o != 3)
	{
		if (c == '3')
		{
			Sleep(300);		//0.3초 지연
		}
		b[0] = 1;		//타자 타석에 들어섬
		re = bat();		//타격 결과 받음
		if (re == 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			o++;		//아웃 추가
			team();
			printf("타자 아웃!");
		}
		else if (re == 1)		//1루타
		{
			re = b[3];		//3루에 주자 있을시 득점
			b[3] = b[2];
			b[2] = b[1];
			b[1] = b[0];
		}
		else if (re == 2)		//2루타
		{
			re = b[3] + b[2];		//2,3루에 주자 있을시 득점
			b[3] = b[1];
			b[2] = b[0];
			b[1] = 0;
		}
		else if (re == 3)
		{
			re = +b[3] + b[2] + b[1];		//1,2,3루에 주자 있을시 득점
			b[3] = b[0];
			b[2] = 0;
			b[1] = 0;
		}
		else if (re == 4)
		{
			re = b[3] + b[2] + b[1] + 1;		//루상에 나간 주자수+1만큼 득점
			b[3] = 0;
			b[2] = 0;
			b[1] = 0;		//루상에 나간 주자 모두 초기화
		}
		else
		{
			re = 0;
			if (b[1] == 0)		//1루가 비었을시
			{
			}
			else if (b[2] == 0)		//2루가 비었을시
			{
				b[2] = b[1];
			}
			else if (b[3] == 0)		//3루가 비었을시
			{
				b[3] = b[2];
				b[2] = b[1];
			}
			else  //만루일시
			{
				b[3] = b[2];
				b[2] = b[1];
				re++;
			}
			b[1] = b[0];
			B[t]++;		//볼넷 추가
		}
		if (re != 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			printf("  %d 득점", re);
			r += re;		//들어온 주자수 만큼 득점
		}
		printf("\n");
	}
	s[t][i] += r;		//이닝 득점 저장
	printf("\n");
}

//경기 결과
void result()
{
	getch();
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\n	경기가 종료되었습니다.\n\n");		//─│┌┐┘└├┬┤┴┼
	printf("┌─┬─┬─┬─┬─┬─┬─┬─┬─┐ \n");
	printf("│  │  │  │  │  │  │  │  │  │ \n");
	printf("├─┼─┼─┼─┼─┼─┼─┼─┼─┤ \n");
	printf("│  │  │  │  │  │  │  │  │  │ \n");
	printf("├─┼─┼─┼─┼─┼─┼─┼─┼─┤ \n");
	printf("│  │  │  │  │  │  │  │  │  │ \n");
	printf("└─┴─┴─┴─┴─┴─┴─┴─┴─┘ \n");
	printf("\n                       %d:%d", sc[0], sc[1]);
	printf("\n                       ");
	/*if (sc[0] > sc[1])
		printf("승리");
	else if (sc[0] == sc[1])
		printf("무승부");
	else
		printf("패배");
	for (i = 1; i <= 9; i++)		//이닝 별 득점 표시
	{
		xy(-2 + 3 * i, 4);
		printf("%X", s[0][i]);
		xy(-2 + 3 * i, 6);
		printf("%X", s[1][i]);
	}
	/*xy(33, 4);
	printf("%2d", sc[0]);		//내 팀 득점 표시
	xy(33, 6);
	printf("%2d", sc[1]);		//상대 팀 득점 표시
	xy(42, 4);
	printf("%2d", hit[0]);
	xy(42, 6);
	printf("%2d", hit[1]);
	xy(50, 4);
	printf("%2d", B[0]);
	xy(50, 6);
	printf("%2d", B[1])*/
}

int main()
{
	srand(time(NULL));

	printf("경기를 시작합니다.\n");
	printf("1:빠른 진행  2:이닝 스킵  3:타석 스킵  4:스킵 없음\n");
	while (c == 0)
	{
		c = getch();
		if (c >= '1'&&c <= '4')
		{
		}
		else
		{
			c = 0;
		}
	}
	for (i = 1; i <= 9; i++)
	{
		base();
		score();
		i -= t;		//내 팀 공격이 끝났을 경우 이닝이 증가하지 않음
	}
	result();		//결과 출력
	getch();
	return 0;
}