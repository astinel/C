#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int p=0,m=0,c=0;		//��ġ, ���� ����
int in=0,d=0;		//���� ����
int lv=1,ex=0,hp=10,mp=5,at;		//���� �ɷ�ġ ����
int plv=1,php=1;		//�� ����
int st=500,it=0,sp=0,q=0;		//���� ����
int h,mat,mex,mst;		//���� ����
int sk[5];		//���� ����
int mmi,mma;		//�� �̵� ����

void xy(int x,int y)		//Ŀ���̵�
{
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void clear(int y,int le)		//���� ����
{
	int l=0;		//�� ���� Ȯ�� ����

	xy(0, y);		//y+1��° �� ���� ����

	while(1)
	{
		l++;
		printf("\r                                                                                     ");		//���� �������� ����
		if(l!=le)		//le�� �����ϰ� ���� �ٱ��� ��
		{
			printf("\n");		//�� �� ������
		}
		else
		{
			printf("\r");
			break;		//���ϴ� �ٱ��� ��ŭ ����� Ż��
		}
	}
}

void info()	//�˸���
{
	clear(15,1);
	xy(0, 14);
	printf("-----------------------------------------------\n");
	printf("");
	if(in==0)	printf("�̵��Ұ��� �����ϼ���.");
	else if(in==1)	printf("�������� �̵�");
	else if(in==2)	printf("���������� �̵�");
	else if(in==3)	printf("�� ������ �� �̻� ���������ϴ�.");
	else if(in==100)	printf("�б��� �����ϼ˽��ϴ�.");
	else if(in==102)	printf("���:��Ϳ�~~");
	else if(in==103)	printf("ī��:ȭ����..ȭ��!");
	else if(in==105)	printf("ī�þ�:���δ� ����� �ϰ��ֽ��ϱ�?");
	else if(in==106)	printf("�극��:...����?");
	else if(in==108)	printf("���̸�:!@#$%?");
	else if(in==109)	printf("��ī��:��ſ��� �ູ��..");
	else if(in==112)	printf("�ָ�:���� ���� �ִ°ų�?");
	else if(in==200)	printf("������ �����ϼ̽��ϴ�.");
	else if(in==202)	printf("�ٸ���:�������.");
	else if(in==204)	printf("����:�������.");
	else if(in==206)	printf("ġ��:ȯ���մϴ�.");
	else if(in==209)	printf("����:�ȳ��ϼ���.");
	else if(in==300)	printf("���� ������ ���ϴ�.");
	else if(in==302)	printf("���׳��:������?");
	else if(in==305)	printf("����:...");
	else if(in==350)	printf("�����Ҽ� �����ϴ�.");
	else if(in==360)	printf("���Ϳ� ������ �����մϴ�.");
	else if(in==370)	printf("������ ��� �����մϴ�.");
	else if(in==400)	printf("	�ɼ�");
	else	printf("�ƹ��͵� �����ϴ�.");
	printf("\n-----------------------------------------------");
	xy(0,1);
	if(in==400)	printf("	1:������ 2:������ 3:������ 5:ó������ 6:����");
}

void level()	//����
{
	int ch;		//���� �� �Ǻ� ����

	if(ex<1)	ch=1;
	else if(ex<3)	ch=2;
	else if(ex<6)	ch=3;
	else if(ex<10)	ch=4;
	else	ch=5;		//����
	if(lv!=ch)
	{
		printf("\n	-���� ��!-\n");
		sp+=(ch-lv);		//���� �� ��ġ��ŭ ��ų����Ʈ ����
		lv=ch;
		hp=lv*10;
		mp=lv*5;
		printf("\n�ִ� hp�� %d�� �Ǿ����ϴ�. ",hp);
		printf("\n�ִ� mp�� %d�� �Ǿ���ϴ�. ",mp);	
	}
}

int skill()
{        
	if(sp==0)
	{
		printf("\r		sp�� ���� �մϴ�.");
		return 0;
	}
	clear(4,1);		//1�� ����
	sp--;
	printf("\n������ ������ϴ�.");
	if(!sk[0] &&in==103)
	{
		sk[0]++;
	}
	else if(!sk[1] &&in==105)
	{
		sk[1]++;
	}
	else if(!sk[2] &&in==106)
	{
		sk[2]++;
	}
	else if(!sk[3] &&in==108)
	{
		sk[3]++;
	}
	else if (!sk[4] && in == 109)
	{
		sk[4]++;
	}
	else
	{
		sp++;
		printf("\r                          \r");		//���� ����
		printf("�̹� ��� �����Դϴ�.");
	}
}

void place()	//���� ���
{
	mmi=0;		//�� ��ǥ�� �ּҰ�
	if(c=='1')		//�б��ϰ��
	{
		if(p==0)	printf("�б��Ա�");
		else if(p==2)	printf("���ӱ���");
		else if(p==3)	printf("�Ҹ�������");
		else if(p==5)	printf("������������");
		else if(p==6)	printf("���⸶������");
		else if(p==8)	printf("���ɸ�������");
		else if(p==9)	printf("�ż���������");
		else if(p==12)	printf("�����");
		else	printf("����");
		mma=12;		//�б� ��ǥ�� �ִ�
	}
	else if(c=='2')		//�����ϰ��
	{
		if(p==0)	printf("�����Ա�");
		else if(p==2)	printf("��������");
		else if(p==4)	printf("�����");
		else if(p==6)	printf("Ŀ����");
		else if(p==9)	printf("�ڷ���Ʈ�͹̳�");
		else	printf("����");
		mma=9;		//���� ��ǥ�� �ִ�
	}
	else if(c=='3')		//���� ���� ���
	{
		if(p==15)	printf("�ױ�");
		else if(p==10)	printf("����");
		else if(p==5)	printf("��");
		else if(p==2)	printf("���Ƹ���");
		else if(p==0)	printf("�����Ա�");
		else if(p==-2)	printf("����");
		else if(p==-5)	printf("��");
		else if(p==-11)	printf("���θ�");
		else	printf("?");
		mmi=-11;		//���� �� ��ǥ�� �ּҰ�
		mma=15;		//���� �� ��ǥ�� �ִ�
	}
}

void item()		//������
{
	printf(" %d��� ������",it);
}

void status()		//������
{
	printf("\n  �� ����\n");
	printf("\n  ����:%d",lv);
	printf("\n  ����ġ:%d",ex);
	printf("\n  ü��:%d",hp);
	printf("\n  ����:%d",mp);
	printf("\n  ���� ��Ÿ:%d",st);
	printf("\n  ���� sp:%d",sp);
	printf("\n  ���� ������:");
	item(it);
	xy(40,3);
	printf("���� ����");
	if(sk[0] !=0)
	{
		xy(40,5);
		printf("�Ұ���");
	}
	if(sk[1] !=0)
	{
		xy(40,6);
		printf("��������\n");
	}
	if(sk[2] !=0)
	{
		xy(40,7);
		printf("�������\n");
	}
	if(sk[3] !=0)
	{
		xy(40,8);
		printf("ȸ��\n");
	}
	if(sk[4] !=0)
	{
		xy(40,9);
		printf("��ȭ\n");
	}
	if(sk[0] + sk[1] + sk[2] + sk[3] + sk[4] ==0)
	{
		xy(40,6);
		printf("������ �����ϰ� ���� �ʽ��ϴ�.");
	}
}

void pet()		//������
{
	printf("\n  ������\n");
	printf("\n  lv:%d",plv);
	printf("\n  hp:%d",php);
}

int player(int c)		//������ �÷��̾� ��
{
	int d;

	if(c=='1')		//�Ϲݰ��� ������
	{
		at=lv;
		d=rand()%at+1;		//at�� �÷��̾� ���ݷ�
	}
	else if(c=='2')		//����ĥ Ȯ��
	{
		d=rand()%10;
	}
	return d;
}

void monster()		//���� �Լ�
{
	if(in==302)		//���� �������� ������ �߻��Ѱ��
	{
		q++;		//����Ʈ �� ����
		h=5;		//���� ü�� �� ����
		mat=3;		//���� ���ݷ� �� ����
		mex=2;		//���Ͱ� �ִ� ����ġ�� ����
		mst=2;		//���Ͱ� �ִ� �� �� ����
	}
	else
	{
		h=2;
		mat=2;
		mex=1;
		mst=1;
	}
}

int quest()		//����Ʈ
{
	int ch;
	 
	in=(c-48)*100+p;		//c�� �ƽ�Ű �ڵ� ���̹Ƿ� 48�� ����, ���(c)�� ��ǥ��(p)�� ���� �˸��� ����
	if(p==0)		//���������϶�
	{
		m='4';		//��������
		in=0;
		return 0;
	}
	info();
	printf("\n		������ġ:");
	place();		//��� ȣ��
	ch=q;
	q++;
	xy(0,4);
	printf("		-�̼�%d-\n\n",q);
	xy(0,6);
	printf("	");
	if(in==102)		//���� ����
	{
		if(q==1||q==3)	
		{
			printf("���� ������ ������");
		}
		else
		{
			clear(4,1);
			q--;
		}
	}
	else if(in==302)		//���Ƹ���
	{
		if(q==2)	
		{	
			printf("���ӱ��Ƿ� ������");
		}
		else if(q==4)	
		{
			printf("���Ϳ��� �������� �¸��ϼ���");
			getch();
			battle();
		}
		else
		{
			clear(4,1);
			q--;
		}
		if(q==5)		//������ ����Ʈ
		{
			printf("����Ʈ �Ϸ�!");
		}
	}
	else		//�� ���� �� �ϰ��
	{
		clear(4,1);		//4��° �� ���� 1�� ����
		q--;
	}
	if(ch!=q)
	{
		getch();
	}
}

void map()		//����
{
	int a;		//�ݺ� ����

	clear(5,1);
	printf("	");		//����
	a=p;		//���� ��ǥ ����
	for(p=a-3;p<a+3;p++)		//�յ� 3ĭ������ ǥ��
	{
		if(a==p)		//���� ��ġ ǥ��
		{
			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),12);
		}
		place();
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),7);
		printf("-");
	}
	place();		//-���� �Ѱ� �� ���ƾ� �ϹǷ� �� ���� ǥ��
	p=a;		//���� ��ǥ �ҷ�����
}

