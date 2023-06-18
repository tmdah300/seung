#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "screen.h"
#include "game.h"
#include "snake.h"
#include "apple.h"

width = 35;
height = 10;


//게임 초기화. 게임 시작 후 한번만 실행된다.
int Initialize()
{
	Running = 1;
	GameState = 0;
	setScreenSize(width, height);
	SetColor(0b1000, 0b1111);
	ClearBuffer();

	int i = 0;
	srand(time(NULL)); //난수 생성기의 시드값을 현재시간값으로 초기화하여 난수의 패턴을 불규칙하게 만든다.
	apple.posX = 1 + rand() % (width); //x값 범위 1 ~ width
	apple.posY = 1 + rand() % (height); //y값 범위 1 ~ height 	//사과와 벽의 위치가 겹치지 않게 + 1 을 한다.
	apple.isActive = 1;
	while (i < snakeSize)
	{
		if (initApple(snakeSkin[i].posX, snakeSkin[i].posY, width, height))
		{
			i = 0;
		}
		else
		{
			i++;
		}
	}
	
	
	initSnake(width, height);
	SetColor(0b0000, 0b1111);
	return 0;
}

void Run()
{
	Initialize();

	unsigned long time_end = GetTickCount64(); //프로그램이 시작된 이후의 시간 반환
	unsigned long deltaTime = GetTickCount64();

	while (Running)
	{	
		switch (GameState)
		{
		case 0: TitleMenu();
			break;
		case 1: 
		{
			deltaTime = GetTickCount64() - time_end; //반복문이 한번 실행되는데 걸린 시간 저장.
			time_end = GetTickCount64(); //현재 시간을 다시 time_end에 저장

			Play(deltaTime); //화면 그리기.

			if (deltaTime < 33) //만약 반복문이 한번 실행되는데 걸린 시간이 33초 이하라면
				Sleep(33 - deltaTime); // 33초에서 deltaTime을 뺀만큼을 대기하여 프레임을 유지한다.

			break;
		}
		case 2: ReStartMenu();
			break;
		default: break;
		}

	}

}


int DeltaTimeSum = 0;

int Play(int DeltaTime)
{
	setCursorPos(0, 0);
	SetColor(0b1111, 0b0000);
	printf("%s", ScreenBuffer);

	DrawSnake(DeltaTime);

	//만약 뱀과 사과의 위치가 같다면 EatApple 함수 실행
	if (snakeSkin[0].posX == apple.posX
		&& snakeSkin[0].posY == apple.posY)
	{
		EatApple();
		int i = 0;
		while (i < snakeSize)
		{
			if (initApple(snakeSkin[i].posX, snakeSkin[i].posY, width, height))
			{
				i = 0;
			}
			else
			{
				i++;
			}
		}
		GrowSnake();
	}
	//사과 출력
	printApple();
	GameOver();

	//시간, 프레임
	SetColor(0b0000, 0b1111);
	setCursorPos(0, height+2);
	if (DeltaTime != 0)
	{
		printf("time : %d                 \nfps :%d                  \n", DeltaTime, 1000 / DeltaTime);
	}

	return 0;
}

void GameOver()
{
	//뱀이 벽에 부딪히면 게임종료.
	if (snakeSkin[0].posX == width + 1
		|| snakeSkin[0].posX == 0
		|| snakeSkin[0].posY == height + 1
		|| snakeSkin[0].posY == 0)
	{
		GameState = 2;
		initSnake(width, height);
		EatCount = 0;
	}
}


void TitleMenu()
{
	int left = 0;
	system("cls"); 
	SetColor(0b0000, 0b1111);
	setCursorPos(15, 5);
	printf("<지렁이 게임>");
	setCursorPos(13, 6);
	printf("시작 하시겠습니까?");

	setCursorPos(15, 8);
	printf("[예]");
	setCursorPos(21, 8);
	printf("[아니요]");

	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 'a')
			{
				SetColor(0b0000, 0b1010);
				setCursorPos(15, 8);
				printf("[예]");
				SetColor(0b0000, 0b1111);
				setCursorPos(21, 8);
				printf("[아니요]");
				left = 1;
			}
			else if (_getch() == 'd')
			{
				SetColor(0b0000, 0b1111);
				setCursorPos(15, 8);
				printf("[예]");
				SetColor(0b0000, 0b1010);
				setCursorPos(21, 8);
				printf("[아니요]");
				left = 0;
			}

			if (_getch() == 13)
			{
				if (left)
				{
					GameState = 1;
					break;
				}
				else
				{
					SetColor(0b0000, 0b1111);
					Running = 0;
					break;
				}
			}
		}
	}
}


void ReStartMenu()
{
	int left = 0;
	system("cls");

	SetColor(0b0000, 0b1111);
	setCursorPos(5, 6);
	printf("[다시 시작]");

	setCursorPos(20, 6);
	printf("[타이틀 메뉴로]");

	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 'a')
			{
				SetColor(0b0000, 0b0010);
				setCursorPos(5, 6);
				printf("[다시 시작]");
				SetColor(0b0000, 0b1111);
				setCursorPos(20, 6);
				printf("[타이틀 메뉴로]");
				left = 1;
			}
			else if (_getch() == 'd')
			{
				SetColor(0b0000, 0b1111);
				setCursorPos(5, 6);
				printf("[다시 시작]");
				SetColor(0b0000, 0b0010);
				setCursorPos(20, 6);
				printf("[타이틀 메뉴로]");
				left = 0;
			}

			if (_getch() == 13)
			{
				if (left)
				{
					GameState = 1;
					break;
				}
				else
				{
					GameState = 0;
					break;
				}
			}
		}
	}
}

	