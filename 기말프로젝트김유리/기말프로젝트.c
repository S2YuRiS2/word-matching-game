/*헤더파일*/
#include <stdio.h>								//표준 입출력 작업을 위한 헤더파일
#include <stdlib.h>								//여러 유틸리티(텍스트를 수로 변환 등)함수 작업을 위한 헤더 파일
#include <time.h>								//시간 작업을 위한 헤더파일
#include <Windows.h>							//윈도우 응용 프로그램을 만들기 위한 헤더파일
#include <conio.h>								//getche()함수를 이용하기 위한 헤더파일
#include <string.h>							    //strcmp 함수가 선언된 헤더파일

#define wordcount 95							//단어의 개수 정의
#define wordtime 20000							//단어가 나타나는 속도 정의

/*키보드값을 매크로로 정의*/
#define UP 0									//0을 UP으로 정의
#define DOWN 1									//1을 DOWN으로 정의
#define SUBMIT 2								//2를 SUBMIT로 정의

time_t starttime = 0, endtime = 0;				//시스템 시간을 저장

/*함수선언*/
int keycontrol();								//키보드 키 출력을 위한 함수선언
void title1();									//프로그램 실행 직후 초기화작업을 진행할 함수선언
int title2();									//처음 게임창의 메뉴 선택화면을 위한 함수선언
void gotoxy(int x, int y);						//커서 위치 이동 함수선언
void design();									//게임 첫화면의 디자인 함수선언					
void design2();									//게임을 플레이 할 때의 함수선언
void gamemain();								//게임 플레이 화면의 함수선언
void printword();								//단어출력을 위한 함수선언
void scanword();								//단어입력을 위한 함수선언
void removecursor();							//커서제거를 위한 함수선언
void help();									//게임 도움말창을 위한 함수선언

/*변수*/
int wordx[250];									//한 번뜬 단어들을 안뜨게 하는 변수
int x, y;										//gotoxy함수의 x값과 y값의 변수
int i, j;										//단어의 수의 변수
int x2, y2;										//x, y값을 다시 불러올 때 쓰는 변수
int score = 0;									//점수를 나타낼 변수 초기화
int f;											//단어의 색깔 변수
int f2;											//단어 색깔 값을 다시 불러올때 변수
int sword;										//입력된 단어를 나타낸 변수
char scan[50];									//입력할 단어를 위한 변수
char remem[263][3];
int gap;										//게임지속시간을 위한 변수

void gotoxy(int x, int y)	//커서 위치 이동 함수정의
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);   //콘솔 핸들가져오기
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

char word[256][256] = { "dog", "cat", "bottle", "phone", "robot", "green", "elephant", "include", "sky",		//단어를 2차원 배열에 값 저장
						"game", "love", "yuri", "max","knife", "glass", "class", "art", "smart",
						 "bell", "carry", "climb", "between", "blow", "album", "ago", "among", "animal",
						 "any", "box","and", "board", "body", "child","city", "boy", "bridge",
						 "clean","club", "coat", "bright", "coin","coffee", "cold", "chance",
						"chalk", "chair", "cheap", "blue","before", "bowl", "aunt", "as", "away", "bicycle",
						"church", "card", "hold","chose", "come", "drink", "give", "get", "hurt", "lay","had",
						"feed", "lend", "met", "sing", "throw", "wet", "tell","set", "wind", "wear", "write",
						"spend", "stand", "worn", "win", "sweep", "account", "achieve", "across", "accept",
						"above", "ability", "abuse","abnormal", "absurd", "absent",
						"nation", "past", "value", "though", "person", "machine", "stand", "null" };


