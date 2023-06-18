#include "apple.h"

EatCount = 0;


void EatApple()
{

	//뱀이 사과를 먹었을 때 커서를 사과 위치로 이동해 사과를 공백으로 바꾸고 새로 초기화 한다.
	setCursorPos(apple.posX, apple.posY);
	SetColor(0b1111, 0b0000);
	printf(" ");

	//먹은 사과 갯수를 +1 한다.
	EatCount = EatCount + 1;
}

void printApple()
{
	setCursorPos(apple.posX, apple.posY);
	SetColor(0b1111, 0b0100);
	printf("*");

	SetColor(0b0000, 0b1111);
	setCursorPos(0, 15);
	printf("Apple : %d", EatCount);
}

int initApple(int snakeX, int snakeY, int Gwidth, int Gheight)
{
	if (snakeX == apple.posX
		&& snakeY == apple.posY)
	{
		srand(time(NULL)); //난수 생성기의 시드값을 현재시간값으로 초기화하여 난수의 패턴을 불규칙하게 만든다.
		apple.posX = 1 + rand() % (Gwidth); //x값 범위 1 ~ width
		apple.posY = 1 + rand() % (Gheight); //y값 범위 1 ~ height 	//사과와 벽의 위치가 겹치지 않게 + 1 을 한다.
		apple.isActive = 1;

		return 1;
	}

	return 0;
}