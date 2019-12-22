#include "Game.h"

Game::Game() :
	race_choice(INVALID),
	levels()
{}

//public:

void Game::initGame()
{
	initRace();
}

//private:

void Game::initRace()
{
	std::string choice;
	while (true)
	{
		std::cout << "		--Choose your race--\n";
		printRaceOptions();
		std::cout << "Your chooice: ";
		if (!validRaceChoice(choice))
		{
			std::cout << "Invalid choice, please try again.\n";
		}
		else
		{
			break;
		}
	}	
	setRace(choice);
}

void Game::setRace(const std::string race_input)
{
	
	if (!race_input.compare("ENCHANTER") || !race_input.compare("enchanter"))
	{
		race_choice = ENCHANTER;
	}
	else if (!race_input.compare("MAGUS") || !race_input.compare("magus"))
	{
		race_choice = MAGUS;
	}
	
}

bool Game::validRaceChoice(const std::string choice)const
{
	return (!choice.compare("ENCHANTER") || !choice.compare("enchanter") || !choice.compare("MAGUS") || !choice.compare("magus"));
}

void Game::initLevels()
{
	std::ifstream levels_file;
	levels_file.open(MAZE_FILE);
	if (!levels_file)
	{
		std::cerr << "Error while openning mazeFile.txt\n";
		exit(0);
	}
	while (!levels_file.eof())
	{
		readMaze(levels_file);
	}
	levels_file.close();
}

void Game::readMaze(std::ifstream& file_name)
{
	MAZE temp;
	char cell_value;
	int x_size, y_size, monsters;
	file_name >> x_size >> y_size;
	for (int row = 0; row < x_size; ++row)
	{
		for (int col = 0; col < y_size; ++col)
		{
			file_name >> cell_value;
			setCell(temp, cell_value, row, col); //position instead of coords??
		}
	}
	file_name >> monsters;
	Maze temp_maze(temp, x_size, y_size, monsters);
	if (temp_maze.validMazeCheck())
	{
		levels.push_back(temp_maze);
	}
}

void Game::setCell(MAZE& maze, char cell_value, int row, int col)const
{
	if (cell_value == '.')
	{
		maze[row][col] = Position(nullptr, nullptr,EMPTY);
	}
	else if (cell_value == '#')
	{
		maze[row][col] = Position(nullptr, nullptr, BLOCKED);
	}
	else
	{
		maze[row][col] = Position(nullptr, nullptr, UNDEFINED);
	}
}



void Game::printRaceOptions()const
{
	/*for(RACE_CHOICE i = ENCHANTER; i < RACE_COUNTER; ++i)
	{
	}
	*/
	std::cout << "->ENCHANTER\n" << "->MAGUS\n";


}
