#include <iostream>
#include <cmath>

using namespace std;

#define TableSize 8

enum PieceColor { White, Black };
enum PieceKind { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

class Piece;

struct FIELD
{
    class Piece* placed;
    class Piece* threads[18];
    short ThreadsNumber;
} **table;

class Piece
{
public:
    Piece(PieceColor c, PieceKind k, short n, short row, short column, struct FIELD** t) : color(c), kind(k), number(n), table(t) { position.row = row; position.column = column; }
    PieceKind GetKind() { return kind; }
    PieceColor GetColor() { return color; }
    short GetNumber() { return number; }
    struct POSITION
    {
        short row;
        short column;
    };
    virtual short GetImportance() = 0; // abstract
    virtual void GetPossibleMoves(struct POSITION** pos, short& n) = 0; // abstract
    virtual void MakeMove(struct POSITION pos);
protected:
    virtual bool CheckMove(struct POSITION pos);
    struct POSITION position;
    FIELD** table;
    PieceColor color;
    PieceKind kind;
    short number;
}; // Piece

class King : public Piece
{
public:
    King(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, row, column, t) { HasBeenMoved = false; }
    virtual short GetImportance() { return 32767; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
    virtual void MakeMove(struct POSITION pos);
protected:
    virtual bool CheckMove(struct POSITION pos);
private:
    bool HasBeenMoved;
}; // King

class Rook : public Piece
{
public:
    Rook(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, row, column, t) { HasBeenMoved = false; }
    virtual short GetImportance() { return 5; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
    virtual void MakeMove(struct POSITION pos);
protected:
    virtual bool CheckMove(struct POSITION pos);
private:
    bool HasBeenMoved;
}; // Rook

class Pawn : public Piece
{
public:
    Pawn(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, row, column, t) { HasBeenMoved = false; }
    virtual short GetImportance() { return 1; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
    virtual void MakeMove(struct POSITION pos);
protected:
    virtual bool CheckMove(struct POSITION pos);
private:
    bool HasBeenMoved;
}; // Pawn

class Queen : public Piece
{
public:
    Queen(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, row, column, t) { }
    virtual short GetImportance() { return 9; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
    virtual void MakeMove(struct POSITION pos);
protected:
    virtual bool CheckMove(struct POSITION pos);
}; // Queen

class Bishop : public Piece
{
public:
    Bishop(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, row, column, t) { }
    virtual short GetImportance() { return 3; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
    virtual void MakeMove(struct POSITION pos);
protected:
    virtual bool CheckMove(struct POSITION pos);
}; // Bishop

class Knight : public Piece
{
public:
    Knight(PieceColor c, PieceKind k, short n, short row, short column, FIELD** t) : Piece(c, k, n, row, column, t) { }
    virtual short GetImportance() { return 3; }
    virtual void GetPossibleMoves(struct POSITION** pos, short& n);
    virtual void MakeMove(struct POSITION pos);
protected:
    virtual bool CheckMove(struct POSITION pos);
}; // Knight

bool Piece::CheckMove(struct POSITION pos)
{
    if ((position.row == pos.row) && (position.column == pos.column))
        return false;
    if ((pos.row < 0) || (pos.row >= TableSize) || (pos.column < 0) || (pos.column >= TableSize))
        return false;
    struct FIELD field = table[pos.row][pos.column];
    if ((field.placed != NULL) && (field.placed->GetColor() == color))
        return false; // полето е заето от фигура със същия цвят
    return true;
} // Piece::CheckMove

void Piece::MakeMove(struct POSITION pos)
{
    struct POSITION* possible = NULL;
    struct FIELD* field;
    short i, j, k, n;
    if ((position.row >= 0) && (position.column >= 0))
    { // не е първоначално поставяне
        table[position.row][position.column].placed = NULL; // клетката, в която е била фигурата става празна
        GetPossibleMoves(&possible, n);
        for (i = 0; i < n; i++)
        { // обхождане на възможните ходове
            field = &(table[possible[i].row][possible[i].column]);
            for (j = 0; j < field->ThreadsNumber; j++)
            { //обхождане на заплахите за клетката
                if (field->threads[j]->GetNumber() == number)
                { // j - индекс на нашата фигура в масива със заплахите
                    // премахваме j-тия елемент
                    for (k = j; k < field->ThreadsNumber - 1; k++)
                        field->threads[k] = field->threads[k + 1];
                    field->ThreadsNumber -= 1;
                    break;
                }
            } // for j...
        } // for i...
    }
    position = pos; // текуща става зададената позиция
    table[position.row][position.column].placed = this; // клетката от таблото е заета с фигурата
    GetPossibleMoves(&possible, n); // възможните ходове (заплахите) от новата позиция
    for (i = 0; i < n; i++)
    { // обхождане на възможните ходове
        field = &(table[possible[i].row][possible[i].column]);
        // добавяне на указателя към нашата фигура към масива със заплахите
        field->threads[field->ThreadsNumber++] = this;
    } // for i...
} // Piece::MakeMove

// Figure King

void King::MakeMove(struct POSITION pos)
{
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
        if (field.threads[i]->GetColor() != color)
            return false; // полето е заплашено от фигура от другия цвят
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
    short i, row = position.row, column = position.column;
    if ((pos.row != row) && (pos.column != column))
        return false;
    if (pos.row == row)
    { // движение по реда
        if (pos.column < column)
        { // движение наляво
            for (i = column - 1; i > pos.column; i--)
                if (table[row][i].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
        else
        { // движение надясно
            for (i = column + 1; i < pos.column; i++)
                if (table[row][i].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
    } // движение по реда
    if (pos.column == column)
    { // движение по колоната
        if (pos.row < row)
        { // движение надолу
            for (i = row - 1; i > pos.row; i--)
                if (table[i][column].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
        else
        { // движение нагоре
            for (i = row + 1; i < pos.row; i++)
                if (table[i][column].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
    } // движение по колоната
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
    Piece::MakeMove(pos);
    HasBeenMoved = true;
} // Pawn::MakeMove

bool Pawn::CheckMove(struct POSITION pos)
{
    if (!Piece::CheckMove(pos))
        return false;
    short i, row = position.row, column = position.column;
    struct FIELD field = table[pos.row][pos.column];
    for (i = 0; i < field.ThreadsNumber; i++)
    {
        if (field.threads[i]->GetColor() != color)
            return false; // полето е заплашено от фигура от другия цвят
    }
    if (HasBeenMoved) {
        if (abs(column - pos.column) > 2)
            return false;
        if (column == pos.column)
            return false;
    }
    else {
        if (abs(column - pos.column) > 1)
            return false;
        if (column == pos.column)
            return false;
    }
    return true;
} // Pawn::CheckMove

void Pawn::GetPossibleMoves(struct POSITION** pos, short& n)
{
    struct POSITION positions[1];
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
    short i, row = position.row, column = position.column;
    struct FIELD field = table[pos.row][pos.column];
    for (i = 0; i < field.ThreadsNumber; i++)
    {
        if (field.threads[i]->GetColor() != color)
            return false; // полето е заплашено от фигура от другия цвят
    }

    if ((abs(row - pos.row) > 1) || (abs(column - pos.column) > 1))
        return false;

    return true;
} // Bishop::CheckMove

void Bishop::GetPossibleMoves(struct POSITION** pos, short& n)
{
    struct POSITION positions[13];
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
    if (n > 0)
    {
        *pos = new POSITION[n];
        for (i = 0; i < n; i++)
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
    short i, row = position.row, column = position.column;
    struct FIELD field = table[pos.row][pos.column];
    for (i = 0; i < field.ThreadsNumber; i++)
    {
        if (field.threads[i]->GetColor() != color)
            return false; // полето е заплашено от фигура от другия цвят
    }
    if (abs(row - pos.row) > 2)
        if (abs(column - pos.column) > 1)
            return false;
    if (abs(column - pos.column) > 2)
        if (abs(row - pos.row) > 1)
            return false;
    return true;
} // King::CheckMove

void Knight::GetPossibleMoves(struct POSITION** pos, short& n)
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
} // Knight::GetPossibleMoves

// Figure Queen

bool Queen::CheckMove(struct POSITION pos)
{
    if (!Piece::CheckMove(pos))
        return false;
    short i, row = position.row, column = position.column;
    if ((pos.row != row) && (pos.column != column))
        return false;
    if (pos.row == row)
    { // движение по реда
        if (pos.column < column)
        { // движение наляво
            for (i = column - 1; i > pos.column; i--)
                if (table[row][i].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
        else
        { // движение надясно
            for (i = column + 1; i < pos.column; i++)
                if (table[row][i].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
    } // движение по реда
    if (pos.column == column)
    { // движение по колоната
        if (pos.row < row)
        { // движение надолу
            for (i = row - 1; i > pos.row; i--)
                if (table[i][column].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
        else
        { // движение нагоре
            for (i = row + 1; i < pos.row; i++)
                if (table[i][column].placed != NULL)
                    return false; // опит да се прескочи фигура
        }
    } // движение по колоната
    return true;
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
    if (n > 0)
    {
        *pos = new POSITION[n];
        for (i = 0; i < n; i++)
            (*pos)[i] = positions[i];
    }
    else
        *pos = NULL;
} // Queen::GetPossibleMoves

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
                        cout << whiteSquare;
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

void printBoard()
{
    for (int row = 8; row >= 1; row--)
    {
        printLine(row);
    }
}

int main()
{
    short row, column;
    table = new FIELD * [TableSize];
    for (row = 0; row < TableSize; row++)
    {
        table[row] = new FIELD[TableSize];
        for (column = 0; column < TableSize; column++)
        {
            table[row][column].placed = NULL;
            table[row][column].ThreadsNumber = 0;
        }
    } // for row...

    cout << " ";
    printBoard();

    struct Piece::POSITION* possible;
    short i, n;

    possible = NULL;
 
    class Piece* WhiteFigures[16];
    WhiteFigures[0] = new class King(White, KING, 1, 4, 0, table);
    WhiteFigures[1] = new class Queen(White, QUEEN, 1, 3, 0, table);
    WhiteFigures[2] = new class Rook(White, ROOK, 2, 7, 0, table);
    WhiteFigures[3] = new class Rook(White, ROOK, 3, 0, 0, table);
    WhiteFigures[4] = new class Bishop(White, BISHOP, 4, 2, 0, table);
    WhiteFigures[5] = new class Bishop(White, BISHOP, 5, 5, 0, table);
    WhiteFigures[6] = new class Knight(White, KNIGHT, 6, 1, 0, table);
    WhiteFigures[7] = new class Knight(White, KNIGHT, 7, 6, 0, table);
    for (i = 8; i < 16; i++)
        WhiteFigures[i] = new class Pawn(White, PAWN, i, i - 8 , 1, table);

    delete possible;
    possible = NULL;
    WhiteFigures[0]->GetPossibleMoves(&possible, n);

    class Piece* BlackFigures[16];
    BlackFigures[0] = new class King(White, KING, 1, 4, 7, table);
    BlackFigures[1] = new class Queen(White, QUEEN, 1, 3, 7, table);
    BlackFigures[2] = new class Rook(White, ROOK, 2, 7, 7, table);
    BlackFigures[3] = new class Rook(White, ROOK, 3, 0, 7, table);
    BlackFigures[4] = new class Bishop(White, BISHOP, 4, 2, 7, table);
    BlackFigures[5] = new class Bishop(White, BISHOP, 5, 5, 7, table);
    BlackFigures[6] = new class Knight(White, KNIGHT, 6, 1, 7, table);
    BlackFigures[7] = new class Knight(White, KNIGHT, 7, 6, 7, table);
    for (i = 8; i < 16; i++)
        BlackFigures[i] = new class Pawn(White, PAWN, i, i - 8, 6, table);

    delete possible;
    possible = NULL;
    BlackFigures[0]->GetPossibleMoves(&possible, n);

    /*
    cout << "King: n = " << n << endl;
    for (i = 0; i < n; i++)
        cout << "row: " << possible[i].row << ", column: " << possible[i].column << endl;
    */

}