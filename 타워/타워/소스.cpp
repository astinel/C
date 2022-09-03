#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

clock_t st, et;		//�ð� ����
int ke;		//�Է� ����
int lv, po;		//����, ����
int x = 1;		//�̵� ����� ��ǥ
int y;		//�ϰ� ����� y ��ǥ
int px;		//�� ����� x ��ǥ
int he;		//����� ����

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

//���� �Լ�
void erase(int x)
{
	int a;		//�ݺ� ����

	for (a = 3; a <= 4; a++)		//����� ���� ũ�Ⱑ 2
	{
		xy(x, a);
		printf("     ");		//�������� ����
	}
}

//����
void level()
{
	xy(32, 1);
	printf("����:%2d", lv);
}

//����
void point()
{
	xy(48, 1);
	printf("����:%d", po);
}

//����
void height()
{
	xy(64,1);
	printf("����:%d",he);
}

//��� ��� �Լ�
void block(int x,int y)
{
	xy(x, y);
	printf("������");
	xy(x, y+1);
	printf("������");
}

//ó�� ȭ��
void title()
{
	int t = 0;		//���� ��� ����
	int co = 1;		//���� ����

	st = clock();		//�ð� �ʱ�ȭ
	xy(40, 1);
	printf("------Ÿ��------");

	while (1)		//���� ����
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), co);		//���� ���� �ٲ�
		if (clock() - st >= 500)		//0.5�ʰ� �������
		{
			st = clock();		//�ð� �ٽ� �ʱ�ȭ
			xy(40, 20);
			t = !t;		//���� ��� ���� �ٲ�
			if (t == 1)		//���� ����Ҷ�
			{
				printf("PRESS ENTER TO START");
				co++;		//���� �� ����
				if (co > 15)		//ǥ���� �� �ִ� ������� �� ǥ���Ұ��
				{
					co = 1;		//1�� ����
				}
			}
			else		//���� ��� ������
			{
				printf("                    ");		//�������� ���� ����
			}
			if (kbhit())		//Ű�� �Է� ������
			{
				ke = getch();		//�Է��� Ű�� ����
				if (ke == '\r')		//�Է��� Ű�� �����ϰ��
				{
					break;		//�ݺ��� Ż��
				}
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);		//���� ���� �ٲ�
}

//��� �ϰ� �Լ�
int fall()
{
	int re = 0;		//��� ��ȯ ��

	he++;
	y -= 1;		//�� ��Ϻ��� ���� ���
	xy(x, y);
	printf("������");
	xy(x, y + 1);
	if (x == px)		//�� ��� �ٷ� ���� ����������
	{
		printf("������");
		re = 2;
	}
	else if (x == px - 2)		//�� ��Ͽ��� �������� �񲸼� ����������
	{
		printf("������");
		re = 1;
	}
	else if (x == px + 2)		//�� ��Ͽ��� ���������� �񲸼� ����������
	{
		xy(x - 1, y + 1);
		printf("������");
		re = 1;
	}
	else if (x == px - 4)		//�� ��� �ٷ� ���ʿ� ����������
	{
		printf("������");
	}
	else if (x == px + 4)		//�� ��� �ٷ� �����ʿ� ����������
	{
		xy(x - 1, y + 1);
		printf("������");
	}
	else		//�� ��Ͽ��� �� ���� ����������
	{
		printf("������");
	}
	px = x;		//���� ����� ��ǥ ����

	return re;
}

//Ÿ�� �Լ�
void tower()
{
	int t = 1;		//�̵� ���� ����
	int re = 1;		//��� ��
	int r=0;		//�̵� �ݺ� ����

	y = 28;			//�ʱ� ��� ��ġ �ʱ�ȭ
	px = 49;		//���� ��� ��ġ �ʱ�ȭ
	lv = 1;			//���� �ʱ�ȭ
	po = 0;			//���� �ʱ�ȭ
	he = 1;			//���� �ʱ�ȭ

	system("cls");		//ȭ�� ����
	xy(px, y);
	printf("������");
	xy(px, y + 1);
	printf("������");		//ó�� ��� ��ġ
	st = clock();		//�ʱ� �ð�

	while (1)
	{
		level();		//���� ���
		point();		//���� ���
		height();		//���� ���
		block(x,3);		//��� ���
		et = clock();		//���� �ð�
		if (kbhit())		//Ű���� ������
		{
			ke = getch();		//�Է� ����
			if (ke == '\r')		//���� Ű�� �����϶�
			{
				re = fall();		//��� �ϰ�
				erase(x);		//���� ����� ��� ����
				x = 3;		//��� ��ġ �ʱ�ȭ
				t = 1;		//�̵� ���� �ʱ�ȭ
				r = 0;		//�̵� �ݺ� ���� �ʱ�ȭ
				st = clock();		//�ð� �ʱ�ȭ
				if (re != 0)
				{
					xy(80, 6);
					printf("%d�� ȹ��", re);
					po += re;
				}
			}
		}
		if (et - st >= 250/lv)
		{
			erase(x);		//���� ����� ��� ����
			x += 2 * t;		//��� ��ġ �̵�
			st = clock();		//�ð� �ʱ�ȭ
			if (x == 1 || x == 99)		//��� ��ġ�� ���� ���� ������ ��
			{
				t *= -1;		//���� �ٲ�
				r++;
			}
		}
		if (re == 0||r==2)
		{
			xy(16, 6);
			printf("����..  ���� ����:%d", po);
			break;
		}
		else if (y == 9)
		{
			system("cls");
			y = 28;
			block(px, y);		//���������� �׾Ҵ� ��� ��ġ���� ����
			xy(80, 6);
			printf("%d�� ȹ��", re);		//�ý��� �Լ��� �����Ȱ� �ٽ� ���
			lv++;		//���� ��
		}
	}
}

//���� �Լ�
int option()
{
	int ke;

	xy(10, 8);
	printf("ENTER�� ������ �ٽ� ���� �մϴ�");
	ke = getch();
	if (ke == '\r')
	{
		ke = 1;		//�ݺ�
	}
	else
	{
		ke = 0;
	}

	return ke;
}

int main()
{
	int rp;		//����� ����

	view(0);		//Ŀ�� �Ⱥ���
	title();		//Ÿ��Ʋ ���
	do
	{
		tower();		//Ÿ�� �Լ� ����
		rp = option();		//����� ���� ����
	} while (rp);

	return 0;
}