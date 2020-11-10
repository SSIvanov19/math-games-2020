#include<iostream>
#include<conio.h>
#include<cstdlib>
using namespace std;

//Setting
//1 = coordinate
//0 = WASD
bool movementType = true;

void printMenu(bool firstActive, bool secondActive, bool thirdActive, bool fourthActive);
void printSettings(bool firstActive, bool secondActive);

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

void printBoard(bool isGame)
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

	if (isGame)
	{
		if (movementType)
		{
		     cout << "Type coordinate: ";
			 char ch;
			 cin >> ch;
		}
		else
		{
			cout << "Move with WASD";
			char ch;
			cin >> ch;
		}
	}
}

void printMenu(bool firstActive, bool secondActive, bool thirdActive, bool fourthActive)
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

	cout << endl;
	cout << endl;
	
	cout << " "; if (firstActive)  cout << "-> ";  else cout << "   "; cout << "New Game " << endl;
	cout << " "; if (secondActive)  cout << "-> ";  else cout << "   "; cout << "Resume Game" << endl;
	cout << " "; if (thirdActive)  cout << "-> ";  else cout << "   "; cout << "Settings" << endl;
	cout << " "; if (fourthActive)  cout << "-> ";  else cout << "   "; cout << "Exit" << endl;

	const char ch = _getch();
	
	if (ch == 's' || ch == 'S')
	{
		if (firstActive)
		{
			printMenu(false, true, false, false);
		}

		if (secondActive)
		{
			printMenu(false, false, true, false);
		}

		if (thirdActive)
		{
			printMenu(false, false, false, true);
		}

		if (fourthActive)
		{
			printMenu(true, false, false, false);
		}
	}

	if (ch == 'w' || ch == 'W')
	{
		if (firstActive)
		{
			printMenu(false, false, false, true);
		}

		if (secondActive)
		{
			printMenu(true, false, false, false);
		}

		if (thirdActive)
		{
			printMenu(false, true, false, false);
		}

		if (fourthActive)
		{
			printMenu(false, false, true, false);
		}
	}

	if (ch == '\r')
	{
		if (firstActive)
		{
			printBoard(true);
		}

		if (secondActive)
		{
			printBoard(true);
		}

		if (thirdActive)
		{
			printSettings(true, false);
		}

		if (fourthActive)
		{
			exit(3);
		}

	}
}

void printSettings(bool firstActive, bool secondActive)
{
	system("CLS");
	 
	cout << "    ===========================================================" << endl;
	cout << "       _____ ______ _______ _______ _____ _   _  _____  _____" << endl;
	cout << "      / ____| ____ |__   __|__   __|_   _| \\ | |/ ____|/ ____|" << endl;
	cout << "     | (___ | |__     | |     | |    | | |  \\| | |  __| (___" << endl;
	cout << R"(      \___ \|  __|    | |     | |    | | | . ` | | |_ |\___ \)" << endl;
	cout << "      ____) | |____   | |     | |   _| |_| |\\  | |__| |____) |" << endl;
	cout << "     |_____/|______|  |_|     |_|  |_____|_| \\_|\\_____|_____/" << endl;
	cout << endl;
	cout << "    ===========================================================" << endl;

	cout << " "; if (firstActive)  cout << "-> ";  else cout << "   "; cout << "Movement type: "; if (movementType)  cout << "Coordinates";  else cout << "Keyboard"; cout << endl;
	cout << " "; if (secondActive)  cout << "-> ";  else cout << "   "; cout << "Back" << endl;

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
			printMenu(true, false, false, false);
		}

	}
}

void newGame()
{
	//Select one ot two players
}

int main()
{
	char board[8][8];

	//1 = white
	//0 = black
	bool turn = true;

	while (true)
	{
		printMenu(true, false, false, false);
	}
}