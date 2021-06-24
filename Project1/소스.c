#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>;


#pragma warning(disable : 4996)
void Game_Finished();
//121 61

//탄막 하나의 정보를 표현하는 구조체
typedef struct bullet
{
	int x;
	int y;
	int direction;
}Bullet;

//기체의 좌표 전역 변수
int X_Plain;
int Y_Plain;
//레벨
int level;

Bullet Bullet_info[50];//탄약 정보 구조체배열
int Bullet_Num;//현재 존재하는 탄막수

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

//키를 입력받고 우주선 위치를 옴기는 함수
void move_Plain()
{
	gotoxy(X_Plain, Y_Plain);
	printf("  ");
	if ((GetAsyncKeyState(VK_UP) & 0x8000) && Y_Plain != 0)Y_Plain--;
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && Y_Plain != 59)Y_Plain++;
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && X_Plain != 0)X_Plain-=2;
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && X_Plain != 118)X_Plain+=2;
	if (X_Plain == 20 && Y_Plain == 20 && level  > 600)
		Game_Finished();
	gotoxy(X_Plain, Y_Plain);
	printf("△");
}

//블릿 대입 함수 a=b
void BulletCpy(int a, int b)
{
	Bullet_info[a].x = Bullet_info[b].x;
	Bullet_info[a].y = Bullet_info[b].y;
	Bullet_info[a].direction = Bullet_info[b].direction;
}

//새로운 랜덤탄막을 만드는 함수
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

//탄막을 지우는 함수 
void ClearBullet(void)
{
	int i;
	for (i = 0; i < Bullet_Num; i++)
	{
		gotoxy(Bullet_info[i].x, Bullet_info[i].y);
		printf(" ");
	}
}

//탄막을 dir에 맞춰 한칸 움직이는 함수
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

//특정 인덱스의 탄막을 삭제하는 함수
void KillBullet(int n)
{
	int i;
	for (i = n; i < Bullet_Num - 1; i++)
	{
		
		BulletCpy(i, i + 1);
		
	}
	Bullet_Num--;
}

//탄막을 출력하는 함수 , 만약 탄막이 벽돌을 넘을 경우 소멸 시키고 새로운 탄막으로 대체
int PrintBullet(void)
{
	int i,NewBullet =0;
	for (i = 0; i < Bullet_Num; i++)//각 Bullet에 접근
	{
		MoveBullet(&Bullet_info[i].x, &Bullet_info[i].y, Bullet_info[i].direction);//불릿을 한칸 움직임

		if (Bullet_info[i].x < 0 || Bullet_info[i].x>119)//블릿 x좌표가 한계를 넘을시 지움
		{
			KillBullet(i);
			i--;
			NewBullet += 1;
		}
		else if (Bullet_info[i].y < 0 || Bullet_info[i].y>59)//블릿 y좌표가 한계를 넘을시 지움
		{
			KillBullet(i);
			i--;
			NewBullet += 1;
		}
	}
	for (i = 0; i < NewBullet; i++)CreateNewBullet();//빠진 수만큼 블릿 생성
	for (i = 0; i < Bullet_Num; i++)
	{
		if (Bullet_info[i].x >= X_Plain -1 && Bullet_info[i].x <= X_Plain + 2)
		{
			// 플레이어와 충돌 감지
			if (Bullet_info[i].y >= Y_Plain-1 && Bullet_info[i].y <= Y_Plain +1)
			{
				gotoxy(50, 60);
				//printf("Bullet(%d,%d), Plain(%d,%d)\n", Bullet_info[i].x, Bullet_info[i].y, X_Plain, Y_Plain);
				return 1;
			}
		}
		gotoxy(Bullet_info[i].x, Bullet_info[i].y);
		if (level > 200 && level < 300 && level % 2 == 0)
			continue;
		printf("o");
	}
	return 0;
}


