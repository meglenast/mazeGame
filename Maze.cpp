#include "Maze.h"

int DX[] = {-1,0,0,1};
int DY[] = {0,-1,1,0};

Maze::Maze() :
	x_size(0),
	y_size(0),
	monsters(0),
	race_choice(INVALID),
	free_cells(0),
	character_pos(&field[0][0])
{}
Maze::Maze(const MAZE& maze, int x_size, int y_size, int monsters):
	field(maze),
	x_size(x_size),
	y_size(y_size),
	monsters(monsters),
	race_choice(INVALID),
	free_cells(0),
	character_pos(&field[0][0])
{}
Maze::Maze(const Maze& other) :
	field(other.field),
	x_size(other.x_size),
	y_size(other.y_size),
	monsters(other.monsters),
	race_choice(other.race_choice),
	free_cells(other.free_cells),
	character_pos(other.character_pos)
{}
Maze& Maze::operator=(const Maze& other)
{
	if (this != &other)
	{
		field = other.field;
		x_size = other.x_size;
		y_size = other.y_size;
		monsters = other.monsters;
		race_choice = other.race_choice;
		free_cells = other.free_cells;
		character_pos = other.character_pos;
	}
	return *this;
}

//public:

void Maze::startLevel(RACE_CHOICE race_choice)
{
	setStartAndPortal();
	setCharacterCell(race_choice);
	print();
	blockCells();
	spawnMonsters();
	print();
	startGame();
}

void Maze::startGame()
{
	//generatePathEnchanter();
	moveMonsters();
	moveMonsters();
	moveMonsters();
	moveMonsters();
	moveMonsters();
	moveMonsters();
}

bool Maze::validMazeCheck()const
{
	if (field[0][0].getPositionType() == BLOCKED || field[x_size - 1][y_size - 1].getPositionType() == BLOCKED)
		return false;
	if (!BFS())
		return false;
	return true;
}

void Maze::setFreeCells(unsigned free_cells)
{
	this->free_cells = (free_cells - 2 - monsters);
}

void Maze::setCharacterCell(RACE_CHOICE choice)
{
	field[0][0].setCharacter(choice);
}

void Maze::printMaze()const
{
	std::cout << "Size :" << x_size << " " << y_size << "\n";
	for (size_t row_index = 0; row_index < x_size; ++row_index)
	{
		for (size_t col_index = 0; col_index < y_size; ++col_index)
		{
			std::cout << field[row_index][col_index].getPositionType();
		}
		std::cout << std::endl;
	}
	std::cout << "Monsters: "<<monsters<<"\n";
}

void Maze::print()const
{
	//printTitel();
	for (unsigned row_index = 0; row_index < field.size(); ++row_index)
	{
		if (row_index % 2 == 0)
		{
			printExtraRow(WHITE_SQUARE, BLACK_SQUARE);
			printRow(row_index, WHITE_SQUARE, BLACK_SQUARE);
			printExtraRow(WHITE_SQUARE, BLACK_SQUARE);
		}
		else
		{
			printExtraRow(BLACK_SQUARE, WHITE_SQUARE);
			printRow(row_index, BLACK_SQUARE, WHITE_SQUARE);
			printExtraRow(BLACK_SQUARE, WHITE_SQUARE);
		}
	}

	std::cout << "Num of free cells: " << free_cells << std::endl;
}

void Maze::printExtraRow(char col1, char col2)const
{
	for (int col_index = 0; col_index < y_size; ++col_index)
	{
		if (col_index % 2 == 0)
		{
			std::cout << col1 << col1 << col1 << col1 << col1;
		}
		else
		{
			std::cout << col2 << col2 << col2 << col2<< col2;
		}
	}
	std::cout << std::endl;
}

void Maze::printRow(int row_index, char col1, char col2)const
{
	for (int col_index = 0; col_index < y_size; ++col_index)
	{
		if (col_index % 2 == 0)
		{
			std::cout << col1 << col1;
			printCell(field[row_index][col_index], col1);
			std::cout << col1 << col1;
		}
		else
		{
			std::cout << col2 << col2;
			printCell(field[row_index][col_index], col2);
			std::cout << col2 << col2;
		}
	}
	std::cout << std::endl;
}

