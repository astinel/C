#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define GA 12		//���� ����
#define SE 23		//���� ����
#define HE 29-SE		//����
#define AP SE+HE-1		//������ ��� ���� ��ǥ
#define KE 300		//Ű ���� ��
#define KY 2		//Ű ���� ��� ����
#define opt 6		//�ɼ� ����

clock_t st, et;		//�ð� ����
clock_t lpt, lvt, cpt;		//��� �ð�(��, ����, ��ǻ�� �ൿ)
int p;		//���� ����
int op = 0;		//���� ����
int nt, svt;		//��� ���� ����
int col, cc;		//��� �� ����
int x, y, xs, ys, cx, cy, cxs, cys;		//��ġ ����
int dx, dr;		//��ǥ �ൿ ����
int yy;		//���� ���� ������ ���� ��ǥ
int po, lv, ca;		//����,����,��ǻ�� �ൿ�ӵ�
int tb;		//����� ��� ����
int co;		//�޺�
int h;		//Ȧ�庯��
int l, al, dl;		//�� ����
int de;		//���� ���� �Ǻ�
int bp;		//��� ��� ��ġ ����
int vb;		//������� ����
int mc[3], ba[3];		//���
int sc[GA][SE + 1], cs[GA][SE + 1];		//ȭ�� �迭 ��
int ub[4][2], nb[4][2], cb[4][2];		//��� �迭
int li[21], cl[21];		//���� �迭
int ra[7];		//�̻� Ȯ�� �迭
int kee[7];		//Ű ����

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
void erase()
{
	int a;		//�ݺ� ����

	for (a = 0; a < 4; a++)
	{
		xy(2 * (ub[a][0] + xs) + bp, ub[a][1] + ys + HE);
		printf("  ");
		xy(2 * (ub[a][0] + xs) + bp, ub[a][1] + yy + HE);
		printf("  ");
	}
}

//ó�� ȭ��
void title()
{
	int c=1;		//���� ����
	int t = 1;		//���/����
	int ke;		//�Է� ����

	st = et - 300;		//ó���� ������ ��
	while (1)
	{
		et = clock();
		if (et - st > 300)		//���� �ð� ���� ����
		{
			st = clock();
			xy(10, 10);	 printf("������  ������  ������  ������  ������  ������  ������");
			color(c % 15 + 1, 0);
			c = rand() % 15 + 1;
			xy(10, 11);	 printf("    ��      ��              ��      ��          ��      ��      ��     ��");
			color(c % 15 + 1, 0);
			c = rand() % 15 + 1;
			xy(10, 12);	 printf("    ��      ������      ��      ������  ������      ��      ������");
			color(c % 15 + 1, 0);
			c = rand() % 15 + 1;
			xy(10, 13);	 printf("    ��      ��              ��      ��          ��   ��         ��               ��");
			color(c % 15 + 1, 0);
			c = rand() % 15 + 1;
			xy(10, 14);	 printf("    ��      ������      ��      ������  ��      ��  ������  ������");
			color(c % 15 + 1, 0);
			c = rand() % 15 + 1;
			xy(40, 20);
			if (t)		printf("PRESS ANY KEY TO START");
			else		printf("                      ");
			t = !t;		//���/������ �����ư��鼭 �����(0�� 1�� ���� �ٲ�)
			c = rand() % 15 + 1;		//16���� ���� �߿��� �������� ����(0�� ����)�ϰ� ����
		}
		if (kbhit())		break;		//�ƹ�Ű�� ������� ���� ����
	}
	ke = getch();
	color(7, 0);
}

//���� â
void option()
{
	int ke;		//�Է� ����

	xy(25, 10);		printf("�Ϲ� ���");
	xy(65, 10);		printf("���� ���");
	xy(25, 15);		printf("���� ���");
	xy(65, 15);		printf("���� ���");
	xy(25, 20);		printf("Ű   ����");
	xy(65, 20);		printf("��� ���");

	do
	{
		xy(29 + 40 * (op % 2), 9 + 5 * (op / 2));	printf("��");		//������ ��� ǥ��
		ke = getch();		//�Է� ����
		xy(29 + 40 * (op % 2), 9 + 5 * (op / 2));	printf("  ");		//������ ������ ��� ����
		if (ke == 224)
		{
			ke = getch();
			if (ke == 72)		op -= 2;
			if (ke == 75)		op--;
			if (ke == 77)		op++;
			if (ke == 80)		op += 2;
		}
		if (op < 0)		op += opt;	//���� ����
		op %= opt;		//�������� 5����
	} while (ke != '\r');
	system("cls");
	p = 1;		//���� ����
}

//����� ����� �ȵǴ� Ű ���Ƿ� ��µǰ� ��
void keyprint(int ke)
{
	if (ke == 8)				printf("Backspace");
	else if (ke == 9)			printf("TAB");
	else if (ke == '\r')		printf("ENTER    ");
	else if (ke == ' ')			printf("Space Bar");
	if (ke > 200)
	{
		ke -= KE;		//Ű�� �纸��
		if (ke == 27)							printf("ESC      ");
		else if (ke >= 59 && ke <= 68)			printf("F%2d     ", ke - 58);
		else if (ke == 71)						printf("Home     ");
		else if (ke == 72)						printf("��       ");
		else if (ke == 73)						printf("Page UP  ");
		else if (ke == 75)						printf("��       ");
		else if (ke == 77)						printf("��       ");
		else if (ke == 79)						printf("END      ");
		else if (ke == 80)						printf("��       ");
		else if (ke == 81)						printf("Page Down");
		else if (ke == 82)						printf("Insert   ");
		else if (ke == 83)						printf("Delete   ");
		else if (ke == 133 || ke == 134)		printf("F%2d     ", ke - 122);
		ke += KE;		//Ű��	����
	}
}

//���� ���
void info()
{
	int a = KY;		//�ʱ� ��� ��ġ

	color(7, 0);
	if (op != 4)		//Ű ������ �ƴҶ�
	{
		xy(29 + bp, 20);		printf("���� ���");
		xy(-15 + bp, 20);		printf("Ȧ�� ���");
	}
	if (op != 3)		//���� ��尡 �ƴҶ�
	{
		xy(30 - bp / 2, a += 2);		printf("����߸���   : %c        ", kee[0]);
		xy(30 - bp / 2, a += 2);		printf("����   �̵�  : %c        ", kee[1]);
		xy(30 - bp / 2, a += 2);		printf("������ �̵�  : %c        ", kee[2]);
		xy(30 - bp / 2, a += 2);		printf("�Ʒ��� �̵�  : %c        ", kee[3]);
		xy(30 - bp / 2, a += 2);		printf("ȸ       ��  : %c        ", kee[4]);
		xy(30 - bp / 2, a += 2);		printf("Ȧ       ��  : %c        ", kee[5]);
		xy(30 - bp / 2, a += 2);		printf("�Ͻ�����/����: %c        ", kee[6]);
		for (a = 0; a < 7; a++)
		{
			xy(45 - bp / 2, 4 + 2 * a);
			keyprint(kee[a]);		//Ű ���
		}
	}
	else
	{
		xy(9, AP);		printf("���� ��");
		xy(87, AP);		printf("�� ����");
		xy(29, 5);		printf("player");
		xy(68, 5);		printf("computer");
	}
}

