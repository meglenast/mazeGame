#include "Maze.h"

Maze::Maze() :
	x_size(0),
	y_size(0),
	monsters(0),
	race_choice(INVALID),
	free_cells(0),
	character_pos(&field[0][0]),
	movingPath(nullptr)
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

bool Maze::startLevel(RACE_CHOICE race_choice)
{
	setStartAndPortal();
	setCharacterCell(race_choice);
	print();
	blockCells();



	//here
	pressAnyKeyToContinue();
	clearConsole();
	
	spawnMonsters();
	print();

	//here
	pressAnyKeyToContinue();
	clearConsole();


	return startGame();
}

bool Maze::startGame()
{
	if (race_choice == MAGUS)
	{
		generateMagusPath();
	}
	else if (race_choice == ENCHANTER)
	{
		generateEnchanterPath();
	}
	while (true)
	{
		moveCharacter();
		moveMonsters();
		
		//here
		pressAnyKeyToContinue();
		clearConsole();


		if (haveReachedPortal())
		{
			print();
			return true;
		}
		if (killedByMonster())
		{
			printTitel();
			printGameOver();
			print();
			return false;
		}
		//print();
	}
}

bool Maze::haveReachedPortal()const
{
	return (character_pos->getCoordinates().getX() == x_size - 1 && character_pos->getCoordinates().getY() == y_size - 1);
}

