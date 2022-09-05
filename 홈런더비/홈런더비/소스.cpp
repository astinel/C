#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int lo = 0;		//��Ÿ�
int ma = 0;		//�ְ� ���
int sc = 0;		//��������
int y = 3;		//�� ��ġ
int ch = 10;		//��ȸ
int bs;			//����
int s;		//���� ����
int le;		//���̵�

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

//���� ����
void color(short b)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 + (b << 4));
}

//���� �Լ�
void erase(int y)
{
	int a;		//�ݺ� ����

	xy(60, y);
	printf("  ");
}

//���� ���� �Լ�
void clear()
{
	int a;		//�ݺ� ����

	for (a = 0; a < 3; a++)
	{
		xy(90, 15 + a);
		printf("                 ");		//���� �������� ����
	}
	xy(57, 25);
	printf("                 ");		//���� ����
	xy(80, 3);
	printf("                 ");		//���� ��Ȳ ����
}

//�����Լ�
int option()
{
	int ke;

	xy(58,4);
	printf("���̵� ����");
	xy(57,6);
	printf("1:��     2:��");
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

//Ÿ�� Ÿ�̹�
void timing()
{
	int a, t = 1;		//�ݺ� ����

	for (a = 0; a < 3; a++)
	{
		xy(59, 21 + a);
		color(12 + t * 2);
		printf(" ");
		t = !t;
	}
	color(0);
}

//Ÿ�� ���
void bat(int y)
{
	int ba, r = 0;		//Ÿ�� ����

	xy(90, 15);
	ba = rand() % 25;		//Ÿ�ݰ�� Ȯ��
	if (y == 22)		//��Ȯ�� Ÿ��
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
			printf("Ȩ��!");
			r = 4;
			ch++;
		}
	}
	else if (y == 21 || y == 23)		//Ÿ�̹� �� ��ģ Ÿ��
	{
		if (ba < 5)
		{
			printf("�Ŀ�");
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
		printf("�꽺��");
	}
	if (r == 1)			lo = rand() % 20 + 40;			//1��Ÿ ��Ÿ�
	else if (r == 2)	lo = rand() % 40 + 60;		//2��Ÿ ��Ÿ�
	else if (r == 3)	lo = rand() % 20 + 100;		//3��Ÿ ��Ÿ�
	else if (r == 4)	lo = rand() % 30 + 120;		//Ȩ�� ��Ÿ�
	else				lo = 0;
	if (lo != 0)		//��Ÿ�� ��� ��Ÿ� ���
	{
		xy(90, 16);
		printf("��Ÿ� %d m", lo);
	}
	if (lo > ma)		//�ְ� ����� ���������
	{
		ma = lo;		//�ְ� ��� �ʱ�ȭ
		xy(90, 17);
		printf("�ְ� ��� ���!");
	}
	sc += lo;
}

//����
void pitch()
{
	int sl;		//��� �ð�

	if (s == 0)
	{
		xy(80,4);		
		printf("�ƹ�Ű�� ������ �����մϴ�.");
		getch();
		xy(80,4);
		printf("                           ");
		s=!s;
	}
	bs = rand() % 50 + 80+20*le;		//����
	sl = rand() % 500 + 1000;		//��� �ð�
	xy(80, 3);
	printf("���� �����");
	Sleep(sl);
	clear();
}

//���� ���
void bpr(int bs)
{
	y = 2;
	ch--;
	xy(57, 25);
	printf("%d KM/h", bs);		//���� ���
}

//�� ���
void ball()
{
	clock_t st, et;		//�ð� ����
	int ke = 0;		//Ű �Է� ����

	st = clock();		//�ð� �ʱ�ȭ
	while (ch>0)		//��ȸ�� ������������
	{
		xy(20, 1);
		printf("�ְ� ���:%3d", ma);
		xy(50, 1);
		printf("���� ����:%4d", sc);
		xy(80, 1);
		printf("���� ��:%2d", ch);
		xy(60, y);		//�� ��ġ
		printf("��");
		if (y == 3)
		{
			pitch();		//���� ���
		}
		et = clock();		//���� �ð� �ʱ�ȭ
		if (kbhit())		//Ű���� ���� ���
		{
			ke = getch();		//���� Ű ����
			if (ke == '\r')		//���� Ű�� �����ϰ��
			{
				bat(y);		//Ÿ�� ��� ���
				erase(y);		//���� ����� �� �������� ����
				st = clock();		//�ð� �ʱ�ȭ
				bpr(bs);
			}
		}
		if (et - st > 6000 / bs)		//���� �ð� ���� ���
		{
			erase(y);		//���� ����� �� �������� ����
			st = clock();		//�ð� �ʱ�ȭ
			if (y == 29)		//���� �� �ر��� �������� ��
			{
				xy(90, 15);
				printf("��Ʈ����ũ");
				ke = '\r';
				bpr(bs);
			}
			y++;		//�� ��ġ �� ����
		}
	}
	for (y = 0; y < 80; y++)
	{
		xy(20 + y, 1);
		printf(" ");
	}
}

//��� ���
int result()
{
	int ke;

	xy(30, 15);
	printf("�ְ� ���:%d", ma);
	xy(70, 15);
	printf("���� ����:%d", sc);
	xy(50, 18);
	printf("����:ESC");
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
	view(0);		//Ŀ�� ����

	while (a)
	{
		le = option();		//���̵� ����
		timing();		//Ÿ�� Ÿ�̹� ���
		ball();			//�����
		a = result();		//��� ���
	}
	return 0;
}