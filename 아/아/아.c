#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int p=0,m=0,c=0;		//위치, 선택 변수
int in=0,d=0;		//정보 변수
int lv=1,ex=0,hp=10,mp=5,at;		//각종 능력치 변수
int plv=1,php=1;		//펫 변수
int st=500,it=0,sp=0,q=0;		//상태 변수
int h,mat,mex,mst;		//몬스터 변수
int sk[5];		//마법 변수
int mmi,mma;		//맵 이동 제한

void xy(int x,int y)		//커서이동
{
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void clear(int y,int le)		//문구 삭제
{
	int l=0;		//줄 길이 확인 변수

	xy(0, y);		//y+1번째 줄 부터 삭제

	while(1)
	{
		l++;
		printf("\r                                                                                     ");		//글자 공백으로 삭제
		if(l!=le)		//le는 삭제하고 싶은 줄길이 수
		{
			printf("\n");		//한 줄 밑으로
		}
		else
		{
			printf("\r");
			break;		//원하는 줄길이 만큼 지우면 탈출
		}
	}
}

void info()	//알림말
{
	clear(15,1);
	xy(0, 14);
	printf("-----------------------------------------------\n");
	printf("");
	if(in==0)	printf("이동할곳을 선택하세요.");
	else if(in==1)	printf("왼쪽으로 이동");
	else if(in==2)	printf("오른쪽으로 이동");
	else if(in==3)	printf("그 쪽으로 더 이상 갈수없습니다.");
	else if(in==100)	printf("학교에 입장하셧습니다.");
	else if(in==102)	printf("루시:어서와요~~");
	else if(in==103)	printf("카렌:화르륵..화륵!");
	else if(in==105)	printf("카시아:공부는 제대로 하고있습니까?");
	else if(in==106)	printf("쥬레이:...뭐냐?");
	else if(in==108)	printf("아이린:!@#$%?");
	else if(in==109)	printf("미카엘:당신에게 축복을..");
	else if(in==112)	printf("멀린:무슨 일이 있는거냐?");
	else if(in==200)	printf("상점에 입장하셨습니다.");
	else if(in==202)	printf("앨리스:어서오세요.");
	else if(in==204)	printf("엘린:어서오세요.");
	else if(in==206)	printf("치노:환영합니다.");
	else if(in==209)	printf("직원:안녕하세요.");
	else if(in==300)	printf("마을 밖으로 갑니다.");
	else if(in==302)	printf("스테노라:누구니?");
	else if(in==305)	printf("국왕:...");
	else if(in==350)	printf("입장할수 없습니다.");
	else if(in==360)	printf("몬스터와 전투를 시작합니다.");
	else if(in==370)	printf("게임을 계속 진행합니다.");
	else if(in==400)	printf("	옵션");
	else	printf("아무것도 없습니다.");
	printf("\n-----------------------------------------------");
	xy(0,1);
	if(in==400)	printf("	1:내정보 2:펫정보 3:아이템 5:처음으로 6:종료");
}

void level()	//레벨
{
	int ch;		//레벱 업 판별 변수

	if(ex<1)	ch=1;
	else if(ex<3)	ch=2;
	else if(ex<6)	ch=3;
	else if(ex<10)	ch=4;
	else	ch=5;		//만렙
	if(lv!=ch)
	{
		printf("\n	-레벨 업!-\n");
		sp+=(ch-lv);		//레벨 업 수치만큼 스킬포인트 증가
		lv=ch;
		hp=lv*10;
		mp=lv*5;
		printf("\n최대 hp가 %d가 되었습니다. ",hp);
		printf("\n최대 mp가 %d가 되어습니다. ",mp);	
	}
}

int skill()
{        
	if(sp==0)
	{
		printf("\r		sp가 부족 합니다.");
		return 0;
	}
	clear(4,1);		//1줄 삭제
	sp--;
	printf("\n마법을 배웠습니다.");
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
		printf("\r                          \r");		//문구 삭제
		printf("이미 배운 마법입니다.");
	}
}

