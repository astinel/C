#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int sc[2];		//����
int i;		//�̴�
int s[2][10];		//�̴� �� ����
int hit[2];		//�� ��Ÿ��
int B[2];		//�� ���ݼ�
int t;		//��
int c;		//��ŵ ����

//Ŀ���̵�
void xy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//�� �Ǻ�
void team()
{
	if (t == 0)
	{
		printf("�� �� ");
	}
	else
	{
		printf("��� �� ");
	}
}

//����
void score()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	sc[t] += s[t][i];		//�̹� �̴׿� ������ ������ŭ ����
	if (t == 0)
	{
		printf("%dȸ��", i);
	}
	else
	{
		printf("%dȸ��", i);
	}
	team();
	printf("%d����\n\n", s[t][i]);
	t = !t;		//��������
	if (c == '2')
	{
		Sleep(500);		//0.5�� ����
	}
}

//����
int pit()
{
	int p;

	p = rand() % 2;		//��,��Ʈ����ũ ����
	if (p == 0)
	{
		return 0;		//��
	}
	else
	{
		return 1;		//��Ʈ����ũ
	}
}

//����
int bat()
{
	int sw, ba, p, a = 0;
	int s = 0, b = 0;		//ī��Ʈ ����

	while (s != 3)
	{
		a++;		//������ �߰�
		p = pit();		//���� ��� ����
		if (c == '4')
		{
			Sleep(250);		//0.3�� ����
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("%d��° ", a);
		sw = rand() % (t + 4);		//���� �� Ȯ��
		if (sw <= 2)		//����
		{
			ba = rand() % 4;		//��Ÿ ĥ Ȯ��
			if (ba == 0)		//��Ÿ
			{
				a = rand() % 20;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				team();
				hit[t]++;		//��Ÿ �߰�
				if (a < 10)
				{
					printf("Ÿ�� ��Ÿ! ");
					return 1;
				}
				else if (a >= 10 && a < 15)
				{
					printf("Ÿ�� 2��Ÿ! ");
					return 2;
				}
				else if (a >= 15 && a < 17)
				{
					printf("Ÿ�� 3��Ÿ! ");
					return 3;
				}
				else
				{
					printf("Ÿ�� Ȩ��! ");
					return 4;
				}
			}
			else if (ba == 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("�Ŀ� ");
				s++;		//��Ʈ����ũ �߰�
				if (s == 3)		//3��Ʈ����ũ�� ��
				{
					s--;		//�ƿ��� �ȵǵ��� ��Ʈ����ũ�� ����
				}
			}
			else if (ba == 2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("�꽺�� ��Ʈ����ũ ");
				s++;		//��Ʈ����ũ �߰�
			}
			else if (ba == 3)		
			{
				printf("���� ");
				s = 3;		//�ƿ�
			}
		}
		else             //���� ���� ���� ���
		{
			if (p == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("�� ");
				b++;		//�� �߰�
				if (b == 4)		//���� 4���� ���
				{
					team();
					printf(" Ÿ�� ����");
					return 5;
				}
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("��Ʈ����ũ  ");
				s++;		//��Ʈ����ũ �߰�
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	return 0;
}

//���̽�
void base()
{
	int b[4] = { 0 };  //���̽�
	int o = 0;  //�ƿ�
	int re;  //���
	int r = 0;  //����
	while (o != 3)
	{
		if (c == '3')
		{
			Sleep(300);		//0.3�� ����
		}
		b[0] = 1;		//Ÿ�� Ÿ���� ��
		re = bat();		//Ÿ�� ��� ����
		if (re == 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			o++;		//�ƿ� �߰�
			team();
			printf("Ÿ�� �ƿ�!");
		}
		else if (re == 1)		//1��Ÿ
		{
			re = b[3];		//3�翡 ���� ������ ����
			b[3] = b[2];
			b[2] = b[1];
			b[1] = b[0];
		}
		else if (re == 2)		//2��Ÿ
		{
			re = b[3] + b[2];		//2,3�翡 ���� ������ ����
			b[3] = b[1];
			b[2] = b[0];
			b[1] = 0;
		}
		else if (re == 3)
		{
			re = +b[3] + b[2] + b[1];		//1,2,3�翡 ���� ������ ����
			b[3] = b[0];
			b[2] = 0;
			b[1] = 0;
		}
		else if (re == 4)
		{
			re = b[3] + b[2] + b[1] + 1;		//��� ���� ���ڼ�+1��ŭ ����
			b[3] = 0;
			b[2] = 0;
			b[1] = 0;		//��� ���� ���� ��� �ʱ�ȭ
		}
		else
		{
			re = 0;
			if (b[1] == 0)		//1�簡 �������
			{
			}
			else if (b[2] == 0)		//2�簡 �������
			{
				b[2] = b[1];
			}
			else if (b[3] == 0)		//3�簡 �������
			{
				b[3] = b[2];
				b[2] = b[1];
			}
			else  //�����Ͻ�
			{
				b[3] = b[2];
				b[2] = b[1];
				re++;
			}
			b[1] = b[0];
			B[t]++;		//���� �߰�
		}
		if (re != 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			printf("  %d ����", re);
			r += re;		//���� ���ڼ� ��ŭ ����
		}
		printf("\n");
	}
	s[t][i] += r;		//�̴� ���� ����
	printf("\n");
}

//��� ���
void result()
{
	getch();
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\n	��Ⱑ ����Ǿ����ϴ�.\n\n");		//����������������������
	printf("�������������������������������������� \n");
	printf("��  ��  ��  ��  ��  ��  ��  ��  ��  �� \n");
	printf("�������������������������������������� \n");
	printf("��  ��  ��  ��  ��  ��  ��  ��  ��  �� \n");
	printf("�������������������������������������� \n");
	printf("��  ��  ��  ��  ��  ��  ��  ��  ��  �� \n");
	printf("�������������������������������������� \n");
	printf("\n                       %d:%d", sc[0], sc[1]);
	printf("\n                       ");
	/*if (sc[0] > sc[1])
		printf("�¸�");
	else if (sc[0] == sc[1])
		printf("���º�");
	else
		printf("�й�");
	for (i = 1; i <= 9; i++)		//�̴� �� ���� ǥ��
	{
		xy(-2 + 3 * i, 4);
		printf("%X", s[0][i]);
		xy(-2 + 3 * i, 6);
		printf("%X", s[1][i]);
	}
	/*xy(33, 4);
	printf("%2d", sc[0]);		//�� �� ���� ǥ��
	xy(33, 6);
	printf("%2d", sc[1]);		//��� �� ���� ǥ��
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

	printf("��⸦ �����մϴ�.\n");
	printf("1:���� ����  2:�̴� ��ŵ  3:Ÿ�� ��ŵ  4:��ŵ ����\n");
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
		i -= t;		//�� �� ������ ������ ��� �̴��� �������� ����
	}
	result();		//��� ���
	getch();
	return 0;
}