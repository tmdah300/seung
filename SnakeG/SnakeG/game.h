#pragma once //��������� �ѹ��� ���Եǵ��� ��

struct game
{
	int GameState;
	int width;
	int height;
};

int Running;
int GameState; // state : 0 Ÿ��Ʋ �޴�. state : 1 ���� �÷���, 2 ����� �޴�
int width;
int height;

int Initialize();
void Run();
int Play(int DeltaTime);
void GameOver();
void TitleMenu();
void ReStartMenu();