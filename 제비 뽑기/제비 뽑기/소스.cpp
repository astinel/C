#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int main()
{
	int nu, pe;		//제비 변수
	int a;		//반복 변수
	int je[100] = { 0 };		//제비 상태
	int b=0;		//랜덤 변수
	int c = 0, d = 0;		//제비 개수

	srand(time(NULL));
	printf("전체 제비수를 입력해주세요(최소:3 최대:100)\n");
	do		//전체 제비수 입력 받음
	{
		scanf("%d", &nu);
	} while (nu < 3 || nu>100);		//참여할 사람수의 범위
	printf("당첨 제비수를 입력하세요(0이 될수없고 제비수와 같거나 클수 없습니다.)");
	do		//당첨 제비수 입력 받음
	{
		scanf("%d", &pe);
	} while (pe >= nu || pe == 0);		//당첨 제비수의 범위
	system("cls");
	for (a = 0; c != pe; a++)		//당첨 제비 선정
	{
		if (a == nu)		//전체 제비수까지 다 돌았을때
		{
			a = 0;
			d++;
		}
		b = rand() % nu;		//당첨 제비가 될 확률
		if (b == 0 && je[a] != 2)		//선택된 제비가 당첨제비가 아닐경우
		{
			je[a] = 2;		//당첨 제비
			c++;		//당첨 제비 개수 증가
		}
	}
	for (a = 0; a < nu; a++)		//남은 제비 초기화                                                                                                                                             
	{
		if (je[a] == 0)
		{
			je[a] = 1;
		}
	}
	system("cls");
	d = nu;
	while (1)
	{
		printf("\n");
		for (a = 0; a < nu; a++)
		{
			if (je[a] != 0)		printf("%3d ", a + 1);		//남은 제비 번호 출력
			else				printf("    ");			//선택된 제비 번호 미출력
			if (a % 10 == 9)
			{
				printf("\n");		//제비 10개 마다 1줄 띄움
			}
		}
		printf("\n\n남은 전체 제비 개수:%d", d);
		printf("\n남은 당첨 제비 개수:%d", c);
		printf("\n\n제비 선택:");
		scanf("%d", &b);		//제비 번호 입력 받음
		system("cls");
		if (b <= 0 || b > 100)
		{
			printf("선택한 제비는 존재하지 않음");
			continue;		//배열 범위를 벗어날경우 다시 입력 받음
		}
		b--;		//배열값에 대입 시키기 위해 1감소
		if (je[b])		//제비가 존재할경우만 들어감
		{
			if (je[b] == 2)
			{
				c--;		//당첨 제비 수 감소
				printf("당첨!");
			}
			je[b] = 0;
			d--;		//전체 제비 수 감소
		}
		else
		{
			printf("선택한 제비는 존재하지 않음");
		}
		if (c == 0)		//남은 제비 수가 0이 될 경우
		{
			break;
		}
	}
	printf("\n");
	for (a = 0; a < nu; a++)
	{
		if (je[a] != 0)		printf("%3d ", a + 1);		//남은 제비 번호 출력
		else				printf("    ");			//선택된 제비 번호 미출력
		if (a % 10 == 9)
		{
			printf("\n");		//제비 10개 마다 1줄 띄움
		}
	}
	printf("\n\n제비 뽑기가 종료 되었습니다.");

	getch();
	return 0;
}