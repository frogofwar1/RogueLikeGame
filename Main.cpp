
#include "pch.h"
#include <iostream>

#include <map>
#include "CWGame.hpp"


int main()
{
	CWGame game("map.txt");

	while (true)
	{
		game.update();
	}

	//getchar();
}
