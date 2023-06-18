#pragma once //헤더파일이 한번만 포함되도록 함

struct game
{
	int GameState;
	int width;
	int height;
};

int Running;
int GameState; // state : 0 타이틀 메뉴. state : 1 게임 플레이, 2 재시작 메뉴
int width;
int height;

int Initialize();
void Run();
int Play(int DeltaTime);
void GameOver();
void TitleMenu();
void ReStartMenu();