int main()
{
	title1();			//title1함수 호출				

	while (1)			//while문 반복
	{
		design();		//design함수 호출

		int menucode = title2();	//menucode변수를 title2함수를 호출해서 저장

		if (menucode == 0)			//menucode가 0일 때
		{
			score = 0;				//점수
			starttime = clock();	//시작시간을 clock함수를 호출해서 저장
			gamemain();				//gamemain함수 호출
			gap = 0;				//게임지속시간
		}
		else if (menucode == 1)		//menucode가 1일 때
		{
			help();					//help함수 호출
		}
		else if (menucode == 2)		//menucode가 2일 때
		{
			exit(1);				//종료
		}
	}

	return 0;

}

int keycontrol()							//키보드 키 출력을 위한 함수정의
{
	char temp = getch();					//enter키를 치지않아도 화면에 바로 글자가 뜸

	if (temp == 'w' || temp == 'W')			//w or W키를 입력할 때
	{
		return UP;							//위쪽 방향키 역할을 함 
	}
	else if (temp == 's' || temp == 'S')	//s or S키를 입력할 때
	{
		return DOWN;						//아래쪽 방향키 역할을 함
	}
	else if (temp == ' ')					//스페이스바(공백)을 입력할 때
	{
		return SUBMIT;						//선택키 역할을 함		
	}
}
void design()     //게임 첫화면의 디자인 함수정의
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);		//콘솔 글자 색 지정 연한 파란색을 나타냄

	printf("□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■");		//게임 시작화면 디자인 출력
	printf("■                                                                            □");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);		//콘솔 글자 색 지정 연한 노란색을 나타냄
	printf("□                    ######       ##        ##    ##      ######             ■");
	printf("■                  ###   ##     #####      ####  ###     ##                  □");
	printf("□                 ##          ##   ##     ##  ##  ##    ##                   ■");
	printf("■                ###  ####   ########    ##   #   ##   ########              □");
	printf("□                 ##    ##  ##     ##   ##        ##   ##                    ■");
	printf("■                  ######  ##      ##  ##         ##  #########              □");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	//콘솔 글자 색 지정 연한 파란색을 나타냄
	printf("□                                                                            ■");
	printf("■                        ||나타나는 단어를 빨리 없애기||                     □");
	printf("□                                                                            ■");
	printf("■                                                                            □");
	printf("□                                                                            ■");
	printf("■                                                                            □");
	printf("□                                                                            ■");
	printf("■                                                                            □");
	printf("□                                                                            ■");
	printf("■                                                                            □");
	printf("□                                                                            ■");
	printf("■                                                                            □");
	printf("□                                                                            ■");
	printf("■                                                                            □");
	printf("□                                                                            ■");
	printf("■                                                                            □");
	printf("□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■");
}

void design2()		//게임 플레이 화면의 디자인 함수정의
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//콘솔 글자 색 지정 연한 노란색을 나타냄

	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");		//게임 플레이화면의 디자인 출력
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■____________________________________________________________________________■");
	printf("■_단어를 입력하세요__________________________________________________________■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■                                                                            ■");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
}

void gamemain()					//게임 플레이 화면의 함수정의
{
	system("cls");				//화면을 지움

	gotoxy(35, 10);				//x좌표를 35 y좌표를 10으로 설정	
	printf("3초 후 시작");
	Sleep(1000);				//아무것도 안하고 1초 기다림
	system("cls");				//화면을 지움
	gotoxy(35, 10);				//x좌표를 35 y좌표를 10으로 설정
	printf("2초 후 시작");
	Sleep(1000);				//아무것도 안하고 1초 기다림
	system("cls");				//화면을 지움
	gotoxy(35, 10);				//x좌표를 35 y좌표를 10으로 설정
	printf("1초 후 시작");
	Sleep(1000);				//아무것도 안하고 1초 기다림
	system("cls");				//화면을 지움

	design2();					//design2함수 호출

	while (1)					//while문 반복
	{
		printword();			//printword함수 호출
		scanword();				//scanword함수 호출
	}
}