//�ʱ�ȭ
void reset()
{
	int a, b;

	system("cls");
	for (a = 1; a < GA - 1; a++)
	{
		for (b = 0; b < SE; b++)
		{
			sc[a][b] = 0;		//���� ���� ���� �迭�� �ʱ�ȭ
			cs[a][b] = 0;		//��ǻ�� ���� ���� �迭�� �ʱ�ȭ
		}
	}
	for (a = 0; a < 21; a++)
	{
		li[a] = 0;		//���� �迭 �� �ʱ�ȭ
		cl[a] = 0;		//��ǻ�� ���� �迭 �� �ʱ�ȭ
	}
	for (a = 0; a < 7; a++)		ra[a] = 0;		//�̻� Ȯ�� �迭 �ʱ�ȭ

	//���� ���� �� �ʱ�ȭ
	lv = 1;	po = 0;		//���� ����
	tb = 0;	de = 0;		//��ϰ��� ��������
	al = 0;	dl = 0;		//��������  �������
	svt = 8;
}

//ȭ��&�ʱ� �� ����
void screen()
{
	int a, b;		//�ݺ� ����

	bp = 40;
	for (a = 0; a < 2; a++)		//�� �� ��� ���
	{
		for (b = 0; b < SE; b++)		//���� ũ�� -1 ��ŭ �ݺ�
		{
			if (b < 3)		color(0, 12);		//�� ���� 3ĭ�� ������
			else			color(0, 7);		//������ ĭ�� ���
			xy(41 + a * 21, b + HE);
			printf(" ");
			sc[0 + 11 * a][b] = 1;		//�� �� ��� �迭 �� �ʱ�ȭ
		}
	}
	xy(40, b + HE);
	for (a = 0; a < GA; a++)				//�� �� ��� ���
	{
		printf("  ");
		sc[a][b] = 1;		//�� �� ��� �迭 �� �ʱ�ȭ
	}
}

//ȭ�� �ΰ�(���� ��� ��)
void twoscreen()
{
	int a, b;		//�ݺ� ����

	bp = 20;
	//���� ȭ��
	for (a = 0; a < 2; a++)		//�� �� ��� ���
	{
		for (b = 0; b < SE; b++)		//���� ũ�� -1 ��ŭ �ݺ�
		{
			if (b < 3)		color(0, 12);		//�� ���� 3ĭ�� ������
			else			color(0, 7);		//������ ĭ�� ���
			xy((a + 1) * 21, b + HE);
			printf(" ");
			sc[0 + 11 * a][b] = 1;		//�� �� ��� �迭 �� �ʱ�ȭ
		}
	}
	xy(20, b + HE);
	for (a = 0; a < GA; a++)				//�� �� ��� ���
	{
		printf("  ");
		sc[a][b] = 1;		//�� �� ��� �迭 �� �ʱ�ȭ
	}

	//��ǻ�� ȭ��
	for (a = 0; a < 2; a++)		//�� �� ��� ���
	{
		for (b = 0; b < SE; b++)		//���� ũ�� -1 ��ŭ �ݺ�
		{
			if (b < 3)		color(0, 12);		//�� ���� 3ĭ�� ������
			else			color(0, 7);		//������ ĭ�� ���
			xy((a + 1) * 21 + 40, b + HE);
			printf(" ");
			cs[0 + 11 * a][b] = 1;		//�� �� ��� �迭 �� �ʱ�ȭ
		}
	}
	xy(60, b + HE);
	for (a = 0; a < GA; a++)				//�� �� ��� ���
	{
		printf("  ");
		cs[a][b] = 1;		//�� �� ��� �迭 �� �ʱ�ȭ
	}
}

//Ű�� ����
int keychange(int ke)
{
	if (ke == 224 || ke == 0 || ke == 27)		//�Է���Ű�� ����� �ȵǴ� Ű�� ���
	{
		if (ke == 224 || ke == 0)		ke = getch();		//�ѹ� �� �Է� ���� ��
		ke += KE;		//�ٸ� Ű�� ��ġ�� �ʰ� Ű �� ����
	}

	return ke;
}

//��� ���� �Լ�
void block(int p, int r)
{
	int a, b;		//�ݺ� ����
	int bl[4][2];

	//������ �ʱ� ���� ��ǥ �������� �ʱ� ������ǥ
	if (r == 0)		//J ���
	{
		bl[0][0] = 0;	bl[0][1] = 1;
		bl[1][0] = 0;	bl[1][1] = 2;
		bl[2][0] = 1;	bl[2][1] = 2;
		bl[3][0] = 2;	bl[3][1] = 2;
	}
	else if (r == 1)		//S ���
	{
		bl[0][0] = 1;	bl[0][1] = 2;
		bl[1][0] = 2;	bl[1][1] = 2;
		bl[2][0] = 2;	bl[2][1] = 1;
		bl[3][0] = 3;	bl[3][1] = 1;
	}
	else if (r == 2)		//I ���
	{
		bl[0][0] = 0;	bl[0][1] = 2;
		bl[1][0] = 1;	bl[1][1] = 2;
		bl[2][0] = 2;	bl[2][1] = 2;
		bl[3][0] = 3;	bl[3][1] = 2;
	}
	else if (r == 3)		//T ���
	{
		bl[0][0] = 1;	bl[0][1] = 1;
		bl[1][0] = 0;	bl[1][1] = 2;
		bl[2][0] = 1;	bl[2][1] = 2;
		bl[3][0] = 2;	bl[3][1] = 2;
	}
	else if (r == 4)		//Z ���
	{
		bl[0][0] = 0;	bl[0][1] = 1;
		bl[1][0] = 1;	bl[1][1] = 1;
		bl[2][0] = 1;	bl[2][1] = 2;
		bl[3][0] = 2;	bl[3][1] = 2;
	}
	else if (r == 5)		//�� ���
	{
		bl[0][0] = 1;	bl[0][1] = 1;
		bl[1][0] = 2;	bl[1][1] = 1;
		bl[2][0] = 1;	bl[2][1] = 2;
		bl[3][0] = 2;	bl[3][1] = 2;
	}
	else if (r == 6)		//L ���
	{
		bl[0][0] = 1;	bl[0][1] = 2;
		bl[1][0] = 2;	bl[1][1] = 2;
		bl[2][0] = 3;	bl[2][1] = 2;
		bl[3][0] = 3;	bl[3][1] = 1;
	}
	if (!p)		//���� ��� ����
	{
		for (a = 0; a < 4; a++)		//������ ����� ���� ������� �ٲ�
		{
			for (b = 0; b < 2; b++)		ub[a][b] = bl[a][b];
		}
		col = r + 9;		//���� ��� ����
	}
	else if (p == 1)
	{
		for (a = 0; a < 4; a++)		//������ ����� ���� ������� �ٲ�
		{
			for (b = 0; b < 2; b++)		nb[a][b] = bl[a][b];
		}
		nt = r;		//���� ��ϰ�
	}
	else if (p == 2)
	{
		for (a = 0; a < 4; a++)		//������ ����� ��ǻ�� ������� �ٲ�
		{
			for (b = 0; b < 2; b++)		cb[a][b] = bl[a][b];
		}
		cc += 9;		//��ǻ�� ��ϰ�
	}
	else if (p == 3)		//Ȧ�� ��� ����
	{
		for (a = 0; a < 4; a++)		//������ ����� ��ǻ�� ������� �ٲ�
		{
			for (b = 0; b < 2; b++)		cb[a][b] = bl[a][b];
		}
		cc += 9;		//��ǻ�� ��ϰ�
	}
}

