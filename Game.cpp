#include "Game.h"

const char* MAZE_FILE = "mazeFile.txt";

Game::Game() :
	race_choice(INVALID),
	levels()
{}

//public:

void Game::initGame()
{
	initRace();
	initLevels();
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
		std::cin >> choice;
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
	while (levels_file)
	{
		if (!readMaze(levels_file))
		{
			break;
		}
	}
	
	levels_file.close();
}

bool Game::readMaze(std::ifstream& file_name)
{
	int x_size, y_size, monsters;
	file_name >> x_size;

	if (file_name.eof())	
		return false;

	file_name>> y_size;

	MAZE temp;
	char cell_value;
	std::string curr_row;

	std::getline(file_name, curr_row);
	for (unsigned row_index = 0; row_index < x_size; ++row_index)
	{
		std::getline(file_name, curr_row);
		setRow(temp, curr_row);
	}

	file_name >> monsters;
	Maze temp_maze(temp, x_size, y_size, monsters);

	if (temp_maze.validMazeCheck())
		levels.push_back(temp_maze);

	return true;
}

void Game::setRow(MAZE& maze, std::string row)const
{
	std::vector<Position> curr_row;
	for (unsigned elem_index = 0; elem_index < row.length(); ++elem_index)
	{
		setCell(curr_row, row[elem_index]);
	}
	maze.push_back(curr_row);
}

void Game::setCell(std::vector<Position>& curr_row, const char cell_value)const
{
	if (cell_value == '.')
	{
		curr_row.push_back(Position(nullptr, nullptr, EMPTY));
	}
	else if (cell_value == '#')
	{
		curr_row.push_back(Position(nullptr, nullptr, BLOCKED));
	}
	else
	{
		curr_row.push_back(Position(nullptr, nullptr, UNDEFINED));
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
