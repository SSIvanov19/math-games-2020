#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "frontEnd.h"
#include "backEnd.h"

using namespace std;

int main()
{
    //Set text to white

    short row, column;
    FIELD** table = new FIELD * [TableSize];
    for (row = 0; row < TableSize; row++)
    {
        table[row] = new FIELD[TableSize];
        for (column = 0; column < TableSize; column++)
        {
            table[row][column].placed = NULL;
            table[row][column].ThreadsNumber = 0;
            table[row][column].ThreatsFromWhiteFigures = 0;
            table[row][column].ThreatsFromBlackFigures = 0;
        }
    } // for row...



    class Piece* CurrentFigure = NULL;
    class Piece* AnotherFigure = NULL;
    struct Piece::POSITION* possible;
    struct Piece::POSITION pos;
    short i, n, choise;
    bool EndOfGame = false, ChoiseEnd = true;
    string ColorTurn = "White";

    class Piece* figures[32];
    figures[0] = new class King(White, KING, 1, 0, 7, table);
    figures[1] = new class Queen(White, QUEEN, 2, 3, 0, table);
    figures[2] = new class Rook(White, ROOK, 3, 7, 0, table);
    figures[3] = new class Rook(White, ROOK, 4, 0, 0, table);
    figures[4] = new class Bishop(White, BISHOP, 5, 2, 0, table);
    figures[5] = new class Bishop(White, BISHOP, 6, 5, 0, table);
    figures[6] = new class Knight(White, KNIGHT, 7, 1, 0, table);
    figures[7] = new class Knight(White, KNIGHT, 8, 6, 0, table);
    for (i = 8; i < 16; i++)
        figures[i] = new class Pawn(White, PAWN, i + 1, i - 8, 1, table);

    figures[16] = new class King(Black, KING, 17, 4, 7, table);
    figures[17] = new class Queen(Black, QUEEN, 18, 3, 7, table);
    figures[18] = new class Rook(Black, ROOK, 19, 7, 7, table);
    figures[19] = new class Rook(Black, ROOK, 20, 4, 0, table);
    figures[20] = new class Bishop(Black, BISHOP, 21, 2, 7, table);
    figures[21] = new class Bishop(Black, BISHOP, 22, 5, 7, table);
    figures[22] = new class Knight(Black, KNIGHT, 23, 1, 7, table);
    figures[23] = new class Knight(Black, KNIGHT, 24, 6, 7, table);
    for (i = 24; i < 32; i++)
        figures[i] = new class Pawn(Black, PAWN, i + 1, i - 24, 6, table);

    do
    {
        //print menu
        //printMenu(true, false, false, false);

        do
        {
            (ColorTurn == "White") ? cout << "White's turn" << endl : cout << "Black's turn" << endl;
            cout << "Please enter row and column, where the figure is placed:";
            
            cin >> row >> column;
            row -= 1;
            column -= 1;
            if ((row < 0) || (column < 0))
            {
                EndOfGame = true;
                break;
            }
            if (table[row][column].placed == NULL) {
                cout << "There is no figure in this field" << endl;
                continue;
            }
            CurrentFigure = table[row][column].placed;
            possible = NULL;
            CurrentFigure->GetPossibleMoves(&possible, n);
            cout << "Color Turn = " << ColorTurn << endl;
            cout << "Figure Number = " << CurrentFigure->GetNumber() << endl;
            cout << "Posible moves: " << n << endl;
            for (i = 0; i < n; i++)
                cout << "row: " << possible[i].row + 1 << ", column: " << possible[i].column + 1 << endl;
            if (n == 0) {
                cout << "This figure can't make a move" << endl;
            }
            else {
                if (ColorTurn == "White" && CurrentFigure->GetNumber() < 16) {
                    if (CurrentFigure == NULL)
                        cout << "This field is empty" << endl;
                    else
                        break;
                }
                else {
                    if (ColorTurn == "Black" && CurrentFigure->GetNumber() > 16) {
                        if (CurrentFigure == NULL)
                            cout << "This field is empty" << endl;
                        else
                            break;
                    }
                    else {
                        cout << "Take the right figure" << endl;
                        continue;
                    }
                }
            }
        } while (true);
        if (EndOfGame)
            break;
        possible = NULL;
        CurrentFigure->GetPossibleMoves(&possible, n);

        do
        {
            cout << "Please enter row and column, where the figure will be moved:";
            cin >> pos.row >> pos.column;
            pos.row -= 1;
            pos.column -= 1;
            if ((pos.row < 0) || (pos.column < 0))
            {
                EndOfGame = true;
                break;
            }
            for (i = 0; i < n; i++)
            {
                if ((possible[i].row == pos.row) && (possible[i].column == pos.column))
                    break;
            } // for i ...
            if (i >= n)
                cout << "This move is impossible" << endl;
            else
                break;
        } while (true);
        if (possible != NULL)
            delete possible;
        if (EndOfGame)
            break;
        AnotherFigure = table[pos.row][pos.column].placed;
        if (AnotherFigure != NULL)
        {
            cout << "Kill " << AnotherFigure->GetLetter() << endl;
            n = AnotherFigure->GetNumber() - 1;
            cout << n << endl;
            //delete figures[n];
            //figures[n] = NULL;
        }
        CurrentFigure->MakeMove(pos);
        pos.row = -1;
        pos.column = -1;
        short number = CurrentFigure->GetNumber();
        pos = CurrentFigure->GetPosition();
        cout << "Now the figure is on field: " << pos.row + 1 << ", " << pos.column + 1 << endl;
        if (CurrentFigure->GetNumber() >= 8 && CurrentFigure->GetNumber() < 16) {
            if (pos.column == 7) {
                cout << "What figure you want?" << endl;
                cout << "Queen-1 Rook-2 Bishop-3 Knight-4" << endl;
                cout << "Please enter number: " << endl;
                do {
                    cin >> choise;
                    switch (choise) {
                    case 1: figures[number - 1] = new class Queen(White, QUEEN, number, pos.row, 7, table); ChoiseEnd = false; break;
                    case 2: figures[number - 1] = new class Rook(White, ROOK, number, pos.row, 7, table); ChoiseEnd = false; break;
                    case 3: figures[number - 1] = new class Bishop(White, BISHOP, number, pos.row, 7, table); ChoiseEnd = false; break;
                    case 4: figures[number - 1] = new class Knight(White, KNIGHT, number, pos.row, 7, table); ChoiseEnd = false; break;
                    default: cout << "Invalid number" << endl;
                    }
                } while (ChoiseEnd);

            }
        }
        if (CurrentFigure->GetNumber() >= 16 && CurrentFigure->GetNumber() < 32) {
            if (pos.column == 0) {
                cout << "What figure you want?" << endl;
                cout << "Queen-1 Rook-2 Bishop-3 Knight-4" << endl;
                cout << "Please enter number: " << endl;
                do {
                    cin >> choise;
                    switch (choise) {
                    case 1: figures[number - 1] = new class Queen(White, QUEEN, number, pos.row, 0, table); ChoiseEnd = false; break;
                    case 2: figures[number - 1] = new class Rook(White, ROOK, number, pos.row, 0, table); ChoiseEnd = false; break;
                    case 3: figures[number - 1] = new class Bishop(White, BISHOP, number, pos.row, 0, table); ChoiseEnd = false; break;
                    case 4: figures[number - 1] = new class Knight(White, KNIGHT, number, pos.row, 0, table); ChoiseEnd = false; break;
                    default: cout << "Invalid number" << endl;
                    }
                } while (ChoiseEnd);

            }
        }
        //
        (ColorTurn == "White") ? ColorTurn = "Black" : ColorTurn = "White";
    } while (true);
}