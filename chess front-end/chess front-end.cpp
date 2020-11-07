#include<iostream>
#include<conio.h>
#include<cstdlib>
using namespace std;

//Setting
//1 = coordinate
//0 = WASD
bool movementType = true;


void printLine(int row)
{
	const char whiteSquare = 0xDB;
	const char blackSquare = 0xFF;

	if (row % 2 == 0)
	{
		for (int subRow = 1; subRow <= 3; subRow++)
		{
			for (int cells = 1; cells <= 4; cells++)
			{
				for (int subCells = 1; subCells <= 6; subCells++)
				{
					if (subCells == 3 && subRow == 2)
					{
						wcout << whiteSquare;
					}
					else
					{
						cout << whiteSquare;
					}
				}

				for (int subCells = 1; subCells <= 6; subCells++)
				{
					cout << blackSquare;
				}

			}
			if (subRow == 2)
			{
				cout << "   " << row;
			}

			cout << endl << " ";
		}
	}
	if (row % 2 != 0)
	{
		for (int subRow = 1; subRow <= 3; subRow++)
		{
			for (int cells = 1; cells <= 4; cells++)
			{
				for (int subCells = 1; subCells <= 6; subCells++)
				{
					cout << blackSquare;
				}

				for (int subCells = 1; subCells <= 6; subCells++)
				{
					cout << whiteSquare;
				}
			}
			if (subRow == 2)
			{
				cout << "   " << row;
			}

			cout << endl << " ";
		}
	}
}
void NewGame()
{
	//Select one ot two players
}

void startGame()
{
	//Connection with back-end
}

void printBoard(bool isMoveActive)
{
	system("CLS");
	cout << "    ======================================" << endl;
	cout << "      ______ _    _ ______  _____ _____" << endl;
	cout << "     /  ____| |  | |  ____|/ ____/ ____|" << endl;
	cout << "     | |    | |__| | |__  | (___| (____" << endl;
	cout << R"(     | |    |  __  |  __|  \____ \\___ \)" << endl;
	cout << "     | |____| |  | | |____  ____) |___) |" << endl;
	cout << "     \\______|_|  |_|______||_____/_____/" << endl;
	cout << endl;
	cout << "    ======================================" << endl;
	cout << "\n Current turn: WHITE";
	cout << "\n\n   A     B     C     D     E     F     G     H\n\n ";

	for (int row = 8; row >= 1; row--)
	{
		printLine(row);
	}

	if (!isMoveActive)
	{
		cout << "\n Commands: (N)ew Game   (R)esume Game   (S)etting   (E)xit " << endl;
		cout << " Type here: ";
	}
	else
	{
		if (movementType)
		{
		     cout << "Type coordinate: ";
		}
		else
		{
			cout << "Move with WASD";
		}

		startGame();
	}
}

void printSettings(bool firstActive, bool secondActive)
{
	system("CLS");
	 
	cout << "    ===========================================================" << endl;
	cout << "       _____ ______ _______ _______ _____ _   _  _____  _____" << endl;
	cout << "      / ____| ____ |__   __|__   __|_   _| \\ | |/ ____|/ ____|" << endl;
	cout << "     | (___ | |__     | |     | |    | | |  \\| | |  __| (___" << endl;
	cout << "      \\___ \\|  __|    | |     | |    | | | . ` | | |_ |\\___ \\" << endl;
	cout << "      ____) | |____   | |     | |   _| |_| |\\  | |__| |____) |" << endl;
	cout << "     |_____/|______|  |_|     |_|  |_____|_| \\_|\\_____|_____/" << endl;
	cout << endl;
	cout << "    ===========================================================" << endl;

	cout << " "; if (firstActive)  cout << ". ";  else cout << "  "; cout << "Movement type: "; if (movementType)  cout << "Coordinates";  else cout << "Keyboard"; cout << endl;
	cout << " "; if (secondActive)  cout << ". ";  else cout << "  "; cout << "Back" << endl;

	const char ch = _getch();
	
	if (ch == 's' || ch == 'S' || ch == 'w' || ch == 'W')
	{
		if (secondActive)
		{
			printSettings(true, false);
		}

		if (firstActive)
		{
			printSettings(false, true);
		}
	}

	if (ch == '\r')
	{
		if (firstActive)
		{
			//Change setting
			if (movementType)
			{
				movementType = false;
			}
			else
			{
				movementType = true;
			}
			
			printSettings(true, false);
		}
		
		if (secondActive)
		{
			//Back to menu
			printBoard(false);
		}

	}
}

void printMenu()
{
	const char ch = _getch();
	cout << endl << " ";

	if (ch == 'N' || ch == 'n')
	{
		cout << "New Game";
		//newGame();
	}
	else if (ch == 'R' || ch == 'r')
	{
		printBoard(true);
	}
	else if (ch == 'S' || ch == 's')
	{
		printSettings(true, false);
	}
	else if (ch == 'E' || ch == 'e')
	{
		exit(3);
	}
	else
	{
		cout << "Invalid command";
	}
}

int main()
{
	char board[8][8];

	//1 = white
	//0 = black
	bool turn = true;

	printBoard(false);

	while (true)
	{
		printMenu();
	}
}