void printword()				//단어출력을 위한 함수 정의
{
	static int check = wordcount;		//정적 변수 선언 및 wordcount에 초기화(변수가 사라지지 않게 함)
	x = rand() % 63;					//x좌표를 63-1까지 랜덤한 값으로 설정
	y = rand() % 15 + 2;					//y좌표를 2에서 15-1까지 랜덤한 값으로 설정
	i = rand() % wordcount;				//i를 wordcount 95개로 정의한 값 중에 랜덤한으로 설정
	f = rand() % 4 + 1;					//색 지정 색을 랜덤하게

	if (wordx[i] != 1)			//한 번 뜬 단언을 안뜨게 하기 위한 if문
	{
		wordx[i] = 1;		//배열 i번째 요소를 1로 저장
		check--;			//cheak값을 감소 시킴

		gotoxy(x, y);		//gotoxy로 x와 y좌표 설정

		for (j = 0; j < 3; j++)		//단어 출력을 위한 for문
		{
			if (j == 0)				//j값이 0일 때
			{
				remem[i][j] = x;	//배열을 x값에
			}
			else if (j == 1)		//j값이 1일 때
			{
				remem[i][j] = y;	//배열을 y값에
			}
			else if (j == 2)		//j값이 2일 때
			{
				remem[i][j] = f;	//색 지정
			}
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), f + 9);		//콘솔 글자 색 지정 단어색을 10번 색부터
		printf("%s ", word[i]);		//단어를 출력
	}
}

void scanword()			//단어 입력을 위한 함수 정의
{
	int p = 0;

	while (p < wordtime)
	{
		p++;

		int scanc;
		endtime = clock();			//종료시간을 clock함수를 호출해서 저장
		gap = (float)(endtime - starttime) / (CLOCKS_PER_SEC);			//게임 지속시간을 위한 변수 gap

		if (gap > 50) //게임지속시간 50s
		{
			system("cls");		//화면을 지움

			design2();			//design2 함수 호출

			gotoxy(32, 11);		//x좌표를 32 y좌표를 11으로 설정
			printf("||게 임 종 료||");
			gotoxy(33, 12);		//x좌표를 32 y좌표를 12으로 설정
			printf("점수: %d", score);
			Sleep(5000);		//아무것도 안하고 5초 기다림

			system("cls");		//화면을 지움

			main();				//main함수 호출
		}

		if (kbhit())		//kbhit()함수를 사용하여 키 눌림의 유무를 판단
		{
			scanc = getch();		//입력한 글자를 엔터키를 사용하지 않고 바로 화면에 출력하기 위해 사용하는 getch함수

			if (scanc != 8 && scanc != 13)	//scamc가 8과 13이 아닐 때
			{
				gotoxy(5, 20);
				scan[sword++] = scanc;
				printf("          ");		//단어를 입력하면 출력됨
				gotoxy(5, 20);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);		//콘솔 글자 색 지정 하얀색을 나타냄
				printf("%s", scan);			//입력한 글자 출력
			}
			else if (scanc == 8)			//scanc가 8일 때
			{
				gotoxy(5, 20);				//x좌표를 5 y좌표를 20으로 설정
				printf("|        ");		//단어를 잘못입력시 지우면 나타나는 커서
				gotoxy(5, 20);				//x좌표를 5 y좌표를 20으로 설정
				scan[--sword] = scanc;		//글자 지우기

				if (sword == -1)			//sword가 -1일 때
					sword = 0;
				printf("%s", scan);			//입력할 단어 출력
			}
			else if (scanc == 13)			//scanc가 13일 때
			{
				sword = 0;
				gotoxy(5, 20);				//x좌표를 5 y좌표를 20으로 설정
				printf("|        ");		//다음 단어 입력 전 입력창이 초기화되어 출력

				for (i = 0; i <= wordcount; i++)
				{
					if (!strcmp(scan, word[i]))		//strcmp 결과 scan과 word[i]값을 거짓을 참으로 바꿈
					{
						x2 = remem[i][0];
						y2 = remem[i][1];
						f2 = remem[i][2];

						gotoxy(x2, y2);
						printf("       ");			//출력된 단어를 입력하면 단어가 사라짐

						gotoxy(4, 20);
						printf("|        ");

						switch (f2)
						{
						case 1:					//10번째 색 연두색일 경우
							score += 150;
							break;

						case 2:					//11번째 색 하늘색일 경우
							score += 200;
							break;

						case 3:					//12번째 색 연한빨간색일 경우
							score += 250;
							break;

						case 4:					//13번째 색 분홍색일 경우
							score += 300;
							break;

						default:
							break;
						}
						gotoxy(62, 22);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
						printf("현재점수 :%d", score);
					}
				}
				for (i = 0; i < 50; i++)
				{
					scan[i] = NULL;			//단어를 입력하는중에 출력되는 글자가 없음 
				}
			}
		}
	}
}