int battle()		//���� �Լ�
{
	int c;		//���� ������ �ٸ� ���� ����
	int d;		//���� �� ����

	monster();

	in=360;
	while(h>0)		//���� ü���� 0������ �� ���� �ݺ�
	{
		info();
		printf("\n	1:������ 2:����ġ��\n");
		c=getch();
		if(!(c>='1'&&c<='2'))	continue;		//�ɼǿ��� Ű�� �������� �ٽ� �Է� �޵��� ��
		d=player(c);
		if(c=='1')		//������
		{
			printf("\n������ %d�� ���ظ� �������ϴ�.\n",d);
			h=h-d;
			getch();
		}
		else if(c=='2')			//����ġ��
		{
			if(in==302)		//����Ʈ ���ΰ��
			{
				d!=0;		//������ ���� ����
			}
			if(d==0)		//���� ����
			{
				printf("\n����ġ�µ� �����Ͽ����ϴ�.\n");
				h=0;		//���� ü���� 0���� �������ν� �ݺ��� ��������
			}
			else		//���� ����
			{
				printf("\n����ġ�µ� �����Ͽ����ϴ�.\n");
			}
			getch();
		}
		if(h>0)		//���Ͱ� ���� ���� �ʾ�����
		{
			d=rand()%mat+1;
			printf("\n���� ����\n");
			printf("\n���� �����Ͽ� %d�� ���ظ� �Ծ����ϴ�.\n",d);
			getch();
			hp=hp-d;		//���Ͱ� �� ������ ��ŭ �÷��̾� ü�°���
		}
		if(hp<=0)		//ü���� 0������ ��
		{
			printf("\n�й��ϼ̽��ϴ�.\n");
			getch();
			exit(0);		//���α׷� ����
		}
	}
	if(c!='2')		//����ģ ��� ���� ����
	{
		printf("\n�¸��ϼ̽��ϴ�.\n");
		ex+=mex;		//����ġ ����
		st+=mst;		//�� ����
		level();		//����ġ ������ ���� ���� �� �Ǻ�
		in=370;
		m=0;		//m�� '4'(Ż��)�� ���� �ʵ��� 0���� �ʱ�ȭ
	}
	else		//������ ������ ��� ��������
	{
		in=370;
	}
	getch();
}

