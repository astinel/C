#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

int status(int hp,int mp,int b,int h,int ih,int im,int p)
{
	printf("                            -현재 상황-           \n");
	printf("                                                  \n");
	printf("                  체력:%d             적의 체력:%d\n",hp,h);     
	printf("                  마력:%d             현재 턴:%d  \n",mp,b);
	printf("                  체력 물약:%d        마력 물약:%d\n\n",ih,im);
	if(p!=0)
	{
		printf("                  버프:              공격력 증가 LV%d\n\n",p);
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
	printf("\n       --보유아이템--\n\n");
	printf("     1:체력물약 2:마력물약 그 외:취소\n");
	printf("개수:     1          1       n\n");
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
		printf("\n도망치는데 성공하였습니다.\n");
		return 0;
	}
	else
	{
		printf("\n도망치는데 실패했습니다.\n");
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
	 
	printf("                        --전투를 시작합니다.--\n\n");
	
	while(h>0)
	{
		b++;

		status(hp,mp,b,h,ih,im,p);
		printf("                 1:때리기 2:마법 3:아이템 4:도망친다\n");
		scanf("%d",&c);
		
		if(c==1)
		{
			a=battle(1)+p*4;
			printf("적에게 %d의 피해를 입혔습니다.\n",a);
			h=h-a;
		}
		else if(c==2)
		{
			a=battle(2)+p*6;
			printf("          1:불마법 2:얼음마법: 3:전기마법 4:회복마법 5:강화마법 그외:취소\n");
			printf("마력 소모:     1         1          1        2         3 \n");
			scanf("%d",&c);
			if(mp<=0)
			{
				printf("\n마력이 부족합니다.\n");
				b--;
				a=0;
			}
			else if(c==1)
			{
				printf("\n불마법으로 적에게 %d의 피해를 입혔습니다.\n",a);
				mp=mp-1;
				h=h-a;
			}
			else if(c==2)
			{
				printf("\n얼음마법으로 적에게 %d의 피해를 입혔습니다.\n",a);
				mp=mp-1;
				h=h-a;
			}
			else if(c==3)
			{
				printf("\n전기마법으로 적에게 %d의 피해를 입혔습니다.\n",a);
				mp=mp-1;
				h=h-a;
			}
			else if(mp<=1)
			{
				printf("\n마력이 부족합니다.\n");
				b--;
				a=0;
			}
			else if(c==4)
			{
				printf("\n회복마법으로 %d만큼 체력을 회복합니다.\n",a/3);
				hp=hp+a/3;
				mp=mp-2;
			}
			else if(mp<=2)
			{
				printf("\n마력이 부족합니다.\n");
				b--;
				a=0;
			}
			else if(c==5)
			{
				printf("\n강화마법으로 공격력이 증가합니다.\n");
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
					printf("\n체력 물약 부족\n");
					b--;
					a=0;
				}
				else
				{
					printf("\n체력 전부 회복!\n");
					hp=10;
					ih--;
				}
			}
			else if(a==2)
			{
				if(im<=0)
				{
					printf("\n마력 물약 부족\n");
					b--;
					a=0;
				}
				else
				{
					printf("\n마력 전부 회복!\n");
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
			printf("\n\n잘못된 선택. 다시 입력\n\n");
			b--;
			a=0;
		}
		if(a!=0)
		{
			if(h>0)
			{
				printf("\n적의 차례\n");
				a=monster();
				hp=hp-a;
				printf("\n적이 공격하여 %d만큼 피해를 입었습니다.\n\n",a);	
			}
		}
		if(hp<=0)
		{
			printf("\n당신이 패배했습니다.");
			getch();
			return 0;
		}
	}
	printf("\n승리하셨습니다.");

	getch();
	return 0;
}