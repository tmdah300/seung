
	char ScreenBuffer[65536];

	void setScreenSize(int width, int height); //스크린 사이즈 
	void setCursorIcon(int isActive); //
	void setCursorPos(int x, int y); //커서 이동 
	void SetColor(unsigned short backgroundColor, unsigned short textColor);
	void ClearBuffer();
