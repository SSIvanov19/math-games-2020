#include<conio.h>
#include<cstdlib>
#include<iostream>
#include <Windows.h>
#include "frontEnd.h"
#include "backEnd.h"

using namespace std;


//Two-dimensional array that hold 
//all white figures
char whiteFig[2][8] =
{
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
};

//Two-dimensional array that hold 
//all black figures
char blackFig[2][8] =
{
	{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}
};

//Two-dimensional array that hold 
//all pieces and their places
char board[8][8] =
{
	{blackFig[0][0], blackFig[0][1], blackFig[0][2], blackFig[0][3], blackFig[0][4], blackFig[0][5], blackFig[0][6], blackFig[0][7]},
	{blackFig[1][0], blackFig[1][1], blackFig[1][2], blackFig[1][3], blackFig[1][4], blackFig[1][5], blackFig[1][6], blackFig[1][7]},
	{32, 32, 32, 32, 32, 32, 32, 32},
	{32, 32, 32, 32, 32, 32, 32, 32},
	{32, 32, 32, 32, 32, 32, 32, 32},
	{32, 32, 32, 32, 32, 32, 32, 32},
	{whiteFig[0][0], whiteFig[0][1], whiteFig[0][2], whiteFig[0][3], whiteFig[0][4], whiteFig[0][5], whiteFig[0][6], whiteFig[0][7]},
	{whiteFig[1][0], whiteFig[1][1], whiteFig[1][2], whiteFig[1][3], whiteFig[1][4], whiteFig[1][5], whiteFig[1][6], whiteFig[1][7]}
};

//Two-dimensional array that hold
//if cell is selected
bool cellsMatrix[8][8] =
{
	{false, false, false, false, false, false, false, false},
	{false, false, false, false, false, false, false, false},
	{false, false, false, false, false, false, false, false},
	{false, false, false, false, false, false, false, false},
	{false, false, false, false, false, false, false, false},
	{false, false, false, false, false, false, false, false},
	{false, false, false, false, false, false, false, false},
	{false, false, false, false, false, false, false, false},
};


//Bool to check for turns
//1 = white
//0 = black
bool turn = true;


//variable for coordination system
bool selectFirst = false;

//variable for coordination system
int saveX;

//variable for coordination system
int saveY;

//variable for coordination system
//Setting
//1 = coordinate
//0 = WASD
bool movementType = false;

//Make all element of arr
//equal false
void initCellsMatrix()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cellsMatrix[i][j] = false;
		}
	}
}

