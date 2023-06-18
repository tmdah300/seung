#include "snake.h"

direction = 0;

void initSnake(Gwidth, Gheight)
{
	snakeSize = GameStartSnakeLength = 3;

	static int a = 0;
	int i = 0;

	if (a == 0) //ó�� ȣ��ɶ��� ����
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
		case 'a': direction = (direction + 3) % 4; break; // �������� 90�� ȸ�� 
		case 'd': direction = (direction + 1) % 4; break; // ���������� 90�� ȸ��
		case 27: exit(0); // ESC�� ������ ����
		}
	}
}

void MoveSnake()
{
	//�����̵� �κ�
	int i = snakeSize - 1;
	while (i > 0)
	{
		snakeSkin[i].posX = snakeSkin[i - 1].posX;
		snakeSkin[i].posY = snakeSkin[i - 1].posY;
		i = i - 1;
	}
	//�Ӹ� �̵��κ�
	switch (direction) 
	{
	case 0: snakeSkin[0].posY--; break; //��
	case 1: snakeSkin[0].posX++; break; //������
	case 2: snakeSkin[0].posY++; break; //�Ʒ�
	case 3: snakeSkin[0].posX--; break; //��
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
	//����� ������ ���� ���� �Ǻΰ� �ٷ� �����κп� �ٰ� �Ѵ�.
	snakeSkin[snakeSize - 1].posX = snakeSkin[snakeSize - 2].posX;
	snakeSkin[snakeSize - 1].posY = snakeSkin[snakeSize - 2].posY;
	snakeSkin[snakeSize - 1].isActive = 1;
}

void DrawSnake(int DeltaTime)
{
	static int DeltaTimeSum = 0; 
	DeltaTimeSum = DeltaTimeSum + DeltaTime;
	ClickEvent(); //���� Ŭ�� �̺�Ʈ a(��), d(��)
	if (DeltaTimeSum >= 500) //DeltaTime �������� ���� �������� ����ȴ�.0.5�ʸ��� �ѹ���
	{
		DeltaTimeSum = 0;
		MoveSnake();
	}
	//�� ���
	printSnake();
}