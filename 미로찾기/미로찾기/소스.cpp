#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define max 30		//최대치

clock_t st, et;		//시간 변수
int ke;		//입력 변수
int x = 1, y = 1;		//위치 변수
int sta;			//상태 변수
int p[2],sl[2],el[2];		//위치 저장 변수
int tr[max][max];		//자취 배열
int ma[max][max];		//미로 배열

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
void color(short t, short b)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), t + (b << 4));
}

//삭제 함수
void erase(int x, int y)
{
	xy(x, y);
	printf("                           ");
}

//처음 화면
void title()
{
	int t = 0;		//문장 출력 유무
	int co = 1;		//문자 색깔
	int ke;		//입력 변수
	int a, b;		//반복 변수

	for (a = 0; a < 2; a++)
	{
		for (b = 0; b < 58; b++)
		{
			printf("─");
		}
		xy(0, 29);
		printf("└");
	}

	xy(0, 0);
	printf("┌-");
	for (a = 0; a < 2; a++)
	{
		for (b = 0; b < 28; b++)
		{
			xy(0 + 117 * a, b + 1);
			printf("│");
		}
	}
	xy(116, 0);
	printf("-┐");
	xy(117, 29);
	printf("┘");
	xy(50, 1);
	printf("-------미로-------");

	while (1)		//무한 루프
	{
		color(co, 0);		//글자 색깔 바꿈
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
	color(7, 0);		//글자 색깔 바꿈
	system("cls");
}

//블록 출력
void block(int x, int y)
{
	xy(2 * x, y);
	if (!ma[x][y])				printf("■");		//벽
	else if (ma[x][y] == 1)		printf("  ");		//길
	else if (ma[x][y] == 2)		printf("○");		//시작 지점
	else if (ma[x][y] == 3)		printf("☆");		//도착 지점
}

//옵션 출력
void option()
{
	xy(70, 3);	printf("1:미로 시작 또는 중단");
	xy(70, 4);	printf("2:시작 지점 등록(○)  3:도착 지점 등록(☆)");
	xy(70, 5);	printf("4:미로 랜덤 생성      5:길찾기");
	xy(70, 6);	printf("6:초기화              7:반전");
}

//상태 출력
void state()
{
	xy(70,1);
	printf("현재 상태:");
	if (sta == 1)				printf("미로 진행중");
	else if (ma[x][y] == 0)		printf("블럭 있음 ");
	else if (ma[x][y] == 1)		printf("블럭 없음 ");
	else if (ma[x][y] == 2)		printf("시작 지점 ");
	else if (ma[x][y] == 3)		printf("도착 지점 ");
}

//미로 출력
void maze()
{
	int a, b;		//반복변수

	for (a = 0; a<max; a++)		//미로 출력
	{
		for (b = 0; b < max; b++)
		{
			block(a, b);		//블록 출력
		}
	}
}

//플레이어 위치 출력
void player()
{
	xy(2 * p[0], p[1]);
	block(p[0],p[1]);		//플레이어가 지나간 자리에 블럭 출력
	xy(2 * x, y);
	printf("□");		//플레이어 출력
	p[0] = x;		//플레이어 가로 위치 저장
	p[1] = y;		//플레이어 위치 저장
}

//자취 정보 저장
void trace()
{
	int a, b;		//반복 변수
	int c;		//확인 변수

	for (a = 1; a < max-1; a++)		//자취 정보 판별
	{
		for (b = 1; b < max-1; b++)
		{
			c = 0;
			if (ma[a - 1][b])		c++;
			if (ma[a + 1][b])		c++;
			if (ma[a][b - 1])		c++;
			if (ma[a][b + 1])		c++;
			tr[a][b] = c;		//자취 정보 입력
		}
	}
	tr[sl[0]][sl[1]] += 1;		//시작 지점 초기화
	tr[el[0]][el[1]] += 1;		//도착 지점 초기화
}

//길 표시
void road(int x,int y)
{
	xy(2 * x, y);
	if (tr[x][y] >1)
	{
		color(0, 12);		//배경 빨간색
		printf("  ");
		tr[x][y]--;
	}
	else
	{
		block(x,y);
	}
	color(7, 0);		//흰색
}

//미로 찾기
void start()
{
	maze();		//미로 다시 출력
	player();		//플레이어 위치 출력
	state();		//상태 출력

	while (!(x == el[0] && y == el[1]))		//도착 지점에 도착 할때 까지 반복
	{
		ke = getch();

		if (ke == 224)
		{
			ke = getch();
			if (ke == 72)			y--;		//위로 이동	
			else if (ke == 75)		x--;		//왼쪽 이동
			else if (ke == 77)		x++;		//오른쪽 이동
			else if (ke == 80)		y++;		//아래 이동
		}
		else if (ke == '1')		break;		//미로 찾기 중단
		if (!ma[x][y])		//움직인 위치에 블럭이 있을경우
		{
			x = p[0];		//가로 좌표 호출
			y = p[1];		//세로 좌표 호출
		}
		else
		{
			player();		//플레이어 위치 출력
		}
	}
	if (ke != '1')		//중단으로 빠져 나오지 않았을때
	{
		xy(70, 25);		printf("성공!");
		getch();
		erase(70, 25);		//문장 삭제
	}
	sta = 0;
}

//길 찾기
int find()
{
	int ke = 0;		//입력 변수
	int di = 0;		//방향 변수
	int x, y;		//위치 변수
	int p[2];		//위치 저장 변수
	int mo = 0;		//이동 변수

	p[0] = x = sl[0];
	p[1] = y = sl[1];
	trace();		//자취 정보 초기화
	if (tr[sl[0]][sl[1]] == 1)		return 1;		//1차 판별
	road(x, y);		//길 표시
	st = clock();
	while (1)		//컴퓨터 길 찾기 인공지능
	{
		et = clock();
		di = ke % 4;		//동서남북 방향 4가지

		if (di == 0)		y--;		//위로 이동
		else if (di == 1)	x++;		//오른쪽 이동
		else if (di == 2)	y++;		//아래 이동
		else				x--;		//왼쪽 이동

		if (!ma[x][y])		//움직인 위치에 블럭이 있을경우
		{
			x = p[0];		//가로 좌표 호출
			y = p[1];		//세로 좌표 호출
			ke++;		//90도로 방향 회전
		}
		else
		{
			road(x,y);		//길 표시
			mo++;
			ke--;		//270도로 방향 회전
			p[0] = x;
			p[1] = y;
		}
		if (ke < 0)		ke += 4;
		if (!di*mo && x == sl[0] && y == sl[1])		return 2;		//길을 못찾을시(다시 출발점으로 돌아왔을때)
		else if (x == el[0] && y == el[1])			return 0;		//길 찾기 성공시
		else if (et - st > 1000)					return 1;
	}
}

//체크
void check()
{
	int a, b;

	xy(0, 0);
	for (a = 0; a < max; a++)
	{
		for (b = 0; b < max; b++)
		{
			printf("%2d", ma[b][a]);
		}
		printf("\n");
	}
	xy(0, 0);
	getch();
	maze();
}

//미로 생성
void make()
{
	int a, b;		//위치 변수
	int di = 0;		//방향 변수
	int l = 0, r = 0, ip;		//진행 변화
	int rs;

	for (a = 1; a < 29; a++)
	{
		for (b = 1; b < 29; b++)
		{
			ma[a][b] = 0;		//미로 초기화
		}
	}
	trace();		//자취 정보 저장
	a = rand() % 28 + 1;	b = rand() % 28 + 1;		//시작 지점 위치 생성
	sl[0] = a;	sl[1] = b;		//시작 지점 등록
	ma[a][b] = 2;		//시작 지점 초기화
	di = rand() % 4;		//초기 방향 설정
	el[0] = 0;		//도착 지점 초기화
	while (1)
	{
		l = rand() % 5 + 2;		//진행 길이
		for (ip = 0; l > 0; l--, ip++)		//진행 길이 만큼 반복
		{
			if (di == 0)			b--;		//위로 이동		
			else if (di == 1)		a++;		//오른쪽 이동	
			else if (di == 2)		b++;		//아래 이동
			else if (di == 3)		a--;		//왼쪽 이동
			if (!(a*b) || a == max - 1 || b == max - 1 || tr[a][b] > 1)			break;		//진행 방향으로 더 이상 미로 생성이 불가할 경우 종료
			if (ip > 0)		//분기점 생성 가능
			{
				r = rand()%3;		//분기점 생성 확률
				if (!r)
				{
					r = rand() % 2;		//분기점 방향 결정
					if (r)		ip = di + 1;		//90도 회전
					else		ip = di - 1;		//-90도 회전
					ma[a][b] = ip + 8;		//분기점 방향 값 저장(후에 나머지 연산시 범위 내의 방향값이 나옴)
					ip = 0;		//분기점 값 초기화
				}
				else
				{
					ma[a][b] = 1;
				}
			}
			else
			{
				ma[a][b] = 1;		//빈 블록 생성
			}
			trace();		//자취 정보 저장
			el[0] = a;	el[1] = b;		//도착 지점 위치 초기화
		}
		r = rand() % 2;		//진행 변화 결정
		if (r)	di++;		//90도 회전
		else	di--;		//-90도 회전
		if (di < 0)		di += 4;		//방향 값이 음수가 될 경우 양수로 만듬
		if (di == 4)		di %= 4;		//방향 값이 범위를 벗어날 경우 범위 안 값으로 만듬
		if (l)		//미로 생성 일시정지
		{
			ip = 0;
			for (a = 1; a < max - 1; a++)		//분기점 유무 판단
			{
				for (b = 1; b < max - 1; b++)
				{
					if (ma[a][b] > 4)		//분기점이 존재할 경우
					{
						ip = 1;		//분기점이 존재
						break;		//분기점 탐색 종료
					}
				}
				if (ip)		break;
			}
			if (ip)		//분기점이 존재할시
			{
				di = ma[a][b] % 4;		//방향값 초기화
				ma[a][b] = 1;		//빈 블록 생성
				continue;
			}
			break;		//분기점이 더 이상 존재하지 않을경우 미로 생성 종료
		}
	}
	if(el[0])	ma[el[0]][el[1]] = 3;		//도착 지점 초기화
}

//플레이어 이동
void miro()
{
	int ke = 0;		//키 입력 변수
	int di = 0;		//방향 변수
	int mo = 0;		//이동 변수
	int ch = 0;		//확인 변수
	int a, b;		//반복 변수

	while (1)
	{
		state();
		player();		//플레이어 출력
		ke = getch();
		if (sta == 2)		//미로 시작 오류 출력시
		{
			xy(70, 20);
			printf("                                             ");
			st = 0;
		}
		if (ke == 224)		//방향키가 눌릴경우
		{
			ke = getch();
			if (ke == 72)			y--;		//위로 이동
			else if (ke == 75)		x--;		//왼쪽 이동
			else if (ke == 77)		x++;		//오른쪽 이동
			else if (ke == 80)		y++;		//아래 이동
			if (x*y == 0 || x == max - 1 || y == max - 1)		//미로의 범위를 벗어나는 조건
			{
				x = p[0];		//가로 좌표 호출
				y = p[1];		//세로 좌표 호출
			}
		}
		else if (ke == '\r')		//블럭 상태 바꿈
		{
			if (ma[x][y] == 2)			sl[0] = 0;		//시작 지점일 경우 초기화
			else if (ma[x][y] == 3)		el[0] = 0;		//도착 지점일 경우 초기화
			ma[x][y] = !ma[x][y];		//블록 상태 바꿈
		}
		else if (ke == '1')		//미로 시작
		{
			if (sl[0] * el[0] == 0)		//시작 지점이나 도착 지점이 등록되어있지 않은 경우
			{
				sta = 2;
				xy(70, 20);		printf("시작 또는 도착 지점이 등록 되어있지 않습니다.");
				continue;		//처음으로
			}
			x = sl[0];		//현재 위치를 시작 지점의 가로 좌표로 초기화
			y = sl[1];		//현재 위치를 시작 지점의 세로 좌표로 초기화
			sta = 1;		//미로 진행 출력
			start();		//미로 시작
		}
		else if (ke == '2')		//시작 지점 등록
		{
			if (sl[0] != 0)		//이미 시작 지점이 등록 되있을 경우
			{
				ma[sl[0]][sl[1]] = 1;		//이전 시작 지점을 길로 바꿈
				block(sl[0],sl[1]);		//블록 교체 출력
			}
			sl[0] = x;		//현재 위치를 시작 지점으로 초기화
			sl[1] = y;		//현재 위치를 시작 지점으로 초기화
			ma[x][y] = 2;		//블럭을 시작 지점으로 바꿈		
			if (sl[0] == el[0] && sl[1] == el[1])		el[0] = 0;		//시작 지점과 도착 지점이 똑같을때 초기화		
		}
		else if (ke == '3')		//도착 지점 등록
		{
			if (el[0] != 0)		//이미 도착 지점이 등록 되있을 경우
			{
				ma[el[0]][el[1]] = 1;		//이전 도착 지점을 길로 바꿈
				block(el[0], el[1]);		//블록 교체 출력
			}
			el[0] = x;		//현재 위치를 도착 지점으로 초기화
			el[1] = y;		//현재 위치를 도착 지점으로 초기화
			ma[x][y] = 3;		//블럭을 도착 지점으로 바꿈
			if (sl[0] == el[0] && sl[1] == el[1])		sl[0] = 0;		//시작 지점과 도착 지점이 똑같을때 초기화		
		}
		else if (ke == '4')		//미로 랜덤 생성
		{
			while (ch < 9)		//9칸 이상의 미로 출력
			{
				ch = 0;
				make();		//미로 생성
				for (a = 1; a < max - 1; a++)
				{
					for (b = 1; b < max - 1; b++)
					{
						if (ma[a][b])	ch++;
					}
				}
			}
			ch = 0;
			maze();		//미로 재출력
		}
		else if (ke == '5')		//길 찾기
		{
			sta = 2;
			if (sl[0] * el[0] == 0)
			{
				xy(70, 20);		printf("길을 찾는데 실패하였습니다.");
				continue;
			}
			ch = find();		//길 찾기
			if (ch)		//길 찾기 실패
			{
				xy(70, 20);		printf("길을 찾는데 실패하였습니다.");
				if (ch > 1)		maze();		//미로 재출력
			}
			else
			{
				xy(70, 20);		printf("아무키나 누르면 진행합니다.");
				getch();
				maze();		//미로 재출력
			}
		}
		else if (ke == '6')		//초기화
		{
			for (a = 1; a < max - 1; a++)
			{
				for (b = 1; b < max - 1; b++)
				{
					ma[a][b] = 0;
				}
			}
			maze();		//미로 재출력
		}
		else if (ke == '7')		//반전
		{
			for (a = 1; a < max - 1; a++)
			{
				for (b = 1; b < max - 1; b++)
				{
					if (ma[a][b] <= 1)	ma[a][b] = !ma[a][b];		//0과 1을 서로 바꿈
				}
			}
			maze();		//미로 재출력
		}
		else if (ke == '0')
		{
			check();
		}
	}
}

int main()
{
	srand(time(NULL));
	view(0);
	title();
	option();		//옵션 출력

	maze();		//미로 출력
	miro();		//미로 이동

	getch();
	return 0;
}