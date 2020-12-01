#include "backEnd.h"

using namespace std;

bool Piece::CheckMove(struct POSITION pos)
{
    if ((position.row == pos.row) && (position.column == pos.column))
        return false;
    if ((pos.row < 0) || (pos.row >= TableSize) || (pos.column < 0) || (pos.column >= TableSize))
        return false;
    struct FIELD field = table[pos.row][pos.column];
    if ((field.placed != NULL) && (field.placed->GetColor() == color))
        return false; // the field is occupied by a figure of the same color
    return true;
} // Piece::CheckMove

void Piece::AddThreat(struct POSITION pos)
{ // makes the corresponding fields threatened by the figure
    struct POSITION* possible = NULL;
    struct FIELD* field;
    short i, n;
    table[position.row][position.column].placed = this; // the cell on the dashboard is occupied with the figure
    GetPossibleMoves(&possible, n); // possible moves (threats) from the new position
    for (i = 0; i < n; i++)
        if ((kind != PAWN) || (possible[i].row != pos.row)) // the pawn does not threaten the field of the same order
        { // crawl the possible moves
            field = &(table[possible[i].row][possible[i].column]);
            // add the pointer to our figure to the threat array
            field->threats[field->ThreadsNumber++] = this;
            if (color == Black)
                field->ThreatsFromBlackFigures++;
            else
                field->ThreatsFromWhiteFigures++;
        } // for i...
} // Piece::AddThreat

void Piece::RemoveThreat()
{
    struct POSITION* possible = NULL;
    struct FIELD* field;
    short i, j, k, n;
    if ((position.row >= 0) && (position.column >= 0))
    { // is not an initial paste
        table[position.row][position.column].placed = NULL; // the cell in which the figure was becomes empty
        GetPossibleMoves(&possible, n);
        for (i = 0; i < n; i++)
            if ((kind != PAWN) || (possible[i].row != position.row)) // the pawn does not threaten the field of the same order
            { // crawl the possible moves
                field = &(table[possible[i].row][possible[i].column]);
                for (j = 0; j < field->ThreadsNumber; j++)
                { // crawl cell threats
                    if (field->threats[j]->GetNumber() == number)
                    { // j - index of the removed figure in the threat array
                        // remove the j-th element
                        for (k = j; k < field->ThreadsNumber - 1; k++)
                            field->threats[k] = field->threats[k + 1];
                        field->ThreadsNumber -= 1;
                        if (color == Black)
                            field->ThreatsFromBlackFigures--;
                        else
                            field->ThreatsFromWhiteFigures--;
                        break;
                    }
                } // for j...
            } // for i...
    }
} // Piece::RemoveThreat

void Piece::MakeMove(struct POSITION pos)
{ // make a move
    RemoveThreat();
    position = pos; // the set position becomes current
    AddThreat(pos);
} // Piece::MakeMove

// Figure King

void King::MakeMove(struct POSITION pos)
{
    //cout << "King::MakeMove" << endl;
    Piece::MakeMove(pos);
    HasBeenMoved = true;
} // King::MakeMove

bool King::CheckMove(struct POSITION pos)
{
    if (!Piece::CheckMove(pos))
        return false;
    short i, row = position.row, column = position.column;
    struct FIELD field = table[pos.row][pos.column];
    for (i = 0; i < field.ThreadsNumber; i++)
    {
        if (field.threats[i]->GetColor() != color)
            return false; // the field is threatened by a figure of the other color
    }
    if ((abs(row - pos.row) > 1) || (abs(column - pos.column) > 1))
        return false;
    return true;
} // King::CheckMove

void King::GetPossibleMoves(struct POSITION** pos, short& n)
{
    struct POSITION positions[8];
    struct POSITION current;
    short i;
    n = 0;
    for (current.row = position.row - 1; current.row <= position.row + 1; current.row++)
    {
        for (current.column = position.column - 1; current.column <= position.column + 1; current.column++)
        {
            if (CheckMove(current))
                positions[n++] = current;
        }
    }
    if (n > 0)
    {
        *pos = new POSITION[n];
        for (i = 0; i < n; i++)
            (*pos)[i] = positions[i];
    }
    else
        *pos = NULL;
} // King::GetPossibleMoves

bool King::IsMate()
{
    struct POSITION* possible;
    short n, tn;
    tn = GetThreatsNumber();
    if (tn == 0)
        return false;
    GetPossibleMoves(&possible, n);
    if (n > 0)
        return false;
    if (tn > 1)
        return true;
} // King::IsMate

// Figure Rook

void Rook::MakeMove(struct POSITION pos)
{
    Piece::MakeMove(pos);
    HasBeenMoved = true;
} // Rook::MakeMove