//Print one line
void printLine(int row)
{
	//variables for two types of squares
	const char whiteSquare = 0xDB;
	const char blackSquare = 0xFF;

	//moment
	//check if row is even
	if (row % 2 == 0)
	{
		for (int subRow = 1; subRow <= 3; subRow++)
		{
			for (int cells = 1; cells <= 4; cells++)
			{
				for (int subCells = 1; subCells <= 6; subCells++)
				{
					//For white squares
					//Chnage color to green, if active
					if (row == 8 && cellsMatrix[0][0] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 8 && cellsMatrix[0][2] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 8 && cellsMatrix[0][4] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 8 && cellsMatrix[0][6] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 6 && cellsMatrix[2][0] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 6 && cellsMatrix[2][2] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 6 && cellsMatrix[2][4] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 6 && cellsMatrix[2][6] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 4 && cellsMatrix[4][0] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 4 && cellsMatrix[4][2] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 4 && cellsMatrix[4][4] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 4 && cellsMatrix[4][6] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 2 && cellsMatrix[6][0] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 2 && cellsMatrix[6][2] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 2 && cellsMatrix[6][4] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 2 && cellsMatrix[6][6] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}

					//print sign, if there is
					if (row == 8 && subCells == 3 && subRow == 2 && cells == 1)
					{
						if (board[0][0] == 32)
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
					else if (row == 8 && subCells == 3 && subRow == 2 && cells == 3)
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
					else if (row == 8 && subCells == 3 && subRow == 2 && cells == 4)
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
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				}

				//For black squares
				//Chnage color to green, if active
				for (int subCells = 1; subCells <= 6; subCells++)
				{
					if (row == 8 && cellsMatrix[0][1] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 8 && cellsMatrix[0][3] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 8 && cellsMatrix[0][5] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 8 && cellsMatrix[0][7] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 6 && cellsMatrix[2][1] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 6 && cellsMatrix[2][3] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 6 && cellsMatrix[2][5] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 6 && cellsMatrix[2][7] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 4 && cellsMatrix[4][1] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 4 && cellsMatrix[4][3] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 4 && cellsMatrix[4][5] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 4 && cellsMatrix[4][7] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 2 && cellsMatrix[6][1] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 2 && cellsMatrix[6][3] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 2 && cellsMatrix[6][5] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 2 && cellsMatrix[6][7] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}

					//print sign, if there is
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
					else if (row == 6 && subCells == 3 && subRow == 2 && cells == 1)
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
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				}

			}
			if (subRow == 2)
			{
				//print line number
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
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
					//For black squares
					//Chnage color to green, if active
					if (row == 7 && cellsMatrix[1][0] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 7 && cellsMatrix[1][2] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 7 && cellsMatrix[1][4] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 7 && cellsMatrix[1][6] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 5 && cellsMatrix[3][0] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 5 && cellsMatrix[3][2] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 5 && cellsMatrix[3][4] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 5 && cellsMatrix[3][6] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 3 && cellsMatrix[5][0] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 3 && cellsMatrix[5][2] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 3 && cellsMatrix[5][4] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 3 && cellsMatrix[5][6] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 1 && cellsMatrix[7][0] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 1 && cellsMatrix[7][2] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 1 && cellsMatrix[7][4] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else if (row == 1 && cellsMatrix[7][6] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
					}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}

					//print sign if active
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
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				}

				//For white squares
				//Chnage color to green, if active
				for (int subCells = 1; subCells <= 6; subCells++)
				{
					if (row == 7 && cellsMatrix[1][1] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 7 && cellsMatrix[1][3] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 7 && cellsMatrix[1][5] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 7 && cellsMatrix[1][7] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 5 && cellsMatrix[3][1] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 5 && cellsMatrix[3][3] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 5 && cellsMatrix[3][5] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 5 && cellsMatrix[3][7] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 3 && cellsMatrix[5][1] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 3 && cellsMatrix[5][3] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 3 && cellsMatrix[5][5] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 3 && cellsMatrix[5][7] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 1 && cellsMatrix[7][1] && cells == 1)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 1 && cellsMatrix[7][3] && cells == 2)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 1 && cellsMatrix[7][5] && cells == 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else if (row == 1 && cellsMatrix[7][7] && cells == 4)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}

					//print if there is sign
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << "   " << row;
			}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << endl << " ";
		}
	}
}

