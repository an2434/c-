#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable : 4996)

//121 61

//ź�� �ϳ��� ������ ǥ���ϴ� ����ü
typedef struct bullet
{
	int x;
	int y;
	int direction;
}Bullet;

//��ü�� ��ǥ ���� ����
int X_Plain;
int Y_Plain;

Bullet Bullet_info[50];//ź�� ���� ����ü�迭
int Bullet_Num;//���� �����ϴ� ź����

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

//Ű�� �Է¹ް� ���ּ� ��ġ�� �ȱ�� �Լ�
void move_Plain()
{
	gotoxy(X_Plain, Y_Plain);
	printf("  ");
	if (GetAsyncKeyState(VK_UP) & 0x8000)Y_Plain--;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)Y_Plain++;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)X_Plain-=2;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)X_Plain+=2;
	gotoxy(X_Plain, Y_Plain);
	printf("��");
}

//�� ���� �Լ� a=b
void BulletCpy(int a, int b)
{
	Bullet_info[a].x = Bullet_info[b].x;
	Bullet_info[a].y = Bullet_info[b].y;
	Bullet_info[a].direction = Bullet_info[b].direction;
}

//���ο� ����ź���� ����� �Լ�
void CreateNewBullet(void)
{
	int starting_point;
	starting_point = rand() % 4;
	switch (starting_point)
	{
	case 0:
		Bullet_info[Bullet_Num].x = rand() % 120;
		Bullet_info[Bullet_Num].y = 0;
		Bullet_info[Bullet_Num].direction = 4 + rand() % 3;
		break;
	case 1:
		Bullet_info[Bullet_Num].x = 119;
		Bullet_info[Bullet_Num].y = rand() % 60;
		Bullet_info[Bullet_Num].direction = 6 + rand() % 3;
		break;
	case 2:
		Bullet_info[Bullet_Num].x = rand() % 120;
		Bullet_info[Bullet_Num].y = 59;
		Bullet_info[Bullet_Num].direction = (7 + rand() % 3)%8+1;
		break;
	case 3:
		Bullet_info[Bullet_Num].x = 0;
		Bullet_info[Bullet_Num].y = rand() % 60;
		Bullet_info[Bullet_Num].direction = 2 + rand() % 3;
		break;
	}
	Bullet_Num++;
}

//ź���� ����� �Լ� 
void ClearBullet(void)
{
	int i;
	for (i = 0; i < Bullet_Num; i++)
	{
		gotoxy(Bullet_info[i].x, Bullet_info[i].y);
		printf(" ");
	}
}

//ź���� dir�� ���� ��ĭ �����̴� �Լ�
void MoveBullet(int *px,int *py,int dir)
{
	switch (dir)
	{
	case 1:
		*py -= 1;
		break;
	case 2:
		*py -= 1;
		*px += 1;
		break;
	case 3:
		*px += 2;
		break;
	case 4:
		*px += 1;
		*py += 1;
		break;
	case 5:
		*py += 1;
		break;
	case 6:
		*px -= 1;
		*py += 1;
		break;
	case 7:
		*px -= 2;
		break;
	case 8:
		*px -= 1;
		*py -= 1;
	}
}

//Ư�� �ε����� ź���� �����ϴ� �Լ�
void KillBullet(int n)
{
	int i;
	for (i = n; i < Bullet_Num - 1; i++)
	{
		
		BulletCpy(i, i + 1);
		
	}
	Bullet_Num--;
}

//ź���� ����ϴ� �Լ� , ���� ź���� ������ ���� ��� �Ҹ� ��Ű�� ���ο� ź������ ��ü
int PrintBullet(void)
{
	int i,NewBullet =0;
	for (i = 0; i < Bullet_Num; i++)//�� Bullet�� ����
	{
		MoveBullet(&Bullet_info[i].x, &Bullet_info[i].y, Bullet_info[i].direction);//�Ҹ��� ��ĭ ������

		if (Bullet_info[i].x < 0 || Bullet_info[i].x>119)//�� x��ǥ�� �Ѱ踦 ������ ����
		{
			KillBullet(i);
			i--;
			NewBullet += 1;
		}
		else if (Bullet_info[i].y < 0 || Bullet_info[i].y>59)//�� y��ǥ�� �Ѱ踦 ������ ����
		{
			KillBullet(i);
			i--;
			NewBullet += 1;
		}
	}
	for (i = 0; i < NewBullet; i++)CreateNewBullet();//���� ����ŭ �� ����
	for (i = 0; i < Bullet_Num; i++)
	{
		if (Bullet_info[i].x >= X_Plain -1 && Bullet_info[i].x <= X_Plain + 2)
		{
			// �÷��̾�� �浹 ����
			if (Bullet_info[i].y >= Y_Plain-1 && Bullet_info[i].y <= Y_Plain +1)
			{
				gotoxy(50, 60);
				printf("Bullet(%d,%d), Plain(%d,%d)\n", Bullet_info[i].x, Bullet_info[i].y, X_Plain, Y_Plain);
				return 1;
			}
		}
		gotoxy(Bullet_info[i].x, Bullet_info[i].y);
		printf("o");
	}
	return 0;
}

