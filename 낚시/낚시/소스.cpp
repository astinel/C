#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

clock_t st, et, pt;		//�ð� ����
int xs = 59, fs[3], gs[2];		//���� ����
int gk = 0, gx = 0, gy = 28, ga = 0;		//������
int d;		//�Ÿ�
int x=59;		//��ġ ����
int ch = 5;		//��ȸ
int ke;		//�Է� ����
int po = 0;		//���� ����
int ad;		//�߰� ����
int f;		//����� ����

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

//���� �Լ�
void erase(int x,int y)
{
	xy(x, y);
	printf(" ");
}

//ó�� ȭ��
void title()
{
	int t = 0;		//���� ��� ����
	int co = 1;		//���� ����
	int ke;		//�Է� ����
	int a,b;		//�ݺ� ����

	for (a = 0; a < 2; a++)
	{
		for (b = 0; b < 58; b++)
		{
			printf("��");
		}
		xy(0,29);
		printf("��");
	}
	
	xy(0,0);
	printf("��-");
	for (a = 0; a < 2; a++)
	{
		for (b = 0; b < 28; b++)
		{
			xy(0+117*a,b+1);
			printf("��");
		}
	}
	xy(116, 0);
	printf("-��");
	xy(117, 29);
	printf("��");
	xy(50, 1);
	printf("-------����-------");

	while (1)		//���� ����
	{
		color(co,0);		//���� ���� �ٲ�
		if (clock() - st >= 500)		//0.5�ʰ� �������
		{
			st = clock();		//�ð� �ٽ� �ʱ�ȭ
			xy(50, 20);
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
	color(7,0);		//���� ���� �ٲ�
	system("cls");
}

//���� ���
void deck()
{
	int a;

	xy(0,24);
	for (a = 0; a < 120; a++)		//���� ���
	{
		printf("-");
	}
}

//���˴� ���
void fishingpole(int x)
{
	int a;

	for (a = 0; a < 10; a++)		//������ ����� ���˴� ����
	{
		erase(xs,20+a);
	}
	xy(xs,24);
	printf("-");
	for (a = 0; a < 10; a++)
	{
		xy(x, 20 + a);
		printf("��");
	}
	xs = x;		//���� ��ġ ����
}

//����� �׷��� ���
void fish()
{
	int x, y;		//����� ��ġ

	x = rand() % 101 + 10;		//����� ���� ��ġ ����
	y = rand() % 15 + 5;		//����� ���� ��ġ ����

	xy(x, y);
	printf("o");		//����� ���
	fs[0] = x;		//����� ���� ��ġ ����
	fs[1] = y;		//����� ���� ��ġ ����
}

//���� ���
void wait()
{
	int t=0;		//�ð� ����

	f = 3;		//����� ���� �ʱ�ȭ
	t = rand()%1000+1000;		//���� ��� �ð�
	st = clock();		//�ð� �ʱ�ȭ
	while (1)
	{
		et = clock();
		if (kbhit())		//Ű�� �������
		{
			ke = getch();		//Ű �Է� ����
			if (ke == '\r')		//���͸� ���� ���
			{
				if (t != 0)		f = 0;
				else			break;		//�ݺ��� Ż��
			}
			if (ke == 224)
			{
				f = 0;		//���� ���(�ݺ��� Ż��)
			}
		}
		if (t != 0 && et >= st + t)		//���� ���ð��� ������
		{
			t = 0;		//������
			st = clock();		//�ð� �ʱ�ȭ
			xy(gs[0] + 3, gs[1]);
			printf("!");		//���� �˸� ���
		}
		if (t == 0 && et - st > 400)		//0.4�� �������
		{
			f--;		//����� ���� �� ����
			st = clock();		//�ð� �ʱ�ȭ
		}
		if (f == 0)		//������ �������� 1.2�ʰ� ������� �Ǵ� ���� ���� ������ ���
		{
			break;		//�ݺ��� Ż��
		}
	}
	erase(gs[0] + 3, gs[1]);		//���� �˸� ����
	erase(gs[0], gs[1]);		//���� ���� ����
}

//������ �Լ�
void gage()
{
	gk = 1;		//������ �Էµ�
	color(0, 12);		//�������� ������ ������
	xy(gx, gy);	printf(" ");		//������ ���
	gx++;		//������ ����
	ga++;		//������ �� ����
	if (gx == 10)
	{
		gx = 0;		//�� ����
		gy--;		//�ٷ����� ������ ���
		if (gy == 25)		//3�ٸ� ���
		{
			gy++;		//�������� ���� �ö��� ����
		}
	}
	if (ga == 31)
	{
		ga--;		//������ �ִ�ġ�� 30
	}
	color(7, 0);		//���� ������� �ʱ�ȭ
	st = clock();		//�ð� �ʱ�ȭ
}

//���˴� ���� �Լ�
int throw_pole()
{
	int si,po=0;		//����� ũ��

	ga = 19 - ga / 2;		//������ ����
	gs[0] = x;		//���˴� ���� ��ġ ����
	gs[1] = ga;		//���˴� ���� ��ġ ����
	d = fs[0] + fs[1] - x - ga;		//������ ���˴� �Ÿ�
	for (; gy <= 28; gy++)		//����� ������ ����
	{
		xy(0, gy);	printf("          ");
	}
	erase(fs[0], fs[1]);		//���� ����� ����� ����
	xy(x, ga);	 printf("*");		//���� ���� ���
	if (d <= 2 && d >= -2)		si = rand() % 5 + 5;	//����� ������ ���˴븦 �������
	else		si = rand() % 4 + 1;		//����⿡�Լ� ������ ������ ���˴븦 �������
	wait();		//���� ���
	if (f == 0)		ch--;		//���� ������ ��� ��ȸ ����
	else			po = si + f;		//���� ����
	xy(60, 2);	printf("%d CM", si);		//����� ũ�� ���
	fish();		//���ο� ����� ����
	pt = clock();		//����� ���� ���� �ð� ����
	gk = 0;		//������ �Է� �ʱ�ȭ
	gx = 0;		//�������� �ʱ�ȭ
	gy = 28;	//���������� �ʱ�ȭ
	ga = 0;		//������ �� �ʱ�ȭ

	return po;
}

//���� �Լ�
void fishing()
{
	fishingpole(x);		//���˴� ���
	fish();		//ù ����� ����

	while (ch > 0)
	{
		et = clock();
		if (kbhit())
		{
			ke = getch();
			if (ke == 224)		//����Ű�� �Է� �������
			{
				ke = getch();
				if (ke == 75 && x != 10)			x--;		//������ ����Ű�� �������� ������ �̵�
				else if (ke == 77 && x != 110)		x++;		//���� ����Ű�� �������� ���� �̵�
			}
			else if (ke == ' ' )		gage();		//������(�����̽��� �Է½�)
			fishingpole(x);		//���˴� ���
		}
		else if (gk == 1 && et - st > 300)		//���˴� ����(Ű���� ���Է��� 0.3�ʰ� �ɰ��)
		{
			ad = throw_pole();
			po += ad;
		}
		else if (et - st > 2000)		//������ ���� ���ķ� 2�ʰ� �������
		{
			st = clock();		//�ð� �ʱ�ȭ
			erase(fs[0], fs[1]);		//���� ����� ����� ����
			fish();		//�� ����� ����
		}
		if (et - pt > 400)		//���� ����� �����ð� �Ŀ� �������� ����
		{
			xy(60, 2);	printf("             ");
		}
		xy(35, 1);	printf("���� ����:%d", po);
		xy(75, 1);	printf("���� ��ȸ:%d", ch);
	}
	xy(50, 15);	printf("����!  ���� ����:%d\n", po);
}

//��� ����
int result()
{
	int re=0;

	xy(50,16);	printf("0���� �����ø� ����� �մϴ�.");
	re = getch();
	if (re == '0')		re = 1;
	else				re = 0;

	system("cls");

	return re;
}

int main()
{
	int ke;		//�Է� ����
	int re;		//�ݺ� ����

	srand(time(NULL));
	view(0);		//Ŀ�� ����
	title();		//Ÿ��Ʋ ���

	do
	{
		deck();				//���� ���
		fishing();			//����
		re = result();		//��� ���
	} while (re);

	return 0;
}