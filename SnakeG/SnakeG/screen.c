#include "screen.h"
#include <Windows.h>

	int screenWidth;
	int screenHeight;

	void setScreenSize(int width, int height) //�� ������
	{
		screenWidth = width;
		screenHeight = height;
	}

	void setCursorPos(int x, int y) //Ŀ�� ��ġ(x, y) ����
	{
		COORD pos = { x,y };											//GetStdHandle -> Window API �Լ�
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //STD_OUTPUT_HANDLE-> �ܼ�â�� ����¿� ���Ǵ� ǥ������ڵ�. 
	}

	void setCursorIcon(int isActive)
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.bVisible = isActive; //Ŀ���� active 1�̸� ���� 0�̸� �Ⱥ��� 
		cursorInfo.dwSize = 1; //Ŀ���� ������
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); //Ŀ�� ������ �����Ѵ�. 
	}

	void SetColor(unsigned short backgroundColor, unsigned short textColor) //��µ� ������ ��׶��� �÷�, �ؽ�Ʈ �÷��� �����Ѵ�.
	{
		unsigned short color = textColor;
		color = color + (backgroundColor << 4); //color ������ �ؽ�Ʈ �÷� ����, ��׶��� �÷����� ����
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}

	void ClearBuffer() //���� 
	{
		int y = 0;
		while (y < screenHeight + 2) // y���� �̿��Ͽ� �� ���� ��ȸ�Ѵ�.
		{
			int x = 0;
			while (x < screenWidth + 2) //x���� �̿��Ͽ� �� ���� ��ȸ�Ѵ�.
			{
				if (y == 0 || y == (screenHeight + 1))	//��ũ���� ����(0), �ǾƷ�(screenHeight)�� ���� ��('-')���� �����Ѵ�.
					ScreenBuffer[x + (y * (screenWidth + 3))] = '-';
				else
				{
					if (x == 0 || x == (screenWidth + 1))	//��ũ���� �� ����(0), �� ������(screenWidth+1)�� ���� ��('l')���� �����Ѵ�.
						ScreenBuffer[x + (y * (screenWidth + 3))] = '|';
					else
						ScreenBuffer[x + (y * (screenWidth + 3))] = ' '; //�������� �������� ä���.
				}
				x = x + 1;
			}
			ScreenBuffer[x + (y * (screenWidth + 3))] = '\n'; //�� ���� ������ ���๮�ڸ� �����Ѵ�.
			y = y + 1;
		}
		ScreenBuffer[(y * (screenWidth + 3))] = '\0';
	}

