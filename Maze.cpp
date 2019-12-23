#include "Maze.h"

int DX[] = {-1,0,0,1};
int DY[] = {0,-1,1,0};

Maze::Maze():
	x_size(0),
	y_size(0),
	monsters(0)
{}
Maze::Maze(const MAZE& maze, int x_size, int y_size, int monsters):
	field(maze),
	x_size(x_size),
	y_size(y_size),
	monsters(monsters)
{}
Maze::Maze(const Maze& other) :
	field(other.field),
	x_size(other.x_size),
	y_size(other.y_size),
	monsters(other.monsters)
{}
Maze& Maze::operator=(const Maze& other)
{
	if (this != &other)
	{
		field = other.field;
		x_size = other.x_size;
		y_size = other.y_size;
		monsters = other.monsters;
	}
	return *this;
}

//public:

bool Maze::validMazeCheck()const
{
	if (field[0][0].getPositionType() == BLOCKED || field[x_size - 1][y_size - 1].getPositionType() == BLOCKED)
		return false;
	if (!BFS())
		return false;
	return true;
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

//privat:
/*void Maze::initField()
{

}*/

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

			if (validCellCheck(new_xCoord, new_yCoord) && !visited[new_xCoord][new_yCoord] && field[new_xCoord][new_yCoord].getPositionType()==EMPTY)//??
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
			if (field[row_index][col_index].getPositionType() != EMPTY)
			{
				if (field[row_index][col_index].getPositionType() == BLOCKED)
				{
					curr_row.push_back(true);
				}
				else
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