bool Rook::CheckMove(struct POSITION pos)
{
    if (!Piece::CheckMove(pos))
        return false;
    short step, row = position.row, column = position.column;

    if (row == pos.row)
    { // move in order:
        step = (pos.column > column) ? 1 : -1;
        for (column += step; table[row][column].placed == NULL; column += step)
        {
            if (column == pos.column)
                return true;
        } // for ... column
        return false; // attempt to skip a figure
    }

    if (column == pos.column)
    { // ход по колоната: 
        step = (pos.row > row) ? 1 : -1;
        for (row += step; table[row][column].placed == NULL; row += step)
        {
            if (row == pos.row)
                return true;
        } // for ... row
        return false; // attempt to skip a figure
    }

    return true;
} // Rook::CheckMove

void Rook::GetPossibleMoves(struct POSITION** pos, short& n)
{
    struct POSITION positions[14];
    struct POSITION current;
    short i;
    n = 0;
    current.row = position.row;
    for (current.column = 0; current.column < TableSize; current.column++)
    {
        if (CheckMove(current))
            positions[n++] = current;
    }
    current.column = position.column;
    for (current.row = 0; current.row < TableSize; current.row++)
    {
        if (CheckMove(current))
            positions[n++] = current;
    }
    if (n > 0)
    {
        *pos = new POSITION[n];
        for (i = 0; i < n; i++)
            (*pos)[i] = positions[i];
    }
    else
        *pos = NULL;
} // Rook::GetPossibleMoves

// Figure Pawn

void Pawn::MakeMove(struct POSITION pos)
{
    if (abs(position.column - pos.column) > 1)
        LongMoveHasBeenPerformed = true;
    if ((position.row >= 0) && (position.column >= 0))
        HasBeenMoved = true;
    Piece::MakeMove(pos);
} // Pawn::MakeMove

bool Pawn::CheckMove(struct POSITION pos)
{
    if (!Piece::CheckMove(pos))
        return false;
    class Piece* AnotherFigure;
    short i, jump, ColumnDistance, row = position.row, column = position.column;
    i = abs(row - pos.row);
    if (i > 1)
        return false;
    ColumnDistance = abs(column - pos.column);
    if (i == 1)
    { // take a figure
        if (ColumnDistance > 1)
            return false;
        AnotherFigure = table[pos.row][pos.column].placed;
        if ((AnotherFigure == NULL) || (AnotherFigure->GetColor() == color))
            return false; // the field is not occupied or there is a figure of the same color
        if (ColumnDistance == 0)
            if (AnotherFigure->GetKind() == PAWN)
            { // en passant
                class Pawn* AnotherPawn = dynamic_cast<class Pawn*>(AnotherFigure);
                if (!AnotherPawn->GetLongMoveHasBeenPerformed())
                    return false; // the other pawn did not move across the field
            }
            else
                return false; // the other figure is not a pawn
    }
    else
    { // move without taking a figure
        jump = (HasBeenMoved) ? 1 : 2; // how many columns the move can be
        if (ColumnDistance > jump)
            return false;
        if (color == White)
        {
            if (pos.column <= column)
                return false;
            for (i = column + 1; i <= pos.column; i++)
                if (table[row][i].placed != NULL)
                    return false; // there is a figure on the road
        }
        else
        { // color != White
            if (column <= pos.column)
                return false;
            for (i = column - 1; i >= pos.column; i--)
                if (table[row][i].placed != NULL)
                    return false; // there is a figure on the road
        }
    }

    return true;
} // Pawn::CheckMove

void Pawn::GetPossibleMoves(struct POSITION** pos, short& n)
{
    struct POSITION positions[6];
    struct POSITION current;
    short i, direction;
    direction = (color == White) ? 1 : -1; // direction of movement
    n = 0;
    // check the moves in the direction of travel
    current.row = position.row;
    current.column = position.column + direction;
    if (CheckMove(current))
        positions[n++] = current;
    current.column += direction;
    if (CheckMove(current))
        positions[n++] = current;
    // check the moves when taking a figure
    for (current.column = position.column + direction, current.row = position.row - 1; current.row <= position.row + 1; current.row += 2)
        if (CheckMove(current))
            positions[n++] = current;
    // check moves at en passant
    for (current.column = position.column, current.row = position.row - 1; current.row <= position.row + 1; current.row += 2)
        if (CheckMove(current))
            positions[n++] = current;
    if (n > 0)
    {
        *pos = new POSITION[n];
        for (i = 0; i < n; i++)
            (*pos)[i] = positions[i];
    }
    else
        *pos = NULL;
} // Pawn::GetPossibleMoves

// Figure Bishop

bool Bishop::CheckMove(struct POSITION pos)
{
    if (!Piece::CheckMove(pos))
        return false;
    short RowStep, ColumnStep, row = position.row, column = position.column;

    // move diagonally:
    if ((row + column == pos.row + pos.column) || (row - column == pos.row - pos.column))
    { // the field on which the figure is and the one on which the move is made are on the same diagonal
        // check if there is no figure in the fields between what the figure is on and what is being moved
        RowStep = (pos.row > row) ? 1 : -1;
        ColumnStep = (pos.column > column) ? 1 : -1;
        for (row += RowStep, column += ColumnStep; table[row][column].placed == NULL; row += RowStep, column += ColumnStep)
        {
            if (row == pos.row)
                return true;
        } // for ...
        return false; // attempt to skip a figure
    }

    return true;
} // Bishop::CheckMove

