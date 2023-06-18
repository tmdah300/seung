#define MAX_SNAKE_LENGTH 1400

int snakeSize; // ���� ���� ����
int GameStartSnakeLength;
int direction; //������ 0(up) 1(right) 2(down) 3(left) 

struct snakeskin
{
	int posX;
	int posY;
	int isActive;
};

struct snakeskin snakeSkin[MAX_SNAKE_LENGTH];

void initSnake(int Gwidth, int Gheight);
void MoveSnake();
void printSnake();
void GrowSnake();
void ClickEvent();
void DrawSnake(int DeltaTime);