void Maze::printCell(const Position& cell, char col)const
{
	 if (cell.occupiedByCharacter())
	{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 5);
	std::cout << 'X';
	SetConsoleTextAttribute(color, 7);
	return;
	}
	else if (cell.occupiedByMonster())
	{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 10);
	std::cout << 'M';
	SetConsoleTextAttribute(color, 7);
	return;
	}
	if (cell.getPositionType() == EMPTY)
	{
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 3); 
		std::cout << '.';
		SetConsoleTextAttribute(color, 7);
	}
	else if (cell.getPositionType() == BLOCKED || cell.getPositionType() == BLOCKED_BY_USER)
	{
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 3);
		std::cout << '#';
		SetConsoleTextAttribute(color, 7);
	}
	else if(cell.getPositionType() == PORTAL)
	{
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 3);
		std::cout << '@';
		SetConsoleTextAttribute(color, 7);
	}
}

bool Maze::operator<(const Maze& other)const
{
	int this_size = (x_size * y_size);
	int other_size = other.getSize();
	if (this_size < other_size)
	{
		return true;
	}
	else if (this_size > other_size)
	{
		return false;
	}
	else
	{
		if (monsters < other.getMonsters())
		{
			return true;
		}
		return false;
	}
}

inline int Maze::getSize()const
{
	return (x_size * y_size);
}

inline int Maze::getMonsters()const
{
	return monsters;
}

bool Maze::BFS()const
{
	VISITED_MATRIX visited;
	if (!markedUnvisited(visited))
		return false;

	std::queue<Position> queue;

	queue.push(field[0][0]);

	while (!queue.empty())
	{
		Position curr = queue.front();

		if (curr.getCoordinates().getX() == x_size - 1 && curr.getCoordinates().getY() == y_size - 1)
			return true;

		queue.pop();

		for (int direction = 0; direction < DIRECTIONS; ++direction)
		{
			int new_xCoord = curr.getCoordinates().getX() + DX[direction];
			int new_yCoord = curr.getCoordinates().getY() + DY[direction];

			if (validCellCheck(new_xCoord, new_yCoord) && !visited[new_xCoord][new_yCoord] && (field[new_xCoord][new_yCoord].getPositionType()==EMPTY || field[new_xCoord][new_yCoord].getPositionType() == PORTAL))//??
			{
				visited[new_xCoord][new_yCoord] = true;
				Position adj_cell(field[new_xCoord][new_yCoord]);
				queue.push(adj_cell);
			}
		}
	}
	return false;
}

bool Maze::validCellCheck(int new_xCoord, int new_yCoord)const
{
	return ((new_xCoord >= 0) && (new_xCoord < x_size) && (new_yCoord >= 0) && (new_yCoord < y_size));
}

bool Maze::markedUnvisited(VISITED_MATRIX& visited)const
{
	for (int row_index = 0; row_index < x_size; ++row_index)
	{
		vector<bool> curr_row;
		for (int col_index = 0; col_index < y_size; ++col_index)
		{
			if (field[row_index][col_index].getPositionType() != EMPTY || field[row_index][col_index].getPositionType() == PORTAL || field[row_index][col_index].getPositionType() == START)
			{
				if (field[row_index][col_index].getPositionType() == BLOCKED || field[row_index][col_index].getPositionType() == BLOCKED_BY_USER)
				{
					curr_row.push_back(true);
				}
				else if (field[row_index][col_index].getPositionType() == UNDEFINED)
				{
					return false;
				}
			}
			curr_row.push_back(false);
			if (col_index == y_size - 1)
			{
				visited.push_back(curr_row);
			}	
		}
	}
	visited[0][0] = true;
	return true;
}

void Maze::setStartAndPortal()
{
	field[0][0].setPositionType(START);
	field[x_size-1][y_size-1].setPositionType(PORTAL);
}

void Maze::blockCells()
{
	while (true)
	{
		unsigned cell_to_block = 0;
		chooseNumCellsToBlock(cell_to_block);
		chooseWhichCellsToBlock(cell_to_block);
		if (validMazeCheck())
		{
			break;
		}
		else
		{
			std::cout << "Invalid maze, try again blocking different cells.\n";
			restartLevel();
		}
	}
}

