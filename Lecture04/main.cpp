#include <iostream>
#include <stdio.h>
#include <conio.h>
int main()
{
	while(1)
	{
		if(_kbhit())
		{
			if(getch() == 27)break;
		}
		std::cout<<"*";
	}
	
	return 0;
}
