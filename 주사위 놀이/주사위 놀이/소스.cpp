#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int x[4];		//��ġ
int p;		//�÷��̾� ����

//Ŀ�� �����
void view(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

//Ŀ�� �̵�
void xy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//���ڻ� ����
void color(short t, short b)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), t + (b << 4));
}

//�÷��̾� ��ġ
void player(int p)
{
	int a, b;

	a = 2 * (x[p] % 10);		//���� ��ǥ
	b = x[p] / 10;		//���� ��ǥ
	xy(a,b);		//Ŀ�� �̵�
	if (p == 0)
	{
		color(8,0);		//ȸ��
		printf("��");
	}
	else if (p == 1)
	{
		color(9, 0);		//�Ķ���
		printf("��");
	}
	else if (p == 2)
	{
		color(10, 0);		//�ʷϻ�
		printf("��");
	}
	else if (p == 3)
	{
		color(11, 0);		//�ϴû�
		printf("��");
	}
	color(7, 0);		//���
}

//������ ���
void board()
{
	int a, b;

	xy(0,0);
	for (a=0;a<10;a++)
	{
		for (b = 0; b < 10; b++)
		{
			printf("��");
		}
		printf("\n");
	}
	for (a = 0; a <p ; a++)
	{
		player(a);		//�÷��̾� ��ġ ���
	}
}

//�ֻ��� �� ����
int dice()
{
	int d;

	d = rand()%6+1;

	return d;
}

//��ġ  ���
void place()
{
	int a;		//�ݺ� ����

	for (a = 0; a < p; a++)
	{
		xy(25, a+3);
		printf("%d P ��ġ:%3d",a+1, x[a] + 1);
	}
}

//���� ����
int play()
{
	int d = 0;		//�ֻ��� ����
	int r = 1;		//�ݺ� ����
	int t = 0;		//�÷��̾� ��

	printf("������ �ο��� �Է����ּ���(�ִ� 4��):");
	scanf("%d",&p);		//�ο� �Է� ����
	system("cls");

	while (r)
	{
		board();		//���� ���
		xy(25, 1);
		printf("%d P�� �ֻ����� �����ϴ�.", t + 1);
		getch();
		d = dice();		//�ֻ��� �� ����
		x[t] += d;		//�ֻ��� ����ŭ �̵�
		if (x[t] >= 99)		//������ ĭ
		{
			x[t] = 99;		//99�� ������� 99�� �ʱ�ȭ
			r = 0;		//�ݺ��� Ż��
		}
		xy(25, 2);
		printf("���� �ֻ��� ��:%d", d);
		place();
		if (x[t] != 99)
		{
			t++;		//�� �ٲ�
		}
		if (t == p)
		{
			t = 0;
		}
	}
	board();		//���� ���
	xy(25, 8);
	printf("%d P ����!", t + 1);

	return r;
}

int main()
{
	int r;		//����� ����

	view(0);		//Ŀ�� ����
	srand(time(NULL));
	
	do
	{
		r = play();
	} while (r);
	
	getch();
	return 0;
}