#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

int status(int hp,int mp,int b,int h,int ih,int im,int p)
{
	printf("                            -���� ��Ȳ-           \n");
	printf("                                                  \n");
	printf("                  ü��:%d             ���� ü��:%d\n",hp,h);     
	printf("                  ����:%d             ���� ��:%d  \n",mp,b);
	printf("                  ü�� ����:%d        ���� ����:%d\n\n",ih,im);
	if(p!=0)
	{
		printf("                  ����:              ���ݷ� ���� LV%d\n\n",p);
	}
}
int battle(int a)
{
	int b,c;

	srand(time(NULL));
	if(a==1)
	{
		b=rand()%5+1;
		c=rand()%5+1;
	}
	if(a==2)
	{
		b=rand()%10+1;
		c=rand()%10+1;
	}
	return b+c;
}

int item(void)
{
	int a;
	printf("\n       --����������--\n\n");
	printf("     1:ü�¹��� 2:���¹��� �� ��:���\n");
	printf("����:     1          1       n\n");
	scanf("%d",&a);
	return a;
}

int run(void)
{
	int a;
	srand(time(NULL));
	
	a=rand()%3;
	if(a==0)
	{
		printf("\n����ġ�µ� �����Ͽ����ϴ�.\n");
		return 0;
	}
	else
	{
		printf("\n����ġ�µ� �����߽��ϴ�.\n");
		return 1;
	}
}

int monster(void)
{
	int b;

	srand(time(NULL));

	b=rand()%4;
	return b;
}

int main(void)
{
	int a=0,b=0,c=0,p=0,ih=1,im=1;
	int h=100;
	int hp=10,mp=5;
	 
	printf("                        --������ �����մϴ�.--\n\n");
	
	while(h>0)
	{
		b++;

		status(hp,mp,b,h,ih,im,p);
		printf("                 1:������ 2:���� 3:������ 4:����ģ��\n");
		scanf("%d",&c);
		
		if(c==1)
		{
			a=battle(1)+p*4;
			printf("������ %d�� ���ظ� �������ϴ�.\n",a);
			h=h-a;
		}
		else if(c==2)
		{
			a=battle(2)+p*6;
			printf("          1:�Ҹ��� 2:��������: 3:���⸶�� 4:ȸ������ 5:��ȭ���� �׿�:���\n");
			printf("���� �Ҹ�:     1         1          1        2         3 \n");
			scanf("%d",&c);
			if(mp<=0)
			{
				printf("\n������ �����մϴ�.\n");
				b--;
				a=0;
			}
			else if(c==1)
			{
				printf("\n�Ҹ������� ������ %d�� ���ظ� �������ϴ�.\n",a);
				mp=mp-1;
				h=h-a;
			}
			else if(c==2)
			{
				printf("\n������������ ������ %d�� ���ظ� �������ϴ�.\n",a);
				mp=mp-1;
				h=h-a;
			}
			else if(c==3)
			{
				printf("\n���⸶������ ������ %d�� ���ظ� �������ϴ�.\n",a);
				mp=mp-1;
				h=h-a;
			}
			else if(mp<=1)
			{
				printf("\n������ �����մϴ�.\n");
				b--;
				a=0;
			}
			else if(c==4)
			{
				printf("\nȸ���������� %d��ŭ ü���� ȸ���մϴ�.\n",a/3);
				hp=hp+a/3;
				mp=mp-2;
			}
			else if(mp<=2)
			{
				printf("\n������ �����մϴ�.\n");
				b--;
				a=0;
			}
			else if(c==5)
			{
				printf("\n��ȭ�������� ���ݷ��� �����մϴ�.\n");
				mp=mp-3;
				p++;
			}
			else
			{
				b--;
				a=0;
			}
		}
		else if(c==3)
		{
			a=item();
			if(a==1)
			{
				if(ih<=0)
				{
					printf("\nü�� ���� ����\n");
					b--;
					a=0;
				}
				else
				{
					printf("\nü�� ���� ȸ��!\n");
					hp=10;
					ih--;
				}
			}
			else if(a==2)
			{
				if(im<=0)
				{
					printf("\n���� ���� ����\n");
					b--;
					a=0;
				}
				else
				{
					printf("\n���� ���� ȸ��!\n");
					mp=5;
					im--;
				}
			}
			else
			{
				b--;
				a=0;
			}
		}
		else if(c==4)
		{
			a=run();
			if(a==0)
			{
				getch();
				return 0;
			}
			else
			{			
				printf("\n\n");
			}
		}
		else
		{
			printf("\n\n�߸��� ����. �ٽ� �Է�\n\n");
			b--;
			a=0;
		}
		if(a!=0)
		{
			if(h>0)
			{
				printf("\n���� ����\n");
				a=monster();
				hp=hp-a;
				printf("\n���� �����Ͽ� %d��ŭ ���ظ� �Ծ����ϴ�.\n\n",a);	
			}
		}
		if(hp<=0)
		{
			printf("\n����� �й��߽��ϴ�.");
			getch();
			return 0;
		}
	}
	printf("\n�¸��ϼ̽��ϴ�.");

	getch();
	return 0;
}