void minimap()	//���� ��
{
	m=0;		//m�� 4�� �ȵǵ��� �ʱ�ȭ
	while(m!='4')		//m�� 4�� �ƴҶ����� �ݺ�
	{
		info();
		clear(2,1);
		printf("		������ġ:");
		place();		//��� ȣ��
		printf("\n\n");		//�� �� ���
		map();		//���� ȣ��
		printf("\n\n	1:���� �̵� 2:������ �̵� 3:���� 4:������\n");
		m=getch();		//�ɼ� �Է� ����
		if(m=='1')		//���� �̵�
		{
			in=1;
			p--;		//��ǥ �� ����
		}
		else if(m=='2')		//������ �̵�
		{
			in=2;
			p++;		//��ǥ �� ����
		}
		else if(m=='3')		//����
		{
			quest();		//����Ʈ �Լ� ȣ��
			if(in==103||in==105||in==106||in==108||in==109)
			{
				skill();
				getch();
			}
		}
		else if(m=='4')		//������(��������)
		{
			in=0;
		}
		if(p<mmi||p>mma)		//���� ������
		{
			if(p<=mmi)		//�������� ������
			{
				p++;		//��ǥ �� ����
			}
			else		//���������� ������
			{
				p--;		//��ǥ �� ����
			}
			in=3;
		}
		else if(c=='3')		//���� ���ϰ��
		{
			if(m=='1'||m=='2')		//�����������
			{
				m=rand()%10;		//���Ϳ� ����ĥ Ȯ��
				if(m==0)		//���Ϳ� ����ħ
				{
					battle();		//���� �Լ� ȣ��
				}
			}
		}
	}
}

void option()		//�ɼ�
{
	while(in==400)
	{
		info(in);
		if(c=='1')		//�� ����
		{
			status();
		}
		else if(c=='2')		//�� ����
		{
			pet();
		}
		else if(c=='3')		//������ ����
		{
			printf("\n\n����������\n\n");
			item();
		}
		else if(c=='5')
		{
			in=0;		//ó������ ���ư�
			break;
		}
		else if(c=='6')
		{
			exit(0);		//����
		}
		c=getch();		//�˸� �Լ��� ���Ͽ� �ٷ� ������ �ʵ��� �Լ� �ϴܿ� ��ġ 
	}
}

int main(void)
{
	srand(time(NULL));

	while(c!='6')
	{
		p=0;
		printf("\n		1:�б� 2:���� 3:���� �� 4:�ɼ�");
		info();
		c=getch();
		clear(1, 1);
		if(c>='1'&&c<='3')
		{
			in=(c-48)*100;
			minimap();
		}
		else if(c=='4')
		{
			in=400;
			option();
		}
	}
	return 0;
}