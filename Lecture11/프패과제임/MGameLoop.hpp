#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <vector>

using namespace std;

namespace MuSoeun
{
	void gotoxy1(int x, int y) {
		//x, y 좌표 설정
		COORD pos = { x,y };
		//커서 이동
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	class MGameLoop
	{
	public:

		bool isGameRunning = false;

		MGameLoop() {}
		~MGameLoop() {}



		void initialize()
		{
			gotoxy1(3, 15);
			isGameRunning = true;
			std::cout << "게임 초기화중" << std::endl;
		}
		void Update()
		{
			std::cout << "게임 키 입력 대기" << std::endl;
			if (_kbhit())
			{
				gotoxy1(3, 16);
			}
		}
		

		void Release()
		{
			gotoxy1(3, 18);
			std::cout << "게임 종료중" << std::endl;
		}
		void Run()
		{
			initialize();
			while (isGameRunning)
			{
				Update();
			}
			Release();
		}
		
	};

}