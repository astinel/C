#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#define N 6		//숫자 개수
#define ML 5		//복권 최대 개수
#define MAX 45		//최댓값
#define MIN 1		//최솟값
#define Red 12		//빨간색상
#define White 15	//하얀색상
#define lineY 20	//줄 위치
#define C 9

char ans[N + 1];		//정답 번호(기본 숫자 + 보너스 숫자 한개)
char n;			//입력 번호
char lot;		//현재 복권 개수
char inp;		//입력된 숫자 개수

//입력된 번호 구조체
struct number
{
	char num[N];		//입력된 번호
	unsigned char sum;		//입력된 번호의 합
	int mul;		//입력된 번호의 곱
};
number num[ML];

//커서 이동
void xy(short x, short y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//커서 숨기기
void cursor() {
	CONSOLE_CURSOR_INFO cur = { 0, };
	cur.dwSize = 1;
	cur.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}

//줄 삭제
void clear(char y) {
	xy(0, y);
	for (char a = 0; a < 80; a++)		printf(" ");
}

//색깔 함수
void color(char col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}

//정렬
void sort(char* arr) {
	char sma;
	char sub;		//대입 변수

	for (char a = 0; a < N - 1; a++) {
		sma = a;
		for (char b = a + 1; b < N; b++)
			if (arr[sma] > arr[b])		sma = b;
		if (a != sma) {
			sub = arr[a];
			arr[a] = arr[sma];
			arr[sma] = sub;
		}
	}
}

//난수 생성 함수
void random(char* arr,char n) {
	char num[MAX];
	char i;
	
	for (char a = 0; a < MAX; a++)		num[a] = a + MIN;		//최솟값부터 최댓값까지 배열에 초기화
	for (char a = 0; a < n;) {		//정해진 개수 만큼 난수 생성
		i = rand() % (MAX - a);		//뽑히진 않은 숫자에서 난수 생성
		arr[a++] = num[i];
		num[i] = num[MAX - a];		//생성된 난수 인덱스 범위에서 제외
	}
	sort(arr);
}

//배열 비교 함수
char equal(char* p) {
	char ar1[N];
	char ar2[N];
	char n = N;		//배열에 남아있는 번호 갯수
	char c = 0;		//똑같은 번호 갯수

	//비교할 배열 초기화
	for (char a = 0; a < N; a++) {
		ar1[a] = ans[a];
		ar2[a] = *(p + a);
	}

	//여기 수정 필요
	for (char a = 0; a < n; a++) {
		for (char b = 0; b < n; b++) {
			if (ar1[a] == ar2[b]) {		//배열에 있는 두 번호가 같을 경우
				c++;	n--;
				//배열에 해당 번호 삭제
				ar1[a] = ar1[n];
				ar2[b] = ar2[n];
				a--;		//오류 방지
				break;
			}
		}
	}

	return c;
}

//순위 결정 함수
void rank() {
	char cou;		//카운트 변수
	char ran[ML] = {0};		//순위

	for (char a = 0; a < lot; a++) {
		cou = equal(num[a].num);		//입력된 번호에서 정답과 같은 번호 갯수 구함

		if (cou == 6)		ran[a] = 1;		//다 맞추면 1등
		else if (cou >= 3) {		//3개이상 맞출 경우
			ran[a] = 8 - cou;		//맞춘 개수에 따라 순위 결정
			if (ran[a] == 3)		//3등일경우 재 판정
				for (char b = 0; b < N; b++)		//보너스 숫자 비교
					if (ans[N] == num[a].num[b])		ran[a] = 2;		//보너스 숫자와 일치하면 2등
		}
		//최종 순위 출력
		xy(31, 5 + 2 * a);
		if (ran[a])			printf("%d 등", ran[a]);		
		else			printf("X");
	}
}

//경계선 출력
void line() {
	const char L = 80;		//콘솔의 가로 길이

	xy(0, lineY);		//줄을 출력할 위치
	for (char a = 0; a < L; a++)		printf("-");		//줄 출력

	xy(1, lineY + 3);
	printf("방향키: 번호 선택  SPACE BAR: 선택 번호 입력  ENTER: 복권 제출");
	xy(1, lineY + 4);
	printf("1: 제출 완료  ");
	printf("2: 번호 초기화  ");
	printf("3: 숫자 랜덤 생성  ");
	printf("4: 종료  ");
}

//알림 말 출력
void notice(char n) {
	char x, y;		//출력 할 위치

	x = 1;	y = lineY + 1;
	clear(y);		//해당 줄 삭제
	xy(x, y);
	
	if (n == 0)				printf("다시 시작하시려면 아무키나 눌러주세요");
	else if (n == 1) {
		if (inp < N)		printf("%d개의 숫자를 입력해 주세요", N - inp);
		else				printf("입력된 숫자를 확인해 주세요");
	}
	else if (n == 2)		printf("더 이상 입력받을 수 없습니다.");
	else if (n == 3)		printf("중복된 숫자가 입력됬습니다.");
	else if (n == 4)		printf("중복된 숫자 조합이 이미 있습니다.");
	else if (n == 5)		printf("입력을 완료해 주세요");
}

//번호판 출력 함수
void print(char n) {
	char x = 40, y = 1;		//시작 출력 위치

	xy(x, y);
	for (char a = 0; a < N; a++) {
		printf("%4d", num[lot].num[a]);		//현재 입력 번호
	}
	xy(x, y+=3);		//번호 출력
	for (char a = MIN; a <= MAX; a++) {
		if (n == a)		color(Red);		//현재 선택 번호는 빨간색
		else			color(White);		//나머지는 흰색
		printf("%2d ", a);		//번호 출력
		if (a % C == 0)		xy(x, ++y);		//일정 숫자 마다 한 줄 띄움
	}
	color(White);
}


//입력된 복권 출력
void lotto() {
	char x = 5, y = 3;		//초기 출력 위치

	xy(x, y);	printf("입력된 번호");
	y += 2;
	xy(x - 2, y + 2 * lot);
	printf("%d: ", lot + 1);
	sort(num[lot].num);		//크기 순으로 정렬
	for (char a = 0; a < N; a++)		printf("%3d", num[lot].num[a]);		//입력된 번호 출력
}

//입력된 번호 초기화
void resetNum(char lot) {
	for (char c = 0; c < N; c++){
		num[lot].num[c] = 0;		//입력된 번호 초기화
		num[lot].sum = 0;
		num[lot].mul = 1;
	}
	inp = 0;
}

//중복 확인
char check() {
	num[lot].mul = 1;		//입력된 번호의 곱
	num[lot].sum = 0;		//입력된 번호의 합
	
	for (char a = 0; a < N; a++) {
		num[lot].mul *= num[lot].num[a];
		num[lot].sum += num[lot].num[a];
	}
	if (lot) {		//입력된 번호 조합이 있을 경우
		for (char a = 0; a < lot; a++) {		//복권 개수 만큼 반복
			if (num[lot].mul == num[a].mul)		//입력된 번호의 곱 비교
				if (num[lot].sum == num[a].sum) {		//입력된 번호의 합 비교
					resetNum(lot);		//입력된 번호 초기화
					notice(4);		//중복 조합 판정
					return 1;
				}
		}
	}
	return 0;
}

//입력 번호 중복 확인
char numCheck() {
	for (char a = 0; a < inp; a++)
		if (num[lot].num[a] == n)		return 1;

	return 0;
}

//정답 공개
void answer() {
	xy(0, 15);

	printf("정답: ");
	for (char a = 0; a < N; a++)		printf("%3d", ans[a]);		//정답 번호 생성
	printf(" + %d", ans[N]);
}

//초기화
void reset() {
	system("cls");		//화면 지움
	system("mode con cols=80 lines=25");		//콘솔창 크기 조정
	cursor();		//커서 숨기기
	color(White);
	line();		//경계선 출력
	random(ans, N + 1);		//중복 없는 난수 생성
	for (char a = 0; a < N; a++)		resetNum(a);		//입력된 번호들 초기화
	n = 1;
	lot = inp = 0;
}

//키 입력 함수
char key() {
	char k;		//입력 받을 키 변수
	char no = 1;

	k = _getch();		//입력 받을 키
	if (k == -32) {		//입력 받은 키가 방향키일 경우
		k = _getch();		//추가 입력 받음
		if (k == 72)			n -= C;		//상
		else if (k == 75)		n--;		//좌
		else if (k == 77)		n++;		//우
		else if (k == 80)		n += C;		//하

		if (n <= 0)			n += MAX;		//번호가 0이하일 경우 최댓값을 더함
		else if (n > MAX)	n -= MAX;		//번호가 최댓값 보다 클 경우 최댓값을 뺌
	}
	else if (k == ' ') {		//스페이스바를 입력 받은 경우
		if (numCheck())		no = 3;
		else if (inp == N)		no = 2;		//더 이상 입력 받을수 없을 경우
		else 			num[lot].num[inp++] = n;		//번호 입력 받음
	}
	else if (k == '\r') {		//엔터를 입력 받은 경우
		no = 5;
		if (inp == N) {		//입력이 다 된 경우
			if (!check())		//중복 확인
			{
				lotto();		//입력된 번호 출력
				lot++;		//복권 개수 증가
				no = 1;
			}
			else	no = 4;
			if (lot == ML)		return 0;		//복권이 최대 갯수와 똑같을때 게임 종료
			inp = 0;		//입력된 번호 개수 초기화
		}
	}
	else if (k == '1') {		//1을 입력 받은 경우 
		return 0;		//게임 종료
	}
	else if (k == '2') {		//2를 입력 받은 경우
		resetNum(lot);		//초기화
	}
	else if (k == '3') {		//3을 입력 받은 경우
		random(num[lot].num,N);
		inp = N;
	}
	else if (k == '4') {
		exit(0);
	}
	else if (k == '0') {		//0을 입력 받은 경우
		answer();		//정답 공개
	}

	notice(no);

	return 1;
}

//복권 추첨
void start() {
	while(1){
		reset();		//초기화
		notice(1);
		do {
			print(n);		//번호 출력
		} while (key());		//키 입력 받음

		notice(0);
		rank();		//순위 출력
		answer();

		_getch();
	}
}

//타이틀 출력
void title() {
	char x = 12;
	char y = 5;

	system("mode con cols=80 lines=25");

	xy(x, y++);		printf("■      ■              ■      ■           ■      ■");
	xy(x, y++);		printf("■■■■■  ■■■■■  ■  ■■■■■   ■■■■■  ■");
	xy(x, y++);		printf("■      ■          ■  ■      ■           ■      ■");
	xy(x, y++);		printf("■■■■■              ■    ■  ■       ■  ■  ■■");
	xy(x, y++);		printf("    ■      ■■■■■  ■  ■      ■   ■      ■  ■");
	xy(x, y++);		printf("■■■■■      ■      ■                           ■");
	xy(x, y++);		printf("            ■  ■  ■■■  ■■■■■     ■■■■■");
	xy(x, y++);		printf("■■■■■  ■          ■      ■         ■      ■");
	xy(x, y++);		printf("        ■  ■■■■■  ■      ■         ■■■■■");
	xy(2*x, y+=2);	printf("    21628001 강경운");
	xy(2*x, y+=2);	printf("PRESS ANY KEY TO START");

	_getch();
}

int main() {
	srand(time(NULL));
	//title();
	start();		//게임 시작

	return 0;
}