bool Maze::killedByMonster()const
{
	int character_xCoord = character_pos->getCoordinates().getX();
	int character_yCoord = character_pos->getCoordinates().getY();

	for (size_t monster_idx = 0; monster_idx < monsters_list.size(); ++monster_idx)
	{
		int monster_xCoord = monsters_list[monster_idx]->getCoordinates().getX();
		int monster_yCoord = monsters_list[monster_idx]->getCoordinates().getY();

		if (character_xCoord == monster_xCoord && character_yCoord == monster_yCoord)
			return true;
	}
	return false;
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
	race_choice = choice;
	field[0][0].setCharacter(choice);
	character_pos = &field[0][0];
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
	printTitel();
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
	/*
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
	*/
	for (int row_index = 0; row_index < x_size; ++row_index)
	{
		std::vector<bool> curr_row;
		for (int col_index = 0; col_index < y_size; ++col_index)
		{
			if (field[row_index][col_index].getPositionType() == UNDEFINED)
				return false;

			if (field[row_index][col_index].getPositionType() == BLOCKED || field[row_index][col_index].getPositionType() == BLOCKED_BY_USER)
			{
				curr_row.push_back(true);
			}
			else
			{
				curr_row.push_back(false);
			}
		}
		visited.push_back(curr_row);
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

bool Maze::isPortal(int x_coord, int y_coord)const
{
	return (x_coord == x_size - 1 && y_coord == y_size - 1);
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

//Moving character:

void Maze::moveCharacter()
{
	Coordinates old_coords = character_pos->getCoordinates();
	Coordinates new_coords = character_pos->getCharacterMove();
	field[new_coords.getX()][new_coords.getY()].setCharacterByReference(field[old_coords.getX()][old_coords.getY()].getCharacter());
	field[old_coords.getX()][old_coords.getY()].removeCharacter();
	character_pos = &field[new_coords.getX()][new_coords.getY()];
}

//Generating magus path: 
void Maze::generateMagusPath()
{
	movingPath = new std::queue<Coordinates>;
	DFS_iterative();
	character_pos->getCharacter().setMovingPath(movingPath);
}

void Maze::DFS_iterative()
{
	VISITED_MATRIX visited;
	markedUnvisited(visited);

	std::stack<Position> dfs_stack;
	dfs_stack.push(field[0][0]);		//pushing the sourse/starting cell on the bottom of the stack

	while (!dfs_stack.empty())
	{
		Position curr_top = dfs_stack.top();

		int curr_xCoord = curr_top.getCoordinates().getX();
		int curr_yCoord = curr_top.getCoordinates().getY();

		dfs_stack.pop();

		movingPath->push(Coordinates(curr_xCoord, curr_yCoord));

		if (curr_xCoord == x_size - 1 && curr_yCoord == y_size - 1)
		{
			movingPath->pop();		//popping the fist cell, where the magus is initiated by default
			break;
		}

		if (validCellCheck(curr_xCoord - ONE_STEP, curr_yCoord) && visited[curr_xCoord - ONE_STEP][curr_yCoord] == false) // check for unvisited adjesent cell upwards
		{
			dfs_stack.push(field[curr_xCoord - ONE_STEP][curr_yCoord]);
			visited[curr_xCoord - ONE_STEP][curr_yCoord] = true;
		}
		if (validCellCheck(curr_xCoord, curr_yCoord - ONE_STEP) && visited[curr_xCoord][curr_yCoord - ONE_STEP] == false) // check for unvisited adjecent cell on the left
		{
			dfs_stack.push(field[curr_xCoord][curr_yCoord - ONE_STEP]);
			visited[curr_xCoord][curr_yCoord - ONE_STEP] = true;
		}
		if (validCellCheck(curr_xCoord + ONE_STEP, curr_yCoord) && visited[curr_xCoord + ONE_STEP][curr_yCoord] == false) // check for unvisited adjecent cell downwards
		{
			dfs_stack.push(field[curr_xCoord + ONE_STEP][curr_yCoord]);
			visited[curr_xCoord + ONE_STEP][curr_yCoord] = true;
		}
		if (validCellCheck(curr_xCoord, curr_yCoord + ONE_STEP) && visited[curr_xCoord][curr_yCoord + ONE_STEP] == false) // check for unvisited adjecent cell on the right
		{
			dfs_stack.push(field[curr_xCoord][curr_yCoord + ONE_STEP]);
			visited[curr_xCoord][curr_yCoord + ONE_STEP] = true;
		}
	}
}

//Generating Enchanter's path:

void Maze::generateEnchanterPath()
{
	movingPath = new std::queue < Coordinates>;
	aStarAlgorithm();
	character_pos->getCharacter().setMovingPath(movingPath);
}

void Maze::aStarAlgorithm()
{
	VISITED_MATRIX closedList;
	markedUnvisited(closedList);

	POSITIONS_INFO posInfo;
	initPositionInfo(posInfo);
	
	std::set<Asoc_pair_dist> openList;
	openList.insert(Asoc_pair_dist(0.0, Coordinates(0, 0)));

	bool reached = false;

	while (!openList.empty())
	{
		Asoc_pair_dist curr_position = *openList.begin();

		openList.erase(openList.begin());

		unsigned  x_coord = curr_position.coords.getX();
		unsigned  y_coord = curr_position.coords.getY();

		closedList[x_coord][y_coord] = true;

		double new_gDist, new_hDist, new_fDist;

		if (validCellCheck(x_coord - 1, y_coord))		//upwards check
		{
			if (isPortal(x_coord - 1, y_coord))
			{
				posInfo[x_coord - 1][y_coord].adjecent_xCoord = x_coord;
				posInfo[x_coord - 1][y_coord].adjecent_yCoord = y_coord;

				pathTracing(posInfo);

				reached = true;
				return;
			}
			else if (closedList[x_coord - 1][y_coord] == false && field[x_coord - 1][y_coord].isBlocked() == false)
			{
				new_gDist = posInfo[x_coord][y_coord].g_distance + 1.0;
				new_hDist = calcHdist(x_coord - 1, y_coord);
				new_fDist = new_gDist + new_hDist;

				if (posInfo[x_coord - 1][y_coord].f_distance == FLT_MAX || posInfo[x_coord - 1][y_coord].f_distance > new_fDist)
				{
					openList.insert(Asoc_pair_dist(new_fDist, Coordinates(x_coord - 1, y_coord)));

					posInfo[x_coord - 1][y_coord].setInfo(new_fDist, new_gDist, new_hDist, x_coord, y_coord);
				}
			}
		}

		///

		if (validCellCheck(x_coord + 1, y_coord))	
		{
			if (isPortal(x_coord + 1, y_coord))
			{
				posInfo[x_coord + 1][y_coord].adjecent_xCoord = x_coord;
				posInfo[x_coord + 1][y_coord].adjecent_yCoord = y_coord;

				pathTracing(posInfo);

				reached = true;
				return;
			}
			else if (closedList[x_coord + 1][y_coord] == false && field[x_coord + 1][y_coord].isBlocked() == false)
			{
				new_gDist = posInfo[x_coord][y_coord].g_distance + 1.0;
				new_hDist = calcHdist(x_coord + 1, y_coord);
				new_fDist = new_gDist + new_hDist;

				if (posInfo[x_coord + 1][y_coord].f_distance == FLT_MAX || posInfo[x_coord + 1][y_coord].f_distance > new_fDist)
				{
					openList.insert(Asoc_pair_dist(new_fDist, Coordinates(x_coord + 1, y_coord)));

					posInfo[x_coord + 1][y_coord].setInfo(new_fDist, new_gDist, new_hDist, x_coord, y_coord);
				}
			}
		}

		///

		if (validCellCheck(x_coord, y_coord + 1))		//on the right check
		{
			if (isPortal(x_coord, y_coord + 1))
			{
				posInfo[x_coord][y_coord + 1].adjecent_xCoord = x_coord;
				posInfo[x_coord][y_coord + 1].adjecent_yCoord = y_coord;

				pathTracing(posInfo);

				reached = true;
				return;
			}
			else if (closedList[x_coord][y_coord + 1] == false && field[x_coord][y_coord + 1].isBlocked() == false)
			{
				new_gDist = posInfo[x_coord][y_coord].g_distance + 1.0;
				new_hDist = calcHdist(x_coord, y_coord + 1);
				new_fDist = new_gDist + new_hDist;

				if (posInfo[x_coord][y_coord + 1].f_distance == FLT_MAX || posInfo[x_coord][y_coord + 1].f_distance > new_fDist)
				{
					openList.insert(Asoc_pair_dist(new_fDist, Coordinates(x_coord, y_coord + 1)));

					posInfo[x_coord][y_coord + 1].setInfo(new_fDist, new_gDist, new_hDist, x_coord, y_coord);
				}
			}
		}

		//

		if (validCellCheck(x_coord, y_coord - 1))		//on the left check
		{
			if (isPortal(x_coord, y_coord - 1))
			{
				posInfo[x_coord][y_coord - 1].adjecent_xCoord = x_coord;
				posInfo[x_coord][y_coord - 1].adjecent_yCoord = y_coord;

				pathTracing(posInfo);

				reached = true;
				return;
			}
			else if (closedList[x_coord][y_coord - 1] == false && field[x_coord][y_coord-1].isBlocked() == false)//&&unblocked
			{
				new_gDist = posInfo[x_coord][y_coord].g_distance + 1.0;
				new_hDist = calcHdist(x_coord, y_coord - 1);
				new_fDist = new_gDist + new_hDist;

				if (posInfo[x_coord][y_coord - 1].f_distance == FLT_MAX || posInfo[x_coord][y_coord - 1].f_distance > new_fDist)
				{
					openList.insert(Asoc_pair_dist(new_fDist, Coordinates(x_coord, y_coord - 1)));

					posInfo[x_coord][y_coord - 1].setInfo(new_fDist, new_gDist, new_hDist, x_coord, y_coord);
				}
			}

		}


	}
}

double Maze::calcHdist(int x_coord, int y_coord)const
{
	double x_dest = x_size - 1.0;
	double y_dest = y_size - 1.0;

	double dx = (double)x_coord - x_dest;//casts?
	double dy = (double)y_coord - y_dest;

	return ((double)sqrt((dx * dx) + (dy * dy)));
}

void Maze::initPositionInfo(POSITIONS_INFO& posInfo)const
{
	for (size_t row_index = 0; row_index < x_size; ++row_index)
	{
		std::vector<PositionInformation> curr_row;
		for (size_t col_index = 0; col_index < y_size; ++col_index)
		{
			curr_row.push_back(PositionInformation(FLT_MAX, FLT_MAX, FLT_MAX, -1, -1));
		}
		posInfo.push_back(curr_row);
	}
	posInfo[0][0].setInfo(0.0, 0.0, 0.0, 0, 0);		//initiating the distances for the source position
}

void Maze::pathTracing(const POSITIONS_INFO& posInfo)
{
	int curr_x = x_size - 1;
	int curr_y = y_size - 1;
	std::stack<Coordinates> path;
	while (!(posInfo[curr_x][curr_y].adjecent_xCoord == curr_x && posInfo[curr_x][curr_y].adjecent_yCoord == curr_y))
	{
		path.push(Coordinates(curr_x, curr_y));

		int next_x = posInfo[curr_x][curr_y].adjecent_xCoord;
		int next_y = posInfo[curr_x][curr_y].adjecent_yCoord;

		curr_x = next_x;
		curr_y = next_y;
	}

	while (!path.empty())
	{
		movingPath->push(path.top());
		path.pop();
	}
}