//Print the board
void printBoard(bool firstGame, string error)
{
	//Clear screen
	system("CLS");

	//print the name of the game
	cout << "    ======================================" << endl;
	cout << "      ______ _    _ ______  _____ _____" << endl;
	cout << "     /  ____| |  | |  ____|/ ____/ ____|" << endl;
	cout << "     | |    | |__| | |__  | (___| (____" << endl;
	cout << R"(     | |    |  __  |  __|  \____ \\___ \)" << endl;
	cout << "     | |____| |  | | |____  ____) |___) |" << endl;
	cout << "     \\______|_|  |_|______||_____/_____/" << endl;
	cout << endl;
	cout << "    ======================================" << endl;

	//Print if there is a problem
	if (error != "noProblem")
	{
		cout << endl;
		cout << " " << error;
		cout << endl;
	}

	//Print turn
	(turn) ? cout << "\n Current turn: WHITE" << endl : cout << "\n Current turn: BLACK" << endl;
	
	cout << "\n\n   A     B     C     D     E     F     G     H\n\n ";

	//if it is first game
	//put first square to green
	if (firstGame && !movementType)
	{
		cellsMatrix[0][0] = true;
	}

	//print each line
	for (int row = 8; row >= 1; row--)
	{
		printLine(row);
	}

	//check if movement type is
	//coordinates or WASD
	if (movementType)
	{
		//Coordinates
		int x = 0;
		int y = 0;
		
		cout << "\n Type coordinate. First is the letter, second is the number. \n Pres Enter to pick up or place the figure. To exit pres ESC.\n";

		//Get coordinates
		const char ch = _getch();

		//Return to main menu
		if (ch == '\x1b')
		{
			initCellsMatrix();
			printMenu(true, false, false, false, false, false);
		}

		//make all element false and save the final coordinates 
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				if (cellsMatrix[i][j])
				{
					cellsMatrix[i][j] = false;
					x = i;
					y = j;
				}
			}
		}


		//check input
		if (ch == '\r')
		{
			//pick up piece
			if (!selectFirst)
			{
				saveX = x;
				saveY = y;
				selectFirst = true;
				cellsMatrix[x][y] = true;
				printBoard(false);
			}
			else
			{
				//check and place the two pieces 
				if (checkPos(saveX, saveY, x, y) == "noProblem")
				{
					//Remove fig from board
					if (board[x][y] != 32)
					{
						board[x][y] = 32;
					}
					
					//Swap the two fig
					swap(board[saveX][saveY], board[x][y]);


					//Make the Rockado
					if (board[x][y] == 'K' && board[x][y + 1] == 'T')
					{
						swap(board[x][y + 1], board[x][y - 1]);
					}
					else if (board[x][y] == 'k' && board[x][y + 1] == 't')
					{
						swap(board[x][y + 1], board[x][y - 1]);
					}
					else if (board[x][y] == 'K' && board[x][y - 2] == 'T')
					{
						swap(board[x][y - 2], board[x][y + 1]);
					}
					else if (board[x][y] == 'k' && board[x][y - 2] == 't')
					{
						swap(board[x][y - 2], board[x][y + 1]);
					}
					
					turn = !turn;
					selectFirst = false;
					cellsMatrix[x][y] = true;
					
					printBoard(false);
				}
				else
				{
					string error = checkPos(saveX, saveY, x, y);
					
					selectFirst = false;
					cellsMatrix[x][y] = true;
					
					printBoard(false, error);
				}
			}
		}

		//Get the second coordinate
		const int num = (int)((char)_getch() - '0');

		//From char to coordinates
		if (ch == 'A' || ch == 'a')
		{
			y = 0;
		}
		else if (ch == 'B' || ch == 'b')
		{
			y = 1;
		}
		else if (ch == 'C' || ch == 'c')
		{
			y = 2;
		}
		else if (ch == 'D' || ch == 'd')
		{
			y = 3;
		}
		else if (ch == 'E' || ch == 'e')
		{
			y = 4;
		}
		else if (ch == 'F' || ch == 'f')
		{
			y = 5;
		}
		else if (ch == 'G' || ch == 'g')
		{
			y = 6;
		}
		else if (ch == 'H' || ch == 'h')
		{
			y = 7;
		}
		else
		{
			//if input is incorrect print board
			printBoard(false, "Incorrect input");
		}

		//From numbers to coordinates
		if (num == 8)
		{
			x = 0;
		}
		else if (num == 7)
		{
			x = 1;
		}
		else if (num == 6)
		{
			x = 2;
		}
		else if (num == 5)
		{
			x = 3;
		}
		else if (num == 4)
		{
			x = 4;
		}
		else if (num == 3)
		{
			x = 5;
		}
		else if (num == 2)
		{
			x = 6;
		}
		else if (num == 1)
		{
			x = 7;
		}
		else
		{
			printBoard(false, "Incorrect input");
		}

		initCellsMatrix();

		cellsMatrix[x][y] = true;

		printBoard(false);
	}
	else
	{
		//WASD movement

		//coordinate for x
		int x = 0;

		//coordinate for y
		int y = 0;

		cout << "\n Move with WASD. Pres Enter to pick up or place the figure. To exit pres ESC.\n";

		//Get char
		const char ch = _getch();

		//Return to menu
		if (ch == '\x1b')
		{
			initCellsMatrix();
			printMenu(true, false, false, false, false, false);
		}

		//make all element false and save the final coordinates 
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				if (cellsMatrix[i][j])
				{
					cellsMatrix[i][j] = false;
					x = i;
					y = j;
				}
			}
		}

		//make sure the y and x aren't out of bounds
		if (ch == 'w')
		{
			if (x == 0)
			{
				x = 7;
			}
			else
			{
				x--;
			}
		}
		else if (ch == 's')
		{
			if (x == 7)
			{
				x = 0;
			}
			else
			{
				x++;
			}
		}
		else if (ch == 'a')
		{
			if (y == 0)
			{
				y = 7;
			}
			else
			{
				y--;
			}
		}
		else if (ch == 'd')
		{
			if (y == 7)
			{
				y = 0;
			}
			else
			{
				y++;
			}
		}
		else if (ch == '\r')
		{
			//Pick up piece
			if (!selectFirst)
			{
				saveX = x;
				saveY = y;
				selectFirst = true;
			}
			else
			{
				//Check and place piece
				if (checkPos(saveX, saveY, x, y) == "noProblem")
				{
					if (board[x][y] == 'K')
					{
						playerTwoWin();
					}

					if (board[x][y] == 'k')
					{
						playerOneWin();
					}
					
					if (board[x][y] != 32)
					{
						board[x][y] = 32;
					}

					
					//Swap the two fig
					swap(board[saveX][saveY], board[x][y]);


					//Make the Rockado
					if (board[x][y] == 'K' && board[x][y + 1] == 'R')
					{
						swap(board[x][y + 1], board[x][y - 1]);
					}
					else if (board[x][y] == 'k' && board[x][y + 1] == 'r')
					{
						swap(board[x][y + 1], board[x][y - 1]);
					}
					else if (board[x][y] == 'K' && board[x][y - 2] == 'R')
					{
						swap(board[x][y - 2], board[x][y + 1]);
					}
					else if (board[x][y] == 'k' && board[x][y - 2] == 'r')
					{
						swap(board[x][y - 2], board[x][y + 1]);
					}
					
					turn = !turn;
					selectFirst = false;
				}
				else
				{
					string error = checkPos(saveX, saveY, x, y);

					selectFirst = false;
					cellsMatrix[x][y] = true;

					printBoard(false, error);
				}
			}
		}
		else
		{
			printBoard(false);
		}

		cellsMatrix[x][y] = true;

		printBoard(false);
	}
}

