#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <vector>

using namespace std;

namespace MuSoeun
{
	void gotoxy1(int x, int y) {
		//x, y ��ǥ ����
		COORD pos = { x,y };
		//Ŀ�� �̵�
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
			std::cout << "���� �ʱ�ȭ��" << std::endl;
		}
		void Update()
		{
			std::cout << "���� Ű �Է� ���" << std::endl;
			if (_kbhit())
			{
				gotoxy1(3, 16);
			}
		}
		

		void Release()
		{
			gotoxy1(3, 18);
			std::cout << "���� ������" << std::endl;
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