//��� ���� �Լ�
int blockselect()
{
	int a, b;		//�ݺ� ����
	int r;		//���� ����

	r = rand() % 7;		//���� ��� ����
	if (tb % 10 == 9)		//10��° ��� ���� ��� Ȯ�� ����
	{
		for (a = 0; a < 6; a++)		//���� �ȳ��� ����� �Ǻ�
		{
			if (ra[a] > ra[a + 1])		b = a + 1;		//�� �迭�� �ּڰ��� ����
		}
		r = a;		//��� ����
	}
	ra[r]++;		//�ش� ��� �� ����

	return r;
}

//��� �ٲ�
void blockchange()
{
	int a;		//�ݺ� ����
	int	b;		//��� ����

	b = blockselect();		//��� ����
	block(0, nt);		//���� ���� ��Ʈ���̳� ����
	block(1, b);		//���� ���� ��Ʈ���̳� ����
	for (a = 0; a < 4; a++)		//���� ����� ���� ��ϻ��� 
	{
		xy(2 * ub[a][0] + 30 + bp, ub[a][1] + 22);
		printf("  ");
	}
	color(b + 9, 0);
	for (a = 0; a < 4; a++)		//���� ��� ���
	{
		xy(2 * nb[a][0] + 30 + bp, nb[a][1] + 22);
		printf("��");
	}
}

//�浹 �Ǻ� �Լ�
int crash()
{
	int a;		//�ݺ� ����
	int c;		//���� ����

	for (a = 0; a < 4; a++)
	{
		if (sc[ub[a][0] + x][ub[a][1] + y])		//�浹 ��
		{
			if (x != xs)
			{
				x = xs;
				a--;
				continue;
			}
			if (y != ys)		//���θ� �ٸ���
			{
				y--;
				if (y < 0)		y = 0;
				return 1;
			}
			else				//ȸ����
			{
				return 1;
			}
			break;
		}
	}
	return 0;
}

//��� ��� �Լ�
void blockprint()
{
	int a, b;		//�ݺ� ����
	int c;		//���� ����

	xs = x;	ys = y;		//����� ��Ʈ���̳� ��ǥ ����

	for (c = y; !crash(); y++);		//�ٷ� �ؿ� ��ϰ� �浹�Ҷ� ���� ��� �ϰ� ��Ŵ
	yy = y;
	y = c;

	for (a = 0; a < 2; a++)
	{
		if (!a)
		{
			color(8, 0);		//ȸ��
			c = yy;		//���� ���� ����
		}
		else
		{
			color(col, 0);		//��� ���� ���� �ٸ�
			c = y;		//���� ��� ��ġ
		}
		for (b = 0; b < 4; b++)		//��� ���
		{
			xy(2 * (ub[b][0] + x) + bp, ub[b][1] + c + HE);
			printf("��");
		}
	}
	color(7, 0);
}

//�� �Լ� 
void line(int l)
{
	int a, b;		//�ݺ� ����

	for (a = l; a > 0; a--)		//������ �ٺ��� ó������ �迭 �� �ʱ�ȭ
	{
		if (a > 2)		li[a - 2] = li[a - 3];
		xy(2 + bp, a + HE);
		for (b = 1; b <= 10; b++)
		{
			sc[b][a] = sc[b][a - 1];
			color(sc[b][a], 0);
			if (sc[b][a])		printf("��");
			else				printf("  ");
		}
	}
	b = 0;
	for (a = 1; a <= 10; a++)		//3��°�� ���� �� ����
	{
		if (sc[a][2])		b++;		//����� ������� �� ����
	}
	li[0] = b;		//������ ���� �迭 �ʱ�ȭ
	color(7, 0);		//���
}

//��Ʈ���̳� �Լ�
void tet()
{
	int a;		//�ݺ� ����
	int c = 0;		//���� �ټ�

	tb++;		//����� ��� �� ����
	if (op == 0&&tb >= 100)		//������ ����̰� ����� ��� 100���� �� ������
	{
		tb -= 100;		//����� ��� �� ����
		lv++;		//���� ����
		xy(80, 9);		printf("���� ��!");
		lvt = et + 500;
	}
	for (a = 0; a < 4; a++)
	{
		sc[ub[a][0] + x][ub[a][1] + y] = col;		//��� ����
		li[ub[a][1] + y - 2]++;		//�ش� ���� �迭 �� ����
	}
	for (a = 1; a < 21; a++)		//ù�� ���� ������ Ȯ��
	{
		if (li[a] == 10)		//���� ����
		{
			c++;		//���� �ټ� ����
			l--;		//�� �� ����
			line(a + 2);		//�� ����
			if (op == 2 && a == 20)		de = 1;		//���� ��
		}
	}
	if (c)			//���� ���� �����Ұ��
	{
		if (op == 3)		//���� ��� �ϰ��
		{
			al += c - 1;		//���� ���� �ټ�
			if (al > 4)		al = 4;		//�ִ� ���� ���� �ټ��� 4��
			color(8, 0);
			for (a = 0; a < al; a++)
			{
				xy(84, AP - a);
				printf("��");
			}
			color(7, 0);
		}
		xy(30 + bp, 12);
		for (a = 1; a <= c; a++)		po += a;		//�Ѳ����� ���� ���ﶧ���� ���� ������ Ŀ��
		po += co;		//�޺� ���ʽ�
		if (c == 2)				printf("����     ");
		else if (c == 3)		printf("Ʈ����   ");
		else if (c == 4)		printf("��Ʈ����!");
		lpt = et + 500;
		if (op != 3)		//���� ��尡 �ƴҶ�
		{
			co++;		//�޺� ����
			if (co > 1)		//2���� ����
			{
				xy(70, 14);		printf("�޺� X %d", co - 1);		//�޺� ���
			}
		}
	}
	else if (co)		//���� ���� ���� �޺��� �־��� ���
	{
		xy(70, 14);		printf("        ");
		co = 0;		//�޺� �ʱ�ȭ
	}
}

