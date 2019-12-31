#include "Game.h"

#include <iostream>
int main()
{	

	while (true)
	{

		std::string command;

		printTitel();
		printMenu();

		std::cin >> command;

		if (!command.compare(std::string("newGame")))
		{
			Game game;
			game.initGame();
		}
		else if (!command.compare(std::string("quit")))
		{
			break;
		}
		else
		{
			std::cout << "Invalid input.\n";
			break;
		}
	}
	
	return 0;
}