int main()
{

	//system("mode con sole = 121 line = 61");
	int i,level=0;
	int x = 13, y = 5;
	int a = 50,b=150;
	gotoxy(x, y + 0); printf("____________________________________________________________________________________________");
	gotoxy(x, y + 1); printf("��                                                                                        ��");
	gotoxy(x, y + 2); printf("��      �ǢǢ�    �ǢǢǢ�       ��          �ǢǢ�    �ǢǢǢǢ�      ��          ��     ��");
	gotoxy(x, y + 3); printf("��    ��      ��  ��      ��    �Ǣ�       ��      ��  ��                ��      ��       ��");
	gotoxy(x, y + 4); printf("��    ��          ��      ��   ��  ��     ��           ��                  ��  ��         ��");
	gotoxy(x, y + 5); printf("��      �ǢǢ�    �ǢǢǢ�    �ǢǢǢ�    ��           �ǢǢǢǢ�            ��           ��");
	gotoxy(x, y + 6); printf("��            ��  ��         ��      ��   ��           ��                  ��  ��         ��");
	gotoxy(x, y + 7); printf("��    ��      ��  ��        ��        ��   ��      ��  ��                ��      ��       ��");
	gotoxy(x, y + 8); printf("��      �ǢǢ�    ��       ��          ��    �ǢǢ�    �ǢǢǢǢ�      ��          ��     ��");
	gotoxy(x, y + 9); printf("��                                                                                        ��");
	gotoxy(x, y + 10);printf("��                      +   +   +  < wait for 3 second >   +  +  +                        ��");
	gotoxy(x, y + 11);printf("��________________________________________________________________________________________��");Sleep(1000);
	gotoxy(x, y + 10);printf("��                          +   +  < wait for 2 second >   +  +                           ��");
	gotoxy(x, y + 11);printf("��________________________________________________________________________________________��");Sleep(1000);
	gotoxy(x, y + 10);printf("��                              +  < wait for 1 second >   +                              ��");
	gotoxy(x, y + 11);printf("��________________________________________________________________________________________��");
	Sleep(1000);
	
	
	
	system("cls");
	//Ŀ�� �����
	CONSOLE_CURSOR_INFO cursorinfo = { 0, };
	cursorinfo.dwSize = 1;
	cursorinfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorinfo);

	//��������� ���� �κ�
	srand(time(NULL));

	X_Plain = 60;
	Y_Plain = 30;
	for (i = 0; i < 10; i++)
	{
		CreateNewBullet();
	}
	PrintBullet();
	Sleep(100);
	while (1)
	{
		ClearBullet();
		move_Plain();
		if (PrintBullet())//���ӿ��� ��Ȳ�ϰ�� ���ǹ� ����
		{
			int x =45, y =20 ;
			gotoxy(x, y+ 0);  printf("__________________________________"); //���ӿ��� �޼��� 
			gotoxy(x, y + 1); printf("��                              ��");
			gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
			gotoxy(x, y + 3); printf("��  |  G A M E  O V E R..   |   ��");
			gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
			gotoxy(x, y + 5); printf("��   YOUR SCORE: %6d         ��", level);
			gotoxy(x, y + 6); printf("��                              ��");
			gotoxy(x, y + 7); printf("��                              ��");
			gotoxy(x, y + 8); printf("��                              ��");
			gotoxy(x, y + 9); printf("��______________________________��");
			Sleep(6000);
			
			return 0;
		}
		level++;
		gotoxy(53, 0);
		printf("point : %d ",level);
		if (level % 20 == 0 && level < 800)CreateNewBullet();
		if (level  == b)
		{
			a -= 7;
			b += 150;
		}
		
		Sleep(a);
		
	}
	return 0;
}