void title1()												  //프로그램 실행 직후 초기화작업을 진행할 함수 정의
{
	system("mode con cols=80 lines=25");					  //콘솔창 크기 조절

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);   //콘솔 핸들가져오기
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

}

int title2()							//처음 게임창의 메뉴 선택화면을 위한 함수 정의
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

	int x = 35, y = 13;

	gotoxy(x - 2, y);		//-2를 하는 이유는 ▷를 출력하기 위해서
	printf("▷ 게임시작");
	gotoxy(x, y + 1);
	printf(" 게임방법");
	gotoxy(x, y + 2);
	printf(" 종    료\n\n");

	gotoxy(x - 15, y + 4);
	printf("  ______________________________________");
	gotoxy(x - 15, y + 6);
	printf(" |UP키: W  DOWN키: S  SELECT키: SPACEBAR|");
	gotoxy(x - 15, y + 7);
	printf("  ______________________________________");
	gotoxy(x - 16, y + 9);
	printf("| 대구가톨릭대학교 19120450 IT공학부 김유리 |");

	while (1)			//메뉴화면 선택을 위한 while문
	{
		int a = keycontrol();			//변수 a를 keycontrol함수에 저장

		switch (a)		//메뉴선택을 위한 switch문 사용
		{
		case UP:		//case값이 UP(W)일 때
		{
			if (y > 13)		//y좌표를 13~15만 이동
			{
				gotoxy(x - 2, y);		//-2를 한 이유는 ▷의 출력을 위해
				printf(" ");			//원래 위치를 지움
				gotoxy(x - 2, --y);		//새로 이동한 위치로 이동
				printf("▷");			//다시 ▷ 출력
			}
			break;
		}
		case DOWN:		//case값이 DOWN(S)일 때 
		{
			if (y < 15)	   //y값이 최대 15
			{
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf("▷");
			}
			break;
		}
		case SUBMIT:		//case값이 SUBMIT(스페이스바)일 때
		{
			return y - 13;			/*스페이바를 눌렀을 경우 y위치가 13이였으므로
									 y-13을 하면 0,1,2 세 숫자를 받을 수 있음*/
		}
		}
	}
}

void help()			//게임 도움말창을 위한 함수 정의
{
	system("cls");		//콘솔창 화면을 지움

	design();		//design함수 호출

	gotoxy(10, 12);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("사방에서 뜨는 단어들을 입력하여 50초 동안 점수를 얻는 게임입니다\n");
	gotoxy(27, 13);
	printf("단어의 색 마다 배점이 다릅니다");

	gotoxy(37, 15);
	printf("[배점]");

	gotoxy(19, 17);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("■ : 150점");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf(" ■ : 200점");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf(" ■ : 250점");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	printf(" ■ : 300점");

	gotoxy(18, 19);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("| 대구가톨릭대학교 19120450 IT공학부 김유리 |");
	gotoxy(19, 21);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("이전페이지로 돌아가려면 SPACEBAR를 누르세요");

	while (1)	//이전페이지로 돌아가기 위한 while문
	{
		if (keycontrol() == SUBMIT)		//스페이스바를 눌렀을 때
		{
			main();			//main함수 호출
		}
	}
}

void removecursor()		//커서를 제거하는 함수
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}