//ȸ�� �Լ�
void rotate()
{
	int a, b = 0;		//�ݺ� ����
	int c;		//���� ����

	for (a = 0; a < 4; a++)		//90�� ȸ��
	{
		c = ub[a][1];		//����� ����
		ub[a][1] = ub[a][0];
		ub[a][0] = 3 - c;
	}
	if (crash())		//�浹��
	{
		a = xs;
		while (b < 2)		//��ǥ ������ ������
		{
			c = 1;
			if (col == 11)		c = 2;
			for (; c > 0; c--)
			{
				if (b == 0)			x--;		//������ ���� �پ� ȸ���ȵǴ� ���� ����
				else if (b == 1)	x++;		//���� ���� �پ� ȸ���ȵǴ� ���� ����
				xs = x;		//����ε� �浹������ ���� ���� ���� ��ǥ�� �ʱ�ȭ
				if (!crash())		break;		//�浹���ҽ� Ż��
			}
			if (!crash())		break;		//�浹���ҽ� Ż��
			b++;
			x = a;
		}
		if (b == 2)
		{
			for (a = 0; a < 4; a++)		//-90�� ȸ��
			{
				c = ub[a][0];		//����� ����
				ub[a][0] = ub[a][1];
				ub[a][1] = 3 - c;
			}
		}
	}
}

//��� Ȧ�� �Լ�
void hold()
{
	int a, b;		//�ݺ� ����
	int d;		//�Ű� ����

	x = 4;	y = 0;		//��ǥ �ʱ�ȭ

	for (a = 0; a < 4; a++)		//������ ������ ��� ����
	{
		for (b = 0; b < 4; b++)
		{
			xy(2 * a - 15 + bp, b + 22);
			printf("  ");
		}
	}
	col -= 9; block(0, col); color(col, 0);		//���� ��� �ʱ�ȭ
	for (a = 0; a < 4; a++)		//������ ��� ���
	{
		xy(2 * ub[a][0] - 15 + bp, ub[a][1] + 22);
		printf("��");
	}
	d = col - 9;		//���� ��� �ӽ� ����
	block(0, svt);		//���� ����� ����� ������� �ٲ�
	if (svt == 8)		blockchange();		//ù Ȧ�忴�����
	svt = d;

	color(7, 0);
}

//���� �����ֱ�
void print()
{
	int rt;		//���� �ð�

	if (op != 3)		//���� ��� ����
	{
		xy(70, 9);		printf("����:%d", lv);
		xy(70, 10);		printf("����:%d", po);
		if (lvt < et)		//����, ���� ��ȭ ���
		{
			xy(80, 9);		printf("         ");
			xy(80, 10);		printf("                 ");
		}
	}
	else		//���� ����϶�
	{
		color(7, 0);
		xy(29, 5);		printf("player");
		xy(68, 5);		printf("computer");
	}
	if (op == 1)		//���� ����� ���
	{
		if (l < 0)		l = 0;		//�����ϰ�� 0���� ����
		xy(70, 16);		 printf("���� ��:%d ", l);
	}
	else if (op == 2)		//���� ����ϰ��
	{
		rt = (cpt - et + 60000) / 1000;
		if (rt > 0)
		{
			xy(50, 4);		printf("%d ", rt);
		}
	}
	if (lpt < et)		//���� ��Ȳ ���
	{
		xy(30 + bp, 12);
		printf("         ");
	}
}

//�Ͻ� ���� �Լ�
int pause()
{
	int ke;		//�Է� ����
	int t = 0;

	st = clock();		//�ð� �ʱ�ȭ
	color(7, 0);		//���
	xy(30 + bp, 7);		printf("�Ͻ� ����");
	xy(5, 18);		printf("����: %c", kee[5]);
	xy(11, 18);		keyprint(kee[5]);

	do
	{
		et = clock();		//���� �ð� �ʱ�ȭ
		if (kbhit())		//�Է� ����
		{
			ke = getch();
			ke = keychange(ke);		//Ű�� ����
			if (ke == kee[6] || ke == kee[5])		break;		//�Ͻ����� ����
		}
		else if (et - st > 500)
		{
			xy(30 + bp, 7);
			if (t)		printf("�Ͻ� ����");
			else		printf("         ");
			t = !t;
			st = clock();		//�ð� �ʱ�ȭ
		}
	} while (1);
	xy(30 + bp, 7);		printf("         ");		//�Ͻ� ���� ���� ����
	xy(5, 18);		printf("               ");		//Ű ���� ����
	if (ke == kee[6])		return 1;		//���� ��� ����
	else					return 0;		//���� �������� ����
}

//�� ���� �Լ�
void linemake()
{
	int a, b, c;		//�ݺ� ����
	int r, l;		//���� ����

	for (a = 0; a < 4; a++)		//������ ������ ��� ����
	{
		for (b = 0; b < 4; b++)
		{
			xy(2 * a - 15 + bp, b + 22);
			printf("  ");
		}
	}
	block(0, 2); color(col, 0);		//���� ��� �ʱ�ȭ
	for (a = 0; a < 4; a++)		//���� ��� ���
	{
		xy(2 * ub[a][0] - 15 + bp, ub[a][1] + 22);
		printf("��");
	}
	svt = 2;
	for (a = 0; a < 6; a++)		//1 ~ 6���� �ʱ�ȭ
	{
		for (c = 1; c <= 10; c++)		sc[c][a + 2] = 0;
	}
	while (a)
	{
		r = rand() % 10 + 1;		//���� ��ġ ���� ����
		l = rand() % 4 + 1;		//�ִ� 4��
		for (b = 0; b < l; b++)
		{
			li[a] = 9;		//�� ĭ ��(���� ����)
			for (c = 1; c <= 10; c++)		sc[c][a + 2] = 7;		//ȸ�� ���
			sc[r][a + 2] = 0;		//��� ����
			a++;
			if (a == 21)
			{
				a = 0;		//�Լ� ����
				break;
			}
		}
	}
	color(7, 0);		//���
	for (a = 22; a > 2; a--)		//������ �ٺ��� ó������ �迭 �� �ʱ�ȭ
	{
		xy(42, a + HE);
		for (b = 1; b <= 10; b++)
		{
			if (sc[b][a])		printf("��");
			else				printf("  ");
		}
	}
	color(7, 0);
}