void Maze::chooseNumCellsToBlock(unsigned& cells_to_block)
{
	if (free_cells == 0)
	{
		std::cout << "There are none free cells to be blocked.\n";
		return;
	}
	while (true)
	{
		std::cout << "Choose number of cells to block in this range : [ 0 : " << free_cells << " ]\n";
		std::cout << "Your choice: ";
		std::cin >> cells_to_block;
		if (cells_to_block == 0) break;
		if (validCellsToBlock(cells_to_block))
		{
			std::cout << "\n";
			break;
		}
		std::cout << "Invalid choice, please try again.\n";
	}
}

bool Maze::validCellsToBlock(unsigned cells_to_block)const
{
	return (cells_to_block >= 0 && cells_to_block <= free_cells);
}

void Maze::chooseWhichCellsToBlock(unsigned num_cells)
{
	for (int i = 0; i < num_cells; ++i)
	{
		blockCell();
	}
}

bool Maze::alreadyBlocked(int x_coord, int y_coord)const
{
	return (field[x_coord][y_coord].isBlocked() || (x_coord == x_size - 1 && y_coord == y_size - 1) || (x_coord == 0 && y_coord == 0));
}

bool Maze::alreadyOccupied(int x_coord, int y_coord)const
{
	return field[x_coord][y_coord].occupiedByMonster();
}

bool Maze::validCoordinates(int x_coord, int y_coord)const
{
	if (!validCellCheck(x_coord, y_coord))
	{
		std::cout << "Invalid coordinates for this maze.\n";
		return false;
	}
	else if (field[x_coord][y_coord].getPositionType() == START)
	{
		std::cout << "Invalid coordinates, you can't block the starting cell of the level.\n";
		return false;
	}
	else if (field[x_coord][y_coord].getPositionType() == PORTAL)
	{
		std::cout << "Invalid coordinates, you can't block the portal to the next level.\n";
		return false;
	}
	else if (alreadyBlocked(x_coord, y_coord))
	{
		std::cout << "Invalid coordinates, the cell is already blocked.\n";
		return false;
	}
	else
		return true;
}

void Maze::blockCell()
{
	std::cout << "Enter the coordinates of the cells you want to block:\n";
	int x_coord, y_coord;
	while (true)
	{
		std::cout << "x coordinate: ";
		std::cin >> x_coord;
		std::cout << std::endl;
		std::cout << "y coordinate: ";
		std::cin >> y_coord;
		std::cout << std::endl;
		if (validCoordinates(x_coord, y_coord))
		{
			field[x_coord][y_coord].setPositionType(BLOCKED_BY_USER);
			break;
		}
	}
}

void Maze::restartLevel()
{
	for (unsigned row_index = 0; row_index < x_size; ++row_index)
	{
		for (unsigned col_index = 0; col_index < y_size; ++col_index)
		{
			if (field[row_index][col_index].getPositionType() == BLOCKED_BY_USER)
			{
				field[row_index][col_index].setPositionType(EMPTY);
			}
		}
	}
}

void Maze::spawnMonsters()
{
	for (size_t curr_num = 0; curr_num < monsters; ++curr_num)
	{
		spawnMonster();
	}
}

void Maze::spawnMonster()
{
	while (true)
	{
		unsigned x_coord, y_coord;
		srand(time(NULL));
		x_coord = std::rand() % x_size;
		y_coord = std::rand() % x_size;

		if (canSpawn(x_coord, y_coord))
		{
			field[x_coord][y_coord].setMonster(x_coord,y_coord);
			addMonsterToList(x_coord, y_coord);
			break;
		}
		
	}
}

bool Maze::canSpawn(unsigned x_coord, unsigned y_coord)const
{
	if (field[x_coord][y_coord].getPositionType() == START)
		return false;
	else if (field[x_coord][y_coord].getPositionType() == PORTAL)
		return false;
	else if (field[x_coord][y_coord].getPositionType() == BLOCKED)
		return false;
	else if (field[x_coord][y_coord].getPositionType() == BLOCKED_BY_USER)
		return false;
	else if (field[x_coord][y_coord].occupiedByMonster() == TRUE)
		return false;
	return true;
}