void playerOneWin()
{
	//Return board to normal
	newGame();
	
	//Clear screen
	system("CLS");

	//Print the winner
	cout << "==============================================================" << endl;
	cout << "  _____  _      __     ________ _____     ____  _   _ ______ " << endl;
	cout << " |  __ \\| |   /\\\\ \\   / /  ____|  __ \\   / __ \\| \\ | |  ____|" << endl;
	cout << " | |__) | |  /  \\\\ \\_/ /| |__  | |__) | | |  | |  \\| | |__   " << endl;
	cout << " |  ___/| | / /\\ \\    / |  __| |  _  /  | |  | | . \\ |  __|  " << endl;
	cout << " | |    | |/ ____ \\| |  | |____| | \\ \\  | |__| | |\\  | |____ " << endl;
	cout << " |_|    |_/_/    \\_\\_|  |______|_|__\\_\\  \\____/|_| \\_|______|" << endl;
	cout << "                  \\ \\        / / __ \\| \\ | |                 " << endl;
	cout << "                   \\ \\  /\\  / / |  | |  \\| |                 " << endl;
	cout << "                    \\ \\/  \\/ /| |  | | . \\ |                 " << endl;
	cout << "                     \\  /\\  / | |__| | |\\  |                 " << endl;
	cout << "                      \\/  \\/   \\____/|_| \\_|                 " << endl;
	cout << "==============================================================" << endl;

	//Wait for input
	const char ch = _getch();

	if (ch == '\r' || ch == '\x1b')
	{
		printMenu(true, false, false, false, false, false);
	}
}

