/*�������*/
#include <stdio.h>								//ǥ�� ����� �۾��� ���� �������
#include <stdlib.h>								//���� ��ƿ��Ƽ(�ؽ�Ʈ�� ���� ��ȯ ��)�Լ� �۾��� ���� ��� ����
#include <time.h>								//�ð� �۾��� ���� �������
#include <Windows.h>							//������ ���� ���α׷��� ����� ���� �������
#include <conio.h>								//getche()�Լ��� �̿��ϱ� ���� �������
#include <string.h>							    //strcmp �Լ��� ����� �������

#define wordcount 95							//�ܾ��� ���� ����
#define wordtime 20000							//�ܾ ��Ÿ���� �ӵ� ����

/*Ű���尪�� ��ũ�η� ����*/
#define UP 0									//0�� UP���� ����
#define DOWN 1									//1�� DOWN���� ����
#define SUBMIT 2								//2�� SUBMIT�� ����

time_t starttime = 0, endtime = 0;				//�ý��� �ð��� ����

/*�Լ�����*/
int keycontrol();								//Ű���� Ű ����� ���� �Լ�����
void title1();									//���α׷� ���� ���� �ʱ�ȭ�۾��� ������ �Լ�����
int title2();									//ó�� ����â�� �޴� ����ȭ���� ���� �Լ�����
void gotoxy(int x, int y);						//Ŀ�� ��ġ �̵� �Լ�����
void design();									//���� ùȭ���� ������ �Լ�����					
void design2();									//������ �÷��� �� ���� �Լ�����
void gamemain();								//���� �÷��� ȭ���� �Լ�����
void printword();								//�ܾ������ ���� �Լ�����
void scanword();								//�ܾ��Է��� ���� �Լ�����
void removecursor();							//Ŀ�����Ÿ� ���� �Լ�����
void help();									//���� ����â�� ���� �Լ�����

/*����*/
int wordx[250];									//�� ���� �ܾ���� �ȶ߰� �ϴ� ����
int x, y;										//gotoxy�Լ��� x���� y���� ����
int i, j;										//�ܾ��� ���� ����
int x2, y2;										//x, y���� �ٽ� �ҷ��� �� ���� ����
int score = 0;									//������ ��Ÿ�� ���� �ʱ�ȭ
int f;											//�ܾ��� ���� ����
int f2;											//�ܾ� ���� ���� �ٽ� �ҷ��ö� ����
int sword;										//�Էµ� �ܾ ��Ÿ�� ����
char scan[50];									//�Է��� �ܾ ���� ����
char remem[263][3];
int gap;										//�������ӽð��� ���� ����

void gotoxy(int x, int y)	//Ŀ�� ��ġ �̵� �Լ�����
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);   //�ܼ� �ڵ鰡������
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

char word[256][256] = { "dog", "cat", "bottle", "phone", "robot", "green", "elephant", "include", "sky",		//�ܾ 2���� �迭�� �� ����
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
	title1();			//title1�Լ� ȣ��				

	while (1)			//while�� �ݺ�
	{
		design();		//design�Լ� ȣ��

		int menucode = title2();	//menucode������ title2�Լ��� ȣ���ؼ� ����

		if (menucode == 0)			//menucode�� 0�� ��
		{
			score = 0;				//����
			starttime = clock();	//���۽ð��� clock�Լ��� ȣ���ؼ� ����
			gamemain();				//gamemain�Լ� ȣ��
			gap = 0;				//�������ӽð�
		}
		else if (menucode == 1)		//menucode�� 1�� ��
		{
			help();					//help�Լ� ȣ��
		}
		else if (menucode == 2)		//menucode�� 2�� ��
		{
			exit(1);				//����
		}
	}

	return 0;

}