//��� �Լ�
void wait()
{
	int c = 0;		//����
	int t = 0;		//Ƚ��

	color(7, 0);
	xy(49, 10);		printf("READY !");
	Sleep(1000);
	st = clock();
	while (t != 10)
	{
		if (clock() - st > 100)
		{
			t++;
			c = rand() % 7 + 8;
			color(c, 0);
			xy(49, 10);		printf("START !");
			st = clock();
		}
		if (kbhit())		c = getch();		//�Է���Ű ���ۿ��� ����
	}
	xy(49, 10);		printf("        ");
}

//��ǻ�� �̵� ����
int control(int x, int y)
{
	int a;		//�ݺ� ����

	for (a = 0; a < 4; a++)		//�� ��� 4�� �浹 ���� �Ǻ�
	{
		if (cs[cb[a][0] + x][cb[a][1] + y])			return 0;		//�浹��
	}

	return 1;		//�浹 ���� ����
}

//��ǻ�� ȸ��
void comrotate()
{
	int a, b;
	for (a = 0; a < 4; a++)		//90�� ȸ��
	{
		b = cb[a][1];		//����� ����
		cb[a][1] = cb[a][0];
		cb[a][0] = 3 - b;
	}
}

//��� ������ ��
int blockheight(int y)
{
	int he = 0;		//��� ����
	int a;		//�ݺ� ����

	for (a = 0; a < 4; a++)		he += cb[a][1];
	he += lv*y;

	return he;
}

//�ϼ��� ���� ����
int linefinish(int x, int y)
{
	int l = 0;		//�ϼ��� ���� ����
	int a;		//�ݺ� ����

	for (a = 0; a < 4; a++)		cl[cb[a][1] + y - 2]++;		//�ش� ���� �迭 �� ����
	for (a = 1; a < 21; a++)	if (cl[a] == 10)		l++;		//�ϼ������� ���� ����

	return 10 * l;
}

//��ü ����� ���� ī��Ʈ
int blockcount()
{
	int bc = 0;		//��� ī��Ʈ
	int a, b;		//�ݺ� ����

	for (a = 1; a <= 10; a++)		//���� 10�� Ȯ��
	{
		for (b = 3; b < 23; b++)		//���� 20�� Ȯ��
		{
			if(!cs[a][b])		bc++;		//��� ī��Ʈ
		}
	}

	return bc;
}

//��ȿ ����� Ȯ��
int voidspace(int x,int y)
{
	int vs = 0;
	int a, b;		//�ݺ� ����

	for (a = 0; a < 4; a++)		cs[cb[a][0] + x][cb[a][1] + y] = 1;		//��� ����
	for (a = 1; a <= 10; a++)		//10�� �� ���� Ȯ��
	{
		for (b = 3; !cs[a][b]; b++)		vs++;		//��ȿ ����� ī��Ʈ
	}

	return 2 * lv * vs + 1;
}

//�ֺ� ��� ���� Ȯ��
int narrowblock(int x,int y)
{
	int a;		//�ݺ� ���
	int c = 0;		//ī��Ʈ ����

	for (a = 0; a < 4; a++)		//4��� Ȯ��
	{
		if (cs[cb[a][0] + x - 1][cb[a][1] + y])		c++;
		if (cs[cb[a][0] + x + 1][cb[a][1] + y])		c++;
		if (cs[cb[a][0] + x][cb[a][1] + y - 1])		c++;
		if (cs[cb[a][0] + x][cb[a][1] + y + 1])		c++;
	}

	return 4 * c;
}

//��� ���� �ǵ���
void blockreturn(int x, int y)
{
	int a;		//�ݺ� ����

	if (lv != 2)		for (a = 0; a < 4; a++)		cl[cb[a][1] + y - 2]--;		//�ش� ���� �迭 �� ����
	for (a = 0; a < 4; a++)		cs[cb[a][0] + x][cb[a][1] + y] = 0;		//��� ����
}

//��ǻ�� �ΰ�����
void computer()
{
	int x, y, r;		//��� ����
	int sc;		//���� ����
	int he;		//��ϳ����� ��
	int	l = 0;		//�ϼ��� ���ǰ���
	int nb = 0;		//�ֺ� ��� ����
	int vs = 0, vb;		//�����
	int cp = -200;		//�� ����
	int a;		//�ݺ� ����

	vb = blockcount();		//��ü ����� ���
	for (r = 0; r < 4; r++)		//ȸ�� ������ 4����
	{
		x = 1;
		while (control(--x, 0));		//��� ���� �ݺ��̵�
		while (control(++x, 0))		//��� ������ �ݺ� �̵�
		{
			y = 0;		//��ǥ�� �ʱ�ȭ
			while (control(x, ++y));		//��ǻ�� ��� �Ʒ� �ݺ� �̵�
			y--;		//���� ��ǥ ����
			he = blockheight(y);		//��� ������ �� ���
			vs = voidspace(x, y);		//��ȿ ����� ���
			vs = vb - vs;		//��� ������ ����� ���
			if (lv >= 3)		l = linefinish(x, y);		//�ϼ��� ���� ���� ���
			if (lv == 4)		nb = narrowblock(x, y);		//������ ��� ���� ���
			sc = he - vs + l + nb;		//���� ���� ���
			if (sc > cp)		//���� ������ ���� �������� �� Ŭ���
			{
				dx = x;	cp = sc; dr = r;		//��� ���� �ʱ�ȭ
			}
			blockreturn(x, y);		//��� �������� ��ȭ�� �� �ʱ�ȭ
		}
		comrotate();		//��ǻ�� ȸ��
	}
}