void place()	//마을 장소
{
	mmi=0;		//맵 좌표의 최소값
	if(c=='1')		//학교일경우
	{
		if(p==0)	printf("학교입구");
		else if(p==2)	printf("담임교실");
		else if(p==3)	printf("불마법교실");
		else if(p==5)	printf("얼음마법교실");
		else if(p==6)	printf("전기마법교실");
		else if(p==8)	printf("정령마법교실");
		else if(p==9)	printf("신성마법교실");
		else if(p==12)	printf("교장실");
		else	printf("복도");
		mma=12;		//학교 좌표의 최댓값
	}
	else if(c=='2')		//상점일경우
	{
		if(p==0)	printf("상점입구");
		else if(p==2)	printf("마법상점");
		else if(p==4)	printf("펫상점");
		else if(p==6)	printf("커피점");
		else if(p==9)	printf("텔레포트터미널");
		else	printf("도로");
		mma=9;		//상점 좌표의 최댓값
	}
	else if(c=='3')		//마을 밖일 경우
	{
		if(p==15)	printf("항구");
		else if(p==10)	printf("마을");
		else if(p==5)	printf("성");
		else if(p==2)	printf("라노아마을");
		else if(p==0)	printf("마을입구");
		else if(p==-2)	printf("병원");
		else if(p==-5)	printf("산");
		else if(p==-11)	printf("오두막");
		else	printf("?");
		mmi=-11;		//마을 밖 좌표의 최소값
		mma=15;		//마을 밖 좌표의 최댓값
	}
}

void item()		//아이템
{
	printf(" %d등급 지팡이",it);
}

void status()		//내정보
{
	printf("\n  내 정보\n");
	printf("\n  수준:%d",lv);
	printf("\n  경험치:%d",ex);
	printf("\n  체력:%d",hp);
	printf("\n  마력:%d",mp);
	printf("\n  보유 스타:%d",st);
	printf("\n  보유 sp:%d",sp);
	printf("\n  장착 아이템:");
	item(it);
	xy(40,3);
	printf("보유 마법");
	if(sk[0] !=0)
	{
		xy(40,5);
		printf("불공격");
	}
	if(sk[1] !=0)
	{
		xy(40,6);
		printf("얼음공격\n");
	}
	if(sk[2] !=0)
	{
		xy(40,7);
		printf("전기공격\n");
	}
	if(sk[3] !=0)
	{
		xy(40,8);
		printf("회복\n");
	}
	if(sk[4] !=0)
	{
		xy(40,9);
		printf("강화\n");
	}
	if(sk[0] + sk[1] + sk[2] + sk[3] + sk[4] ==0)
	{
		xy(40,6);
		printf("마법을 보유하고 있지 않습니다.");
	}
}

void pet()		//펫정보
{
	printf("\n  펫정보\n");
	printf("\n  lv:%d",plv);
	printf("\n  hp:%d",php);
}

int player(int c)		//전투시 플레이어 턴
{
	int d;

	if(c=='1')		//일반공격 데미지
	{
		at=lv;
		d=rand()%at+1;		//at는 플레이어 공격력
	}
	else if(c=='2')		//도망칠 확률
	{
		d=rand()%10;
	}
	return d;
}

void monster()		//몬스터 함수
{
	if(in==302)		//라노아 마을에서 전투가 발생한경우
	{
		q++;		//퀘스트 값 증가
		h=5;		//몬스터 체력 값 설정
		mat=3;		//몬스터 공격력 값 설정
		mex=2;		//몬스터가 주는 경험치값 설정
		mst=2;		//몬스터가 주는 돈 값 설정
	}
	else
	{
		h=2;
		mat=2;
		mex=1;
		mst=1;
	}
}

int quest()		//퀘스트
{
	int ch;
	 
	in=(c-48)*100+p;		//c가 아스키 코드 값이므로 48을 빼줌, 장소(c)와 좌표값(p)를 통해 알림말 결정
	if(p==0)		//시작지점일때
	{
		m='4';		//빠져나감
		in=0;
		return 0;
	}
	info();
	printf("\n		현재위치:");
	place();		//장소 호출
	ch=q;
	q++;
	xy(0,4);
	printf("		-미션%d-\n\n",q);
	xy(0,6);
	printf("	");
	if(in==102)		//담임 교실
	{
		if(q==1||q==3)	
		{
			printf("라노아 마을로 가세요");
		}
		else
		{
			clear(4,1);
			q--;
		}
	}
	else if(in==302)		//라노아마을
	{
		if(q==2)	
		{	
			printf("담임교실로 가세요");
		}
		else if(q==4)	
		{
			printf("몬스터와의 전투에서 승리하세요");
			getch();
			battle();
		}
		else
		{
			clear(4,1);
			q--;
		}
		if(q==5)		//마지막 퀘스트
		{
			printf("퀘스트 완료!");
		}
	}
	else		//그 외의 곳 일경우
	{
		clear(4,1);		//4번째 줄 부터 1줄 삭제
		q--;
	}
	if(ch!=q)
	{
		getch();
	}
}

void map()		//지도
{
	int a;		//반복 변수

	clear(5,1);
	printf("	");		//공백
	a=p;		//현재 좌표 저장
	for(p=a-3;p<a+3;p++)		//앞뒤 3칸까지만 표시
	{
		if(a==p)		//현재 위치 표시
		{
			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),12);
		}
		place();
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),7);
		printf("-");
	}
	place();		//-보다 한개 더 많아야 하므로 한 번더 표시
	p=a;		//현재 좌표 불러오기
}