void playerTwoWin()
{
	//Return board to normal
	newGame();
	
	//Clear screen
	system("CLS");
	
	//Print the winner
	cout << "====================================================================" << endl;
	cout << "  _____  _      __     ________ _____    _________          ______  " << endl;
	cout << " |  __ \\| |   /\\\\ \\   / /  ____|  __ \\  |__   __\\ \\        / / __ \\ " << endl;
	cout << " | |__) | |  /  \\\\ \\_/ /| |__  | |__) |    | |   \\ \\  /\\  / / |  | |" << endl;
	cout << " |  ___/| | / /\\ \\\\   / |  __| |  _  /     | |    \\ \\/  \\/ /| |  | |" << endl;
	cout << " | |    | |/ ____ \\| |  | |____| | \\ \\     | |     \\  /\\  / | |__| |" << endl;
	cout << " |_|    |_/_/    \\_\\_|  |______|_|__\\_\\   _|_|      \\/  \\/   \\____/ " << endl;
	cout << "                  \\ \\        / / __ \\| \\ | |                        " << endl;
	cout << "                   \\ \\  /\\  / / |  | |  \\| |                        " << endl;
	cout << "                    \\ \\/  \\/ /| |  | | . \\ |                        " << endl;
	cout << "                     \\  /\\  / | |__| | |\\  |                        " << endl;
	cout << "                      \\/  \\/   \\____/|_| \\_|                        " << endl;
	cout << "====================================================================" << endl;

	//Wait for input
	const char ch = _getch();

	if (ch == '\r' || ch == '\x1b')
	{
		printMenu(true, false, false, false, false, false);
	}
}


void printAbout()
{
	//Clear screen
	system("CLS");

	//print About
	cout << "    ==========================================" << endl;
	cout << "                ____   ____  _    _ _______" << endl; 
	cout << "          /\\   |  _ \\ / __ \\| |  | |__   __|" << endl; 
	cout << "         /  \\  | |_) | |  | | |  | |  | |" << endl; 
	cout << "        / /\\ \\ |  _ <| |  | | |  | |  | |   " << endl; 
	cout << "       / ____ \\| |_) | |__| | |__| |  | |" << endl; 
	cout << "      /_/    \\_\\____/ \\____/ \\____/   |_|" << endl;
	cout << "    ==========================================" << endl;
                                       



	cout << endl;
	cout << " MathGames2020" << endl;
	cout << " A basic chess program made in vanilla C++." << endl;
	cout << endl;
	cout << " Participants:" << endl;
	cout << " Atanas Pozharliev - ABPozharliev19@codingburgas.bg - Code Checker" << endl;
	cout << " Stoyan Ivanov - SSIvanov19@codingburgas.bg - Front - End Developer" << endl;
	cout << " Stas Uzunov - SSUzunov19@codingburgas.bg - C++ Developer" << endl;
	cout << " Stefan Hristov - SHHristov19@codingburgas.bg - Scrum Trainer" << endl;
	cout << endl;
	cout << " Team VAVILON" << endl;
	cout << endl;
	cout << " -> Back" << endl;

	//Wait for input
	const char ch = _getch();

	if (ch == '\r' || ch == '\x1b')
	{
		printMenu(false, false, false, false, true, false);
	}
}