int keycontrol()							//Ű���� Ű ����� ���� �Լ�����
{
	char temp = getch();					//enterŰ�� ġ���ʾƵ� ȭ�鿡 �ٷ� ���ڰ� ��

	if (temp == 'w' || temp == 'W')			//w or WŰ�� �Է��� ��
	{
		return UP;							//���� ����Ű ������ �� 
	}
	else if (temp == 's' || temp == 'S')	//s or SŰ�� �Է��� ��
	{
		return DOWN;						//�Ʒ��� ����Ű ������ ��
	}
	else if (temp == ' ')					//�����̽���(����)�� �Է��� ��
	{
		return SUBMIT;						//����Ű ������ ��		
	}
}
void design()     //���� ùȭ���� ������ �Լ�����
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);		//�ܼ� ���� �� ���� ���� �Ķ����� ��Ÿ��

	printf("�����������������������������������������");		//���� ����ȭ�� ������ ���
	printf("��                                                                            ��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);		//�ܼ� ���� �� ���� ���� ������� ��Ÿ��
	printf("��                    ######       ##        ##    ##      ######             ��");
	printf("��                  ###   ##     #####      ####  ###     ##                  ��");
	printf("��                 ##          ##   ##     ##  ##  ##    ##                   ��");
	printf("��                ###  ####   ########    ##   #   ##   ########              ��");
	printf("��                 ##    ##  ##     ##   ##        ##   ##                    ��");
	printf("��                  ######  ##      ##  ##         ##  #########              ��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	//�ܼ� ���� �� ���� ���� �Ķ����� ��Ÿ��
	printf("��                                                                            ��");
	printf("��                        ||��Ÿ���� �ܾ ���� ���ֱ�||                     ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("�����������������������������������������");
}

void design2()		//���� �÷��� ȭ���� ������ �Լ�����
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//�ܼ� ���� �� ���� ���� ������� ��Ÿ��

	printf("�����������������������������������������");		//���� �÷���ȭ���� ������ ���
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��____________________________________________________________________________��");
	printf("��_�ܾ �Է��ϼ���__________________________________________________________��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("��                                                                            ��");
	printf("�����������������������������������������");
}

void gamemain()					//���� �÷��� ȭ���� �Լ�����
{
	system("cls");				//ȭ���� ����

	gotoxy(35, 10);				//x��ǥ�� 35 y��ǥ�� 10���� ����	
	printf("3�� �� ����");
	Sleep(1000);				//�ƹ��͵� ���ϰ� 1�� ��ٸ�
	system("cls");				//ȭ���� ����
	gotoxy(35, 10);				//x��ǥ�� 35 y��ǥ�� 10���� ����
	printf("2�� �� ����");
	Sleep(1000);				//�ƹ��͵� ���ϰ� 1�� ��ٸ�
	system("cls");				//ȭ���� ����
	gotoxy(35, 10);				//x��ǥ�� 35 y��ǥ�� 10���� ����
	printf("1�� �� ����");
	Sleep(1000);				//�ƹ��͵� ���ϰ� 1�� ��ٸ�
	system("cls");				//ȭ���� ����

	design2();					//design2�Լ� ȣ��

	while (1)					//while�� �ݺ�
	{
		printword();			//printword�Լ� ȣ��
		scanword();				//scanword�Լ� ȣ��
	}
}

void printword()				//�ܾ������ ���� �Լ� ����
{
	static int check = wordcount;		//���� ���� ���� �� wordcount�� �ʱ�ȭ(������ ������� �ʰ� ��)
	x = rand() % 63;					//x��ǥ�� 63-1���� ������ ������ ����
	y = rand() % 15 + 2;					//y��ǥ�� 2���� 15-1���� ������ ������ ����
	i = rand() % wordcount;				//i�� wordcount 95���� ������ �� �߿� ���������� ����
	f = rand() % 4 + 1;					//�� ���� ���� �����ϰ�

	if (wordx[i] != 1)			//�� �� �� �ܾ��� �ȶ߰� �ϱ� ���� if��
	{
		wordx[i] = 1;		//�迭 i��° ��Ҹ� 1�� ����
		check--;			//cheak���� ���� ��Ŵ

		gotoxy(x, y);		//gotoxy�� x�� y��ǥ ����

		for (j = 0; j < 3; j++)		//�ܾ� ����� ���� for��
		{
			if (j == 0)				//j���� 0�� ��
			{
				remem[i][j] = x;	//�迭�� x����
			}
			else if (j == 1)		//j���� 1�� ��
			{
				remem[i][j] = y;	//�迭�� y����
			}
			else if (j == 2)		//j���� 2�� ��
			{
				remem[i][j] = f;	//�� ����
			}
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), f + 9);		//�ܼ� ���� �� ���� �ܾ���� 10�� ������
		printf("%s ", word[i]);		//�ܾ ���
	}
}

void scanword()			//�ܾ� �Է��� ���� �Լ� ����
{
	int p = 0;

	while (p < wordtime)
	{
		p++;

		int scanc;
		endtime = clock();			//����ð��� clock�Լ��� ȣ���ؼ� ����
		gap = (float)(endtime - starttime) / (CLOCKS_PER_SEC);			//���� ���ӽð��� ���� ���� gap

		if (gap > 50) //�������ӽð� 50s
		{
			system("cls");		//ȭ���� ����

			design2();			//design2 �Լ� ȣ��

			gotoxy(32, 11);		//x��ǥ�� 32 y��ǥ�� 11���� ����
			printf("||�� �� �� ��||");
			gotoxy(33, 12);		//x��ǥ�� 32 y��ǥ�� 12���� ����
			printf("����: %d", score);
			Sleep(5000);		//�ƹ��͵� ���ϰ� 5�� ��ٸ�

			system("cls");		//ȭ���� ����

			main();				//main�Լ� ȣ��
		}

		if (kbhit())		//kbhit()�Լ��� ����Ͽ� Ű ������ ������ �Ǵ�
		{
			scanc = getch();		//�Է��� ���ڸ� ����Ű�� ������� �ʰ� �ٷ� ȭ�鿡 ����ϱ� ���� ����ϴ� getch�Լ�

			if (scanc != 8 && scanc != 13)	//scamc�� 8�� 13�� �ƴ� ��
			{
				gotoxy(5, 20);
				scan[sword++] = scanc;
				printf("          ");		//�ܾ �Է��ϸ� ��µ�
				gotoxy(5, 20);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);		//�ܼ� ���� �� ���� �Ͼ���� ��Ÿ��
				printf("%s", scan);			//�Է��� ���� ���
			}
			else if (scanc == 8)			//scanc�� 8�� ��
			{
				gotoxy(5, 20);				//x��ǥ�� 5 y��ǥ�� 20���� ����
				printf("|        ");		//�ܾ �߸��Է½� ����� ��Ÿ���� Ŀ��
				gotoxy(5, 20);				//x��ǥ�� 5 y��ǥ�� 20���� ����
				scan[--sword] = scanc;		//���� �����

				if (sword == -1)			//sword�� -1�� ��
					sword = 0;
				printf("%s", scan);			//�Է��� �ܾ� ���
			}
			else if (scanc == 13)			//scanc�� 13�� ��
			{
				sword = 0;
				gotoxy(5, 20);				//x��ǥ�� 5 y��ǥ�� 20���� ����
				printf("|        ");		//���� �ܾ� �Է� �� �Է�â�� �ʱ�ȭ�Ǿ� ���

				for (i = 0; i <= wordcount; i++)
				{
					if (!strcmp(scan, word[i]))		//strcmp ��� scan�� word[i]���� ������ ������ �ٲ�
					{
						x2 = remem[i][0];
						y2 = remem[i][1];
						f2 = remem[i][2];

						gotoxy(x2, y2);
						printf("       ");			//��µ� �ܾ �Է��ϸ� �ܾ �����

						gotoxy(4, 20);
						printf("|        ");

						switch (f2)
						{
						case 1:					//10��° �� ���λ��� ���
							score += 150;
							break;

						case 2:					//11��° �� �ϴû��� ���
							score += 200;
							break;

						case 3:					//12��° �� ���ѻ������� ���
							score += 250;
							break;

						case 4:					//13��° �� ��ȫ���� ���
							score += 300;
							break;

						default:
							break;
						}
						gotoxy(62, 22);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
						printf("�������� :%d", score);
					}
				}
				for (i = 0; i < 50; i++)
				{
					scan[i] = NULL;			//�ܾ �Է��ϴ��߿� ��µǴ� ���ڰ� ���� 
				}
			}
		}
	}
}