void Bishop::GetPossibleMoves(struct POSITION** pos, short& n)
{
    struct POSITION positions[13];
    struct POSITION current;
    n = 0;
    for (current.row = position.row + position.column, current.column = 0; current.row >= 0; current.row--, current.column++) // движение по левия диагонал
        if (CheckMove(current))
            positions[n++] = current;
    for (current.row = position.row - position.column, current.column = 0; (current.row < TableSize) && (current.column < TableSize); current.row++, current.column++) // движение по десния диагонал
        if (CheckMove(current))
            positions[n++] = current;
    if (n > 0)
    {
        *pos = new POSITION[n];
        for (short i = 0; i < n; i++)
            (*pos)[i] = positions[i];
    }
    else
        *pos = NULL;
} // Bishop::GetPossibleMoves

// Figure Knight

bool Knight::CheckMove(struct POSITION pos)
{
    if (!Piece::CheckMove(pos))
        return false;
    short RowDisparity = abs(position.row - pos.row);
    short ColumnDisparity = abs(position.column - pos.column);
    if (RowDisparity == ColumnDisparity)
        return false;
    if ((RowDisparity < 1) || (RowDisparity > 2) || (ColumnDisparity < 1) || (ColumnDisparity > 2))
        return false;
    return true;
} // Knight::CheckMove

void Knight::GetPossibleMoves(struct POSITION** pos, short& n)
{
    struct POSITION positions[8];
    struct POSITION current;
    short RowStep, ColumnStep;
    n = 0;
    for (RowStep = 1; RowStep <= 2; RowStep++)
    {
        ColumnStep = (RowStep == 1) ? 2 : 1;
        for (current.row = position.row - RowStep; current.row <= position.row + RowStep; current.row += (RowStep + RowStep))
            for (current.column = position.column - ColumnStep; current.column <= position.column + ColumnStep; current.column += (ColumnStep + ColumnStep))
                if (CheckMove(current))
                    positions[n++] = current;
    } // for RowStep ...
    if (n > 0)
    {
        *pos = new POSITION[n];
        for (short i = 0; i < n; i++)
            (*pos)[i] = positions[i];
    }
    else
        *pos = NULL;
} // Knight::GetPossibleMoves

// Figure Queen

bool Queen::CheckMove(struct POSITION pos)
{
    if (!Piece::CheckMove(pos))
        return false;
    short step, RowStep, ColumnStep, row = position.row, column = position.column;

    // move diagonally:
    if ((row + column == pos.row + pos.column) || (row - column == pos.row - pos.column))
    { // the field on which the figure is and the one on which the move is made are on the same diagonal
      // check if there is no figure in the fields between what the figure is on and what is being moved  
        RowStep = (pos.row > row) ? 1 : -1;
        ColumnStep = (pos.column > column) ? 1 : -1;
        for (row += RowStep, column += ColumnStep; table[row][column].placed == NULL; row += RowStep, column += ColumnStep)
        {
            if (row == pos.row)
                return true;
        } // for ...
        return false; // attempt to skip a figure
    }

    if (row == pos.row)
    { // move in a order:
        step = (pos.column > column) ? 1 : -1;
        for (column += step; table[row][column].placed == NULL; column += step)
        {
            if (column == pos.column)
                return true;
        } // for ... column
        return false; // attempt to skip a figure
    }

    if (column == pos.column)
    { // move in a column: 
        step = (pos.row > row) ? 1 : -1;
        for (row += step; table[row][column].placed == NULL; row += step)
        {
            if (row == pos.row)
                return true;
        } // for ... row
        return false; // attempt to skip a figure
    }

} // Queen::CheckMove

void Queen::GetPossibleMoves(struct POSITION** pos, short& n)
{
    struct POSITION positions[28];
    struct POSITION current;
    short i;
    n = 0;
    current.row = position.row;
    for (current.column = 0; current.column < TableSize; current.column++)
    {
        if (CheckMove(current))
            positions[n++] = current;
    }
    current.column = position.column;
    for (current.row = 0; current.row < TableSize; current.row++)
    {
        if (CheckMove(current))
            positions[n++] = current;
    }
    for (current.row = position.row + position.column, current.column = 0; current.row >= 0; current.row--, current.column++) // движение по левия диагонал
        if (CheckMove(current))
            positions[n++] = current;
    for (current.row = position.row - position.column, current.column = 0; (current.row < TableSize) && (current.column < TableSize); current.row++, current.column++) // движение по десния диагонал
        if (CheckMove(current))
            positions[n++] = current;
    if (n > 0)
    {
        *pos = new POSITION[n];
        for (i = 0; i < n; i++)
            (*pos)[i] = positions[i];
    }
    else
        *pos = NULL;
} // Queen::GetPossibleMoves