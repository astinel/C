#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define max 30		//�ִ�ġ

clock_t st, et;		//�ð� ����
int ke;		//�Է� ����
int x = 1, y = 1;		//��ġ ����
int sta;			//���� ����
int p[2],sl[2],el[2];		//��ġ ���� ����
int tr[max][max];		//���� �迭
int ma[max][max];		//�̷� �迭

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
void color(short t, short b)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), t + (b << 4));
}

//���� �Լ�
void erase(int x, int y)
{
	xy(x, y);
	printf("                           ");
}

//ó�� ȭ��
void title()
{
	int t = 0;		//���� ��� ����
	int co = 1;		//���� ����
	int ke;		//�Է� ����
	int a, b;		//�ݺ� ����

	for (a = 0; a < 2; a++)
	{
		for (b = 0; b < 58; b++)
		{
			printf("��");
		}
		xy(0, 29);
		printf("��");
	}

	xy(0, 0);
	printf("��-");
	for (a = 0; a < 2; a++)
	{
		for (b = 0; b < 28; b++)
		{
			xy(0 + 117 * a, b + 1);
			printf("��");
		}
	}
	xy(116, 0);
	printf("-��");
	xy(117, 29);
	printf("��");
	xy(50, 1);
	printf("-------�̷�-------");

	while (1)		//���� ����
	{
		color(co, 0);		//���� ���� �ٲ�
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
	color(7, 0);		//���� ���� �ٲ�
	system("cls");
}

//��� ���
void block(int x, int y)
{
	xy(2 * x, y);
	if (!ma[x][y])				printf("��");		//��
	else if (ma[x][y] == 1)		printf("  ");		//��
	else if (ma[x][y] == 2)		printf("��");		//���� ����
	else if (ma[x][y] == 3)		printf("��");		//���� ����
}

//�ɼ� ���
void option()
{
	xy(70, 3);	printf("1:�̷� ���� �Ǵ� �ߴ�");
	xy(70, 4);	printf("2:���� ���� ���(��)  3:���� ���� ���(��)");
	xy(70, 5);	printf("4:�̷� ���� ����      5:��ã��");
	xy(70, 6);	printf("6:�ʱ�ȭ              7:����");
}

//���� ���
void state()
{
	xy(70,1);
	printf("���� ����:");
	if (sta == 1)				printf("�̷� ������");
	else if (ma[x][y] == 0)		printf("�� ���� ");
	else if (ma[x][y] == 1)		printf("�� ���� ");
	else if (ma[x][y] == 2)		printf("���� ���� ");
	else if (ma[x][y] == 3)		printf("���� ���� ");
}

//�̷� ���
void maze()
{
	int a, b;		//�ݺ�����

	for (a = 0; a<max; a++)		//�̷� ���
	{
		for (b = 0; b < max; b++)
		{
			block(a, b);		//��� ���
		}
	}
}

//�÷��̾� ��ġ ���
void player()
{
	xy(2 * p[0], p[1]);
	block(p[0],p[1]);		//�÷��̾ ������ �ڸ��� �� ���
	xy(2 * x, y);
	printf("��");		//�÷��̾� ���
	p[0] = x;		//�÷��̾� ���� ��ġ ����
	p[1] = y;		//�÷��̾� ��ġ ����
}

//���� ���� ����
void trace()
{
	int a, b;		//�ݺ� ����
	int c;		//Ȯ�� ����

	for (a = 1; a < max-1; a++)		//���� ���� �Ǻ�
	{
		for (b = 1; b < max-1; b++)
		{
			c = 0;
			if (ma[a - 1][b])		c++;
			if (ma[a + 1][b])		c++;
			if (ma[a][b - 1])		c++;
			if (ma[a][b + 1])		c++;
			tr[a][b] = c;		//���� ���� �Է�
		}
	}
	tr[sl[0]][sl[1]] += 1;		//���� ���� �ʱ�ȭ
	tr[el[0]][el[1]] += 1;		//���� ���� �ʱ�ȭ
}

//�� ǥ��
void road(int x,int y)
{
	xy(2 * x, y);
	if (tr[x][y] >1)
	{
		color(0, 12);		//��� ������
		printf("  ");
		tr[x][y]--;
	}
	else
	{
		block(x,y);
	}
	color(7, 0);		//���
}

//�̷� ã��
void start()
{
	maze();		//�̷� �ٽ� ���
	player();		//�÷��̾� ��ġ ���
	state();		//���� ���

	while (!(x == el[0] && y == el[1]))		//���� ������ ���� �Ҷ� ���� �ݺ�
	{
		ke = getch();

		if (ke == 224)
		{
			ke = getch();
			if (ke == 72)			y--;		//���� �̵�	
			else if (ke == 75)		x--;		//���� �̵�
			else if (ke == 77)		x++;		//������ �̵�
			else if (ke == 80)		y++;		//�Ʒ� �̵�
		}
		else if (ke == '1')		break;		//�̷� ã�� �ߴ�
		if (!ma[x][y])		//������ ��ġ�� ���� �������
		{
			x = p[0];		//���� ��ǥ ȣ��
			y = p[1];		//���� ��ǥ ȣ��
		}
		else
		{
			player();		//�÷��̾� ��ġ ���
		}
	}
	if (ke != '1')		//�ߴ����� ���� ������ �ʾ�����
	{
		xy(70, 25);		printf("����!");
		getch();
		erase(70, 25);		//���� ����
	}
	sta = 0;
}

//�� ã��
int find()
{
	int ke = 0;		//�Է� ����
	int di = 0;		//���� ����
	int x, y;		//��ġ ����
	int p[2];		//��ġ ���� ����
	int mo = 0;		//�̵� ����

	p[0] = x = sl[0];
	p[1] = y = sl[1];
	trace();		//���� ���� �ʱ�ȭ
	if (tr[sl[0]][sl[1]] == 1)		return 1;		//1�� �Ǻ�
	road(x, y);		//�� ǥ��
	st = clock();
	while (1)		//��ǻ�� �� ã�� �ΰ�����
	{
		et = clock();
		di = ke % 4;		//�������� ���� 4����

		if (di == 0)		y--;		//���� �̵�
		else if (di == 1)	x++;		//������ �̵�
		else if (di == 2)	y++;		//�Ʒ� �̵�
		else				x--;		//���� �̵�

		if (!ma[x][y])		//������ ��ġ�� ���� �������
		{
			x = p[0];		//���� ��ǥ ȣ��
			y = p[1];		//���� ��ǥ ȣ��
			ke++;		//90���� ���� ȸ��
		}
		else
		{
			road(x,y);		//�� ǥ��
			mo++;
			ke--;		//270���� ���� ȸ��
			p[0] = x;
			p[1] = y;
		}
		if (ke < 0)		ke += 4;
		if (!di*mo && x == sl[0] && y == sl[1])		return 2;		//���� ��ã����(�ٽ� ��������� ���ƿ�����)
		else if (x == el[0] && y == el[1])			return 0;		//�� ã�� ������
		else if (et - st > 1000)					return 1;
	}
}

//üũ
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

//�̷� ����
void make()
{
	int a, b;		//��ġ ����
	int di = 0;		//���� ����
	int l = 0, r = 0, ip;		//���� ��ȭ
	int rs;

	for (a = 1; a < 29; a++)
	{
		for (b = 1; b < 29; b++)
		{
			ma[a][b] = 0;		//�̷� �ʱ�ȭ
		}
	}
	trace();		//���� ���� ����
	a = rand() % 28 + 1;	b = rand() % 28 + 1;		//���� ���� ��ġ ����
	sl[0] = a;	sl[1] = b;		//���� ���� ���
	ma[a][b] = 2;		//���� ���� �ʱ�ȭ
	di = rand() % 4;		//�ʱ� ���� ����
	el[0] = 0;		//���� ���� �ʱ�ȭ
	while (1)
	{
		l = rand() % 5 + 2;		//���� ����
		for (ip = 0; l > 0; l--, ip++)		//���� ���� ��ŭ �ݺ�
		{
			if (di == 0)			b--;		//���� �̵�		
			else if (di == 1)		a++;		//������ �̵�	
			else if (di == 2)		b++;		//�Ʒ� �̵�
			else if (di == 3)		a--;		//���� �̵�
			if (!(a*b) || a == max - 1 || b == max - 1 || tr[a][b] > 1)			break;		//���� �������� �� �̻� �̷� ������ �Ұ��� ��� ����
			if (ip > 0)		//�б��� ���� ����
			{
				r = rand()%3;		//�б��� ���� Ȯ��
				if (!r)
				{
					r = rand() % 2;		//�б��� ���� ����
					if (r)		ip = di + 1;		//90�� ȸ��
					else		ip = di - 1;		//-90�� ȸ��
					ma[a][b] = ip + 8;		//�б��� ���� �� ����(�Ŀ� ������ ����� ���� ���� ���Ⱚ�� ����)
					ip = 0;		//�б��� �� �ʱ�ȭ
				}
				else
				{
					ma[a][b] = 1;
				}
			}
			else
			{
				ma[a][b] = 1;		//�� ��� ����
			}
			trace();		//���� ���� ����
			el[0] = a;	el[1] = b;		//���� ���� ��ġ �ʱ�ȭ
		}
		r = rand() % 2;		//���� ��ȭ ����
		if (r)	di++;		//90�� ȸ��
		else	di--;		//-90�� ȸ��
		if (di < 0)		di += 4;		//���� ���� ������ �� ��� ����� ����
		if (di == 4)		di %= 4;		//���� ���� ������ ��� ��� ���� �� ������ ����
		if (l)		//�̷� ���� �Ͻ�����
		{
			ip = 0;
			for (a = 1; a < max - 1; a++)		//�б��� ���� �Ǵ�
			{
				for (b = 1; b < max - 1; b++)
				{
					if (ma[a][b] > 4)		//�б����� ������ ���
					{
						ip = 1;		//�б����� ����
						break;		//�б��� Ž�� ����
					}
				}
				if (ip)		break;
			}
			if (ip)		//�б����� �����ҽ�
			{
				di = ma[a][b] % 4;		//���Ⱚ �ʱ�ȭ
				ma[a][b] = 1;		//�� ��� ����
				continue;
			}
			break;		//�б����� �� �̻� �������� ������� �̷� ���� ����
		}
	}
	if(el[0])	ma[el[0]][el[1]] = 3;		//���� ���� �ʱ�ȭ
}

//�÷��̾� �̵�
void miro()
{
	int ke = 0;		//Ű �Է� ����
	int di = 0;		//���� ����
	int mo = 0;		//�̵� ����
	int ch = 0;		//Ȯ�� ����
	int a, b;		//�ݺ� ����

	while (1)
	{
		state();
		player();		//�÷��̾� ���
		ke = getch();
		if (sta == 2)		//�̷� ���� ���� ��½�
		{
			xy(70, 20);
			printf("                                             ");
			st = 0;
		}
		if (ke == 224)		//����Ű�� �������
		{
			ke = getch();
			if (ke == 72)			y--;		//���� �̵�
			else if (ke == 75)		x--;		//���� �̵�
			else if (ke == 77)		x++;		//������ �̵�
			else if (ke == 80)		y++;		//�Ʒ� �̵�
			if (x*y == 0 || x == max - 1 || y == max - 1)		//�̷��� ������ ����� ����
			{
				x = p[0];		//���� ��ǥ ȣ��
				y = p[1];		//���� ��ǥ ȣ��
			}
		}
		else if (ke == '\r')		//�� ���� �ٲ�
		{
			if (ma[x][y] == 2)			sl[0] = 0;		//���� ������ ��� �ʱ�ȭ
			else if (ma[x][y] == 3)		el[0] = 0;		//���� ������ ��� �ʱ�ȭ
			ma[x][y] = !ma[x][y];		//��� ���� �ٲ�
		}
		else if (ke == '1')		//�̷� ����
		{
			if (sl[0] * el[0] == 0)		//���� �����̳� ���� ������ ��ϵǾ����� ���� ���
			{
				sta = 2;
				xy(70, 20);		printf("���� �Ǵ� ���� ������ ��� �Ǿ����� �ʽ��ϴ�.");
				continue;		//ó������
			}
			x = sl[0];		//���� ��ġ�� ���� ������ ���� ��ǥ�� �ʱ�ȭ
			y = sl[1];		//���� ��ġ�� ���� ������ ���� ��ǥ�� �ʱ�ȭ
			sta = 1;		//�̷� ���� ���
			start();		//�̷� ����
		}
		else if (ke == '2')		//���� ���� ���
		{
			if (sl[0] != 0)		//�̹� ���� ������ ��� ������ ���
			{
				ma[sl[0]][sl[1]] = 1;		//���� ���� ������ ��� �ٲ�
				block(sl[0],sl[1]);		//��� ��ü ���
			}
			sl[0] = x;		//���� ��ġ�� ���� �������� �ʱ�ȭ
			sl[1] = y;		//���� ��ġ�� ���� �������� �ʱ�ȭ
			ma[x][y] = 2;		//���� ���� �������� �ٲ�		
			if (sl[0] == el[0] && sl[1] == el[1])		el[0] = 0;		//���� ������ ���� ������ �Ȱ����� �ʱ�ȭ		
		}
		else if (ke == '3')		//���� ���� ���
		{
			if (el[0] != 0)		//�̹� ���� ������ ��� ������ ���
			{
				ma[el[0]][el[1]] = 1;		//���� ���� ������ ��� �ٲ�
				block(el[0], el[1]);		//��� ��ü ���
			}
			el[0] = x;		//���� ��ġ�� ���� �������� �ʱ�ȭ
			el[1] = y;		//���� ��ġ�� ���� �������� �ʱ�ȭ
			ma[x][y] = 3;		//���� ���� �������� �ٲ�
			if (sl[0] == el[0] && sl[1] == el[1])		sl[0] = 0;		//���� ������ ���� ������ �Ȱ����� �ʱ�ȭ		
		}
		else if (ke == '4')		//�̷� ���� ����
		{
			while (ch < 9)		//9ĭ �̻��� �̷� ���
			{
				ch = 0;
				make();		//�̷� ����
				for (a = 1; a < max - 1; a++)
				{
					for (b = 1; b < max - 1; b++)
					{
						if (ma[a][b])	ch++;
					}
				}
			}
			ch = 0;
			maze();		//�̷� �����
		}
		else if (ke == '5')		//�� ã��
		{
			sta = 2;
			if (sl[0] * el[0] == 0)
			{
				xy(70, 20);		printf("���� ã�µ� �����Ͽ����ϴ�.");
				continue;
			}
			ch = find();		//�� ã��
			if (ch)		//�� ã�� ����
			{
				xy(70, 20);		printf("���� ã�µ� �����Ͽ����ϴ�.");
				if (ch > 1)		maze();		//�̷� �����
			}
			else
			{
				xy(70, 20);		printf("�ƹ�Ű�� ������ �����մϴ�.");
				getch();
				maze();		//�̷� �����
			}
		}
		else if (ke == '6')		//�ʱ�ȭ
		{
			for (a = 1; a < max - 1; a++)
			{
				for (b = 1; b < max - 1; b++)
				{
					ma[a][b] = 0;
				}
			}
			maze();		//�̷� �����
		}
		else if (ke == '7')		//����
		{
			for (a = 1; a < max - 1; a++)
			{
				for (b = 1; b < max - 1; b++)
				{
					if (ma[a][b] <= 1)	ma[a][b] = !ma[a][b];		//0�� 1�� ���� �ٲ�
				}
			}
			maze();		//�̷� �����
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
	option();		//�ɼ� ���

	maze();		//�̷� ���
	miro();		//�̷� �̵�

	getch();
	return 0;
}