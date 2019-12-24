#include "Game.h"

const char* MAZE_FILE = "mazeFile.txt";

Game::Game() :
	race_choice(INVALID),
	levels()
{}

//public:

void Game::initGame()
{
	initLevels();
	sortLevels();
	initRace();
	startGame();
}

void Game::printLevels()
{
	vector<Maze> ::iterator iter;
	iter = levels.begin();

	while (iter != levels.end())
	{
		(*iter).print();
		++iter;
	}
}

//private:

void Game::startGame()
{
	for (unsigned levels_cnt = 0; levels_cnt < levels.size(); ++levels_cnt)
	{
		levels[levels_cnt].setCharacterCell(race_choice.getRace());
		levels[levels_cnt].startLevel();
	}
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
	unsigned free_cells_cnt = 0;

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
		setRow(temp, curr_row, row_index, free_cells_cnt);
	}

	file_name >> monsters;
	Maze temp_maze(temp, x_size, y_size, monsters);

	if (temp_maze.validMazeCheck())
	{
		temp_maze.setFreeCells(free_cells_cnt);
		levels.push_back(temp_maze);
	}

	std::getline(file_name, curr_row);

	return true;
}

void Game::setRow(MAZE& maze, std::string row, int row_index, unsigned& free_cells_cnt)const
{
	std::vector<Position> curr_row;
	for (unsigned col_index = 0; col_index < row.length(); ++col_index)
	{
		setCell(curr_row, row[col_index], row_index, col_index, free_cells_cnt);
	}
	maze.push_back(curr_row);
}

void Game::setCell(std::vector<Position>& curr_row, const char cell_value, int row_index, int col_index, unsigned& free_cells_cnt)const
{
	if (cell_value == '.')
	{
		curr_row.push_back(Position(nullptr, nullptr, EMPTY, Coordinates(row_index, col_index), '.'));
		++free_cells_cnt;
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
	mergeSort(levels, 0, levels.size() - 1);
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

void Game::merge(vector<Maze>& array, int left, int mid, int right)
{
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::vector<Maze> leftArr, rightArr;

	for (int i = 0; i < n1; ++i)
	{
		leftArr.push_back(array[left + i]);
	}
	for (int j = 0; j < n2; ++j)
	{
		rightArr.push_back(array[mid + 1 + j]);
	}
	i = j = 0;
	k = left;

	while (i < n1 && j < n2)
	{
		if (leftArr[i] < rightArr[j])
		{
			array[k] = leftArr[i];
			++i;
		}
		else
		{
			array[k] = rightArr[j];
			++j;
		}
		++k;
	}
	while (i < n1)
	{
		array[k] = leftArr[i];
		++i;
		++k;
	}
	while (j < n2)
	{
		array[k] = rightArr[j];
		++j;
		++k;
	}
}

void Game::mergeSort(vector<Maze>& array, int left, int right)
{
	if (left < right)
	{
		int mid = left+(right-1)/2;
		mergeSort(array, left, mid);
		mergeSort(array, mid + 1, right);
		merge(array, left, mid, right);
	}
}

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

void Game::printRaceOptions()const
{
	std::cout << "		__RACE CHOICES:__\n";
	std::cout << "-ENCHANTER\n-MAGUS\n";
}