//���� �Լ�
void attack(int p)
{
	int a, b;		//�ݺ� ����
	int r;		//���� ����

	if (p == 1)		//���� ����
	{
		r = rand() % 10 + 1;		//���� ��ġ
		for (a = 2; a <= 22 - al; a++)		//ó������ ������ �ٱ��� �迭 �� �ʱ�ȭ
		{
			cl[a - 2] = cl[a - 2 + al];		//���� �迭�� ����Ʈ
			xy(2 + 3 * bp, a + HE);
			for (b = 1; b <= 10; b++)		//ȭ�� �迭�� ����Ʈ �� �����
			{
				cs[b][a] = cs[b][a + al];
				color(cs[b][a], 0);
				if (cs[b][a])		printf("��");
				else				printf("  ");
			}
		}
		for (a = 22; al > 0; al--, a--)		//�ؿ��� ��� �ö��
		{
			cl[a - 2] = 9;		//�� ĭ ��(���� ����)
			for (b = 1; b <= 10; b++)		cs[b][a] = 7;		//��� ���
			cs[r][a] = 0;		//��� ����
			xy(2 + 3 * bp, a + HE);
			for (b = 1; b <= 10; b++)		//ȭ�� �迭�� �ʱ�ȭ �� �����
			{
				color(7, 0);
				if (cs[b][a])		printf("��");
				else				printf("  ");
			}
		}
		for (a = 0; a < 4; a++)
		{
			xy(84, AP - a);
			printf("  ");
		}
	}
	else if (p == 2)		//��ǻ�� ����
	{
		r = rand() % 10 + 1;		//���� ��ġ
		for (a = 2; a <= 22 - dl; a++)		//ó������ ������ �ٱ��� �迭 �� �ʱ�ȭ
		{
			li[a - 2] = li[a - 2 + dl];		//���� �迭�� ����Ʈ
			xy(2 + bp, a + HE);
			for (b = 1; b <= 10; b++)		//ȭ�� �迭�� ����Ʈ �� �����
			{
				sc[b][a] = sc[b][a + dl];
				color(sc[b][a], 0);
				if (sc[b][a])		printf("��");
				else				printf("  ");
			}
		}
		for (a = 22; dl > 0; dl--, a--)		//�ؿ��� ��� �ö��
		{
			li[a - 2] = 9;		//�� ĭ ��(���� ����)
			for (b = 1; b <= 10; b++)		sc[b][a] = 7;		//��� ���
			sc[r][a] = 0;		//��� ����
			xy(2 + bp, a + HE);
			for (b = 1; b <= 10; b++)		//ȭ�� �迭�� �ʱ�ȭ �� �����
			{
				color(7, 0);
				if (sc[b][a])		printf("��");
				else				printf("  ");
			}
		}
		for (a = 0; a < 4; a++)
		{
			xy(18, AP - a);
			printf("  ");
		}
	}
}

//��ǻ�� �ൿ
int AI()		//ȸ�� ���¸� �Է� ����
{
	int a, b, c;		//�ݺ� ����
	int lc = 0;		//�ټ� ī��Ʈ

	cpt = clock();
	color(cc, 0);		//��ǻ�� ��ϻ� ����
	if (de == 0)		//���� ����� ������
	{
		de = 1;		//���� ��� ����
		cx = 4; cy = 0;
		cc = rand() % 7;
		//������ �ʱ� ���� ��ǥ �������� �ʱ� ������ǥ
		block(2, cc);
		color(cc, 0);		//��ǻ�� ��� ����
		for (a = 0; a < 4; a++)
		{
			xy(2 * (cb[a][0] + cx) + 3 * bp, cb[a][1] + cy + HE);	printf("��");		//��� ���
		}
		cys = cy;	cxs = cx;		//��ǻ�� ��� ��ġ �ʱ�ȭ	
		computer();		//��ǻ�� �ൿ ����

		return 1;
	}
	if (dr)		//��ǻ�� ��� ȸ��
	{
		for (a = 0; a < 4; a++)
		{
			xy(2 * (cb[a][0] + cxs) + 3 * bp, cb[a][1] + cys + HE);			printf("  ");		//��� ����
		}
		dr--;
		for (a = 0; a < 4; a++)		//90�� ȸ��
		{
			c = cb[a][1];		//����� ����
			cb[a][1] = cb[a][0];
			cb[a][0] = 3 - c;
		}
		for (a = 0; a < 4; a++)		//�浹 �Ǻ�
		{
			if (cs[cb[a][0] + cx][cb[a][1] + cy])		//�浹 ��
			{
				for (a = 0; a < 4; a++)		//-90�� ȸ��
				{
					c = cb[a][0];		//����� ����
					cb[a][0] = cb[a][1];
					cb[a][1] = 3 - c;
				}
				dr = 0;		//�� �̻� ȸ�� ���� ����
			}
		}
		for (a = 0; a < 4; a++)
		{
			xy(2 * (cb[a][0] + cx) + 3 * bp, cb[a][1] + cy + HE);			printf("��");		//��� ���
		}
	}
	else if (cx == dx)		//��ǥ ���������� �����ϰų� �����Ұ��
	{
		cy++;		//��ǻ�� ��� �ϰ�
	}
	else		//��ǻ�� ��� ���� �̵�
	{
		if (cx > dx)		cx--;
		if (cx < dx)		cx++;
	}
	if (0)		//��ǻ�� Ȧ��(�̱���)
	{
		//h++;		//Ȧ�� �� ������ ���� Ȧ�� ����
		erase();		//���� ����� ��� ����
		hold();		//��� ����
		blockprint();		//�ٲ� ��� ���
		st = clock();		//�ð� �ʱ�ȭ
							//continue;		//�ٲ� ������� ��� ����
	}
	for (a = 0; a < 4; a++)		//�浹 �Ǻ�
	{
		if (cs[cb[a][0] + cx][cb[a][1] + cy])		//�浹 ��
		{
			if (cx != cxs)
			{
				dx = cx = cxs;		//���̻� ���η� �������� ����
				a--;
				continue;		//������
			}
			if (cy != cys)		//���θ� �ٸ���
			{
				de = 0;		//��� ����
				cy--;
				for (a = 0; a < 4; a++)
				{
					cs[cb[a][0] + cx][cb[a][1] + cy] = cc;		//��� ����
					cl[cb[a][1] + cy - 2]++;		//�ش� ���� �迭 �� ����
				}
				for (a = 1; a < 21; a++)		//ù�� ���� ������ Ȯ��
				{
					if (cl[a] == 10)		//���� ����
					{
						lc++;
						for (b = a + 2; b > 0; b--)		//������ �ٺ��� ó������ �迭 �� �ʱ�ȭ
						{
							if (b > 2)		cl[b - 2] = cl[b - 3];
							xy(2 + 3 * bp, b + HE);
							for (c = 1; c <= 10; c++)
							{
								cs[c][b] = cs[c][b - 1];
								color(cs[c][b], 0);
								if (cs[c][b])		printf("��");
								else				printf("  ");
							}
						}
						b = 0;
						for (c = 1; c <= 10; c++)		//3��°�� ���� �� ����
						{
							if (cs[c][2])		b++;		//����� ������� �� ����
						}
						cl[0] = b;		//������ ���� �迭 �ʱ�ȭ
					}
				}
				if (lc >= 2)		//������ ���� ���� 2���̻��϶�
				{
					dl += lc - 1;
					if (dl > 4)		dl = 4;		//����� �ִ� ���� ���� 4��
					color(8, 0);
					for (a = 0; a < dl; a++)
					{
						xy(18, AP - a);
						printf("��");
					}
					color(cc, 0);
				}
				if (al)		attack(1);		//������ ���� ������ ���� ����
				if (cl[0])		//����� 20�� �Ѱ� �׿�����
				{
					return 0;		//����
				}
			}
		}
	}
	if (cx + cy != cxs + cys)		//����� �����������
	{
		for (a = 0; a < 4; a++)
		{
			xy(2 * (cb[a][0] + cxs) + 3 * bp, cb[a][1] + cys + HE);			printf("  ");		//���� ����� ��� ����

		}
		for (a = 0; a < 4; a++)
		{
			xy(2 * (cb[a][0] + cx) + 3 * bp, cb[a][1] + cy + HE);			printf("��");		//��� ���
		}
		cys = cy;	cxs = cx;		//��ǻ�� ��� ��ġ �ʱ�ȭ
	}

	return  1;		//��� ����
}