int battle()		//전투 함수
{
	int c;		//전역 변수와 다른 지역 변수
	int d;		//랜덤 값 변수

	monster();

	in=360;
	while(h>0)		//몬스터 체력이 0이하일 때 까지 반복
	{
		info();
		printf("\n	1:때리기 2:도망치기\n");
		c=getch();
		if(!(c>='1'&&c<='2'))	continue;		//옵션외의 키를 눌렀을때 다시 입력 받도록 함
		d=player(c);
		if(c=='1')		//때리기
		{
			printf("\n적에게 %d의 피해를 입혔습니다.\n",d);
			h=h-d;
			getch();
		}
		else if(c=='2')			//도망치기
		{
			if(in==302)		//퀘스트 중인경우
			{
				d!=0;		//무조건 도망 실패
			}
			if(d==0)		//도망 성공
			{
				printf("\n도망치는데 성공하였습니다.\n");
				h=0;		//몬스터 체력을 0으로 만듬으로써 반복문 빠져나감
			}
			else		//도망 실패
			{
				printf("\n도망치는데 실패하였습니다.\n");
			}
			getch();
		}
		if(h>0)		//몬스터가 아직 죽지 않았을때
		{
			d=rand()%mat+1;
			printf("\n적의 차례\n");
			printf("\n적이 공격하여 %d의 피해를 입었습니다.\n",d);
			getch();
			hp=hp-d;		//몬스터가 준 데미지 만큼 플레이어 체력감소
		}
		if(hp<=0)		//체력이 0이하일 때
		{
			printf("\n패배하셨습니다.\n");
			getch();
			exit(0);		//프로그램 종료
		}
	}
	if(c!='2')		//도망친 경우 들어가지 않음
	{
		printf("\n승리하셨습니다.\n");
		ex+=mex;		//경험치 증가
		st+=mst;		//돈 증가
		level();		//경험치 증가로 인한 레벨 업 판별
		in=370;
		m=0;		//m이 '4'(탈출)가 되지 않도록 0으로 초기화
	}
	else		//도망에 성공할 경우 빠져나옴
	{
		in=370;
	}
	getch();
}

void minimap()	//내부 맵
{
	m=0;		//m이 4가 안되도록 초기화
	while(m!='4')		//m이 4가 아닐때까지 반복
	{
		info();
		clear(2,1);
		printf("		현재위치:");
		place();		//장소 호출
		printf("\n\n");		//두 줄 띄움
		map();		//지도 호출
		printf("\n\n	1:왼쪽 이동 2:오른쪽 이동 3:들어가기 4:나가기\n");
		m=getch();		//옵션 입력 받음
		if(m=='1')		//왼쪽 이동
		{
			in=1;
			p--;		//좌표 값 감소
		}
		else if(m=='2')		//오른쪽 이동
		{
			in=2;
			p++;		//좌표 값 증가
		}
		else if(m=='3')		//들어가기
		{
			quest();		//퀘스트 함수 호출
			if(in==103||in==105||in==106||in==108||in==109)
			{
				skill();
				getch();
			}
		}
		else if(m=='4')		//나가기(빠져나감)
		{
			in=0;
		}
		if(p<mmi||p>mma)		//맵을 벗어날경우
		{
			if(p<=mmi)		//왼쪽으로 벗어날경우
			{
				p++;		//좌표 값 증가
			}
			else		//오른쪽으로 벗어날경우
			{
				p--;		//좌표 값 감소
			}
			in=3;
		}
		else if(c=='3')		//마을 밖일경우
		{
			if(m=='1'||m=='2')		//움직였을경우
			{
				m=rand()%10;		//몬스터와 마주칠 확률
				if(m==0)		//몬스터와 마주침
				{
					battle();		//전투 함수 호출
				}
			}
		}
	}
}

void option()		//옵션
{
	while(in==400)
	{
		info(in);
		if(c=='1')		//내 정보
		{
			status();
		}
		else if(c=='2')		//펫 정보
		{
			pet();
		}
		else if(c=='3')		//아이템 정보
		{
			printf("\n\n보유아이템\n\n");
			item();
		}
		else if(c=='5')
		{
			in=0;		//처음으로 돌아감
			break;
		}
		else if(c=='6')
		{
			exit(0);		//종료
		}
		c=getch();		//알림 함수로 인하여 바로 꺼지지 않도록 함수 하단에 위치 
	}
}

int main(void)
{
	srand(time(NULL));

	while(c!='6')
	{
		p=0;
		printf("\n		1:학교 2:상점 3:마을 밖 4:옵션");
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