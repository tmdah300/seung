#include "snake.h"

direction = 0;

void initSnake(Gwidth, Gheight)
{
	snakeSize = GameStartSnakeLength = 3;

	static int a = 0;
	int i = 0;

	if (a == 0) //처음 호출될때만 실행
	{
		while (i < MAX_SNAKE_LENGTH)
		{
			snakeSkin[i].posX = Gwidth/2;
			snakeSkin[i].posY = Gheight/2;
			snakeSkin[i].isActive = 0;
			i = i + 1;
		}
		i = 0;
		a++;
	}

	while (i < snakeSize)
	{
		snakeSkin[i].posX = Gwidth/2 - i;
		snakeSkin[i].posY = Gheight/2;
		snakeSkin[i].isActive = 1;
		i = i + 1;
	}
}

void ClickEvent()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a': direction = (direction + 3) % 4; break; // 왼쪽으로 90도 회전 
		case 'd': direction = (direction + 1) % 4; break; // 오른쪽으로 90도 회전
		case 27: exit(0); // ESC를 누르면 종료
		}
	}
}

void MoveSnake()
{
	//몸통이동 부분
	int i = snakeSize - 1;
	while (i > 0)
	{
		snakeSkin[i].posX = snakeSkin[i - 1].posX;
		snakeSkin[i].posY = snakeSkin[i - 1].posY;
		i = i - 1;
	}
	//머리 이동부분
	switch (direction) 
	{
	case 0: snakeSkin[0].posY--; break; //위
	case 1: snakeSkin[0].posX++; break; //오른쪽
	case 2: snakeSkin[0].posY++; break; //아래
	case 3: snakeSkin[0].posX--; break; //왼
	}

	
}

void printSnake()
{
	int i = 1;

	while (i < snakeSize)
	{
		setCursorPos(snakeSkin[i].posX, snakeSkin[i].posY);
		SetColor(0b1111, 0b0010);
		printf("O");
		i = i + 1;
	}
	setCursorPos(snakeSkin[0].posX, snakeSkin[0].posY);
	SetColor(0b1111, 0b0000);
	printf("O");
}

void GrowSnake()
{
	snakeSize = snakeSize + 1;
	//사과를 먹으면 새로 생긴 피부가 바로 꼬리부분에 붙게 한다.
	snakeSkin[snakeSize - 1].posX = snakeSkin[snakeSize - 2].posX;
	snakeSkin[snakeSize - 1].posY = snakeSkin[snakeSize - 2].posY;
	snakeSkin[snakeSize - 1].isActive = 1;
}

void DrawSnake(int DeltaTime)
{
	static int DeltaTimeSum = 0; 
	DeltaTimeSum = DeltaTimeSum + DeltaTime;
	ClickEvent(); //뱀의 클릭 이벤트 a(좌), d(우)
	if (DeltaTimeSum >= 500) //DeltaTime 기준으로 뱀의 움직임이 진행된다.0.5초마다 한번씩
	{
		DeltaTimeSum = 0;
		MoveSnake();
	}
	//뱀 출력
	printSnake();
}