void printHowToPlay()
{
	//Clear screen
	system("CLS");

	//print How to play
	cout << "    ==================================================" << endl;
	cout << "	 _    _  ______          __  _______ ____" << endl;
	cout << "	| |  | |/ __ \\ \\        / / |__   __/ __ \\" << endl;
	cout << "	| |__| | |  | \\ \\  /\\  / /     | | | |  | |" << endl;
	cout << "	|  __  | |  | |\\ \\/  \\/ /      | | | |  | |" << endl;
	cout << "	| |  | | |__| | \\  /\\  /       | | | |__| |" << endl;
	cout << "	|_|  |_|\\____/   \\/  \\/   _    |_|  \\____/ " << endl;
	cout << "	     |  __ \\| |        /\\\\ \\   / /" << endl;
	cout << "	     | |__) | |       /  \\\\ \\_/ /" << endl;
	cout << "	     |  ___/| |      / /\\ \\\\   /" << endl;
	cout << "	     | |    | |____ / ____ \\| |" << endl;
	cout << "	     |_|    |______/_/    \\_\\_|" << endl;
	cout << "    ==================================================" << endl;

	cout << endl;
	cout << " There are two type of movement in the game. You can change them in Setting tab. By default Keyboard is selected." << endl << " This means that you go around the board by pressing w, a, s or d. You can pick or please a figure with the enter button." << endl << " The other settings is Coordinates, then you need to enter the coordinate manual. After that press enter to pick up or place the figure." << endl;
	cout << endl;
	cout << " The white figures are represented in uppercase letters, the black figures are represented in lowercase letters." << endl << " They are all represented by the first letter of their names, the only exception being the Knight," << endl << " which is represented by an N, leaving the K for the king):" << endl;
	cout << endl;
	cout << " Pawn" << endl;
	cout << " Rook" << endl;
	cout << " kNight" << endl;
	cout << " Bishop" << endl;
	cout << " Queen" << endl;
	cout << " King" << endl;
	cout << endl;
	cout << " And don't forget to have fun, while playing." << endl << endl;
	
	cout << " -> Back" << endl;
	
	//Wait for input
	const char ch = _getch();
	
	if (ch == '\r' || ch == '\x1b')
	{
		printMenu(false, false, false, true, false, false);
	}
}


//Print the menu
void printMenu(bool firstActive, bool secondActive, bool thirdActive, bool fourthActive, bool fifthActive, bool sixthActive)
{
	//Clear screen
	system("CLS");

	//print the name of the game
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

	//Check which choice is active
	cout << " "; if (firstActive)  cout << "-> ";  else cout << "   "; cout << "New Game " << endl;
	cout << endl;
	cout << " "; if (secondActive)  cout << "-> ";  else cout << "   "; cout << "Resume Game" << endl;
	cout << endl;
	cout << " "; if (thirdActive)  cout << "-> ";  else cout << "   "; cout << "Settings" << endl;
	cout << endl;
	cout << " "; if (fourthActive)  cout << "-> ";  else cout << "   "; cout << "How to play" << endl;
	cout << endl;
	cout << " "; if (fifthActive)  cout << "-> ";  else cout << "   "; cout << "About" << endl;
	cout << endl;
	cout << " "; if (sixthActive)  cout << "-> ";  else cout << "   "; cout << "Exit" << endl;

	//Get ch
	const char ch = _getch();

	//Change active choice
	if (ch == 's' || ch == 'S')
	{
		if (firstActive)
		{
			printMenu(false, true, false, false, false, false);
		}

		if (secondActive)
		{
			printMenu(false, false, true, false, false, false);
		}

		if (thirdActive)
		{
			printMenu(false, false, false, true, false, false);
		}

		if (fourthActive)
		{
			printMenu(false, false, false, false, true, false);
		}

		if (fifthActive)
		{
			printMenu(false, false, false, false, false, true);
		}

		if (sixthActive)
		{
			printMenu(true, false, false, false, false, false);
		}
	}

	//Change active choice
	if (ch == 'w' || ch == 'W')
	{
		if (firstActive)
		{
			printMenu(false, false, false, false, false, true);
		}

		if (secondActive)
		{
			printMenu(true, false, false, false, false, false);
		}

		if (thirdActive)
		{
			printMenu(false, true, false, false, false, false);
		}

		if (fourthActive)
		{
			printMenu(false, false, true, false, false, false);
		}

		if (fifthActive)
		{
			printMenu(false, false, false, true, false, false);
		}

		if (sixthActive)
		{
			printMenu(false, false, false, false, true, false);
		}
	}

	//Check for enter
	if (ch == '\r')
	{
		if (firstActive)
		{
			//New game and print board
			newGame();
			printBoard(true);
		}

		if (secondActive)
		{
			//Print board
			printBoard(true);
		}

		if (thirdActive)
		{
			//Print Settings
			printSettings(true, false);
		}

		if (fourthActive)
		{
			//Print How to Play
			printHowToPlay();
		}

		if (fifthActive)
		{
			//Print About Section
			printAbout();
		}

		if (sixthActive)
		{
			//Exit the game
			exit(3);
		}

	}
	else
	{
		printMenu(firstActive, secondActive, thirdActive, fourthActive, fifthActive, sixthActive);
	}
}

