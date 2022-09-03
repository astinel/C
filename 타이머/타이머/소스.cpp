#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int ho, min, sec, mil;		//�ð� ����
int ts[15][4], re;		//�ð� ��� ����(�ִ� 15������ ��� ����)
int mo;				//��� ����
int al;		//�˶� ����

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
void clear(int y,int l)
{
	int a,b;		//�ݺ� ����

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

//Ÿ�̸� �׵θ� ���
void edge()
{
	xy(50, 8);		printf("����������������");
	xy(50, 9);		printf("��            ��");
	xy(50, 10);		printf("����������������");
}

//�ð� ��� �ڸ� ����
void timeprint()
{
	xy(52, 9);
	printf("%2d:", ho);		//�ð� ���
	if (min<10)		//���� 1�ڸ� �� �϶�
	{
		xy(55, 9);
		printf("0");		//�ڸ��� ������ 0���� ä��
		xy(56, 9);
	}
	printf("%d:", min);		//�� ���
	if (sec < 10)		//�ʰ� 1�ڸ� �� �϶�
	{
		xy(58, 9);
		printf("0");		//�ڸ��� ������ 0���� ä��
		xy(59, 9);
	}
	printf("%d:", sec);		//�� ���
	if (mil < 10)		//�и��ʰ� 1�ڸ����϶�
	{
		xy(61, 9);
		printf("0");		//�ڸ��� ������ 0���� ä��
		xy(62, 9);
	}
	printf("%d �� ", mil);		//�и��� ���
}

//�ð� ���
void timerecord()
{
	int a,b;		//�ݺ�����

	ts[0][0] = mil;		//�и��� ����
	ts[0][1] = sec;		//�� ����
	ts[0][2] = min;		//�� ����
	ts[0][3] = ho;		//�ð� ����
	xy(0, 5);
	for (a = re; a>=0; a--)		//����� �ð� ���
	{
		printf("%2d�� ���: %2d�� %2d�� %2d�� %2d\n",re-a+1, ts[a][3], ts[a][2], ts[a][1], ts[a][0]);
	}
	if (re < 14)		//re�� �����ϵ� 14�� �ѱ�� ����(�ִ밡 14)
	{
		re++;		//re�� ����
	}
	for (a=re;a>0;a--)		//��� ����Ʈ
	{
		for (b = 0; b < 4; b++)		//�� ��ϸ��� 4���� ������ ����Ʈ
		{
			ts[a][b] = ts[a - 1][b];
		}
	}
}

//�ð� �� �ʱ�ȭ
void reset()
{
	ho = 0;			//�ð� �ʱ�ȭ
	min = 0;		//�� �ʱ�ȭ
	sec = 0;		//�� �ʱ�ȭ
	mil = 0;		//�и��� �ʱ�ȭ
}

//Ÿ�̸� �Լ�
void timer()
{
	clock_t st=0, et=0;		//�ð� ����
	int ke = 0, ks = 0;		//�Է� ����

	system("cls");
	edge();		//�׵θ� ���
	xy(35, 12);
	printf("1:����  2:�Ͻ�����  3:�ð����  4:�ʱ�ȭ  0:��庯��");
	while (1)		//���� ����
	{
		if (kbhit())		//Ű�� �������
		{
			ke = getch();		//Ű �Է� ����
			if (ke == '1')		//����
			{
				if (ks != '1')		//���� ������ Ű�� ������ �ƴϿ�����
				{
					st = clock();		//���� �ð�
				}
			}
			else if (ke == '2')		//�Ͻ�����
			{
			}
			else if (ke == '3')		//�ð����
			{
				timerecord();		//�ð� ���
				ke = ks;		//�� ���¸� ������
			}
			else if (ke == '4')
			{
				reset();		//�ʱ�ȭ
				ke = ks;		//�� ���¸� ������
			}
			else if (ke == '0')		//�˶� ���� ����
			{
				mo = !mo;		//��� ����
				break;		//�ݺ��� Ż��
			}
			else		//�ɼ� �̿��� Ű�� �������
			{
				ke = ks;		//���� ������ Ű�� �ٽ� �ʱ�ȭ
			}
		}
		if (ke == '1')		//����Ű�� ������� �ð��� �帧
		{
			et = clock();		//���� �ð�
			if (et - st >= 10)		//���� �ð��� ���� �ð����� 0.01�� Ŭ��
			{
				st = clock();		//���� �ð��� �ٽ� ���� �ð����� �ʱ�ȭ
				mil++;		//�и��� ����
			}
			if (mil >= 100)		//�и��ʰ� 100 �̻��ϴ�
			{
				sec++;		//�� ����
				mil -= 100;		//�и��� 100 ����
			}
			if (sec >= 60)		//�ʰ� 60 �̻��϶�
			{
				min++;		//�� ����
				sec -= 60;		//�� 60 ����
			}
			if (min >= 60)		//���� 60 �̻��϶�
			{
				ho++;		//�ð� ����
				min -= 60;		//�� 60 ����
			}
		}
		ks = ke;		//Ű �Է� �ʱ�ȭ
		timeprint();		//�ð� ��� �ڸ� ����
	}
}

//�˶� �Լ�
void alarm()
{
	clock_t st = 0, et = 0;		//�ð� ����
	int ke;		//�Է� ����
	int a;		//�ݺ� ����

	system("cls");
	edge();
	reset();
	xy(40, 12);
	printf("1:�˶� ����  2:��� �ҷ�����  3:�˶� ���  0:��� ����");
	while (1)
	{
		xy(52,9);		//�׵θ� �ȿ� ���
		printf("%3d�� ����",al);
		if (kbhit())
		{
			ke = getch();
			if (ke == '1')		//�˶� ����
			{
				view(1);		//Ŀ�� ����
				xy(40,15);
				printf("�˶��� ���� �մϴ�.");
				xy(40, 17);
				printf("������ �ʸ� �Է����ּ���	");
				scanf("%d",&al);
				xy(40,19);
				printf("%d�� �� �����Ǿ����ϴ�.",al);
				getch();
				view(0);		//Ŀ�� �Ⱥ���
				st = clock();		//���� �ð�
				clear(15,5);		//15���� 5�� ����
			}
			else if (ke == '2')
			{
				xy(0, 0);
				if (re == 0)		continue;		//��ϵȰ� ������ �ٽ� ���ư�
				for (a = re-1; a >= 0; a--)		//����� �ð� ���
				{
					printf("%2d�� ���: %2d�� %2d�� %2d�� %2d\n", re - a, ts[a][3], ts[a][2], ts[a][1], ts[a][0]);
				}	
			}
			else if (ke == '3')
			{
				al = 0;
			}
			else if (ke == '0')
			{
				mo = !mo;		//��� ����
				break;		//�ݺ��� Ż��
			}
		}
		xy(40, 15);
		if (al != 0)
		{
			printf("�˶� ������");
			et = clock();
			if (et - st > 1000)
			{
				al--;
				st = clock();
			}
		}
		else
		{
			printf("�˶� ����  ");
		}
	}
}

int main()
{
	view(0);		//Ŀ�� �Ⱥ���
	while (1)
	{
		if(mo==0)	timer();		//Ÿ�̸� �۵�
		else		alarm();		//�˶� �۵�
	}
	getch();
	return 0;
}