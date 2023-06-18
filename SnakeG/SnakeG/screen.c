#include "screen.h"
#include <Windows.h>

	int screenWidth;
	int screenHeight;

	void setScreenSize(int width, int height) //맵 사이즈
	{
		screenWidth = width;
		screenHeight = height;
	}

	void setCursorPos(int x, int y) //커서 위치(x, y) 지정
	{
		COORD pos = { x,y };											//GetStdHandle -> Window API 함수
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //STD_OUTPUT_HANDLE-> 콘솔창의 입출력에 사용되는 표준출력핸들. 
	}

	void setCursorIcon(int isActive)
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.bVisible = isActive; //커서의 active 1이면 보임 0이면 안보임 
		cursorInfo.dwSize = 1; //커서의 사이즈
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); //커서 정보를 적용한다. 
	}

	void SetColor(unsigned short backgroundColor, unsigned short textColor) //출력될 글자의 백그라운드 컬러, 텍스트 컬러를 변경한다.
	{
		unsigned short color = textColor;
		color = color + (backgroundColor << 4); //color 변수에 텍스트 컬러 값과, 백그라운드 컬러값을 저장
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}

	void ClearBuffer() //맵을 
	{
		int y = 0;
		while (y < screenHeight + 2) // y값을 이용하여 각 행을 순회한다.
		{
			int x = 0;
			while (x < screenWidth + 2) //x값을 이용하여 각 열을 순회한다.
			{
				if (y == 0 || y == (screenHeight + 1))	//스크린의 맨위(0), 맨아래(screenHeight)의 값에 벽('-')값을 저장한다.
					ScreenBuffer[x + (y * (screenWidth + 3))] = '-';
				else
				{
					if (x == 0 || x == (screenWidth + 1))	//스크린의 맨 왼쪽(0), 맨 오른쪽(screenWidth+1)의 값에 벽('l')값을 저장한다.
						ScreenBuffer[x + (y * (screenWidth + 3))] = '|';
					else
						ScreenBuffer[x + (y * (screenWidth + 3))] = ' '; //나머지는 공백으로 채운다.
				}
				x = x + 1;
			}
			ScreenBuffer[x + (y * (screenWidth + 3))] = '\n'; //한 행이 끝나면 개행문자를 저장한다.
			y = y + 1;
		}
		ScreenBuffer[(y * (screenWidth + 3))] = '\0';
	}