void title1()												  //���α׷� ���� ���� �ʱ�ȭ�۾��� ������ �Լ� ����
{
	system("mode con cols=80 lines=25");					  //�ܼ�â ũ�� ����

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);   //�ܼ� �ڵ鰡������
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

}

int title2()							//ó�� ����â�� �޴� ����ȭ���� ���� �Լ� ����
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

	int x = 35, y = 13;

	gotoxy(x - 2, y);		//-2�� �ϴ� ������ ���� ����ϱ� ���ؼ�
	printf("�� ���ӽ���");
	gotoxy(x, y + 1);
	printf(" ���ӹ��");
	gotoxy(x, y + 2);
	printf(" ��    ��\n\n");

	gotoxy(x - 15, y + 4);
	printf("  ______________________________________");
	gotoxy(x - 15, y + 6);
	printf(" |UPŰ: W  DOWNŰ: S  SELECTŰ: SPACEBAR|");
	gotoxy(x - 15, y + 7);
	printf("  ______________________________________");
	gotoxy(x - 16, y + 9);
	printf("| �뱸���縯���б� 19120450 IT���к� ������ |");

	while (1)			//�޴�ȭ�� ������ ���� while��
	{
		int a = keycontrol();			//���� a�� keycontrol�Լ��� ����

		switch (a)		//�޴������� ���� switch�� ���
		{
		case UP:		//case���� UP(W)�� ��
		{
			if (y > 13)		//y��ǥ�� 13~15�� �̵�
			{
				gotoxy(x - 2, y);		//-2�� �� ������ ���� ����� ����
				printf(" ");			//���� ��ġ�� ����
				gotoxy(x - 2, --y);		//���� �̵��� ��ġ�� �̵�
				printf("��");			//�ٽ� �� ���
			}
			break;
		}
		case DOWN:		//case���� DOWN(S)�� �� 
		{
			if (y < 15)	   //y���� �ִ� 15
			{
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT:		//case���� SUBMIT(�����̽���)�� ��
		{
			return y - 13;			/*�����̹ٸ� ������ ��� y��ġ�� 13�̿����Ƿ�
									 y-13�� �ϸ� 0,1,2 �� ���ڸ� ���� �� ����*/
		}
		}
	}
}

void help()			//���� ����â�� ���� �Լ� ����
{
	system("cls");		//�ܼ�â ȭ���� ����

	design();		//design�Լ� ȣ��

	gotoxy(10, 12);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("��濡�� �ߴ� �ܾ���� �Է��Ͽ� 50�� ���� ������ ��� �����Դϴ�\n");
	gotoxy(27, 13);
	printf("�ܾ��� �� ���� ������ �ٸ��ϴ�");

	gotoxy(37, 15);
	printf("[����]");

	gotoxy(19, 17);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("�� : 150��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf(" �� : 200��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf(" �� : 250��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	printf(" �� : 300��");

	gotoxy(18, 19);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("| �뱸���縯���б� 19120450 IT���к� ������ |");
	gotoxy(19, 21);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("������������ ���ư����� SPACEBAR�� ��������");

	while (1)	//������������ ���ư��� ���� while��
	{
		if (keycontrol() == SUBMIT)		//�����̽��ٸ� ������ ��
		{
			main();			//main�Լ� ȣ��
		}
	}
}

void removecursor()		//Ŀ���� �����ϴ� �Լ�
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}