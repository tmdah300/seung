#include <iostream>
#include <conio.h>

int print_titleScreen()
{
	printf("***************************************\n");
	printf("*                                     *\n");
	printf("*                                     *\n");
	printf("*             지렁이 게임             *\n");
	printf("*            (Snake  Bite)            *\n");
	printf("*                                     *\n");
	printf("*    1. 게임 시작                     *\n");
	printf("*    2. 게임 설명                     *\n");
	printf("*    3. 게임 랭킹 보기                *\n");
	printf("*    4. 게임 종료 (esc)               *\n");
	printf("***************************************\n");

	return 0;

}

int print_introductionScreen()
{
	printf("\n************************************\n");
	printf("*       게임 설명 화면입니다.      *\n");
	printf("************************************\n");
	printf("타이틀 화면으로 돌아갈까요?(Y/N).\n\n");

	return 0;
}

int print_playScreen()
{
	printf("********************************************\n");
	printf("*                                          *\n");
	printf("*                                          *\n");
	printf("*                                          *\n");
	printf("*                                          *\n");
	printf("*                                          *\n");
	printf("*                                          *\n");
	printf("*                                          *\n");
	printf("*                                          *\n");
	printf("*                                          *\n");
	printf("*                                          *\n");
	printf("********************************************\n");
	printf("타이틀 화면으로 돌아갈까요? (Y/N).\n\n");
	return 0;
}

int main()
{

	char input;
	int game_status=0, running = 1;

	while (running)
	{
		switch (game_status)
		{
			case 0: print_titleScreen(); 
					while (1)
					{
						input = _getch();
						if (input == '1') {
							game_status = 1; break;
						}
						if (input == '2') {
							game_status = 2; break;
						}
						if (input == '4'||input == 27)
						{
							running = 0; break;
						}
						else
						{
							continue;
						}
					}
					break;
			case 1: print_playScreen();
					while (true)
					{
						input = _getch();
						if (input == 'y') {
							game_status = 0; break;
						}
						else if (input == 'n') continue;
					}
				break;
			case 2: print_introductionScreen(); 
					while (1)
					{
						input = _getch();
						if (input == 'y') {
							game_status = 0; break;
						}
						else if (input == 'n') continue;
					}
					break;
			default: break;
		}

		

	}
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