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
	printLevels();
	//std::cout << std::endl << std::endl;
//	sortLevels();
	//printLevels();
}

void Game::printLevels()
{
	vector<Maze> ::iterator iter;
	iter = levels.begin();

	while (iter != levels.end())
	{
		//(*iter).printMaze();
		(*iter).print();
		++iter;
	}
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
	{
		return false;
	}

	file_name>> y_size;

	MAZE temp;
	char cell_value;
	std::string curr_row;

	std::getline(file_name, curr_row);
	for (unsigned row_index = 0; row_index < x_size; ++row_index)
	{
		std::getline(file_name, curr_row);
		setRow(temp, curr_row, row_index);
	}

	file_name >> monsters;
	Maze temp_maze(temp, x_size, y_size, monsters);

	if (temp_maze.validMazeCheck())
		levels.push_back(temp_maze);

	std::getline(file_name, curr_row);

	return true;
}

void Game::setRow(MAZE& maze, std::string row, int row_index)const
{
	std::vector<Position> curr_row;
	for (unsigned col_index = 0; col_index < row.length(); ++col_index)
	{
		setCell(curr_row, row[col_index], row_index, col_index);
	}
	maze.push_back(curr_row);
}

void Game::setCell(std::vector<Position>& curr_row, const char cell_value, int row_index, int col_index)const
{
	if (cell_value == '.')
	{
		curr_row.push_back(Position(nullptr, nullptr, EMPTY, Coordinates(row_index, col_index), '.'));
	}
	else if (cell_value == '#')
	{
		curr_row.push_back(Position(nullptr, nullptr, BLOCKED, Coordinates(row_index, col_index), '#'));
	}
	else
	{
		curr_row.push_back(Position(nullptr, nullptr, UNDEFINED, Coordinates(row_index, col_index), '/'));
	}
}

void Game::sortLevels()
{
	/*
	int low = 0;
	int high = levels.size();
	quickSort(low,high-1);
	*/
	bubbleSort();
}
void Game::bubbleSort()
{
	int size = levels.size();

	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = i; j < size - i - 1; ++j)
		{
			if (levels[j+1] < levels[j])
			{
				std::swap(levels[j + 1], levels[j]);
			}
		}
	}
}
/*
void Game::quickSort(int low, int high)
{
	if (low < high)
	{
		int pivot = partition(low, high);
		quickSort(low, pivot - 1);
		quickSort(pivot + 1, high);
	}
}


int Game::partition(int low, int high)const
{
	Maze pivot = levels[high];
	int smallest_indx = low - 1;

	for (int iter = low; iter <= high - 1; ++iter)
	{
		if (levels[iter] < pivot)
		{
			++smallest_indx;
			std::swap(levels[smallest_indx],levels[iter]);
		}
	}
	std::swap(levels[smallest_indx + 1], levels[high]);
	return (smallest_indx + 1);
}
*/

//interface funcs. /.../
void Game::printRaceOptions()const
{
	/*for(RACE_CHOICE i = ENCHANTER; i < RACE_COUNTER; ++i)
	{
	}
	*/
	std::cout << "->ENCHANTER\n" << "->MAGUS\n";


}