//Ű���� �ʱ�ȭ
void keyreset()
{
	int a;		//�ݺ� ����

	kee[0] = 72; kee[1] = 75; kee[2] = 77; kee[3] = 80;		//����Ű �ʱ�ȭ(��,����,������,�Ʒ�)
	kee[4] = 'a';	kee[5] = '\r';	kee[6] = ' ';	//Ư��Ű �ʱ�ȭ(ȸ��, Ȧ��, �Ͻ�����)
	for (a = 0; a < 4; a++)		kee[a] += KE;		//Ű�� ����
}

//Ű ���� �Լ�
void key()
{
	int ke;		//�Է� ����
	int a, b = 0, c;		//�̵� ����
	int dc = 0;		//ȭ��ǥ ����
	int sk[7];		//Ű �Ű� ����

	bp = 0;

	for (a = 0; a < 7; a++)		sk[a] = kee[a];		//Ű �ӽ� ����
	system("cls");
	while (1)
	{
		a = KY + 14;
		color(7 + dc * 5, 0);		//ȭ��ǥ ���� ����
		xy(27, KY + 2 + 2 * b);		printf("��");
		color(7, 0);
		info();		//Ű ���� ���
		xy(30, a += 2);		printf("�ʱⰪ   ");
		xy(30, a += 2);		printf("���     ");
		xy(30, a += 2);		printf("����     ");
		ke = getch();
		xy(27, KY + 2 + 2 * b);		printf("  ");		//���� ȭ��ǥ ����
		if (dc == 1)		//Ű ������
		{
			dc = 0;
			if (b < 7)
			{
				ke = keychange(ke);		//Ű�� ����
				kee[b] = ke;		//Ű ����
			}
		}
		else if (ke == 224)		//����Ű ����
		{
			ke = getch();
			if (ke == 72)		b--;		//����
			if (ke == 80)		b++;		//�Ʒ���
			if (b < 0)		b += 10;		//���� �� ����
			b %= 10;		//�ɼ��� 10����
		}
		else if (ke == '\r')		//���� �Է½� Ű ���� ��� ��ȯ
		{
			if (b > 6)
			{
				if (b == 7)		//�ʱⰪ
				{
					system("cls");
					keyreset();		//Ű �ʱⰪ �ҷ���
				}
				else if (b == 8)		//���
				{
					for (a = 0; a < 7; a++)		kee[a] = sk[a];		//Ű �ʱ�ȭ
					break;		//Ű�� ����
				}
				else if (b == 9)		//����
				{
					for (a = 0; a < 6; a++)		//�ߺ� �˻�
					{
						for (c = a + 1; c < 7; c++)
						{
							if (kee[a] == kee[c])		//�ߺ�Ű�� �������
							{
								a = c = 7;		//�ΰ��� �ݺ��� Ż�� ����
								xy(40, 22);		printf("�ߺ�Ű ����");
								getch();
								xy(40, 22);		printf("           ");
							}
						}
					}
					if (a != 8)		break;		//Ű�� ����
				}
			}
			else
			{
				dc = 1;
			}
		}
	}
}

//Ű���� ����
int keyboard(int ke)
{
	int sat[2];		//�ð� ���� ����

	ke = keychange(ke);		//Ű�� ����
	if (ke == kee[0])		//��� �ϰ�
	{
		for (; !crash(); y++);		//�ٷ� �ؿ� ��ϰ� �浹�Ҷ� ���� ��� �ϰ� ��Ŵ
		erase();
		blockprint();
		y++;		//�浹 ������ ���� ��� �ϰ�
		st = clock();		//�ð� �ʱ�ȭ
	}
	else if (ke == kee[1])		//���� �̵�
	{
		x--;
	}
	else if (ke == kee[2])		//������ �̵�
	{
		x++;
	}
	else if (ke == kee[3])		//�Ʒ� �̵�
	{
		y++;
		st = clock();		//�Է� �ð� �ʱ�ȭ
	}
	if (ke == kee[4])		//ȸ��
	{
		erase();		//���� ����� ��� ����
		rotate();
		blockprint();		//��� ���
	}
	else if (!h&&ke == kee[5])		//Ȧ��(�� ��ϴ� �ѹ��� ����)
	{
		h++;		//Ȧ�� �� ������ ���� Ȧ�� ����
		erase();		//���� ����� ��� ����
		hold();		//��� ����
		blockprint();		//�ٲ� ��� ���
		st = clock();		//�ð� �ʱ�ȭ
		return 1;		//��Ƽ��
	}
	else if (ke == kee[6])			//�Ͻ�����	
	{
		sat[0] = et - st;		//���� �ð� ����
		sat[1] = et - cpt;		//���� ��ǻ�� �ð� ����
		ke = pause();		//�Ͻ� ����
		st = et - sat[0];		//���� �ð� ����
		cpt = et - sat[1];		//���� ��ǻ�� �ð� ����
		if (!ke)		return 2;		//ESC�� ������� ���� ����
	}
	return 0;
}

