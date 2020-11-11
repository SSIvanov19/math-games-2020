#include<iostream>
#include<conio.h>
#include<cstdlib>
using namespace std;

char board[8][8] =
{
	{'t', 'h', 'o', 'q', 'k', 'o', 'h', 't'},
	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
	{32, 32, 32, 32, 32, 32, 32, 32},
	{32, 32, 32, 32, 32, 32, 32, 32},
	{32, 32, 32, 32, 32, 32, 32, 32},
	{32, 32, 32, 32, 32, 32, 32, 32},
	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
	{'t', 'h', 'o', 'q', 'k', 'o', 'h', 't'}
};

//1 = white
//0 = black
bool turn = true;

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
					
					if (row == 8 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if(board[0][0] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[0][0];
						}
					}
					else if (row == 8 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[0][2] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[0][2];
						}
					}
					else if(row == 8 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[0][4] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[0][4];
						}
					}
					else if(row == 8 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[0][6] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[0][6];
						}
					}
					else if (row == 6 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[2][0] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[2][0];
						}
					}
					else if (row == 6 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[2][2] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[2][2];
						}
					}
					else if (row == 6 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[2][4] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[2][4];
						}
					}
					else if (row == 6 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[2][6] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[2][6];
						}
					}
					else if (row == 4 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[4][0] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[4][0];
						}
					}
					else if (row == 4 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[4][2] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[4][2];
						}
					}
					else if (row == 4 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[4][4] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[4][4];
						}
					}
					else if (row == 4 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[4][6] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[4][6];
						}
					}
					else if (row == 2 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[6][0] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[6][0];
						}
					}
					else if (row == 2 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[6][2] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[6][2];
						}
					}
					else if (row == 2 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[6][4] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[6][4];
						}
					}
					else if (row == 2 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[6][6] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[6][6];
						}
					}
					else
					{
						cout << whiteSquare;
					}
				}

				for (int subCells = 1; subCells <= 6; subCells++)
				{
					if (row == 8 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[0][1] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[0][1];
						}
					}
					else if (row == 8 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[0][3] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[0][3];
						}
					}
					else if (row == 8 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[0][5] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[0][5];
						}
					}
					else if (row == 8 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[0][7] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[0][7];
						}
					}
					else if(row == 6 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[2][1] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[2][1];
						}
					}
					else if (row == 6 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[2][3] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[2][3];
						}
					}
					else if (row == 6 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[2][5] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[2][5];
						}
					}
					else if (row == 6 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[2][7] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[2][7];
						}
					}
					else if (row == 4 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[4][1] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[4][1];
						}
					}
					else if (row == 4 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[4][3] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[4][3];
						}
					}
					else if (row == 4 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[4][5] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[4][5];
						}
					}
					else if (row == 4 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[4][7] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[4][7];
						}
					}
					else if (row == 2 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[6][1] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[6][1];
						}
					}
					else if (row == 2 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[6][3] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[6][3];
						}
					}
					else if (row == 2 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[6][5] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[6][5];
						}
					}
					else if (row == 2 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[6][7] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[6][7];
						}
					}
					else
					{
						cout << blackSquare;
					}
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
					if (row == 7 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[1][0] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[1][0];
						}
					}
					else if (row == 7 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[1][2] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[1][2];
						}
					}
					else if (row == 7 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[1][4] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[1][4];
						}
					}
					else if (row == 7 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[1][6] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[1][6];
						}
					}
					else if (row == 5 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[3][0] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[3][0];
						}
					}
					else if (row == 5 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[3][2] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[3][2];
						}
					}
					else if (row == 5 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[3][4] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[3][4];
						}
					}
					else if (row == 5 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[3][6] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[3][6];
						}
					}
					else if (row == 3 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[5][0] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[5][0];
						}
					}
					else if (row == 3 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[5][2] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[5][2];
						}
					}
					else if (row == 3 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[5][4] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[5][4];
						}
					}
					else if (row == 3 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[5][6] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[5][6];
						}
					}
					else if (row == 1 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[7][0] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[7][0];
						}
					}
					else if (row == 1 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[7][2] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[7][2];
						}
					}
					else if (row == 1 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[7][4] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[7][4];
						}
					}
					else if (row == 1 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[7][6] == 32)
						{
							cout << blackSquare;
						}
						else
						{
							cout << board[7][6];
						}
					}
					else
					{
						cout << blackSquare;
					}
				}

				for (int subCells = 1; subCells <= 6; subCells++)
				{
					if (row == 7 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[1][1] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[1][1];
						}
					}
					else if (row == 7 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[1][3] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[1][3];
						}
					}
					else if (row == 7 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[1][5] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[1][5];
						}
					}
					else if (row == 7 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[1][7] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[1][7];
						}
					}
					else if (row == 5 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[3][1] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[3][1];
						}
					}
					else if (row == 5 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[3][3] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[3][3];
						}
					}
					else if (row == 5 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[3][5] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[3][5];
						}
					}
					else if (row == 5 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[3][7] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[3][7];
						}
					}
					else if (row == 3 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[5][1] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[5][1];
						}
					}
					else if (row == 3 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[5][3] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[5][3];
						}
					}
					else if (row == 3 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[5][5] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[5][5];
						}
					}
					else if (row == 3 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[5][7] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[5][7];
						}
					}
					else if (row == 1 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[7][1] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[7][1];
						}
					}
					else if (row == 1 && subCells == 3 && subRow == 2 && cells == 2)
					{
						if (board[7][3] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[7][3];
						}
					}
					else if (row == 1 && subCells == 3 && subRow == 2 && cells == 3)
					{
						if (board[7][5] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[7][5];
						}
					}
					else if (row == 1 && subCells == 3 && subRow == 2 && cells == 4)
					{
						if (board[7][7] == 32)
						{
							cout << whiteSquare;
						}
						else
						{
							cout << board[7][7];
						}
					}
					else
					{
						cout << whiteSquare;
					}
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
			 const char ch = _getch();
			 int num = _getch();	 
		}
		else
		{
			cout << "Move with WASD";
			const char ch = _getch();
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


	while (true)
	{
		printMenu(true, false, false, false);
	}
}