void title(void) {
	int x = 13; //타이틀화면이 표시되는 x좌표 
	int y = 5; //타이틀화면이 표시되는 y좌표 
	int cnt; //타이틀 프레임을 세는 변수  
	int o = 10;
    gotoxy(x, y + 0); printf("■□□□■■■□□■■□□■■■□□□■■■□□■■□□■■■□□□■■■□□■■□□■■■"); Sleep(100);
	gotoxy(x, y + 1); printf("□                                                                                        □"); Sleep(100);
	gotoxy(x, y + 2); printf("□      ■■■▤   ■■■■▤     ■▤        ■■■▤   ■■■■▤    ■▤          ■▤ ■"); Sleep(100);
	gotoxy(x, y + 3); printf("■    ■▤    ■▤ ■▤   ■▤   ■■▤     ■▤    ■▤ ■▤            ■▤      ■▤   ■"); Sleep(100);
	gotoxy(x, y + 4); printf("■    ■▤         ■▤   ■▤  ■| ■▤   ■▤          ■▤              ■▤  ■▤     □"); Sleep(100);
	gotoxy(x, y + 5); printf("□      ■■■▤   ■■■■▤  ■■■■▤  ■▤          ■■■■▤          ■■▤       ■"); Sleep(100);
	gotoxy(x, y + 6); printf("■            ■▤ ■▤       ■▤    ■▤ ■▤          ■▤              ■▤ ■▤      □"); Sleep(100);
	gotoxy(x, y + 7); printf("□    ■▤    ■▤ ■▤      ■▤      ■▤ ■▤    ■▤ ■▤            ■▤      ■▤   ■"); Sleep(100);
	gotoxy(x, y + 8); printf("■      ■■■▤   ■▤     ■▤        ■▤  ■■■▤   ■■■■▤    ■▤          ■▤ ■"); Sleep(100);
	gotoxy(x, y + 9); printf("□                                                                                        □"); Sleep(100);
	gotoxy(x, y + 10);printf("■                 +   +   +  < Please Enter Any Key to Start.. >   +  +  +               ■"); Sleep(100);
	gotoxy(x, y + 11);printf("■□□■■■■□□■■■□□■■□□■■□□■■■□□□■■■□□■■□□■□□■□□■■■");Sleep(100);
	
	gotoxy(x, y + 13); printf("  △   : Shift");
	gotoxy(x, y + 14); printf("◁  ▷ : Left / Right");
	gotoxy(x, y + 15); printf("  ▽   : Soft Drop");
	//gotoxy(x, y + 15); printf(" Space : Pause");
	for (cnt = 0;; cnt++) { //cnt를 1씩 증가시키면서 계속 반복    //하나도 안중요한 별 반짝이는 애니메이션효과 
		if (kbhit())
		{
			 //키입력이 있으면 무한루프 종료 
			gotoxy(x, y + 10); printf("■                      +   +   +  < wait for 3 second >   +  +  +                        ■");
			gotoxy(x, y + 11); printf("■□□■■■■□□■■■□□■■□□■■□□■■■□□□■■■□□■■□□■□□■□□■■■"); Sleep(1000);
			gotoxy(x, y + 10); printf("■                          +   +  < wait for 2 second >   +  +                           ■");
			gotoxy(x, y + 11); printf("■□□■■■■□□■■■□□■■□□■■□□■■■□□□■■■□□■■□□■□□■□□■■■"); Sleep(1000);
			gotoxy(x, y + 10); printf("■                              +  < wait for 1 second >   +                              ■");
			gotoxy(x, y + 11); printf("■□□■■■■□□■■■□□■■□□■■□□■■■□□□■■■□□■■□□■□□■□□■■■"); Sleep(1000);
			break;
		}Sleep(10); // 00.1초 딜레이  
	}



	while (_kbhit()) _getch(); //버퍼에 기록된 키값을 버림 

}
int main()
{
	system("mode con cols=120 lines=60");
	title();
	//PlaySound(TEXT("bgm.wav"), NULL, SND_ASYNC | SND_LOOP);//음악 재생
	int i;

	int a = 50,b=150;
	
	//if (_getch('p'))일시정지
	//{
	//	system("pause");
	//    system("cls"); //화면 지우고 새로 그림 
	//}
	
	system("cls");
	//커서 숨기기
	CONSOLE_CURSOR_INFO cursorinfo = { 0, };
	cursorinfo.dwSize = 1;
	cursorinfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorinfo);

	//난수사용을 위한 부분
	srand((unsigned int)time(NULL));

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
		if (PrintBullet())//게임오버 상황일경우 조건문 진입
		{
			system("cls");
			int x =45, y =20 ;
			gotoxy(x, y+ 0);  printf("■□□■■□□■□□■■■■□□■"); //게임오버 메세지 
			gotoxy(x, y + 1); printf("■                              □");
			gotoxy(x, y + 2); printf("□   +-----------------------+  □");
			gotoxy(x, y + 3); printf("■   |  G A M E  O V E R..   |  ■");
			gotoxy(x, y + 4); printf("□   +-----------------------+  □");
			gotoxy(x, y + 5); printf("□     YOUR SCORE: %6d       ■", level);
			gotoxy(x, y + 6); printf("■                              □");
			gotoxy(x, y + 7); printf("■                              □");
			gotoxy(x, y + 8); printf("□                              ■");
			gotoxy(x, y + 9); printf("■□□■■■■□□■■■■□□■■\n");
			Sleep(1000);
			level = 0;
			system("pause");
			Bullet_Num = 0;
			return main();
			
			
		}
		level++;
		gotoxy(53, 0);
		printf("point : %d ",level);
		if (level % 20 == 0 && level < 800)CreateNewBullet();

		if (level  == b)//속도 조절
		{
			a -= 7;
			b += 150;
		}
		
		Sleep(a);
		if (level == 600)
		{
			
			gotoxy(20, 20);printf("↓");
			
		}
		
	}
	//return main();
}

void Game_Finished()
{
	int x = 13, y = 5;
	system("cls");
	gotoxy(x, y + 1); printf("                                                                        ");
	gotoxy(x, y + 2); printf("            Thank you for play the Space X                              ");
	gotoxy(x, y + 3); printf("                                                                        ");
	gotoxy(x, y + 4); printf("              (☞ºヮº)☞  Team Member:JinHyung && SungHyun  ☜(ºヮº☜)  ");
	gotoxy(x, y + 5); printf("                                                                        ");
	gotoxy(x, y + 6); printf("   (つ 0_0)つ                                           o==(>▽<*)o     ");
	gotoxy(x, y + 7); printf("                                                                        ");
	gotoxy(x, y + 8); printf("                                                                        ");
	gotoxy(x, y + 9); printf("                                                                        ");
	system("pause");
}