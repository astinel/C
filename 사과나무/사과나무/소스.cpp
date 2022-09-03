#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>

int ke;		//�Է� ����
int nu;		//��� ����
int ap[100];		//��� ����
int pa;		//�� ��� ����

//Ŀ�� �����
void CursorView(char show)
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
void erase(int x, int y)
{
	xy(x, y);
	printf(" ");		//����� ����� �������� ����
}

//ó�� ȭ��
void title()
{
	clock_t st, et;		//�ð� ����
	int t = 0;		//���� ��� ����
	int co = 1;		//���� ����

	st = clock();		//�ð� �ʱ�ȭ
	xy(40, 1);
	printf("-----�����������-----");

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
				xy(0, 0);		//Ŀ�� �̵��Ͽ� ������ �ʰ���
				co++;		//���� �� ����
				if (co > 15)		//ǥ���� �� �ִ� ������� �� ǥ���Ұ��
				{
					co = 1;		//1�� ����
				}
			}
			else		//���� ��� ������
			{
				printf("                    ");		//�������� ���� ����
				xy(0, 0);		//Ŀ�� �̵��Ͽ� ������ �ʰ���
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
}

//��� �Լ�
void apple()
{
	int a;		//�ݺ� ����
	int b;		//���� ����
	int s=0;		//ī��Ʈ ����

	for (a=0;a<100;a++)
	{
		ap[a] = 0;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);		//���� �� ������� �ٲ�
	while (1)		//���� ����
	{
		system("cls");		//ȭ�� ����
		xy(40, 1);
		printf("��������� �Է����ּ���(�ּ�60,�ִ�100��)\n");
		scanf("%d", &nu);		//��� ���� �Է� ����
		if (nu >= 60 && nu <= 100)		//��� ������ ���� �ȿ� �鶧
		{
			break;		//�ݺ��� Ż��
		}
	}
	for (a=0;s!=nu;a++)		//��� ���� ��ġ
	{
		b = rand()%2;		//����� ��ġ �� Ȯ��
		if (b==0&&ap[a] == 0)
		{
			s++;		//����� ��ġ�ȼ� ��ŭ ī��Ʈ
			ap[a] = 1;		//����� ����
		}
		if (a==99)		//��� ��ġ�� �����������
		{
			a = -1;		//ó������
		}
	}
	for (a = 0;; a++)		//�� ��� ���� ��ġ
	{
		b = rand() % nu;		//�� ����� �� Ȯ��
		if (b == 0&&ap[a]==1)
		{
			ap[a] = 2;		//�� ����� ����
			pa = a;		//�� ��� ��ġ ����
			break;		//�� ����� ������� ��� Ż��
		}
		if (a == 99)		//��� ��ġ�� �����������
		{
			a = -1;		//ó������
		}
	}
	system("cls");		//ȭ�� ����	
}

//������ ���
void leaf()
{
	int a,b=1,s;		//�ݺ� ����
	int c=0;		//��� ���� ī��Ʈ ����

	for (a=1;a<=10;a++,b+=2)
	{
		xy(40-a,a+3);
		for (s=1;s<=b;s++,c++)
		{
			if(ap[c]==2)			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);		//�� ������� ���ֻ�
			else if (ap[c] == 1)	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);		//������� ������
			else					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);		//������ ���� ���λ�
			printf("*");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);		//���ڻ� ������� �ٲ�
}

//���� ��� ���
void wood()
{
	int a;		//�ݺ� ����

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);		//���ڻ� ������� �ٲ�
	for (a=1;a<=5;a++)
	{
		xy(38, a+13);
		printf("***");
	}
}

//�߶� �׷���
void fall(int c)
{
	int a,b;		//�ݺ� ����
	int xs[100],ys[100];		//��ǥ ����

	for (a = 0; a < c; a++)		//������ ��� ���� ��ŭ �ݺ�
	{
		xs[a] = rand() % 20 + 30;		//�߶��ϴ� ������ġ ����
		ys[a] = rand() % 6 + 15;		//�߶��ϴ� ������ġ ����
	}
	for (a = 0; a<2; a++)		//�߶�
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);		//������� ������
		for (b = 0; b < c; b++)		//������ ��� ���� ��ŭ �ݺ�
		{
			xy(xs[b], ys[b] + a);
			printf("*");		//�߶��ϴ� ��� ���
		}
		Sleep(500);		//0.5�� ����
		for (b = 0; b < c; b++)		//�������� ��� ����
		{
			erase(xs[b],ys[b]+a);		//����� ��� ����
		}
		wood();		//���������� ����� ���� ��� �ٽ� ���
	}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);		//���ڻ� ������� �ٲ�
}

//���� �Լ�
void tree()
{
	int ke;			//�Է� ����
	int fa;			//����� ������ Ȯ��
	int a;			//�ݺ� ����
	int c=0;		//ī��Ʈ ����
	int lo = 0, log[10] = {0},ks=0;		//�α׺���

	wood();		//���� ��� ���
	while (1)		//���ѷ���
	{
		if (kbhit())		//Ű�� �Է� ������
		{
			ke = getch();		//�Է��� Ű�� ����
			if (ke == 224)		//����Ű�� ��� ó���� 224�� ��ȯ
			{
				ke = getch();		//�� ��°�� �ٸ� ���ڸ� �Է¹���
				if (ke == 72 || ke == 75 || ke == 77 || ke == 80)		//�����¿��� �� ��° �ƽ�Ű �ڵ� ��
				{
					xy(15, 25);
					printf("                                 ");		//�������� ���� ����
					for (a=0;a<100;a++)
					{
						if (ap[a] == 0)		//�̹� ������ ����ϰ��
						{
							continue;		//ó������
						}
						fa = rand()% (nu / 5);		//����� ������ Ȯ��(����)
						if (fa == 0)
						{
							c++;		//������ ����� ���� ī��Ʈ
							ap[a] = 0;		//��� ������
						}
					}
					nu -= log[0]=  c;		//������ ���� ��ŭ ��� ���� ����,�α� ���
					xy(60, 10);
					printf("����� %d�� ���������ϴ�.", c);
					xy(60,14);
					printf("�α�");
					for (a = 1; a <= lo; a++)		//�α� ���
					{
						xy(60, 15 + a);
						printf("%2d", log[a]);
					}
					for (a=9;a>=1;a--)		//�α� ����Ʈ
					{
						log[a] = log[a - 1];
					}
					if (lo < 9)
					{
						lo++;		//�α� ��� ���� �ø�
					}
					if (nu < 0)		//���� ��������� ������ �ɰ��
					{
						nu = 0;		//0���� �ʱ�ȭ
					}
					if (ap[pa] == 0||nu<4)		//�� ��� ������
					{
						xy(60,12);
						ap[pa] = 0;		//������� ������ ������ ��츦 ����Ͽ� �ʱ�ȭ
						printf("�� ����� ���������ϴ�.");
						leaf();		//�� ��� ���� ���� ���
					}
				}
			}
		}
		xy(40, 1);
		printf("���� �������:%3d", nu);		//���� ��� ���� ���
		leaf();		//������ ���
		if (c!=0)		//����� ����������
		{
			fall(c);		//��� �߶� �׷��� ���
			c = 0;
		}
		if (ap[pa] == 0)	break;		//�� ��� ������
	}
}

//���� �Լ�
void chose()
{
	Sleep(1000);		//1�� ����
	xy(15, 27);
	printf("�ٽ��Ϸ��� 0�� �����ּ���");
	ke = getch();
}

int main()
{
	CursorView(0);		//Ŀ�� �����
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
