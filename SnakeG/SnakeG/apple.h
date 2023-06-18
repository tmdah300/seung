#define NULL 0

int EatCount;

struct Apple
{
	int posX;
	int posY;
	int isActive;
};


struct Apple apple;

void EatApple();
void printApple();
int initApple(int snakeX, int snakeY, int Gwidth, int Gheight);

