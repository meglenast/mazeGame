#include "InterfaceFunctions.h"

void clearConsole()
{
	//#ifdef _WIN64
	std::system("cls");
	//#else
		//std::system("clear");
	//#endif
}

void pressAnyKeyToContinue()
{
	system("pause");
}

void printMapInformation()
{
	std::cout << "					 --MAP INFORMATION--\n";
	std::cout << "			        ==========================================" << std::endl << std::endl;

	std::cout << "					 -Hero: ";
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 12);
	std::cout << "X\n";
	SetConsoleTextAttribute(color, 7);

	std::cout << "					 -Monster: ";
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 2);
	std::cout << "M\n";
	SetConsoleTextAttribute(color, 7);

	std::cout << "					 -Hidrance: ";
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 3);
	std::cout << "#\n";
	SetConsoleTextAttribute(color, 7);

	std::cout << "					 -Blocked by player: ";
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 14);
	std::cout << "#\n";
	SetConsoleTextAttribute(color, 7);

	std::cout << "					 -Empty: ";
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 3);
	std::cout << ".\n";
	SetConsoleTextAttribute(color, 7);

	std::cout << "					 -Portal: ";
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 13);
	std::cout << "@\n";
	SetConsoleTextAttribute(color, 7);
}

void printTitel()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 2);
	std::cout << "		,--.   ,--.  ,---.  ,-------.,------.     ,----.     ,---.  ,--.   ,--.,------.\n";
	std::cout << "		|   `.'   | /  O  \ `--.   /  |  .---'    '  .-./    /  O  \ |   `.'    ||  .---' \n";
	std::cout << "		|  |'.'|  ||  .-.  |  /   /  |  `--,     |  | .---.|  .-.  ||  |'.'|  ||  `--, \n";
	std::cout << "		|  |   |  ||  | |  | /   `--.|  `---.    '  '--'  ||  | |  ||  |   |  ||  `---. \n";
	std::cout << "		`--   `--'`--' `--'`-------'`------'     `------' `--' `--'`--'   `--'`------' \n";
	std::cout << "	________________________________________________________________________________________________\n";
	std::cout << "	________________________________________Escape the maze_________________________________________\n";
	std::cout << "	________________________________________________________________________________________________\n";
	SetConsoleTextAttribute(color, 7);
}

void printWon()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 5);
	std::cout << "		,--.   ,--.,-----. ,--. ,--.,--.    ,--.   ,--.,------.    ,--.   ,--. ,-----. ,--.  ,--.\n";
	std::cout << "		 \\  `.'  /'  .-.  '|  | |  ||  |     \\  `.'  / |  .---'    |  |   |  |'  .-.  '|  ,'.|  |\n";
	std::cout << "		  '.    / |  | |  ||  | |  |`-'       \\     /  |  `--,     |  |.'.|  ||  | |  ||  |' '  |\n";
	std::cout << "		    |  |  '  '-'  ''  '-'  '           \\   /   |  `---.    |   ,'.   |'  '-'  '|  | `   |\n";
	std::cout << "		    `--'   `-----'  `-----'             `-'    `------'    '--'   '--' `-----' `--'  `--'\n";
	SetConsoleTextAttribute(color, 7);
}

void printGameOver()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 5);
	std::cout << "		 ,----.     ,---.  ,--.   ,--.,------.     ,-----.,--.   ,--.,------.,------.  \n";
	std::cout << "		'  .-./    /  O  \ |   `.'   ||  .---'    '  .-.  '\\  `.'  / |  .---'|  .--. ' \n";
	std::cout << "		|  | .---.|  .-.  ||  |'.'|  ||  `--,     |  | |  | \\     /  |  `--, |  '--'.' \n";
	std::cout << "		'  '--'  ||  | |  ||  |   |  ||  `---.    '  '-'  '  \\   /   |  `---.|  |\\  \\  \n";
	std::cout << "		 `------' `--' `--'`--'   `--'`------'     `-----'    `-'    `------'`--' '--' \n";
	SetConsoleTextAttribute(color, 7);
}

void printNextLevel()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 5);
	std::cout << "					| |___ _ _ ___| |___ _ _ ___ \n";
	std::cout << "					| | -_| | | -_| |___| | | . |\n";
	std::cout << "					|_|___|\\_/|___|_|   |___|  _|\n";
	std::cout << "					                        |_|  \n";
	std::cout << "					Teleporting to...\n";
	std::cout << "					\n";
	SetConsoleTextAttribute(color, 7);
}

void printMenu()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 2);
	std::cout << "				====================MENU==================" << std::endl;
	std::cout << std::endl << "						  * newGame " << std::endl << "						    *quit" << std::endl;
	std::cout << "			        ==========================================" << std::endl;
	SetConsoleTextAttribute(color, 7);
	std::cout << "					  Type command: ";
}

void printRaceOptions()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 2);
	std::cout << "	________________________________________________________________________________________________\n";
	std::cout << "					 --Choose your race--\n";
	std::cout << "			        ==========================================" << std::endl << std::endl;
	std::cout << "					 ==RACE CHOICES==\n\n";
	std::cout << "					 * ENCHANTER\n					 * MAGUS\n";
	std::cout << "			        ==========================================" << std::endl << std::endl;
	SetConsoleTextAttribute(color, 7);
}