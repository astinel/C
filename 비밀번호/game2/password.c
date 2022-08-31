#include <stdio.h>
#include <conio.h>

int pas(int p,int c)
{
	int a;
	if(p!=c)
	{
	printf("\n입력하신 두 개의 비밀번호가 일치하지 않습니다\n");
	printf("1:취소 그 이외:계속\n");
	scanf("%d",&a);
	return a;
	}
}

void check(void)
{
	printf("\n\n5회 오류.\n종료됩니다.");
}

int main(void)
{
	int a=0,p=0,b=0;
	int n,c;

	while(b!=2)
	{
		printf("비밀번호를 입력해주세요.\n초기비밀번호는 0이며 5회 오류시 종료됩니다.\n\n비밀번호:");
		scanf("%d",&n);
		a=0;
		while(n!=p)
		{
			a++;
			printf("\n비밀번호 오류. 다시 입력해주세요.\n틀린횟수: %d\n",a);
			if(a==5)
			{
				check();
				getch();
				return 0;
			}
			printf("\n비밀번호;");
			scanf("%d",&n);
		}
		printf("\n일치 확인\n");
		a=1;
		while(a==1)
		{
			printf("\n1:비밀번호 바꾸기 2:종료 그 이외: 처음\n");
			scanf("%d",&b);
			printf("\n");
			if(b==1)
			{
				a=0;
				printf("현재 비밀번호를 입력해주세요\n");
				scanf("%d",&n);
				while(n!=p)
				{
					a++;
					printf("\n비밀번호 오류. 다시 입력해주세요.\n틀린횟수: %d\n",a);
					if(a==5)
					{
						check();
						getch();
						return 0;
					}
					printf("\n비밀번호:");
					scanf("%d",&n);
				}
				c=-1;
				while(p!=c)
				{
					printf("\n바꿀 비밀번호를 입력하세요.\n");
					scanf("%d",&p);
					printf("\n다시 한번 입력해주세요\n");
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
					printf("\n변경되었습니다.\n처음으로 돌아갑니다.\n\n\n");
				}
			}
			else
			{
				a=0;
			}
		}
	}
	printf("\n종료합니다.");
	getch();
	return 0;
}