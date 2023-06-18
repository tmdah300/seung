#include "apple.h"

EatCount = 0;


void EatApple()
{

	//���� ����� �Ծ��� �� Ŀ���� ��� ��ġ�� �̵��� ����� �������� �ٲٰ� ���� �ʱ�ȭ �Ѵ�.
	setCursorPos(apple.posX, apple.posY);
	SetColor(0b1111, 0b0000);
	printf(" ");

	//���� ��� ������ +1 �Ѵ�.
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
		srand(time(NULL)); //���� �������� �õ尪�� ����ð������� �ʱ�ȭ�Ͽ� ������ ������ �ұ�Ģ�ϰ� �����.
		apple.posX = 1 + rand() % (Gwidth); //x�� ���� 1 ~ width
		apple.posY = 1 + rand() % (Gheight); //y�� ���� 1 ~ height 	//����� ���� ��ġ�� ��ġ�� �ʰ� + 1 �� �Ѵ�.
		apple.isActive = 1;

		return 1;
	}

	return 0;
}