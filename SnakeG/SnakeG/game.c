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


//���� �ʱ�ȭ. ���� ���� �� �ѹ��� ����ȴ�.
int Initialize()
{
	Running = 1;
	GameState = 0;
	setScreenSize(width, height);
	SetColor(0b1000, 0b1111);
	ClearBuffer();

	int i = 0;
	srand(time(NULL)); //���� �������� �õ尪�� ����ð������� �ʱ�ȭ�Ͽ� ������ ������ �ұ�Ģ�ϰ� �����.
	apple.posX = 1 + rand() % (width); //x�� ���� 1 ~ width
	apple.posY = 1 + rand() % (height); //y�� ���� 1 ~ height 	//����� ���� ��ġ�� ��ġ�� �ʰ� + 1 �� �Ѵ�.
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

	unsigned long time_end = GetTickCount64(); //���α׷��� ���۵� ������ �ð� ��ȯ
	unsigned long deltaTime = GetTickCount64();

	while (Running)
	{	
		switch (GameState)
		{
		case 0: TitleMenu();
			break;
		case 1: 
		{
			deltaTime = GetTickCount64() - time_end; //�ݺ����� �ѹ� ����Ǵµ� �ɸ� �ð� ����.
			time_end = GetTickCount64(); //���� �ð��� �ٽ� time_end�� ����

			Play(deltaTime); //ȭ�� �׸���.

			if (deltaTime < 33) //���� �ݺ����� �ѹ� ����Ǵµ� �ɸ� �ð��� 33�� ���϶��
				Sleep(33 - deltaTime); // 33�ʿ��� deltaTime�� ����ŭ�� ����Ͽ� �������� �����Ѵ�.

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

	//���� ��� ����� ��ġ�� ���ٸ� EatApple �Լ� ����
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
	//��� ���
	printApple();
	GameOver();

	//�ð�, ������
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
	//���� ���� �ε����� ��������.
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
	printf("<������ ����>");
	setCursorPos(13, 6);
	printf("���� �Ͻðڽ��ϱ�?");

	setCursorPos(15, 8);
	printf("[��]");
	setCursorPos(21, 8);
	printf("[�ƴϿ�]");

	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 'a')
			{
				SetColor(0b0000, 0b1010);
				setCursorPos(15, 8);
				printf("[��]");
				SetColor(0b0000, 0b1111);
				setCursorPos(21, 8);
				printf("[�ƴϿ�]");
				left = 1;
			}
			else if (_getch() == 'd')
			{
				SetColor(0b0000, 0b1111);
				setCursorPos(15, 8);
				printf("[��]");
				SetColor(0b0000, 0b1010);
				setCursorPos(21, 8);
				printf("[�ƴϿ�]");
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
	printf("[�ٽ� ����]");

	setCursorPos(20, 6);
	printf("[Ÿ��Ʋ �޴���]");

	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 'a')
			{
				SetColor(0b0000, 0b0010);
				setCursorPos(5, 6);
				printf("[�ٽ� ����]");
				SetColor(0b0000, 0b1111);
				setCursorPos(20, 6);
				printf("[Ÿ��Ʋ �޴���]");
				left = 1;
			}
			else if (_getch() == 'd')
			{
				SetColor(0b0000, 0b1111);
				setCursorPos(5, 6);
				printf("[�ٽ� ����]");
				SetColor(0b0000, 0b0010);
				setCursorPos(20, 6);
				printf("[Ÿ��Ʋ �޴���]");
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

	