//���� ����
int play()
{
	int a;
	int ke;		//�Է� ����

	while (p)
	{
		x = 4; y = 0;		//�ʱ� ��ǥ ����
		h = 0;		//Ȧ�� �� �ʱ�ȭ
		blockchange();		//���ο� ��� ����
		blockprint();		//��� ���
		st = clock();		//�Է� �ð� �ʱ�ȭ
		while (p)
		{
			et = clock();		//���� �ð� �ʱ�ȭ
			if (op == 3 && cpt + ca < et)		p = AI();
			else		print();
			if (kbhit())
			{
				ke = getch();
				ke = keyboard(ke);
				if (ke == 1)
				{
					continue;		//�ٲ� ������� ��� ����
				}
				else if (ke == 2)
				{
					li[0] = 1;		//���� �й� ����
					p = 0;		//���� ����
				}
			}
			if (et - st > 2000 / lv)		//������ Ű �Է� �� ���� �ð��� �������
			{
				st = clock();		//�Է� �ð� �ʱ�ȭ
				y++;		//��� �ϰ�
			}
			if (crash())		//Ÿ ��� ���� �浹��
			{
				tet();		//��� ����
				if (op == 2 && de == 1)		//���� ��� �϶�
				{
					de = 0;		//���� ���� �ʱ�ȭ
					po += lv*lv;		//���ʽ� ����
					xy(80, 9);		printf("���� ��!");
					xy(80, 10);		printf("���ʽ� ���� %d", lv*lv);
					lvt = et + 500;
					lv++;		//���� ����
					linemake();		//�� ����
					cpt = clock();		//�ð� �ʱ�ȭ
				}
				break;		//�� ��� �̵� ����
			}
			if (x + y != xs + ys)		//����� �����������
			{
				erase();		//���� ����� ��� ����
				blockprint();		//��� ���
			}
		}
		if (dl > 0)			attack(2);		//��������� ������ ��ǻ�� ����
		if (op == 2 && cpt + 60000 < et)		//������忡�� �ð��� ���� ��� �ؿ��� ��� �ö��
		{
			cpt = clock();
			dl = 1;			//������� 1�� ����
			attack(2);		//��� �ö��
		}
		if (li[0] || (op == 1 && l <= 0))		//���� ���� ������ �޼�������
		{
			p = 0;		//���� ����
			break;
		}
	}
	system("cls");
	color(7, 0);
	xy(40, 15);
	if (op == 0)		printf("Game Over!  ");		//�Ϲ� ��� �϶�
	else if (op == 1)		//���� ��� �϶�
	{
		if (l <= 0)		printf("Game Clear!  ");		//���� ��ǥġ ��ŭ �����ؼ� ����Ȱ��
		else		printf("Game Over!  ");		//����� 20���̻� �׿��� ����Ȱ��
	}
	if (op != 3)
	{
		printf("��������:%d", po);
		if (po > mc[op])
		{
			xy(40, 17);		printf("�ְ� ���!");
			mc[op] = po;		//�ְ� ��� ���
		}
	}
	else
	{
		if (li[0])		printf("YOU LOSE!");
		else
		{
			lv -= 2;
			printf("YOU WIN!");
			ba[lv]++;
		}
	}
	FILE*fp = fopen("record.txt", "wt");
	for (a = 0; a < 3; a++)			fprintf(fp, "%d\n%d\n", mc[a], ba[a]);
	fclose(fp);
	xy(40, 20);		printf("re?    Y/N");
	do
	{
		ke = getch();
		if (ke == 'y' || ke == 'Y')				return 1;		//�����
		else if (ke == 'n' || ke == 'N')		return 0;		//����
	} while (1);
}

//�ְ� ����
void record()
{
	int a;

	a = 8;
	xy(30, a += 2);	printf("�Ϲ� ��� �ְ� : %d��", mc[0]);
	xy(30, a += 2);	printf("���� ��� �ְ� : %d��", mc[1]);
	xy(30, a += 2);	printf("���� ��� �ְ� : %d��", mc[2]);
	xy(30, a += 2);	printf("���� ��� �ϱ� : %d��", ba[0]);
	xy(30, a += 2);	printf("���� ��� �߱� : %d��", ba[1]);
	xy(30, a += 2);	printf("���� ��� ��� : %d��", ba[2]);
	getch();
}

//�������� �Լ�
void game()
{
	system("cls");
	option();		//�ɼ� ����
	if (op >= 4)	//���� ������ �ƴ�
	{
		p = 0;		//���� ���� ����
		if (op == 4)		key();		//Ű ����
		else				record();		//�ְ� ����
	}
	while (p)		//���� ����
	{
		reset();		//�ʱ�ȭ
		if (op == 1)		//���� ��� �϶�
		{
			view(1);		//Ŀ�� ����
			do
			{
				xy(10, 10);
				printf("���̵��� �Է��ϼ���(�ּ� 1�̻�): ");
				scanf("%d", &lv);		//���̵� �Է� ����
				system("cls");
			} while (lv <= 0);		//���� ������ ��� Ż��
			do
			{
				xy(10, 10);
				printf("������ ��ǥġ�� �Է��ϼ���: ");
				scanf("%d", &l);
				system("cls");
			} while (l <= 0);		//0�� �̻��� ��� Ż��
			view(0);		//Ŀ�� �ٽ� ����
		}
		else if (op == 3)		//���� ��� �϶�
		{
			do
			{
				xy(20, 10);
				printf("���̵��� �����ϼ���   1: ��  2: ��  3: ��  ");
				scanf("%d", &lv);
				system("cls");
			} while (lv < 1 || lv > 3);		//���� ������ �鶧 Ż��
			if (lv == 1)			ca = 17;
			else if (lv == 2)		ca = 134;
			else if (lv == 3)		ca = 286;
			lv = 5 - lv;		//���� ����
		}
		if (op != 3)		screen();		//ȭ�� & �ʱ� �� ����
		else				twoscreen();		//2ȭ�� ���
		info();
		blockchange();		//�ʱ� ��� ����
		wait();		//���
		if (op == 2)			linemake();		//�� ����
		else if (op == 3)		AI();		//��ǻ�� �ൿ
		cpt = clock();
		p = play();
		color(7, 0);		//���
	}
}

//���Ͽ���
void file()
{
	int a;

	FILE*fp = fopen("record.txt", "rt");
	for (a = 0; a < 3; a++)		fscanf(fp, "%d %d", &mc[a], &ba[a]);
	fclose(fp);
}

int main()
{
	srand(time(NULL));
	view(0);
	title();		//Ÿ��Ʋ ���
	keyreset();		//Ű �ʱ�ȭ
	file();		//���� ����
	while (1)		game();		//���� ����

	return 0;
}