//Print the settings
void printSettings(bool firstActive, bool secondActive)
{
	//Clear screen
	system("CLS");

	//Print the settings
	cout << "    ===========================================================" << endl;
	cout << "       _____ ______ _______ _______ _____ _   _  _____  _____" << endl;
	cout << "      / ____| ____ |__   __|__   __|_   _| \\ | |/ ____|/ ____|" << endl;
	cout << "     | (___ | |__     | |     | |    | | |  \\| | |  __| (___" << endl;
	cout << R"(      \___ \|  __|    | |     | |    | | | . ` | | |_ |\___ \)" << endl;
	cout << "      ____) | |____   | |     | |   _| |_| |\\  | |__| |____) |" << endl;
	cout << "     |_____/|______|  |_|     |_|  |_____|_| \\_|\\_____|_____/" << endl;
	cout << endl;
	cout << "    ===========================================================" << endl;

	//Check which choice is active
	cout << " "; if (firstActive)  cout << "-> ";  else cout << "   "; cout << "Movement type: "; if (movementType)  cout << "Coordinates";  else cout << "Keyboard"; cout << endl;
	cout << " "; if (secondActive)  cout << "-> ";  else cout << "   "; cout << "Back" << endl;

	//Get ch
	const char ch = _getch();

	//Change active choice
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


	//Check for enter
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

			//print settings
			printSettings(true, false);
		}

		if (secondActive)
		{
			//Back to menu
			printMenu(true, false, false, false, false, false);
		}

	}
}

//Make pawn in another fig
void makePawnInFig(int x, int y, char ch)
{
	board[x][y] = ch;
}


//Return board back to start
void newGame()
{
	//Return backend to start
	initBackEnd();

	turn = 1;
	selectFirst = false;
	
	//Standard board
	char standardBoard[8][8] =
	{
		{blackFig[0][0], blackFig[0][1], blackFig[0][2], blackFig[0][3], blackFig[0][4], blackFig[0][5], blackFig[0][6], blackFig[0][7]},
		{blackFig[1][0], blackFig[1][1], blackFig[1][2], blackFig[1][3], blackFig[1][4], blackFig[1][5], blackFig[1][6], blackFig[1][7]},
		{32, 32, 32, 32, 32, 32, 32, 32},
		{32, 32, 32, 32, 32, 32, 32, 32},
		{32, 32, 32, 32, 32, 32, 32, 32},
		{32, 32, 32, 32, 32, 32, 32, 32},
		{whiteFig[0][0], whiteFig[0][1], whiteFig[0][2], whiteFig[0][3], whiteFig[0][4], whiteFig[0][5], whiteFig[0][6], whiteFig[0][7]},
		{whiteFig[1][0], whiteFig[1][1], whiteFig[1][2], whiteFig[1][3], whiteFig[1][4], whiteFig[1][5], whiteFig[1][6], whiteFig[1][7]}
	};

	//Make active board same as standard
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = standardBoard[i][j];
		}
	}
}