void Maze::addMonsterToList(int x_coord, int y_coord)
{
	monsters_list.push_back(&field[x_coord][y_coord]);
}

void Maze::moveMonsters()
{
	for (int iter = 0; iter < monsters_list.size(); ++iter)
	{
		Coordinates init_coords(monsters_list[iter]->getMonster()->getCoordinates());
		Monster* curr_monster = monsters_list[iter]->getMonster();
		while (true)
		{
			int curr_xCoord = curr_monster->nextCoordinates().getX();
			int curr_yCoord = curr_monster->nextCoordinates().getY();
			if(!validCellCheck(curr_xCoord, curr_yCoord) || alreadyBlocked(curr_xCoord, curr_yCoord) || alreadyOccupied(curr_xCoord, curr_yCoord))
			{
				curr_monster->changeDirection();
			}
			else
			{
				curr_monster->changeCoordinates(curr_xCoord, curr_yCoord);
				moveMonster(init_coords.getX(), init_coords.getY(), curr_xCoord, curr_yCoord);
				break;
			}
		}			
	}
	print();
}

void Maze::changeMonsterList(int old_x, int old_y, int new_x, int new_y)
{
	for (size_t i = 0; i < monsters_list.size(); ++i)
	{
		int curr_x = monsters_list[i]->getCoordinates().getX();
		int curr_y = monsters_list[i]->getCoordinates().getY();

		if (curr_x == old_x && curr_y == old_y)
		{
			monsters_list[i] = &field[new_x][new_y];
		}
	}
}

void Maze::moveMonster(int old_x, int old_y, int new_x , int new_y)
{
	field[new_x][new_y].setMonsterByReference(field[old_x][old_y].getMonsterByReference());
	field[old_x][old_y].removeMonster();
	changeMonsterList(old_x, old_y, new_x, new_y);
}
/*
void Maze::BFS(std::queue<Coordinates>& mem_path)const
{
	VISITED_MATRIX visited;
	markedUnvisited(visited);

	std::queue<Position> queue;

	queue.push(field[0][0]);

	while (!queue.empty())
	{
		Position curr = queue.front();
		int curr_x = curr.getCoordinates().getX();
		int curr_y = curr.getCoordinates().getY();
		if (curr_x == x_size - 1 && curr_y == y_size - 1)
			mem_path.push(Coordinates(curr_x, curr_y));

		queue.pop();

		for (int direction = 0; direction < DIRECTIONS; ++direction)
		{
			int new_xCoord = curr.getCoordinates().getX() + DX[direction];
			int new_yCoord = curr.getCoordinates().getY() + DY[direction];

			if (validCellCheck(new_xCoord, new_yCoord) && !visited[new_xCoord][new_yCoord] && (field[new_xCoord][new_yCoord].getPositionType() == EMPTY || field[new_xCoord][new_yCoord].getPositionType() == PORTAL))//??
			{
				visited[new_xCoord][new_yCoord] = true;
				mem_path.push(Coordinates(new_xCoord, new_yCoord));
				Position adj_cell(field[new_xCoord][new_yCoord]);
				queue.push(adj_cell);
			}
		}
	}
}
*/
/*
void Maze::generatePathEnchanter()const
{
	//std::queue<Coordinates> mem_path;
	//BFS(mem_path);
	//printQ(mem_path);
	buildGraph();
}
*/
/*
void Maze::buildGraph()const
{
	unsigned size = ((x_size - 1) * y_size) + ((y_size - 1) * x_size);
	Graph mazeGraph(size);

	for (unsigned row_index = 0; row_index < x_size; ++row_index)
	{
		for (unsigned col_index = 0; col_index < y_size; ++col_index)
		{
			if (row_index != x_size - 1)
			{
				mazeGraph.addEdge(field[row_index][col_index], field[row_index][col_index + 1]);

			
			}
		}
	}
}
*/
/*
void Maze::printQ(std::queue<Coordinates>& queue)const
{
	while (!queue.empty())
	{
		std::cout << queue.front().getX() << " " << queue.front().getY() << std::endl;
		queue.pop();
	}
}
*/