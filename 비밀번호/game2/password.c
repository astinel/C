#include <stdio.h>
#include <conio.h>

int pas(int p,int c)
{
	int a;
	if(p!=c)
	{
	printf("\n�Է��Ͻ� �� ���� ��й�ȣ�� ��ġ���� �ʽ��ϴ�\n");
	printf("1:��� �� �̿�:���\n");
	scanf("%d",&a);
	return a;
	}
}

void check(void)
{
	printf("\n\n5ȸ ����.\n����˴ϴ�.");
}

int main(void)
{
	int a=0,p=0,b=0;
	int n,c;

	while(b!=2)
	{
		printf("��й�ȣ�� �Է����ּ���.\n�ʱ��й�ȣ�� 0�̸� 5ȸ ������ ����˴ϴ�.\n\n��й�ȣ:");
		scanf("%d",&n);
		a=0;
		while(n!=p)
		{
			a++;
			printf("\n��й�ȣ ����. �ٽ� �Է����ּ���.\nƲ��Ƚ��: %d\n",a);
			if(a==5)
			{
				check();
				getch();
				return 0;
			}
			printf("\n��й�ȣ;");
			scanf("%d",&n);
		}
		printf("\n��ġ Ȯ��\n");
		a=1;
		while(a==1)
		{
			printf("\n1:��й�ȣ �ٲٱ� 2:���� �� �̿�: ó��\n");
			scanf("%d",&b);
			printf("\n");
			if(b==1)
			{
				a=0;
				printf("���� ��й�ȣ�� �Է����ּ���\n");
				scanf("%d",&n);
				while(n!=p)
				{
					a++;
					printf("\n��й�ȣ ����. �ٽ� �Է����ּ���.\nƲ��Ƚ��: %d\n",a);
					if(a==5)
					{
						check();
						getch();
						return 0;
					}
					printf("\n��й�ȣ:");
					scanf("%d",&n);
				}
				c=-1;
				while(p!=c)
				{
					printf("\n�ٲ� ��й�ȣ�� �Է��ϼ���.\n");
					scanf("%d",&p);
					printf("\n�ٽ� �ѹ� �Է����ּ���\n");
					scanf("%d",&c);		
					a=pas(p,c);
					
					if(a==1)
					{
						p=n;
						c=n;	
					}
				}
				if(c!=0)
				{
					printf("\n����Ǿ����ϴ�.\nó������ ���ư��ϴ�.\n\n\n");
				}
			}
			else
			{
				a=0;
			}
		}
	}
	printf("\n�����մϴ�.");
	getch();
	return 0;
}